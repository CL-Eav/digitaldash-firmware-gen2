/*
 * linear.c
 *
 *  Created on: Apr 2, 2025
 *      Author: Matth
 */


#include "themes.h"
#include "lib_pid.h"

#if UI_HOR_RES == 800
#define BAR_WIDTH 600
#define BAR_HEIGHT 50
#define BAR_LABEL_Y 30
#define BAR_FONT &lv_font_montserrat_22
#elif UI_HOR_RES == 1024
#define BAR_WIDTH 680
#define BAR_HEIGHT 64
#define BAR_LABEL_Y 40
#define BAR_FONT &lv_font_montserrat_24
#endif

static void event_cb(lv_event_t * e)
{
	// Get the PID data
	PID_DATA * data = (PID_DATA *)lv_event_get_param(e);
	lv_obj_t * gauge = lv_event_get_target(e);
    lv_obj_t * needle = lv_obj_get_child(gauge, 1);
    lv_obj_t * value = lv_obj_get_child(gauge, 2);
    lv_obj_t * min = lv_obj_get_child(gauge, 3);
    lv_obj_t * max = lv_obj_get_child(gauge, 4);

    int32_t pid_value = data->pid_value;

    // Check if the value needs to be refreshed
    //if( lv_bar_get_value(needle) == (int32_t)data->pid_value )
    //	return;

    lv_bar_set_value(needle, pid_value, LV_ANIM_OFF);

    // Update the numbers
    switch( data->precision )
    {
		case 2:
			lv_label_set_text_fmt(value, "%.2f%s", data->pid_value, data->unit_label);
			lv_label_set_text_fmt(min, "%.2f", data->pid_min);
			lv_label_set_text_fmt(max, "%.2f", data->pid_max);
			break;

		case 1:
			lv_label_set_text_fmt(value, "%.1f%s", data->pid_value, data->unit_label);
			lv_label_set_text_fmt(min, "%.1f", data->pid_min);
			lv_label_set_text_fmt(max, "%.1f", data->pid_max);
			break;

		case 0:
		default:
			lv_label_set_text_fmt(value, "%.0f%s", data->pid_value, data->unit_label);
			lv_label_set_text_fmt(min, "%.0f", data->pid_min);
			lv_label_set_text_fmt(max, "%.0f", data->pid_max);
			break;
    }
}

lv_obj_t * add_linear_gauge( int32_t x, int32_t y, lv_obj_t * parent, PID_DATA * pid)
{
	lv_obj_t * gauge = lv_obj_create(parent);
    lv_obj_remove_style_all(gauge);
    lv_obj_set_width(gauge, UI_HOR_RES);
    lv_obj_set_height(gauge, 110);
    lv_obj_set_align(gauge, LV_ALIGN_TOP_MID);
    lv_obj_remove_flag(gauge, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_user_data(gauge, pid);
    lv_obj_add_event_cb(gauge, event_cb, LV_EVENT_REFRESH, pid);

    lv_obj_t * pid_label = lv_label_create(gauge);
    lv_obj_set_width(pid_label, 200);
    lv_obj_set_height(pid_label, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(pid_label, 110);
    lv_obj_set_y(pid_label, BAR_LABEL_Y);
    lv_obj_set_align(pid_label, LV_ALIGN_CENTER);
    lv_label_set_text(pid_label, pid->label);
    lv_obj_set_style_text_font(pid_label, BAR_FONT, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t * needle = lv_bar_create(gauge);
    lv_bar_set_range(needle, pid->lower_limit, pid->upper_limit);
    lv_obj_set_width(needle, BAR_WIDTH);
    lv_obj_set_height(needle, BAR_HEIGHT);
    lv_obj_set_x(needle, 0);
    lv_obj_set_y(needle, 10);
    lv_obj_set_align(needle, LV_ALIGN_TOP_MID);
    lv_obj_set_style_radius(needle, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(needle, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(needle, 125, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(needle, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(needle, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(needle, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    //Compensating for LVGL9.1 draw crash with bar/slider max value when top-padding is nonzero and right-padding is 0
    if(lv_obj_get_style_pad_top(needle, LV_PART_MAIN) > 0) lv_obj_set_style_pad_right(needle, lv_obj_get_style_pad_right(needle, LV_PART_MAIN) + 1, LV_PART_MAIN);

    lv_obj_t * value = lv_label_create(gauge);
    lv_obj_set_width(value, 200);
    lv_obj_set_height(value, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(value, -110);
    lv_obj_set_y(value, BAR_LABEL_Y);
    lv_obj_set_align(value, LV_ALIGN_CENTER);
    lv_label_set_text(value, "value");
    lv_obj_set_style_text_align(value, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(value, BAR_FONT, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t * min = lv_label_create(gauge);
    lv_obj_set_width(min, 90);
    lv_obj_set_height(min, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(min, -1 * (BAR_WIDTH/2));
    lv_obj_set_y(min, BAR_LABEL_Y);
    lv_obj_set_align(min, LV_ALIGN_CENTER);
    lv_label_set_text(min, "min");
    lv_obj_set_style_text_color(min, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(min, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(min, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(min, BAR_FONT, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t * max = lv_label_create(gauge);
    lv_obj_set_width(max, 90);
    lv_obj_set_height(max, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(max, BAR_WIDTH/2);
    lv_obj_set_y(max, BAR_LABEL_Y);
    lv_obj_set_align(max, LV_ALIGN_CENTER);
    lv_label_set_text(max, "max");
    lv_obj_set_style_text_color(max, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(max, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(max, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(max, BAR_FONT, LV_PART_MAIN | LV_STATE_DEFAULT);

    return gauge;
}
