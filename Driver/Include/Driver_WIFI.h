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

#ifndef __DRIVER_WIFI_H__
#define __DRIVER_WIFI_H__

/*============================ INCLUDES ======================================*/
#include "EDAL_Common.h"

#ifdef   __cplusplus
extern "C" {
#endif
/*============================ MACROS ========================================*/
#define EDAL_WIFI_API_VERSION       EDAL_VERSION_MAJOR_MINOR(1, 0)  /* API version */


#define _EDAL_Driver_WIFI_(n)             Driver_WIFI##n
#define  EDAL_Driver_WIFI_(n)       _EDAL_Driver_WIFI_(n)



/****** WiFi SetOption/GetOption Function Option Codes *****/
#define EDAL_WIFI_BSSID                      1U         //!< Station/AP Set/Get BSSID of AP to connect or of AP;        data = &bssid,    len =  6, uint8_t[6]
#define EDAL_WIFI_TX_POWER                   2U         //!< Station/AP Set/Get transmit power;                         data = &power,    len =  4, uint32_t: 0 .. 20 [dBm]
#define EDAL_WIFI_LP_TIMER                   3U         //!< Station    Set/Get low-power deep-sleep time;              data = &time,     len =  4, uint32_t [seconds]: 0 = disable (default)
#define EDAL_WIFI_DTIM                       4U         //!< Station/AP Set/Get DTIM interval;                          data = &dtim,     len =  4, uint32_t [beacons]
#define EDAL_WIFI_BEACON                     5U         //!<         AP Set/Get beacon interval;                        data = &interval, len =  4, uint32_t [ms]
#define EDAL_WIFI_MAC                        6U         //!< Station/AP Set/Get MAC;                                    data = &mac,      len =  6, uint8_t[6]
#define EDAL_WIFI_IP                         7U         //!< Station/AP Set/Get IPv4 static/assigned address;           data = &ip,       len =  4, uint8_t[4]
#define EDAL_WIFI_IP_SUBNET_MASK             8U         //!< Station/AP Set/Get IPv4 subnet mask;                       data = &mask,     len =  4, uint8_t[4]
#define EDAL_WIFI_IP_GATEWAY                 9U         //!< Station/AP Set/Get IPv4 gateway address;                   data = &ip,       len =  4, uint8_t[4]
#define EDAL_WIFI_IP_DNS1                    10         //!< Station/AP Set/Get IPv4 primary   DNS address;             data = &ip,       len =  4, uint8_t[4]
#define EDAL_WIFI_IP_DNS2                    11         //!< Station/AP Set/Get IPv4 secondary DNS address;             data = &ip,       len =  4, uint8_t[4]
#define EDAL_WIFI_IP_DHCP                    12         //!< Station/AP Set/Get IPv4 DHCP client/server enable/disable; data = &dhcp,     len =  4, uint32_t: 0 = disable, non-zero = enable (default)
#define EDAL_WIFI_IP_DHCP_POOL_BEGIN         13         //!<         AP Set/Get IPv4 DHCP pool begin address;           data = &ip,       len =  4, uint8_t[4]
#define EDAL_WIFI_IP_DHCP_POOL_END           14         //!<         AP Set/Get IPv4 DHCP pool end address;             data = &ip,       len =  4, uint8_t[4]
#define EDAL_WIFI_IP_DHCP_LEASE_TIME         15         //!<         AP Set/Get IPv4 DHCP lease time;                   data = &time,     len =  4, uint32_t [seconds]
#define EDAL_WIFI_IP6_GLOBAL                 16         //!< Station/AP Set/Get IPv6 global address;                    data = &ip6,      len = 16, uint8_t[16]
#define EDAL_WIFI_IP6_LINK_LOCAL             17         //!< Station/AP Set/Get IPv6 link local address;                data = &ip6,      len = 16, uint8_t[16]
#define EDAL_WIFI_IP6_SUBNET_PREFIX_LEN      18         //!< Station/AP Set/Get IPv6 subnet prefix length;              data = &len,      len =  4, uint32_t: 1 .. 127
#define EDAL_WIFI_IP6_GATEWAY                19         //!< Station/AP Set/Get IPv6 gateway address;                   data = &ip6,      len = 16, uint8_t[16]
#define EDAL_WIFI_IP6_DNS1                   20         //!< Station/AP Set/Get IPv6 primary   DNS address;             data = &ip6,      len = 16, uint8_t[16]
#define EDAL_WIFI_IP6_DNS2                   21         //!< Station/AP Set/Get IPv6 secondary DNS address;             data = &ip6,      len = 16, uint8_t[16]
#define EDAL_WIFI_IP6_DHCP_MODE              22         //!< Station/AP Set/Get IPv6 DHCPv6 client mode;                data = &mode,     len =  4, uint32_t: EDAL_WIFI_IP6_DHCP_xxx (default Off)

/****** WiFi Security Type *****/
#define EDAL_WIFI_SECURITY_OPEN              0U         //!< Open
#define EDAL_WIFI_SECURITY_WEP               1U         //!< Wired Equivalent Privacy (WEP) with Pre-Sheared Key (PSK)
#define EDAL_WIFI_SECURITY_WPA               2U         //!< WiFi Protected Access (WPA) with PSK
#define EDAL_WIFI_SECURITY_WPA2              3U         //!< WiFi Protected Access II (WPA2) with PSK
#define EDAL_WIFI_SECURITY_UNKNOWN           25         //!< Unknown

/****** WiFi Protected Setup (WPS) Method *****/
#define EDAL_WIFI_WPS_METHOD_NONE            0U         //!< Not used
#define EDAL_WIFI_WPS_METHOD_PBC             1U         //!< Push Button Configuration
#define EDAL_WIFI_WPS_METHOD_PIN             2U         //!< PIN

/****** WiFi IPv6 Dynamic Host Configuration Protocol (DHCP) Mode *****/
#define EDAL_WIFI_IP6_DHCP_OFF               0U         //!< Static Host Configuration (default)
#define EDAL_WIFI_IP6_DHCP_STATELESS         1U         //!< Dynamic Host Configuration stateless DHCPv6
#define EDAL_WIFI_IP6_DHCP_STATEFULL         2U         //!< Dynamic Host Configuration statefull DHCPv6

/****** WiFi Event *****/
#define EDAL_WIFI_EVENT_AP_CONNECT          (1UL << 0)  //!< Access Point: Station has connected;           arg = &mac, mac (uint8_t[6])
#define EDAL_WIFI_EVENT_AP_DISCONNECT       (1UL << 1)  //!< Access Point: Station has disconnected;        arg = &mac, mac (uint8_t[6])
#define EDAL_WIFI_EVENT_ETH_RX_FRAME        (1UL << 4)  //!< Ethernet Frame Received (in bypass mode only); arg = interface (0 = Station, 1 = Access Point)


/****** Socket Address Family definitions *****/
#define EDAL_SOCKET_AF_INET                  1          //!< IPv4
#define EDAL_SOCKET_AF_INET6                 2          //!< IPv6

/****** Socket Type definitions *****/
#define EDAL_SOCKET_SOCK_STREAM              1          //!< Stream socket
#define EDAL_SOCKET_SOCK_DGRAM               2          //!< Datagram socket

/****** Socket Protocol definitions *****/
#define EDAL_SOCKET_IPPROTO_TCP              1          //!< TCP
#define EDAL_SOCKET_IPPROTO_UDP              2          //!< UDP

/****** Socket Option definitions *****/
#define EDAL_SOCKET_IO_FIONBIO               1          //!< Non-blocking I/O (Set only, default = 0); opt_val = &nbio, opt_len = sizeof(nbio), nbio (integer): 0=blocking, non-blocking otherwise
#define EDAL_SOCKET_SO_RCVTIMEO              2          //!< Receive timeout in ms (default = 0); opt_val = &timeout, opt_len = sizeof(timeout)
#define EDAL_SOCKET_SO_SNDTIMEO              3          //!< Send timeout in ms (default = 0); opt_val = &timeout, opt_len = sizeof(timeout)
#define EDAL_SOCKET_SO_KEEPALIVE             4          //!< Keep-alive messages (default = 0); opt_val = &keepalive, opt_len = sizeof(keepalive), keepalive (integer): 0=disabled, enabled otherwise
#define EDAL_SOCKET_SO_TYPE                  5          //!< Socket Type (Get only); opt_val = &socket_type, opt_len = sizeof(socket_type), socket_type (integer): EDAL_SOCKET_SOCK_xxx

/****** Socket Function return codes *****/
#define EDAL_SOCKET_ERROR                   (-1)        //!< Unspecified error
#define EDAL_SOCKET_ESOCK                   (-2)        //!< Invalid socket
#define EDAL_SOCKET_EINVAL                  (-3)        //!< Invalid argument
#define EDAL_SOCKET_ENOTSUP                 (-4)        //!< Operation not supported
#define EDAL_SOCKET_ENOMEM                  (-5)        //!< Not enough memory
#define EDAL_SOCKET_EAGAIN                  (-6)        //!< Operation would block or timed out
#define EDAL_SOCKET_EINPROGRESS             (-7)        //!< Operation in progress
#define EDAL_SOCKET_ETIMEDOUT               (-8)        //!< Operation timed out
#define EDAL_SOCKET_EISCONN                 (-9)        //!< Socket is connected
#define EDAL_SOCKET_ENOTCONN                (-10)       //!< Socket is not connected
#define EDAL_SOCKET_ECONNREFUSED            (-11)       //!< Connection rejected by the peer
#define EDAL_SOCKET_ECONNRESET              (-12)       //!< Connection reset by the peer
#define EDAL_SOCKET_ECONNABORTED            (-13)       //!< Connection aborted locally
#define EDAL_SOCKET_EALREADY                (-14)       //!< Connection already in progress
#define EDAL_SOCKET_EADDRINUSE              (-15)       //!< Address in use
#define EDAL_SOCKET_EHOSTNOTFOUND           (-16)       //!< Host not found


/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/

/**
 * \brief WIFI Configuration
 */
typedef struct _EDAL_WIFI_CONFIG {
    const char   *ssid;                 //!< Pointer to Service Set Identifier (SSID) null-terminated string
    const char   *pass;                 //!< Pointer to Password null-terminated string
          uint8_t security;             //!< Security type (EDAL_WIFI_SECURITY_xxx)
          uint8_t ch;                   //!< WiFi Channel (0 = auto, otherwise = exact channel)
          uint8_t reserved;             //!< Reserved
          uint8_t wps_method;           //!< WiFi Protected Setup (WPS) method (EDAL_WIFI_WPS_METHOD_xxx)
    const char   *wps_pin;              //!< Pointer to WiFi Protected Setup (WPS) PIN null-terminated string
} EDAL_WIFI_CONFIG;

/**
 * \brief WIFI Scan Information
 */
typedef struct _EDAL_WIFI_SCAN_INFO {
    char    ssid[32+1];                 //!< Service Set Identifier (SSID) null-terminated string
    uint8_t bssid[6];                   //!< Basic Service Set Identifier (BSSID)
    uint8_t security;                   //!< Security type (EDAL_WIFI_SECURITY_xxx)
    uint8_t ch;                         //!< WiFi Channel
    uint8_t rssi;                       //!< Received Signal Strength Indicator
} EDAL_WIFI_SCAN_INFO;

/**
 * \brief WIFI Network Information
 */
typedef struct _EDAL_WIFI_NET_INFO {
    char    ssid[32+1];                 //!< Service Set Identifier (SSID) null-terminated string
    uint8_t pass[64+1];                 //!< Password null-terminated string
    uint8_t security;                   //!< Security type (EDAL_WIFI_SECURITY_xxx)
    uint8_t ch;                         //!< WiFi Channel
    uint8_t rssi;                       //!< Received Signal Strength Indicator
} EDAL_WIFI_NET_INFO;


// Function documentation
/**
 * 
 */

typedef void (*EDAL_WIFI_SignalEvent_t) (uint32_t event);


/**
 * \brief WIFI Driver Capabilities.
 */
typedef struct _EDAL_WIFI_CAPABILITIES {
    uint32_t station             : 1;       //!< Station
    uint32_t ap                  : 1;       //!< Access Point
    uint32_t station_ap          : 1;       //!< Concurrent Station and Access Point
    uint32_t wps_station         : 1;       //!< WiFi Protected Setup (WPS) for Station
    uint32_t wps_ap              : 1;       //!< WiFi Protected Setup (WPS) for Access Point
    uint32_t event_ap_connect    : 1;       //!< Access Point: event generated on Station connect
    uint32_t event_ap_disconnect : 1;       //!< Access Point: event generated on Station disconnect
    uint32_t event_eth_rxs_frame : 1;       //!< Event generated on Ethernet frame reception in bypass mode
    uint32_t bypass_mode         : 1;       //!< Bypass or pass-through mode (Ethernet interface)
    uint32_t ip                  : 1;       //!< IP (UDP/TCP) (Socket interface)
    uint32_t ip6                 : 1;       //!< IPv6 (Socket interface)
    uint32_t ping                : 1;       //!< Ping (ICMP)
    uint32_t reserved            : 20;      //!< Reserved (must be zero)
} EDAL_WIFI_CAPABILITIES;


/**
 * \brief Access structure of the WIFI Driver.
 */
typedef struct _EDAL_DRIVER_WIFI {
    EDAL_VERSION            (*GetVersion)           (void);
    EDAL_WIFI_CAPABILITIES  (*GetCapabilities)      (void);
    int32_t                 (*Initialize)           (EDAL_WIFI_SignalEvent_t cb_event);
    int32_t                 (*Uninitialize)         (void);
    int32_t                 (*PowerControl)         (EDAL_POWER_STATE state);
    int32_t                 (*GetModuleInfo)        (char *module_info, uint32_t max_len);
    int32_t                 (*SetOption)            (uint32_t interface, uint32_t option, const void *data, uint32_t  len);
    int32_t                 (*GetOption)            (uint32_t interface, uint32_t option,       void *data, uint32_t *len);
    int32_t                 (*Scan)                 (EDAL_WIFI_SCAN_INFO scan_info[], uint32_t max_num);
    int32_t                 (*Activate)             (uint32_t interface, const EDAL_WIFI_CONFIG *config);
    int32_t                 (*Deactivate)           (uint32_t interface);
    uint32_t                (*IsConnected)          (void);
    int32_t                 (*GetNetInfo)           (EDAL_WIFI_NET_INFO *net_info);
    int32_t                 (*BypassControl)        (uint32_t interface, uint32_t mode);
    int32_t                 (*EthSendFrame)         (uint32_t interface, const uint8_t *frame, uint32_t len);
    int32_t                 (*EthReadFrame)         (uint32_t interface,       uint8_t *frame, uint32_t len);
    uint32_t                (*EthGetRxFrameSize)    (uint32_t interface);
    int32_t                 (*SocketCreate)         (int32_t af, int32_t type, int32_t protocol);
    int32_t                 (*SocketBind)           (int32_t socket, const uint8_t *ip, uint32_t  ip_len, uint16_t  port);
    int32_t                 (*SocketListen)         (int32_t socket, int32_t backlog);
    int32_t                 (*SocketAccept)         (int32_t socket,       uint8_t *ip, uint32_t *ip_len, uint16_t *port);
    int32_t                 (*SocketConnect)        (int32_t socket, const uint8_t *ip, uint32_t  ip_len, uint16_t  port);
    int32_t                 (*SocketRecv)           (int32_t socket, void *buf, uint32_t len);
    int32_t                 (*SocketRecvFrom)       (int32_t socket, void *buf, uint32_t len, uint8_t *ip, uint32_t *ip_len, uint16_t *port);
    int32_t                 (*SocketSend)           (int32_t socket, const void *buf, uint32_t len);
    int32_t                 (*SocketSendTo)         (int32_t socket, const void *buf, uint32_t len, const uint8_t *ip, uint32_t ip_len, uint16_t port);
    int32_t                 (*SocketGetSockName)    (int32_t socket, uint8_t *ip, uint32_t *ip_len, uint16_t *port);
    int32_t                 (*SocketGetPeerName)    (int32_t socket, uint8_t *ip, uint32_t *ip_len, uint16_t *port);
    int32_t                 (*SocketGetOpt)         (int32_t socket, int32_t opt_id,       void *opt_val, uint32_t *opt_len);
    int32_t                 (*SocketSetOpt)         (int32_t socket, int32_t opt_id, const void *opt_val, uint32_t  opt_len);
    int32_t                 (*SocketClose)          (int32_t socket);
    int32_t                 (*SocketGetHostByName)  (const char *name, int32_t af, uint8_t *ip, uint32_t *ip_len);
    int32_t                 (*Ping)                 (const uint8_t *ip, uint32_t ip_len);
} EDAL_DRIVER_WIFI;

/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/
/*============================ IMPLEMENTATION ================================*/
/*============================ END ===========================================*/
#ifdef   __cplusplus
}
#endif
#endif /* __DRIVER_WIFI_H__ */
