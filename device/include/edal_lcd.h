#ifndef __EDAL_LCD_H__
#define __EDAL_LCD_H__

/*============================ INCLUDES ======================================*/
#include <stdint.h>
#include "../edal_types.h"

#ifdef   __cplusplus
extern "C" {
#endif
/*============================ MACROS ========================================*/
/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/
/**
 * @brief LCD driver operations shared by multiple instances.
 */
typedef struct {
    EDAL_Status_t (*Init      )(void *context);
    EDAL_Status_t (*DeInit    )(void *context);

    EDAL_Status_t (*DisplayOn )(void *context);
    EDAL_Status_t (*DisplayOff)(void *context);
    EDAL_Status_t (*SetDirection)(void *context, uint8_t direction);
    EDAL_Status_t (*SetBacklight)(void *context, uint8_t brightness);
    EDAL_Status_t (*DisplayClear)(void *context, void *color);
    EDAL_Status_t (*DisplayDraw )(void *context, uint16_t x_start, 
                                                uint16_t y_start, 
                                                uint16_t x_end, 
                                                uint16_t y_end,
                                                void *color);
} LCD_DrvType_t;

/**
 * @brief LCD device instance.
 * @note context holds hardware configuration and private data for this instance.
 *       state is managed by LCD_Init and LCD_DeInit.
 */
typedef struct {
    uint16_t Id;
    uint16_t Width;
    uint16_t Height;
    LCD_DrvType_t *drv;
    EDAL_DeviceState_t state;
    void *context;
} LCD_DeviceInfo;

/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/
EDAL_Status_t LCD_Init      (LCD_DeviceInfo *device);
EDAL_Status_t LCD_DeInit    (LCD_DeviceInfo *device);

EDAL_Status_t LCD_DisplayOn (LCD_DeviceInfo *device);
EDAL_Status_t LCD_DisplayOff(LCD_DeviceInfo *device);
EDAL_Status_t LCD_SetDirection(LCD_DeviceInfo *device, uint8_t direction);
EDAL_Status_t LCD_SetBacklight(LCD_DeviceInfo *device, uint8_t brightness);
EDAL_Status_t LCD_DisplayClear(LCD_DeviceInfo *device, void *color);
EDAL_Status_t LCD_DisplayDraw (LCD_DeviceInfo *device, uint16_t x_start,
                                                      uint16_t y_start, 
                                                      uint16_t x_end, 
                                                      uint16_t y_end,
                                                      void *color);

/*============================ IMPLEMENTATION ================================*/
/*============================ END ===========================================*/
#ifdef   __cplusplus
}
#endif
#endif /* __EDAL_LCD_H__ */
