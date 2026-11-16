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
#include "Driver_USART.h"

/*============================ MACROS ========================================*/
#define EDAL_USART_DRV_VERSION      EDAL_VERSION_MAJOR_MINOR(1, 0)  /* driver version */

/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/
/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/* Driver Version */
static const EDAL_VERSION DriverVersion = {
    EDAL_USART_API_VERSION,
    EDAL_USART_DRV_VERSION
};

/* Driver Capabilities */
static const EDAL_USART_CAPABILITIES DriverCapabilities = {
    1,  /* supports UART (Asynchronous) mode */
    0,  /* supports Synchronous Master mode */
    0,  /* supports Synchronous Slave mode */
    0,  /* supports UART Single-wire mode */
    0,  /* supports UART IrDA mode */
    0,  /* supports UART Smart Card mode */
    0,  /* Smart Card Clock generator available */
    0,  /* RTS Flow Control available */
    0,  /* CTS Flow Control available */
    0,  /* Transmit completed event: \ref EDAL_USART_EVENT_TX_COMPLETE */
    0,  /* Signal receive character timeout event: \ref EDAL_USART_EVENT_RX_TIMEOUT */
    0,  /* RTS Line: 0=not available, 1=available */
    0,  /* CTS Line: 0=not available, 1=available */
    0,  /* DTR Line: 0=not available, 1=available */
    0,  /* DSR Line: 0=not available, 1=available */
    0,  /* DCD Line: 0=not available, 1=available */
    0,  /* RI  Line: 0=not available, 1=available */
    0,  /* Signal CTS change event: \ref EDAL_USART_EVENT_CTS */
    0,  /* Signal DSR change event: \ref EDAL_USART_EVENT_DSR */
    0,  /* Signal DCD change event: \ref EDAL_USART_EVENT_DCD */
    0,  /* Signal RI  change event: \ref EDAL_USART_EVENT_RI */
    0,  /* Reserved (must be zero) */
};

/*============================ IMPLEMENTATION ================================*/
static EDAL_VERSION EDAL_USART_GetVersion(void)
{
    return DriverVersion;
}

static EDAL_USART_CAPABILITIES EDAL_USART_GetCapabilities(void)
{
    return DriverCapabilities;
}

static int32_t EDAL_USART_Initialize(EDAL_USART_SignalEvent_t cb_event)
{
}

static int32_t EDAL_USART_Uninitialize(void)
{
}

static int32_t EDAL_USART_PowerControl(EDAL_POWER_STATE state)
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

static int32_t EDAL_USART_Send(const void *data, uint32_t num)
{
}

static int32_t EDAL_USART_Receive(void *data, uint32_t num)
{
}

static int32_t EDAL_USART_Transfer(const void *data_out, void *data_in, uint32_t num)
{
}

static int32_t EDAL_USART_GetTxCount(void)
{
}

static int32_t EDAL_USART_GetRxCount(void)
{
}

static int32_t EDAL_USART_SetModemControl(EDAL_USART_MODEM_CONTROL control)
{
}

static EDAL_USART_MODEM_STATUS EDAL_USART_GetModemStatus(void)
{
}

static int32_t EDAL_USART_Control(uint32_t control, uint32_t arg)
{
}

static EDAL_USART_STATUS EDAL_USART_GetStatus(void)
{
}

static void EDAL_USART_SignalEvent(uint32_t event)
{
    // function body
}

/*============================ PROTOTYPES ====================================*/
extern
EDAL_DRIVER_USART EDAL_Driver_USART_(0);
EDAL_DRIVER_USART EDAL_Driver_USART_(0) = {
    EDAL_USART_GetVersion,
    EDAL_USART_GetCapabilities,
    EDAL_USART_Initialize,
    EDAL_USART_Uninitialize,
    EDAL_USART_PowerControl,
    EDAL_USART_Send,
    EDAL_USART_Receive,
    EDAL_USART_Transfer,
    EDAL_USART_GetTxCount,
    EDAL_USART_GetRxCount,
    EDAL_USART_SetModemControl,
    EDAL_USART_GetModemStatus,
    EDAL_USART_Control,
    EDAL_USART_GetStatus
};

/*============================ END ===========================================*/
