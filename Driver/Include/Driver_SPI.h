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

#ifndef __DRIVER_SPI_H__
#define __DRIVER_SPI_H__

/*============================ INCLUDES ======================================*/
#include "EDAL_Common.h"

#ifdef   __cplusplus
extern "C" {
#endif
/*============================ MACROS ========================================*/
#define EDAL_SPI_API_VERSION    EDAL_VERSION_MAJOR_MINOR(1, 0)  /* API version */

#define _EDAL_Driver_SPI_(n)          Driver_SPI##n
#define  EDAL_Driver_SPI_(n)    _EDAL_Driver_SPI_(n)


/****** SPI Control Codes *****/

#define EDAL_SPI_CONTROL_Pos                 0
#define EDAL_SPI_CONTROL_Msk                (0xFFUL << EDAL_SPI_CONTROL_Pos)

/*----- SPI Control Codes: Mode -----*/
#define EDAL_SPI_MODE_INACTIVE              (0x00UL << EDAL_SPI_CONTROL_Pos)     //!< SPI Inactive
#define EDAL_SPI_MODE_MASTER                (0x01UL << EDAL_SPI_CONTROL_Pos)     //!< SPI Master (Output on MOSI, Input on MISO); arg = Bus Speed in bps
#define EDAL_SPI_MODE_SLAVE                 (0x02UL << EDAL_SPI_CONTROL_Pos)     //!< SPI Slave  (Output on MISO, Input on MOSI)
#define EDAL_SPI_MODE_MASTER_SIMPLEX        (0x03UL << EDAL_SPI_CONTROL_Pos)     //!< SPI Master (Output/Input on MOSI); arg = Bus Speed in bps @deprecated Simplex Mode has been removed
#define EDAL_SPI_MODE_SLAVE_SIMPLEX         (0x04UL << EDAL_SPI_CONTROL_Pos)     //!< SPI Slave  (Output/Input on MISO) @deprecated Simplex Mode has been removed

/*----- SPI Control Codes: Mode Parameters: Frame Format -----*/
#define EDAL_SPI_FRAME_FORMAT_Pos            8
#define EDAL_SPI_FRAME_FORMAT_Msk           (7UL << EDAL_SPI_FRAME_FORMAT_Pos)
#define EDAL_SPI_CPOL0_CPHA0                (0UL << EDAL_SPI_FRAME_FORMAT_Pos)   //!< Clock Polarity 0, Clock Phase 0 (default)
#define EDAL_SPI_CPOL0_CPHA1                (1UL << EDAL_SPI_FRAME_FORMAT_Pos)   //!< Clock Polarity 0, Clock Phase 1
#define EDAL_SPI_CPOL1_CPHA0                (2UL << EDAL_SPI_FRAME_FORMAT_Pos)   //!< Clock Polarity 1, Clock Phase 0
#define EDAL_SPI_CPOL1_CPHA1                (3UL << EDAL_SPI_FRAME_FORMAT_Pos)   //!< Clock Polarity 1, Clock Phase 1
#define EDAL_SPI_TI_SSI                     (4UL << EDAL_SPI_FRAME_FORMAT_Pos)   //!< Texas Instruments Frame Format
#define EDAL_SPI_MICROWIRE                  (5UL << EDAL_SPI_FRAME_FORMAT_Pos)   //!< National Semiconductor Microwire Frame Format

/*----- SPI Control Codes: Mode Parameters: Data Bits -----*/
#define EDAL_SPI_DATA_BITS_Pos               12
#define EDAL_SPI_DATA_BITS_Msk              (0x3FUL << EDAL_SPI_DATA_BITS_Pos)
#define EDAL_SPI_DATA_BITS(n)               (((n) & 0x3FUL) << EDAL_SPI_DATA_BITS_Pos) //!< Number of Data bits

/*----- SPI Control Codes: Mode Parameters: Bit Order -----*/
#define EDAL_SPI_BIT_ORDER_Pos               18
#define EDAL_SPI_BIT_ORDER_Msk              (1UL << EDAL_SPI_BIT_ORDER_Pos)
#define EDAL_SPI_MSB_LSB                    (0UL << EDAL_SPI_BIT_ORDER_Pos)      //!< SPI Bit order from MSB to LSB (default)
#define EDAL_SPI_LSB_MSB                    (1UL << EDAL_SPI_BIT_ORDER_Pos)      //!< SPI Bit order from LSB to MSB

/*----- SPI Control Codes: Mode Parameters: Slave Select Mode -----*/
#define EDAL_SPI_SS_MASTER_MODE_Pos          19
#define EDAL_SPI_SS_MASTER_MODE_Msk         (3UL << EDAL_SPI_SS_MASTER_MODE_Pos)
#define EDAL_SPI_SS_MASTER_UNUSED           (0UL << EDAL_SPI_SS_MASTER_MODE_Pos) //!< SPI Slave Select when Master: Not used (default)
#define EDAL_SPI_SS_MASTER_SW               (1UL << EDAL_SPI_SS_MASTER_MODE_Pos) //!< SPI Slave Select when Master: Software controlled
#define EDAL_SPI_SS_MASTER_HW_OUTPUT        (2UL << EDAL_SPI_SS_MASTER_MODE_Pos) //!< SPI Slave Select when Master: Hardware controlled Output
#define EDAL_SPI_SS_MASTER_HW_INPUT         (3UL << EDAL_SPI_SS_MASTER_MODE_Pos) //!< SPI Slave Select when Master: Hardware monitored Input
#define EDAL_SPI_SS_SLAVE_MODE_Pos           21
#define EDAL_SPI_SS_SLAVE_MODE_Msk          (1UL << EDAL_SPI_SS_SLAVE_MODE_Pos)
#define EDAL_SPI_SS_SLAVE_HW                (0UL << EDAL_SPI_SS_SLAVE_MODE_Pos)  //!< SPI Slave Select when Slave: Hardware monitored (default)
#define EDAL_SPI_SS_SLAVE_SW                (1UL << EDAL_SPI_SS_SLAVE_MODE_Pos)  //!< SPI Slave Select when Slave: Software controlled


/*----- SPI Control Codes: Miscellaneous Controls  -----*/
#define EDAL_SPI_SET_BUS_SPEED              (0x10UL << EDAL_SPI_CONTROL_Pos)     //!< Set Bus Speed in bps; arg = value
#define EDAL_SPI_GET_BUS_SPEED              (0x11UL << EDAL_SPI_CONTROL_Pos)     //!< Get Bus Speed in bps
#define EDAL_SPI_SET_DEFAULT_TX_VALUE       (0x12UL << EDAL_SPI_CONTROL_Pos)     //!< Set default Transmit value; arg = value
#define EDAL_SPI_CONTROL_SS                 (0x13UL << EDAL_SPI_CONTROL_Pos)     //!< Control Slave Select; arg: 0=inactive, 1=active 
#define EDAL_SPI_ABORT_TRANSFER             (0x14UL << EDAL_SPI_CONTROL_Pos)     //!< Abort current data transfer


/****** SPI Slave Select Signal definitions *****/
#define EDAL_SPI_SS_INACTIVE                 0UL                                 //!< SPI Slave Select Signal Inactive
#define EDAL_SPI_SS_ACTIVE                   1UL                                 //!< SPI Slave Select Signal Active


/****** SPI specific error codes *****/
#define EDAL_SPI_ERROR_MODE                 (EDAL_DRIVER_ERROR_SPECIFIC - 1)     //!< Specified Mode not supported
#define EDAL_SPI_ERROR_FRAME_FORMAT         (EDAL_DRIVER_ERROR_SPECIFIC - 2)     //!< Specified Frame Format not supported
#define EDAL_SPI_ERROR_DATA_BITS            (EDAL_DRIVER_ERROR_SPECIFIC - 3)     //!< Specified number of Data bits not supported
#define EDAL_SPI_ERROR_BIT_ORDER            (EDAL_DRIVER_ERROR_SPECIFIC - 4)     //!< Specified Bit order not supported
#define EDAL_SPI_ERROR_SS_MODE              (EDAL_DRIVER_ERROR_SPECIFIC - 5)     //!< Specified Slave Select Mode not supported

/****** SPI Event *****/
#define EDAL_SPI_EVENT_TRANSFER_COMPLETE    (1UL << 0)  //!< Data Transfer completed
#define EDAL_SPI_EVENT_DATA_LOST            (1UL << 1)  //!< Data lost: Receive overflow / Transmit underflow
#define EDAL_SPI_EVENT_MODE_FAULT           (1UL << 2)  //!< Master Mode Fault (SS deactivated when Master)

/*============================ TYPES =========================================*/
/**
\brief SPI Status
*/
typedef struct _EDAL_SPI_STATUS {
  uint32_t busy       : 1;              //!< Transmitter/Receiver busy flag
  uint32_t data_lost  : 1;              //!< Data lost: Receive overflow / Transmit underflow (cleared on start of transfer operation)
  uint32_t mode_fault : 1;              //!< Mode fault detected; optional (cleared on start of transfer operation)
  uint32_t reserved   : 29;
} EDAL_SPI_STATUS;

typedef void (*EDAL_SPI_SignalEvent_t) (uint32_t event);



/**
 * \brief SPI Driver Capabilities.
 */
typedef struct _EDAL_SPI_CAPABILITIES {
    uint32_t simplex          : 1;      //!< supports Simplex Mode (Master and Slave) @deprecated Reserved (must be zero)
    uint32_t ti_ssi           : 1;      //!< supports TI Synchronous Serial Interface
    uint32_t microwire        : 1;      //!< supports Microwire Interface
    uint32_t event_mode_fault : 1;      //!< Signal Mode Fault event: \ref EDAL_SPI_EVENT_MODE_FAULT
    uint32_t reserved         : 28;     //!< Reserved (must be zero)
} EDAL_SPI_CAPABILITIES;


/**
 * \brief Access structure of the SPI Driver.
 */
typedef struct _EDAL_DRIVER_SPI {
    EDAL_VERSION            (*GetVersion)       (void);
    EDAL_SPI_CAPABILITIES   (*GetCapabilities)  (void);
    int32_t                 (*Initialize)       (EDAL_SPI_SignalEvent_t cb_event);
    int32_t                 (*Uninitialize)     (void);
    int32_t                 (*PowerControl)     (EDAL_POWER_STATE state);
    int32_t                 (*Send)             (const void *data, uint32_t num);
    int32_t                 (*Receive)          (      void *data, uint32_t num);
    int32_t                 (*Transfer)         (const void *data_out,
                                                       void *data_in,
                                                 uint32_t    num);
    uint32_t                (*GetDataCount)     (void);
    int32_t                 (*Control)          (uint32_t control, uint32_t arg);
    EDAL_SPI_STATUS         (*GetStatus)        (void);
} const EDAL_DRIVER_SPI;

/*============================ END ===========================================*/
#ifdef   __cplusplus
}
#endif
#endif /* __DRIVER_SPI_H__ */
