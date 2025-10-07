/*
 * alert.c
 *
 *  Created on: May 12, 2025
 *      Author: Matth
 */

#include "ui.h"

lv_obj_t * ui_system_message_container = NULL;
lv_obj_t * ui_system_message = NULL;

lv_obj_t * add_system_message(lv_obj_t * parent) {
    ui_system_message_container = lv_obj_create(parent);
    lv_obj_remove_style_all(ui_system_message_container);
    lv_obj_set_width(ui_system_message_container, 670);
    lv_obj_set_height(ui_system_message_container, 75);
    lv_obj_set_x(ui_system_message_container, X_OFFSET);
    lv_obj_set_y(ui_system_message_container, 5);
    lv_obj_set_align(ui_system_message_container, LV_ALIGN_TOP_MID);

    lv_obj_remove_flag(ui_system_message_container,
                       LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE |
                       LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE |
                       LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN);

    lv_obj_set_style_radius(ui_system_message_container, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_system_message_container, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_system_message_container, LV_OPA_COVER, LV_PART_MAIN | LV_STATE_DEFAULT);  // fully opaque
    lv_obj_set_style_border_color(ui_system_message_container, lv_color_hex(0xFFFF00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_system_message_container, LV_OPA_COVER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_system_message_container, 3, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Remove all shadow styles by setting them to 0 or default
    lv_obj_set_style_shadow_width(ui_system_message_container, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_system_message_container, LV_OPA_TRANSP, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui_system_message_container, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_offset_x(ui_system_message_container, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_offset_y(ui_system_message_container, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_system_message = lv_label_create(ui_system_message_container);
    lv_obj_set_width(ui_system_message, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_system_message, LV_SIZE_CONTENT);
    lv_obj_set_align(ui_system_message, LV_ALIGN_CENTER);
    lv_label_set_text(ui_system_message, "No message set");
    lv_obj_set_style_text_font(ui_system_message, &lv_font_montserrat_30, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_flag(ui_system_message_container, LV_OBJ_FLAG_HIDDEN);
    return ui_system_message_container;
}

bool get_system_message(void)
{
	return lv_obj_has_flag(ui_system_message_container, LV_OBJ_FLAG_HIDDEN);
}

void set_system_message(char *msg)
{
    lv_label_set_text(ui_system_message, msg);
    lv_obj_clear_flag(ui_system_message_container, LV_OBJ_FLAG_HIDDEN);

    // Allow label size to update
    lv_obj_update_layout(ui_system_message);  // force layout update so size is valid

    int label_width = lv_obj_get_width(ui_system_message);
    int padding = 60;  // padding for left/right sides

    // Set container width based on label width plus padding, min 200, max 670
    int new_width = label_width + padding;
    if (new_width < 300) new_width = 300;
    if (new_width > UI_HOR_RES - X_PADDING) new_width = UI_HOR_RES - X_PADDING;

    lv_obj_set_width(ui_system_message_container, new_width);

    lv_obj_remove_flag(ui_system_message_container, LV_OBJ_FLAG_HIDDEN);
}

void clear_system_message(void)
{
	lv_label_set_text(ui_system_message, "No error set");
	lv_obj_add_flag(ui_system_message_container, LV_OBJ_FLAG_HIDDEN);
}
