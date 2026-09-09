# Scuba Cat — fresh ZMK implementation

Target: Corne LEFT / nice!nano v2 / 128x32 SSD1306 OLED.

## Design

* Keeps `nice_oled` in `build.yaml` because it supplies the SSD1306/I2C display configuration.
* Disables only `NICE_OLED_WIDGET_STATUS` on the left. That prevents the old module from compiling its own `zmk_display_status_screen()` implementation.
* Uses a custom ZMK status screen on the left.
* Uses LVGL `lv_image`, but **not** `lv_animimg` and **not** `LV_COLOR_FORMAT_I1`.
* Each frame is LVGL `LV_COLOR_FORMAT_A1` (alpha-only), 128x32, 512 bytes.
* A normal `lv_timer` changes the image source every 100 ms (10 FPS).
* Display work runs on ZMK's dedicated display queue with priority 10 so it does not compete with BLE at the default priority.

ZMK's current display configuration supports a custom status screen and a dedicated display work queue; the current upstream Kconfig defaults the dedicated display thread to priority 5, while BLE also defaults to 5. A current upstream issue reports animated I2C displays causing HID stalls at that setting, and reports priority 10 as the workaround.

## Do not remove `nice_oled` yet

The `nice_oled` shield supplies `CONFIG_I2C=y` and `CONFIG_SSD1306=y` as part of its `nice_oled.conf`. Keep `nice_oled` in the build until the physical OLED node is moved into your own shield. We are only disabling its widget/status code on the left.

## Replace/add

1. Delete the old `src/main.c`.
2. Add `src/scuba_cat.c`, `src/scuba_cat_frames.c`, and `include/scuba_cat.h` from this package.
3. Replace your module `CMakeLists.txt` with the one in this package.
4. Replace `boards/shields/corneroe/corneroe_left.conf` with the one in this package.
5. Leave `boards/shields/corneroe/corneroe_right.conf` alone if it is empty; the packaged file is just a comment.
6. Use the packaged `build.yaml`, which intentionally retains `nice_oled`.
7. Keep your existing `config/corneroe.conf` settings (RGB, encoder, Studio, pointing, battery proxy, etc.). Only make sure it contains the common display lines:

```ini
CONFIG_ZMK_DISPLAY=y
CONFIG_ZMK_DISPLAY_BLANK_ON_IDLE=n
CONFIG_ZMK_DISPLAY_STATUS_SCREEN_CUSTOM=y
```

Do **not** add `CONFIG_LV_USE_ANIMIMG=y`. This implementation intentionally does not use `lv_animimg`.

## Build

Commit and push normally. GitHub Actions should produce `corneroe_left_with_studio.uf2`. Flash only the left half for this test.

## Expected behavior

The left OLED should show the dancing cat, looping at 10 FPS. Keyboard/BLE should remain responsive.

If the static image is perfect but the animation still causes stalls, reduce `SCUBA_CAT_FRAME_MS` in `include/scuba_cat.h` from 100 to 150 or 200.
