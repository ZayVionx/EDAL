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

#ifndef __DRIVER_I2C_H__
#define __DRIVER_I2C_H__

/*============================ INCLUDES ======================================*/
#include "../../EDAL_Common.h"

#ifdef   __cplusplus
extern "C" {
#endif
/*============================ MACROS ========================================*/
#define EDAL_I2C_API_VERSION    EDAL_VERSION_MAJOR_MINOR(0, 0)  /* API version */


#define _EDAL_Driver_I2C_(n)          Driver_I2C##n
#define  EDAL_Driver_I2C_(n)    _EDAL_Driver_I2C_(n)

/*============================ TYPES =========================================*/

/**
 * \brief Access structure of the I2C Driver.
 */
typedef struct _EDAL_DRIVER_I2C {
    EDAL_VERSION        (*GetVersion)   (void);
    int32_t             (*Initialize)   (void);
    int32_t             (*Uninitialize) (void);
    int32_t             (*PowerControl) (EDAL_POWER_STATE state);
    
} const EDAL_DRIVER_I2C;

/*============================ END ===========================================*/
#ifdef   __cplusplus
}
#endif
#endif /* __DRIVER_I2C_H__ */
