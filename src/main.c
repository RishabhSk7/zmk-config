/*
 * Scuba Cat OLED animation for a Corne left half / nice!nano v2.
 * The left half is normally the ZMK central half.
 */
#include <lvgl.h>
#include <zmk/display/status_screen.h>
#include "scuba_cat.h"

lv_obj_t *zmk_display_status_screen(void) {
    lv_obj_t *screen = lv_obj_create(NULL);

    /* No border/padding/background is needed; the OLED is 128x32. */
    lv_obj_set_style_pad_all(screen, 0, LV_PART_MAIN);
    lv_obj_set_style_border_width(screen, 0, LV_PART_MAIN);
    lv_obj_set_style_bg_opa(screen, LV_OPA_TRANSP, LV_PART_MAIN);
    lv_obj_clear_flag(screen, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_t *anim = lv_animimg_create(screen);
    lv_obj_set_size(anim, 128, 32);
    lv_obj_center(anim);

    lv_animimg_set_src(anim,
                       (const void **)scuba_cat_frames,
                       (uint8_t)scuba_cat_frame_count);

    /* Original video: 56 frames @ 25 FPS = 2240 ms per loop. */
    lv_animimg_set_duration(anim, 2240);
    lv_animimg_set_repeat_count(anim, LV_ANIM_REPEAT_INFINITE);
    lv_animimg_start(anim);

    return screen;
}
