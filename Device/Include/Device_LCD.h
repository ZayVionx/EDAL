/****************************************************************************
*  Copyright 2026 ZJY <Email:zhujinyuan818@gmail.com>                       *
*                                                                           *
*  Licensed under the Apache License, Version 2.0 (the "License");          *
*  you may not use this file except in compliance with the License.         *
*  You may obtain a copy of the License at                                  *
*                                                                           *
*     http://www.apache.org/licenses/LICENSE-2.0                            *
*                                                                           *
*
*  Unless required by applicable law or agreed to in writing, software      *
*  distributed under the License is distributed on an "AS IS" BASIS,        *
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. *
*  See the License for the specific language governing permissions and      *
*  limitations under the License.                                           *
*                                                                           *
****************************************************************************/

#ifndef __DEVICE_LCD_H__
#define __DEVICE_LCD_H__

/*============================ INCLUDES ======================================*/
#include "EDAL_Common.h"

#ifdef   __cplusplus
extern "C" {
#endif
/*============================ MACROS ========================================*/
#define EDAL_LCD_API_VERSION    EDAL_VERSION_MAJOR_MINOR(0, 0)  /* API version */

#define _EDAL_Device_LCD_(n)          Device_LCD##n
#define  EDAL_Device_LCD_(n)    _EDAL_Device_LCD_(n)

/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/

/**
 * \brief LCD Status
 */
typedef struct _EDAL_LCD_STATUS {
    uint32_t busy     : 1;          //!< 
    uint32_t reserved : 31;         //!< 
} EDAL_LCD_STATUS;

typedef void (*EDAL_LCD_SignalEvent_t) (uint32_t event);


/**
 * \brief LCD Device Capabilities. 
 */
typedef struct _EDAL_LCD_CAPABILITIES {
    uint32_t reserved    : 32;      //!< Reserved (must be zero)
} EDAL_LCD_CAPABILITIES;


/**
 * \brief Access structure of the LCD Device.
 */
typedef struct _EDAL_DEVICE_LCD {
    EDAL_VERSION            (*GetVersion)       (void);
    EDAL_LCD_CAPABILITIES   (*GetCapabilities)  (void);
    int32_t                 (*Initialize)       (EDAL_LCD_SignalEvent_t cb_event);
    int32_t                 (*Uninitialize)     (void);
    int32_t                 (*PowerControl)     (EDAL_POWER_STATE state);
    int32_t                 (*Control)          (uint32_t control, uint32_t arg);
    EDAL_LCD_STATUS         (*GetStatus)        (void);
} const EDAL_DEVICE_LCD;

/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/
/*============================ IMPLEMENTATION ================================*/
/*============================ END ===========================================*/
#ifdef   __cplusplus
}
#endif
#endif /* __DEVICE_LCD_H__ */
