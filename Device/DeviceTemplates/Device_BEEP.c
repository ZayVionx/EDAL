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

/*============================ INCLUDES ======================================*/
#include "../Include/Device_BEEP.h"

/*============================ MACROS ========================================*/
#define EDAL_BEEP_DRV_VERSION    EDAL_VERSION_MAJOR_MINOR(0, 0) /* driver version */

/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/
/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/* Device Version */
static const EDAL_VERSION DeviceVersion = {
    EDAL_BEEP_API_VERSION,
    EDAL_BEEP_DRV_VERSION
};



/*============================ IMPLEMENTATION ================================*/
static EDAL_VERSION EDAL_BEEP_GetVersion(void)
{
    return DeviceVersion;
}

static int32_t EDAL_BEEP_Initialize(void)
{
}

static int32_t EDAL_BEEP_Uninitialize(void)
{
}

/*============================ PROTOTYPES ====================================*/
extern EDAL_DEVICE_BEEP EDAL_Device_BEEP_(0);
EDAL_DEVICE_BEEP EDAL_Device_BEEP_(0) = {
    EDAL_BEEP_GetVersion,
    EDAL_BEEP_Initialize,
    EDAL_BEEP_Uninitialize,

};

/*============================ END ===========================================*/
