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
#include "Driver_WIFI.h"

/*============================ MACROS ========================================*/
#define EDAL_WIFI_DRV_VERSION       EDAL_VERSION_MAJOR_MINOR(1, 0)  /* driver version */

/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/
/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/* Driver Version */
static const EDAL_VERSION DriverVersion = {
    EDAL_WIFI_API_VERSION,
    EDAL_WIFI_DRV_VERSION
};

/* Driver Capabilities */
static const EDAL_WIFI_CAPABILITIES DriverCapabilities = {
    0,  /* Station supported */
    0,  /* Access Point supported */
    0,  /* Concurrent Station and Access Point not supported */
    0,  /* WiFi Protected Setup (WPS) for Station supported */
    0,  /* WiFi Protected Setup (WPS) for Access Point not supported */
    0,  /* Access Point: event generated on Station connect */
    0,  /* Access Point: event not generated on Station disconnect */
    0,  /* Event not generated on Ethernet frame reception in bypass mode */
    0,  /* Bypass or pass-through mode (Ethernet interface) not supported */
    0,  /* IP (UDP/TCP) (Socket interface) supported */
    0,  /* IPv6 (Socket interface) not supported */
    0,  /* Ping (ICMP) supported */
    0   /* Reserved (must be zero) */
};

/*============================ IMPLEMENTATION ================================*/
static EDAL_VERSION EDAL_WIFI_GetVersion(void)
{
    return DriverVersion;
}

static EDAL_WIFI_CAPABILITIES EDAL_WIFI_GetCapabilities(void)
{
    return DriverCapabilities;
}

static int32_t EDAL_WIFI_Initialize(EDAL_WIFI_SignalEvent_t cb_event)
{
}

static int32_t EDAL_WIFI_Uninitialize(void)
{
}

static int32_t EDAL_WIFI_PowerControl(EDAL_POWER_STATE state)
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

static int32_t EDAL_WIFI_GetModuleInfo(char *module_info, uint32_t max_len)
{
}

static int32_t EDAL_WIFI_SetOption(uint32_t interface, uint32_t option, const void *data, uint32_t len)
{
}

static int32_t EDAL_WIFI_GetOption(uint32_t interface, uint32_t option, void *data, uint32_t *len)
{
}

static int32_t EDAL_WIFI_Scan(EDAL_WIFI_SCAN_INFO scan_info[], uint32_t max_num)
{
}

static int32_t EDAL_WIFI_Activate(uint32_t interface, const EDAL_WIFI_CONFIG *config)
{
}

static int32_t EDAL_WIFI_Deactivate(uint32_t interface)
{
}

static uint32_t EDAL_WIFI_IsConnected(void)
{
    return 0U;
}

static int32_t EDAL_WIFI_GetNetInfo(EDAL_WIFI_NET_INFO *net_info)
{
}

static int32_t EDAL_WIFI_BypassControl(uint32_t interface, uint32_t mode)
{
}

static int32_t EDAL_WIFI_EthSendFrame(uint32_t interface, const uint8_t *frame, uint32_t len)
{
}

static int32_t EDAL_WIFI_EthReadFrame(uint32_t interface, uint8_t *frame, uint32_t len)
{
}

static uint32_t EDAL_WIFI_EthGetRxFrameSize(uint32_t interface)
{
    return 0U;
}

static int32_t EDAL_WIFI_SocketCreate(int32_t af, int32_t type, int32_t protocol)
{
}

static int32_t EDAL_WIFI_SocketBind(int32_t socket, const uint8_t *ip, uint32_t ip_len, uint16_t port)
{
}

static int32_t EDAL_WIFI_SocketListen(int32_t socket, int32_t backlog)
{
}

static int32_t EDAL_WIFI_SocketAccept(int32_t socket, uint8_t *ip, uint32_t *ip_len, uint16_t *port)
{
}

static int32_t EDAL_WIFI_SocketConnect(int32_t socket, const uint8_t *ip, uint32_t  ip_len, uint16_t  port)
{
}

static int32_t EDAL_WIFI_SocketRecv(int32_t socket, void *buf, uint32_t len)
{
}

static int32_t EDAL_WIFI_SocketRecvFrom(int32_t socket, void *buf, uint32_t len, uint8_t *ip, uint32_t *ip_len, uint16_t *port)
{
}

static int32_t EDAL_WIFI_SocketSend(int32_t socket, const void *buf, uint32_t len)
{
}

static int32_t EDAL_WIFI_SocketSendTo(int32_t socket, const void *buf, uint32_t len, const uint8_t *ip, uint32_t ip_len, uint16_t port)
{
}

static int32_t EDAL_WIFI_SocketGetSockName(int32_t socket, uint8_t *ip, uint32_t *ip_len, uint16_t *port)
{
}

static int32_t EDAL_WIFI_SocketGetPeerName(int32_t socket, uint8_t *ip, uint32_t *ip_len, uint16_t *port)
{
}

static int32_t EDAL_WIFI_SocketGetOpt(int32_t socket, int32_t opt_id, void *opt_val, uint32_t *opt_len)
{
}

static int32_t EDAL_WIFI_SocketSetOpt(int32_t socket, int32_t opt_id, const void *opt_val, uint32_t opt_len)
{
}

static int32_t EDAL_WIFI_SocketClose(int32_t socket)
{
}

static int32_t EDAL_WIFI_SocketGetHostByName(const char *name, int32_t af, uint8_t *ip, uint32_t *ip_len)
{
}

static int32_t EDAL_WIFI_Ping(const uint8_t *ip, uint32_t ip_len)
{
}

/*============================ PROTOTYPES ====================================*/
extern
EDAL_DRIVER_WIFI EDAL_Driver_WIFI_(0);
EDAL_DRIVER_WIFI EDAL_Driver_WIFI_(0) = {
    EDAL_WIFI_GetVersion,
    EDAL_WIFI_GetCapabilities,
    EDAL_WIFI_Initialize,
    EDAL_WIFI_Uninitialize,
    EDAL_WIFI_PowerControl,
    EDAL_WIFI_GetModuleInfo,
    EDAL_WIFI_SetOption,
    EDAL_WIFI_GetOption,
    EDAL_WIFI_Scan,
    EDAL_WIFI_Activate,
    EDAL_WIFI_Deactivate,
    EDAL_WIFI_IsConnected,
    EDAL_WIFI_GetNetInfo,
    EDAL_WIFI_BypassControl,
    EDAL_WIFI_EthSendFrame,
    EDAL_WIFI_EthReadFrame,
    EDAL_WIFI_EthGetRxFrameSize,
    EDAL_WIFI_SocketCreate,
    EDAL_WIFI_SocketBind,
    EDAL_WIFI_SocketListen,
    EDAL_WIFI_SocketAccept,
    EDAL_WIFI_SocketConnect,
    EDAL_WIFI_SocketRecv,
    EDAL_WIFI_SocketRecvFrom,
    EDAL_WIFI_SocketSend,
    EDAL_WIFI_SocketSendTo,
    EDAL_WIFI_SocketGetSockName,
    EDAL_WIFI_SocketGetPeerName,
    EDAL_WIFI_SocketGetOpt,
    EDAL_WIFI_SocketSetOpt,
    EDAL_WIFI_SocketClose,
    EDAL_WIFI_SocketGetHostByName,
    EDAL_WIFI_Ping
};


/*============================ END ===========================================*/
