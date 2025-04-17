/*
 * regs_rtc_io_mux.h
 *
 *  Created on: Apr 14, 2025
 *      Author: diogo
 */

#ifndef COMPONENTS_MYHWMAP_REGS_RTC_IO_MUX_H_
#define COMPONENTS_MYHWMAP_REGS_RTC_IO_MUX_H_

/* IO definitions (access restrictions to peripheral registers) */
/**
    \defgroup CMSIS_glob_defs CMSIS Global Defines

    <strong>IO Type Qualifiers</strong> are used
    \li to specify the access to peripheral variables.
    \li for automatic generation of peripheral register debug information.
*/
#include <stdint.h>

#ifdef __cplusplus
    #define   __I     volatile             /*!< Defines 'read only' permissions                 */
#else
    #define   __I     volatile const       /*!< Defines 'read only' permissions                 */
#endif
#define     __O     volatile             /*!< Defines 'write only' permissions                */
#define     __IO    volatile             /*!< Defines 'read / write' permissions              */

#define RTC_IO_MUX_BASE                         0x3FF48000
#define RTC_IO_MUX_REG_START_BASE               RTC_IO_MUX_BASE + 0x0400
#define RTC_IO_MUX_REG_SIZE                     32

typedef struct {
    //GPIO configuration / data registers
    __IO uint32_t RTCIO_RTC_GPIO_OUT;
    __O  uint32_t RTCIO_RTC_GPIO_OUT_W1TS;
    __O  uint32_t RTCIO_RTC_GPIO_OUT_W1TC;
    __IO uint32_t RTCIO_RTC_GPIO_ENABLE;
    __O  uint32_t RTCIO_RTC_GPIO_ENABLE_W1TS;
    __O  uint32_t RTCIO_RTC_GPIO_ENABLE_W1TC;
    __O  uint32_t RTCIO_RTC_GPIO_STATUS;
    __O  uint32_t RTCIO_RTC_GPIO_STATUS_W1TS;
    __O  uint32_t RTCIO_RTC_GPIO_STATUS_W1TC;
    __I  uint32_t RTCIO_RTC_GPIO_IN;
    __IO uint32_t RTCIO_RTC_GPIO_PIN0;
    __IO uint32_t RTCIO_RTC_GPIO_PIN1;
    __IO uint32_t RTCIO_RTC_GPIO_PIN2;
    __IO uint32_t RTCIO_RTC_GPIO_PIN3;
    __IO uint32_t RTCIO_RTC_GPIO_PIN4;
    __IO uint32_t RTCIO_RTC_GPIO_PIN5;
    __IO uint32_t RTCIO_RTC_GPIO_PIN6;
    __IO uint32_t RTCIO_RTC_GPIO_PIN7;
    __IO uint32_t RTCIO_RTC_GPIO_PIN8;
    __IO uint32_t RTCIO_RTC_GPIO_PIN9;
    __IO uint32_t RTCIO_RTC_GPIO_PIN10;
    __IO uint32_t RTCIO_RTC_GPIO_PIN11;
    __IO uint32_t RTCIO_RTC_GPIO_PIN12;
    __IO uint32_t RTCIO_RTC_GPIO_PIN13;
    __IO uint32_t RTCIO_RTC_GPIO_PIN14;
    __IO uint32_t RTCIO_RTC_GPIO_PIN15;
    __IO uint32_t RTCIO_RTC_GPIO_PIN16;
    __IO uint32_t RTCIO_RTC_GPIO_PIN17;
         uint32_t RESERVED0;
    __IO uint32_t RTCIO_DIG_PAD_HOLD;

    //GPIO RTC function configuration registers
         uint32_t RESERVED1;
    __IO uint32_t RTCIO_SENSOR_PADS;
    __IO uint32_t RTCIO_ADC_PAD;
    __IO uint32_t RTCIO_PAD_DAC1;
    __IO uint32_t RTCIO_PAD_DAC2;
    __IO uint32_t RTCIO_XTAL_32K_PAD;
    __IO uint32_t RTCIO_TOUCH_CFG;
    __IO uint32_t RTCIO_TOUCH_PAD0;
    __IO uint32_t RTCIO_TOUCH_PAD1;
    __IO uint32_t RTCIO_TOUCH_PAD2;
    __IO uint32_t RTCIO_TOUCH_PAD3;
    __IO uint32_t RTCIO_TOUCH_PAD4;
    __IO uint32_t RTCIO_TOUCH_PAD5;
    __IO uint32_t RTCIO_TOUCH_PAD6;
    __IO uint32_t RTCIO_TOUCH_PAD7;
    __IO uint32_t RTCIO_TOUCH_PAD8;
    __IO uint32_t RTCIO_TOUCH_PAD9;
    __IO uint32_t RTCIO_EXT_WAKEUP0;
    __IO uint32_t RTCIO_XTL_EXT_CTR;
    __IO uint32_t RTCIO_SAR_12C_IO;
} RTC_IO_MUX_Type;

#define RTC_IO_MUX ((RTC_IO_MUX_Type *) RTC_IO_MUX_REG_START_BASE)

#endif /* COMPONENTS_MYHWMAP_REGS_RTC_IO_MUX_H_ */
