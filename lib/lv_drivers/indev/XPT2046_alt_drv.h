/**
 * @file XPT2046_alt_drv.h
 *
 */

#ifndef XPT2046_ALT_DRV_H
#define XPT2046_ALT_DRV_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#ifndef LV_DRV_NO_CONF
#ifdef LV_CONF_INCLUDE_SIMPLE
#include "lv_drv_conf.h"
#else
#include "../../lv_drv_conf.h"
#endif
#endif

#if USE_XPT2046_ALT_DRV

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/
void xpt2046_alt_drv_init(uint8_t rotation);
bool xpt2046_alt_drv_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data);

/**********************
 *      MACROS
 **********************/

#endif /* USE_XPT2046_ALT_DRV */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* XPT2046_ALT_DRV_H */