/*
 * Scuba Cat — custom left/central Corne OLED screen.
 *
 * Hardware: nice!nano v2 + 128x32 SSD1306 (via nice_oled shield)
 *
 * We deliberately do NOT use lv_animimg or LV_COLOR_FORMAT_I1.
 * Each frame is an LVGL A1 (alpha-only) image. A small LVGL timer swaps
 * the image source every 100 ms. This keeps the implementation simple and
 * avoids the I1 image/palette path that caused the previous garbage output.
 */

#include <lvgl.h>
#include <zmk/display/status_screen.h>

#include "scuba_cat.h"

struct scuba_cat_state {
    lv_obj_t *image;
    lv_timer_t *timer;
    uint8_t frame;
};

static void scuba_cat_timer_cb(lv_timer_t *timer)
{
    struct scuba_cat_state *state = lv_timer_get_user_data(timer);

    if (state == NULL || state->image == NULL) {
        return;
    }

    state->frame++;
    if (state->frame >= SCUBA_CAT_FRAME_COUNT) {
        state->frame = 0;
    }

    lv_image_set_src(state->image, &scuba_cat_frames[state->frame]);
}

static void scuba_cat_screen_delete_cb(lv_event_t *event)
{
    struct scuba_cat_state *state = lv_event_get_user_data(event);

    if (state != NULL && state->timer != NULL) {
        lv_timer_delete(state->timer);
        state->timer = NULL;
    }

    if (state != NULL) {
        state->image = NULL;
    }
}

lv_obj_t *zmk_display_status_screen(void)
{
    /* The ZMK status screen is a single instance in normal operation. */
    static struct scuba_cat_state state;

    state.image = NULL;
    state.timer = NULL;
    state.frame = 0;

    lv_obj_t *screen = lv_obj_create(NULL);
    lv_obj_remove_style_all(screen);
    lv_obj_clear_flag(screen, LV_OBJ_FLAG_SCROLLABLE);

    /* Explicitly paint the full 128x32 background black so transparent A1
     * pixels clear the previous frame instead of leaving trails. */
    lv_obj_set_style_bg_color(screen, lv_color_black(), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(screen, LV_OPA_COVER, LV_PART_MAIN);

    lv_obj_t *image = lv_image_create(screen);
    state.image = image;

    lv_obj_set_size(image, SCUBA_CAT_WIDTH, SCUBA_CAT_HEIGHT);
    lv_obj_set_pos(image, 0, 0);

    /* A1 is alpha-only, so the visible pixels take this image color. */
    lv_obj_set_style_image_recolor(image, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_image_recolor_opa(image, LV_OPA_COVER, LV_PART_MAIN);

    lv_image_set_src(image, &scuba_cat_frames[0]);

    state.timer = lv_timer_create(
        scuba_cat_timer_cb,
        SCUBA_CAT_FRAME_MS,
        &state
    );

    lv_obj_add_event_cb(
        screen,
        scuba_cat_screen_delete_cb,
        LV_EVENT_DELETE,
        &state
    );

    return screen;
}
