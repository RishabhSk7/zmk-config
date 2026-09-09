#include <lvgl.h>
#include <zmk/display/status_screen.h>

lv_obj_t *zmk_display_status_screen(void)
{
    lv_obj_t *screen = lv_obj_create(NULL);

    lv_obj_remove_style_all(screen);
    lv_obj_set_size(screen, 128, 32);
    lv_obj_set_style_bg_color(screen, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(screen, LV_OPA_COVER, LV_PART_MAIN);

    return screen;
}
