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
#include "EDAL_Common.h"

#ifdef   __cplusplus
extern "C" {
#endif
/*============================ MACROS ========================================*/
#define EDAL_I2C_API_VERSION    EDAL_VERSION_MAJOR_MINOR(1, 0)  /* API version */


#define _EDAL_Driver_I2C_(n)          Driver_I2C##n
#define  EDAL_Driver_I2C_(n)    _EDAL_Driver_I2C_(n)


/****** I2C Control Codes *****/

#define EDAL_I2C_OWN_ADDRESS                (0x01UL)    //!< Set Own Slave Address; arg = address
#define EDAL_I2C_BUS_SPEED                  (0x02UL)    //!< Set Bus Speed; arg = speed
#define EDAL_I2C_BUS_CLEAR                  (0x03UL)    //!< Execute Bus clear: send nine clock pulses
#define EDAL_I2C_ABORT_TRANSFER             (0x04UL)    //!< Abort Master/Slave Transmit/Receive

/*----- I2C Bus Speed -----*/
#define EDAL_I2C_BUS_SPEED_STANDARD         (0x01UL)    //!< Standard Speed (100kHz)
#define EDAL_I2C_BUS_SPEED_FAST             (0x02UL)    //!< Fast Speed     (400kHz)
#define EDAL_I2C_BUS_SPEED_FAST_PLUS        (0x03UL)    //!< Fast+ Speed    (  1MHz)
#define EDAL_I2C_BUS_SPEED_HIGH             (0x04UL)    //!< High Speed     (3.4MHz)


/****** I2C Address Flags *****/

#define EDAL_I2C_ADDRESS_10BIT              (0x0400UL)  //!< 10-bit address flag
#define EDAL_I2C_ADDRESS_GC                 (0x8000UL)  //!< General Call flag


/****** I2C Event *****/
#define EDAL_I2C_EVENT_TRANSFER_DONE        (1UL << 0)  //!< Master/Slave Transmit/Receive finished
#define EDAL_I2C_EVENT_TRANSFER_INCOMPLETE  (1UL << 1)  //!< Master/Slave Transmit/Receive incomplete transfer
#define EDAL_I2C_EVENT_SLAVE_TRANSMIT       (1UL << 2)  //!< Addressed as Slave Transmitter but transmit operation is not set.
#define EDAL_I2C_EVENT_SLAVE_RECEIVE        (1UL << 3)  //!< Addressed as Slave Receiver but receive operation is not set.
#define EDAL_I2C_EVENT_ADDRESS_NACK         (1UL << 4)  //!< Address not acknowledged from Slave
#define EDAL_I2C_EVENT_GENERAL_CALL         (1UL << 5)  //!< Slave addressed with general call address
#define EDAL_I2C_EVENT_ARBITRATION_LOST     (1UL << 6)  //!< Master lost arbitration
#define EDAL_I2C_EVENT_BUS_ERROR            (1UL << 7)  //!< Bus error detected (START/STOP at illegal position)
#define EDAL_I2C_EVENT_BUS_CLEAR            (1UL << 8)  //!< Bus clear finished

/*============================ TYPES =========================================*/

typedef struct _EDAL_I2C_STATUS {
    uint32_t busy               : 1;        //!< Busy flag
    uint32_t mode               : 1;        //!< Mode: 0=Slave, 1=Master
    uint32_t direction          : 1;        //!< Direction: 0=Transmitter, 1=Receiver
    uint32_t general_call       : 1;        //!< General Call indication (cleared on start of next Slave operation)
    uint32_t arbitration_lost   : 1;        //!< Master lost arbitration (cleared on start of next Master operation)
    uint32_t bus_error          : 1;        //!< Bus error detected (cleared on start of next Master/Slave operation)
    uint32_t reserved           : 26;       //!< Reserved (must be zero)
} EDAL_I2C_STATUS;


// Function documentation
/**
 * \fn          EDAL_VERSION EDAL_I2C_GetVersion (void)
 * \brief       Get driver version.
 * \return      \ref EDAL_VERSON
 * 
 * \fn          EDAL_I2C_CAPABILITIES EDAL_I2C_GetCapabilities (void)
 * \brief       Get driver capabilities.
 * \return      \ref EDAL_I2C_CAPABILITIES
 * 
 * \fn          int32_t EDAL_I2C_Initialize (EDAL_I2C_SignalEvent_t cb_event)
 * \brief       Initialize I2C Interface.
 * \param[in]   cb_event  Pointer to \ref EDAL_I2C_SignalEvent
 * \return      \ref execution_status
 * 
 * \fn          int32_t EDAL_I2C_Uninitialize (void)
 * \brief       De-initialize I2C Interface.
 * \return      \ref execution_status
 * 
 * \fn          int32_t EDAL_I2C_PowerControl (EDAL_POWER_STATE state)
 * \brief       Control I2C Interface Power.
 * \param[in]   state  Power state
 * \return      \ref execution_status
 * 
 * \fn          int32_t EDAL_I2C_MasterTransmit (uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending)
 * \brief       Start transmitting data as I2C Master.
 * \param[in]   addr          Slave address (7-bit or 10-bit)
 * \param[in]   data          Pointer to buffer with data to transmit to I2C Slave
 * \param[in]   num           Number of data bytes to transmit
 * \param[in]   xfer_pending  Transfer operation is pending - Stop condition will not be generated
 * \return      \ref execution_status
 * 
 * \fn          int32_t EDAL_I2C_MasterReceive (uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending)
 * \brief       Start receiving data as I2C Master.
 * \param[in]   addr          Slave address (7-bit or 10-bit)
 * \param[out]  data          Pointer to buffer for data to receive from I2C Slave
 * \param[in]   num           Number of data bytes to receive
 * \param[in]   xfer_pending  Transfer operation is pending - Stop condition will not be generated
 * \return      \ref execution_status
 * 
 * \fn          int32_t EDAL_I2C_SlaveTransmit (const uint8_t *data, uint32_t num)
 * \brief       Start transmitting data as I2C Slave.
 * \param[in]   data  Pointer to buffer with data to transmit to I2C Master
 * \param[in]   num   Number of data bytes to transmit
 * \return      \ref execution_status
 * 
 * \fn          int32_t EDAL_I2C_SlaveReceive (uint8_t *data, uint32_t num)
 * \brief       Start receiving data as I2C Slave.
 * \param[out]  data  Pointer to buffer for data to receive from I2C Master
 * \param[in]   num   Number of data bytes to receive
 * \return      \ref execution_status
 * 
 * \fn          int32_t EDAL_I2C_GetDataCount (void)
 * \brief       Get transferred data count.
 * \return      number of data bytes transferred; -1 when Slave is not addressed by Master
 * 
 * \fn          int32_t EDAL_I2C_Control (uint32_t control, uint32_t arg)
 * \brief       Control I2C Interface.
 * \param[in]   control  Operation
 * \param[in]   arg      Argument of operation (optional)
 * \return      \ref execution_status
 * 
 * \fn          EDAL_I2C_STATUS EDAL_I2C_GetStatus (void)
 * \brief       Get I2C status.
 * \return      I2C status \ref EDAL_I2C_STATUS
 * 
 * \fn          void EDAL_I2C_SignalEvent (uint32_t event)
 * \brief       Signal I2C Events.
 * \param[in]   event  \ref I2C_events notification mask
 */

typedef void (*EDAL_I2C_SignalEvent_t) (uint32_t event);


/**
 * \brief I2C Driver Capabilities.
 */
typedef struct _EDAL_I2C_CAPABILITIES {
    uint32_t address_10_bit : 1;        //!< supports 10-bit addressing
    uint32_t reserved       : 31;       //!< Reserved (must be zero)
} EDAL_I2C_CAPABILITIES;

/**
 * \brief Access structure of the I2C Driver.
 */
typedef struct _EDAL_DRIVER_I2C {
    EDAL_VERSION            (*GetVersion)       (void);
    EDAL_I2C_CAPABILITIES   (*GetCapabilities)  (void);
    int32_t                 (*Initialize)       (EDAL_I2C_SignalEvent_t cb_event);
    int32_t                 (*Uninitialize)     (void);
    int32_t                 (*PowerControl)     (EDAL_POWER_STATE state);
    int32_t                 (*MasterTransmit)   (uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending);
    int32_t                 (*MasterReceive)    (uint32_t addr,       uint8_t *data, uint32_t num, bool xfer_pending);
    int32_t                 (*SlaveTransmit)    (               const uint8_t *data, uint32_t num);
    int32_t                 (*SlaveReceive)     (                     uint8_t *data, uint32_t num);
    int32_t                 (*GetDataCount)     (void);
    int32_t                 (*Control)          (uint32_t control, uint32_t arg);
    EDAL_I2C_STATUS         (*GetStatus)        (void);
} const EDAL_DRIVER_I2C;

/*============================ END ===========================================*/
#ifdef   __cplusplus
}
#endif
#endif /* __DRIVER_I2C_H__ */
