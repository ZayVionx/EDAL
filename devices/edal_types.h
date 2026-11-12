#ifndef __EDAL_TYPES_H__
#define __EDAL_TYPES_H__

/*============================ INCLUDES ======================================*/

#ifdef   __cplusplus
extern "C" {
#endif
/*============================ MACROS ========================================*/
/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/

typedef enum {
    EDAL_STATUS_OK = 0,                          //!< Operation succeeded.
    EDAL_STATUS_ERROR,                           //!< Operation failed.
    EDAL_STATUS_INVALID_ARG,                     //!< Invalid argument.
    EDAL_STATUS_NOT_READY,                       //!< Device is not ready.
    EDAL_STATUS_NOT_SUPPORTED                    //!< Operation is not supported.
} EDAL_Status_t;

typedef enum {
    EDAL_DEVICE_UNINITIALIZED = 0,               //!< Device is not initialized.
    EDAL_DEVICE_READY                            //!< Device is initialized and ready.
} EDAL_DeviceState_t;

/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/
/*============================ IMPLEMENTATION ================================*/
/*============================ END ===========================================*/
#ifdef   __cplusplus
}
#endif
#endif /* __EDAL_TYPES_H__ */

