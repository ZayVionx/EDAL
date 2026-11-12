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
#include "Driver_SPI.h"

/*============================ MACROS ========================================*/
#define EDAL_SPI_DRV_VERSION    EDAL_DRIVER_VERSION_MAJOR_MINOR(0,0)    /* driver version */

/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/
/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/* Driver Version */
static const EDAL_DRIVER_VERSION DriverVersion = {
    EDAL_SPI_API_VERSION,
    EDAL_SPI_DRV_VERSION
};


/*============================ IMPLEMENTATION ================================*/
static EDAL_DRIVER_VERSION EDAL_SPI_GetVersion(void)
{
    return DriverVersion;
}

static int32_t EDAL_SPI_Initialize(void)
{
}

static int32_t EDAL_SPI_Uninitialize(void)
{
}

static int32_t EDAL_SPI_PowerControl(EDAL_POWER_STATE state)
{
    switch(state)
    {
        case EDAL_POWER_FULL:
            break;

        case EDAL_POWER_LOW:
            break;

        case EDAL_POWER_OFF:
            break;
    }
    return EDAL_DRIVER_OK;
}

/*============================ PROTOTYPES ====================================*/
extern EDAL_DRIVER_SPI EDAL_Driver_SPI_(0);
EDAL_DRIVER_SPI EDAL_Driver_SPI_(0) = {
    EDAL_SPI_GetVersion,
    EDAL_SPI_Initialize,
    EDAL_SPI_Uninitialize,
    EDAL_SPI_PowerControl,

};

/*============================ END ===========================================*/
