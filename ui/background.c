/*
 * background.c
 *
 *  Created on: Mar 30, 2025
 *      Author: Matth
 */

#include "ui.h"

static const __attribute__((section(".ExtFlash_Section"))) __attribute__((used)) uint8_t backgrounds_external[1][UI_HOR_RES*UI_VER_RES*3];

void load_background( lv_obj_t * view, VIEW_BACKGROUND background )
{
	  uint8_t is_image = 0;
	  const lv_image_dsc_t * img = NULL;
	  lv_color_t color = {0};

	  lv_image_dsc_t ext_background = {
	    .header.cf = LV_COLOR_FORMAT_RGB888,
	    .header.magic = LV_IMAGE_HEADER_MAGIC,
	    .header.w = UI_HOR_RES,
	    .header.h = UI_VER_RES,
	    .data_size = sizeof(backgrounds_external[0]),
	    .data = backgrounds_external[0],
	  };

	  switch( background )
	  {
		  case VIEW_BACKGROUND_FLARE:
			  //img = &ui_img_flare_png;
			  is_image = 1;
			  break;

		  case VIEW_BACKGROUND_USER1:
			  img = &ext_background;
			  is_image = 1;
			  break;

		  case VIEW_BACKGROUND_BLACK:
		  default:
			  color.red = 255;
			  color.green = 255;
			  color.blue = 0;
			  is_image = 0;
			  break;
	  }

	  if( is_image )
		  lv_obj_set_style_bg_image_src(view, img, LV_PART_MAIN | LV_STATE_DEFAULT);
	  else
		  lv_obj_set_style_bg_color(view, color, LV_PART_MAIN | LV_STATE_DEFAULT);
}
