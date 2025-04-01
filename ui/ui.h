/*
 * ui.h
 *
 *  Created on: Mar 30, 2025
 *      Author: Matth
 */

#ifndef UI_H_
#define UI_H_

#include "lvgl.h"
#include "lib_pid.h"
#include "lvgl_port_display.h"
#include "ke_config.h"

lv_obj_t * add_gauge( GAUGE_THEME theme, int32_t x, int32_t y, lv_obj_t * parent, PID_DATA * pid );

#endif /* UI_H_ */
