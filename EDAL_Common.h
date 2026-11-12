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

#ifndef __EDAL_COMMON_H__
#define __EDAL_COMMON_H__

/*============================ INCLUDES ======================================*/
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef   __cplusplus
extern "C" {
#endif
/*============================ MACROS ========================================*/
#define EDAL_VERSION_MAJOR_MINOR(major, minor)   (((major) << 8) | (minor))

/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/
/**
 * \brief Device Version
 */
typedef struct _EDAL_VERSION {
    uint16_t api;
    uint16_t drv;
} EDAL_VERSION;

/**
 * \brief General power status
 */
typedef enum _EDAL_POWER_STATE {
    EDAL_POWER_OFF,                         //!< Power off: no operation possible
    EDAL_POWER_LOW,                         //!< Low Power mode: retain state, detect and signal wake-up events
    EDAL_POWER_FULL                         //!< Power on: full operation at maximum performance
} EDAL_POWER_STATE;


/* General driver return codex */
#define EDAL_DRIVER_OK                   0  //!< Operation succeeded
#define EDAL_DRIVER_ERROR               -1  //!< Unspecified error
#define EDAL_DRIVER_ERROR_BUSY          -2  //!< Driver is busy
#define EDAL_DRIVER_ERROR_TIMEOUT       -3  //!< Timeout occurred
#define EDAL_DRIVER_ERROR_UNSUPPORTED   -4  //!< Operation not supported
#define EDAL_DRIVER_ERROR_PARAMETER     -5  //!< Parameter error
#define EDAL_DRIVER_ERROR_SPECIFIC      -6  //!< Start of driver specific errors

/* General device return codex */
#define EDAL_DEVICE_OK                   0  //!< Operation succeeded
#define EDAL_DEVICE_ERROR               -1  //!< Unspecified error
#define EDAL_DEVICE_ERROR_BUSY          -2  //!< Driver is busy
#define EDAL_DEVICE_ERROR_TIMEOUT       -3  //!< Timeout occurred
#define EDAL_DEVICE_ERROR_UNSUPPORTED   -4  //!< Operation not supported
#define EDAL_DEVICE_ERROR_PARAMETER     -5  //!< Parameter error
#define EDAL_DEVICE_ERROR_SPECIFIC      -6  //!< Start of driver specific errors

/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/
/*============================ IMPLEMENTATION ================================*/
/*============================ END ===========================================*/
#ifdef   __cplusplus
}
#endif
#endif /* __EDAL_COMMON_H__ */
