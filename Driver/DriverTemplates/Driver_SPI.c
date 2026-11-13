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
#include "Driver/Include/Driver_SPI.h"

/*============================ MACROS ========================================*/
#define EDAL_SPI_DRV_VERSION    EDAL_VERSION_MAJOR_MINOR(0, 0)  /* driver version */

/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/
/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/* Driver Version */
static const EDAL_VERSION DriverVersion = {
    EDAL_SPI_API_VERSION,
    EDAL_SPI_DRV_VERSION
};

/* Driver Capabilities */
static const EDAL_SPI_CAPABILITIES DriverCapabilities = {
    0,  /* Reserved (must be zero) */
    0,  /* TI Synchronous Serial Interface */
    0,  /* Microwire Interface */
    0,  /* Signal Mode Fault event: \ref EDAL_SPI_EVENT_MODE_FAULT */
    0   /* Reserved (must be zero) */
};

/*============================ IMPLEMENTATION ================================*/
static EDAL_VERSION EDAL_SPI_GetVersion(void)
{
    return DriverVersion;
}

static EDAL_SPI_CAPABILITIES EDAL_SPI_GetCapabilities(void)
{
    return DriverCapabilities;
}

static int32_t EDAL_SPI_Initialize(EDAL_SPI_SignalEvent_t cb_event)
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

static int32_t EDAL_SPI_Send(const void *data, uint32_t num)
{
}

static int32_t EDAL_SPI_Receive(void *data, uint32_t num)
{
}

static int32_t EDAL_SPI_Transfer(const void *data_out, void *data_in, uint32_t num)
{
}

static uint32_t EDAL_SPI_GetDataCount(void)
{
}

static int32_t EDAL_SPI_Control(uint32_t control, uint32_t arg)
{
    switch (control & EDAL_SPI_CONTROL_Msk)
    {
        case EDAL_SPI_MODE_INACTIVE:            // SPI Inactive
            return EDAL_DRIVER_OK;

        case EDAL_SPI_MODE_MASTER:              // SPI Master (Output on MOSI, Input on MISO); arg = Bus Speed in bps
            break;
        
        case EDAL_SPI_MODE_SLAVE:               // SPI Slave  (Output on MISO, Input on MOSI)
            break;

        case EDAL_SPI_SET_BUS_SPEED:            // Set Bus Speed in bps; arg = value
            break;

        case EDAL_SPI_GET_BUS_SPEED:            // Get Bus Speed in bps
            break;

        case EDAL_SPI_SET_DEFAULT_TX_VALUE:     // Set default Transmit value; arg = value
            break;

        case EDAL_SPI_CONTROL_SS:               // Control Slave Select; arg = 0:inactive, 1:active
            break;

        case EDAL_SPI_ABORT_TRANSFER:           // Abort current data transfer
            break;
            
        default:
            return EDAL_DRIVER_ERROR_UNSUPPORTED;
    }
}

static EDAL_SPI_STATUS EDAL_SPI_GetStatus(void)
{
}

static void EDAL_SPI_SignalEvent(uint32_t event)
{
    // function body
}

/*============================ PROTOTYPES ====================================*/
extern 
EDAL_DRIVER_SPI EDAL_Driver_SPI_(0);
EDAL_DRIVER_SPI EDAL_Driver_SPI_(0) = {
    EDAL_SPI_GetVersion,
    EDAL_SPI_GetCapabilities,
    EDAL_SPI_Initialize,
    EDAL_SPI_Uninitialize,
    EDAL_SPI_PowerControl,
    EDAL_SPI_Send,
    EDAL_SPI_Receive,
    EDAL_SPI_Transfer,
    EDAL_SPI_GetDataCount,
    EDAL_SPI_Control,
    EDAL_SPI_GetStatus,
};

/*============================ END ===========================================*/
