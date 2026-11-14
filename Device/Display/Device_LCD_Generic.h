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

#ifndef __DEVICE_LCD_GENERIC_H__
#define __DEVICE_LCD_GENERIC_H__

/*============================ INCLUDES ======================================*/

#ifdef   __cplusplus
extern "C" {
#endif
/*============================ MACROS ========================================*/
/* MIPI DCS (Display Command Set) v1.02.00 User Command Set */
#define EDAL_LCD_CMD_NOP                    0x00    /* No Operation */
#define EDAL_LCD_CMD_SOFT_RESET             0x01    /* Software Reset */
#define EDAL_LCD_CMD_GET_POWER_MODE         0x0A    /* Get the current power mode */
#define EDAL_LCD_CMD_GET_ADDRESS_MODE       0x0B    /* Get the data order for transfers from the Host to the display module and from the frame memory to the display device */
#define EDAL_LCD_CMD_GET_PIXEL_FORMAT       0x0C    /* Get the current pixel format */
#define EDAL_LCD_CMD_GET_DISPLAY_MODE       0x0D    /* Get the current display mode from the peripheral */
#define EDAL_LCD_CMD_GET_SIGNAL_MODE        0x0E    /* Get display module signaling mode */
#define EDAL_LCD_CMD_GET_DIAGNOSTIC_RESULT  0x0F    /* Get Peripheral Self-Diagnostic Result */
#define EDAL_LCD_CMD_ENTER_SLEEP_MODE       0x10    /* Power for the display panel is off */
#define EDAL_LCD_CMD_EXIT_SLEEP_MODE        0x11    /* Power for the display panel is on */
#define EDAL_LCD_CMD_ENTER_PARTIAL_MODE     0x12    /* Part of the display area is used for image display */
#define EDAL_LCD_CMD_ENTER_NORMAL_MODE      0x13    /* The whole display area is used for image display */
#define EDAL_LCD_CMD_EXIT_INVERT_MODE       0x20    /* Displayed image colors are not inverted */
#define EDAL_LCD_CMD_ENTER_INVERT_MODE      0x21    /* Displayed image colors are inverted */
#define EDAL_LCD_CMD_SET_GAMMA_CURVE        0x26    /* Selects the gamma curve used by the display device */
#define EDAL_LCD_CMD_SET_DISPLAY_OFF        0x28    /* Blanks the display device */
#define EDAL_LCD_CMD_SET_DISPLAY_ON         0x29    /* Show the image on the display device */
#define EDAL_LCD_CMD_SET_COLUMN_ADDRESS     0x2A    /* Set the column extent */
#define EDAL_LCD_CMD_SET_PAGE_ADDRESS       0x2B    /* Set the page extent */
#define EDAL_LCD_CMD_WRITE_MEMORY_START     0x2C    /* Transfer image data from the Host Processor to the peripheral starting at the location provided by set_column_address and set_page_address */
#define EDAL_LCD_CMD_READ_MEMORY_START      0x2E    /* Transfer image data from the peripheral to the Host Processor interface starting at the location provided by set_column_address and set_page_address */
#define EDAL_LCD_CMD_SET_PARTIAL_ROWS       0x30    /* Defines the number of rows in the partial display area on the display device */
#define EDAL_LCD_CMD_SET_PARTIAL_COLUMNS    0x31    /* Defines the number of columns in the partial display area on the display device */
#define EDAL_LCD_CMD_SET_SCROLL_AREA        0x33    /* Defines the vertical scrolling and fixed area on display device */
#define EDAL_LCD_CMD_SET_TEAR_OFF           0x34    /* Synchronization information is not sent from the display module to the host processor */
#define EDAL_LCD_CMD_SET_TEAR_ON            0x35    /* Synchronization information is sent from the display module to the host processor at the start of VFP */
#define EDAL_LCD_CMD_SET_ADDRESS_MODE       0x36    /* Set the data order for transfers from the Host to the display module and from the frame memory to the display device */
#define EDAL_LCD_CMD_SET_SCROLL_START       0x37    /* Defines the vertical scrolling starting point */
#define EDAL_LCD_CMD_EXIT_IDLE_MODE         0x38    /* Full color depth is used on the display panel */
#define EDAL_LCD_CMD_ENTER_IDLE_MODE        0x39    /* Reduced color depth is used on the display panel */
#define EDAL_LCD_CMD_SET_PIXEL_FORMAT       0x3A    /* Defines how many bits per pixel are used in the interface */
#define EDAL_LCD_CMD_WRITE_MEMORY_CONTINUE  0x3C    /* Transfer image information from the Host Processor interface to the peripheral from the last written location */
#define EDAL_LCD_CMD_READ_MEMORY_CONTINUE   0x3E    /* Read image data from the peripheral continuing after the last read_memory_continue or read_memory_start */
#define EDAL_LCD_CMD_SET_TEAR_SCANLINE      0x44    /* Synchronization information is sent from the display module to the host processor when the display device refresh reaches the provided scanline */
#define EDAL_LCD_CMD_GET_SCANLINE           0x45    /* Get the current scanline */
#define EDAL_LCD_CMD_READ_DDB_CONTINUE      0xA8    /* Continue reading the DDB from the last read location */
#define EDAL_LCD_CMD_READ_DDB_START         0xA1    /* Read the DDB from the provided location */

/* address mode flag masks */
#define EDAL_LCD_MASK_FLIP_VERTICAL                     (1 << 0)    /* This bit flips the image shown on the display device top to bottom. No change is made to the frame memory */
#define EDAL_LCD_MASK_FLIP_HORIZONTAL                   (1 << 1)    /* This bit flips the image shown on the display device left to right. No change is made to the frame memory */
#define EDAL_LCD_MASK_DATA_LATCH_DATA_ORDER             (1 << 2)    /* Display Data Latch Order */
#define EDAL_LCD_MASK_RGB_ORDER                         (1 << 3)    /* RGB/BGR Order */
#define EDAL_LCD_MASK_LINE_ADDRESS_ORDER                (1 << 4)    /* Line Address Order */
#define EDAL_LCD_MASK_PAGE_COLUMN_ORDER                 (1 << 5)    /* Page/Column Order */
#define EDAL_LCD_MASK_COLUMN_ADDRESS_ORDER              (1 << 6)    /* Column Address Order */
#define EDAL_LCD_MASK_PAGE_ADDRESS_ORDER                (1 << 7)    /* Page Address Order */

#define EDAL_LCD_BIT_FLIP_VERTICAL__NOT_FLIPPED         0
#define EDAL_LCD_BIT_FLIP_VERTICAL__FLIPPED             EDAL_LCD_MASK_FLIP_VERTICAL             /* This bit flips the image shown on the display device top to bottom. No change is made to the frame memory */
#define EDAL_LCD_BIT_FLIP_HORIZONTAL__NOT_FLIPPED       0
#define EDAL_LCD_BIT_FLIP_HORIZONTAL__FLIPPED           EDAL_LCD_MASK_FLIP_HORIZONTAL           /* This bit flips the image shown on the display device left to right. No change is made to the frame memory */
#define EDAL_LCD_BIT_DATA_LATCH_DATA_ORDER__LTOR        0                                       /* Display Data Latch Order: LCD Refresh Left to Right */
#define EDAL_LCD_BIT_DATA_LATCH_DATA_ORDER__RTOL        EDAL_LCD_MASK_DATA_LATCH_DATA_ORDER     /* Display Data Latch Order: LCD Refresh Right to Left */
#define EDAL_LCD_BIT_RGB_ORDER__RGB                     0                                       /* RGB/BGR Order: RGB */
#define EDAL_LCD_BIT_RGB_ORDER__BGR                     EDAL_LCD_MASK_RGB_ORDER                 /* RGB/BGR Order: BGR */
#define EDAL_LCD_BIT_LINE_ADDRESS_ORDER__TTOB           0                                       /* Line Address Order: LCD Refresh Top to Bottom */
#define EDAL_LCD_BIT_LINE_ADDRESS_ORDER__BTOT           EDAL_LCD_MASK_LINE_ADDRESS_ORDER        /* Line Address Order: LCD Refresh Bottom to Top */
#define EDAL_LCD_BIT_PAGE_COLUMN_ORDER__NORMAL          0                                       /* Page/Column Order: Normal Mode */
#define EDAL_LCD_BIT_PAGE_COLUMN_ORDER__REVERSE         EDAL_LCD_MASK_PAGE_COLUMN_ORDER         /* Page/Column Order: Reverse Mode */
#define EDAL_LCD_BIT_COLUMN_ADDRESS_ORDER__LTOR         0                                       /* Column Address Order: Left to Right */
#define EDAL_LCD_BIT_COLUMN_ADDRESS_ORDER__RTOL         EDAL_LCD_MASK_COLUMN_ADDRESS_ORDER      /* Column Address Order: Right to Left */
#define EDAL_LCD_BIT_PAGE_ADDRESS_ORDER__TTOB           0                                       /* Page Address Order: Top to Bottom */
#define EDAL_LCD_BIT_PAGE_ADDRESS_ORDER__BTOT           EDAL_LCD_MASK_PAGE_ADDRESS_ORDER        /* Page Address Order: Bottom to Top */

/* predefined gamma curves */
#define EDAL_LCD_GAMMA_2_2                              0x01    /* 2.2 */
#define EDAL_LCD_GAMMA_1_8                              0x02    /* 1.8 */
#define EDAL_LCD_GAMMA_2_5                              0x04    /* 2.5 */
#define EDAL_LCD_GAMMA_1_0                              0x08    /* 1.0 */

/* common pixel formats */
#define EDAL_LCD_PIXEL_FORMAT_RGB565                    0x55    /* bus: 16 bits, pixel: 16 bits */
#define EDAL_LCD_PIXEL_FORMAT_RGB666                    0x66    /* bus: 18 bits, pixel: 18 bits */

/* flags for edal_lcd_xxx_create() */
#define EDAL_LCD_FLAG_NONE                              0x00000000UL
#define EDAL_LCD_FLAG_MIRROR_X                          0x00000001UL
#define EDAL_LCD_FLAG_MIRROR_Y                          0x00000002UL
#define EDAL_LCD_FLAG_BGR                               0x00000008UL
#define EDAL_LCD_FLAG_RGB666                            0x00000010UL

/* command list */
#define EDAL_LCD_CMD_DELAY_MS                           0xff
#define EDAL_LCD_CMD_EOF                                0xff

/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/
/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/
/*============================ IMPLEMENTATION ================================*/
/*============================ END ===========================================*/
#ifdef   __cplusplus
}
#endif
#endif /* __DEVICE_LCD_GENERIC_H__ */
