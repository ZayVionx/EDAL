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
#include "Driver_I2C.h"

/*============================ MACROS ========================================*/
#define EDAL_I2C_DRV_VERSION    EDAL_VERSION_MAJOR_MINOR(1, 0)  /* driver version */

/*============================ LOCAL VARIABLES ===============================*/
/* Driver Version */
static const EDAL_VERSION DriverVersion = {
    EDAL_I2C_API_VERSION,
    EDAL_I2C_DRV_VERSION
};

/* Driver Capabilities */
static const EDAL_I2C_CAPABILITIES DriverCapabilities = {
    0,  /* supports 10-bit addressing */
    0   /* Reserved (must be zero) */
};

/*============================ IMPLEMENTATION ================================*/
static EDAL_VERSION EDAL_I2C_GetVersion(void)
{
    return DriverVersion;
}

static EDAL_I2C_CAPABILITIES EDAL_I2C_GetCapabilities(void)
{
    return DriverCapabilities;
}

static int32_t EDAL_I2C_Initialize(EDAL_I2C_SignalEvent_t cb_event)
{
}

static int32_t EDAL_I2C_Uninitialize(void)
{
}

static int32_t EDAL_I2C_PowerControl(EDAL_POWER_STATE state)
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

static int32_t EDAL_I2C_MasterTransmit(uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending)
{
}

static int32_t EDAL_I2C_MasterReceive(uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending)
{
}

static int32_t EDAL_I2C_SlaveTransmit(const uint8_t *data, uint32_t num)
{
}

static int32_t EDAL_I2C_SlaveReceive(uint8_t *data, uint32_t num)
{
}

static int32_t EDAL_I2C_GetDataCount(void)
{
}

static int32_t EDAL_I2C_Control(uint32_t control, uint32_t arg)
{
    switch(control)
    {
        case EDAL_I2C_OWN_ADDRESS:
            break;

        case EDAL_I2C_BUS_SPEED:
            switch(arg)
            {
                case EDAL_I2C_BUS_SPEED_STANDARD:
                    break;
                case EDAL_I2C_BUS_SPEED_FAST:
                    break;
                case EDAL_I2C_BUS_SPEED_FAST_PLUS:
                    break;
            }
            break;
        
        case EDAL_I2C_BUS_CLEAR:
            break;

        case EDAL_I2C_ABORT_TRANSFER:
            break;

        default:
            return EDAL_DRIVER_ERROR_UNSUPPORTED;
    }
}

static EDAL_I2C_STATUS EDAL_I2C_GetStatus(void)
{
}

static void EDAL_I2C_SignalEvent(uint32_t event)
{
    // function body
}

/*============================ PROTOTYPES ====================================*/
extern 
EDAL_DRIVER_I2C EDAL_Driver_I2C_(0);
EDAL_DRIVER_I2C EDAL_Driver_I2C_(0) = {
    EDAL_I2C_GetVersion,
    EDAL_I2C_GetCapabilities,
    EDAL_I2C_Initialize,
    EDAL_I2C_Uninitialize,
    EDAL_I2C_PowerControl,
    EDAL_I2C_MasterTransmit,
    EDAL_I2C_MasterReceive,
    EDAL_I2C_SlaveTransmit,
    EDAL_I2C_SlaveReceive,
    EDAL_I2C_GetDataCount,
    EDAL_I2C_Control,
    EDAL_I2C_GetStatus
};

/*============================ END ===========================================*/
