/*
 * regs_io_mux.h
 *
 *  Created on: 14/04/2025
 *      Author: Diogo
 */

#ifndef COMPONENTS_MYHWMAP_REGS_IO_MUX_H_
#define COMPONENTS_MYHWMAP_REGS_IO_MUX_H_

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

#define IO_MUX_MCU_SEL_MASK                     (0X07 << 12)
#define IO_MUX_FUN_DRV_MASK                     (0X03 << 10)
#define IO_MUX_FUN_IE_MASK                      (0X01 << 9)
#define IO_MUX_FUN_WPU_MASK                     (0X01 << 8)
#define IO_MUX_FUN_WPD_MASK                     (0X01 << 7)
#define IO_MUX_MCU_DRV_MASK                     (0X03 << 5)
#define IO_MUX_MCU_IE_MASK                      (0X01 << 4)
#define IO_MUX_MCU_WPU_MASK                     (0X01 << 3)
#define IO_MUX_MCU_WPD_MASK                     (0X01 << 2)
#define IO_MUX_SLP_SEL_MASK                     (0X01 << 1)
#define IO_MUX_MCU_OE_MASK                      (0X01 << 0)

#define IO_MUX_BASE                             0x3FF49000
#define IO_MUX_REG_SIZE                         32

typedef struct {
    __IO uint32_t PIN_CTRL;         /*!< 0x00 - GPIO pin control register         (R/W) */
    __IO uint32_t GPIO36;           /*!< 0x04 - GPIO36 configuration register     (R/W) */
    __IO uint32_t GPIO37;           /*!< 0x08 - GPIO37 configuration register     (R/W) */
    __IO uint32_t GPIO38;           /*!< 0x0C - GPIO38 configuration register     (R/W) */
    __IO uint32_t GPIO39;           /*!< 0x10 - GPIO39 configuration register     (R/W) */
    __IO uint32_t GPIO34;           /*!< 0x14 - GPIO34 configuration register     (R/W) */
    __IO uint32_t GPIO35;           /*!< 0x18 - GPIO35 configuration register     (R/W) */
    __IO uint32_t GPIO32;           /*!< 0x1C - GPIO32 configuration register     (R/W) */
    __IO uint32_t GPIO33;           /*!< 0x20 - GPIO33 configuration register     (R/W) */
    __IO uint32_t GPIO25;           /*!< 0x24 - GPIO25 configuration register     (R/W) */
    __IO uint32_t GPIO26;           /*!< 0x28 - GPIO26 configuration register     (R/W) */
    __IO uint32_t GPIO27;           /*!< 0x2C - GPIO27 configuration register     (R/W) */
    __IO uint32_t MTMS;             /*!< 0x30 - MTMS configuration register       (R/W) */
    __IO uint32_t MTDI;             /*!< 0x34 - MTDI configuration register       (R/W) */
    __IO uint32_t MTCK;             /*!< 0x38 - MTCK configuration register       (R/W) */
    __IO uint32_t MTDO;             /*!< 0x3C - MTDO configuration register       (R/W) */
    __IO uint32_t GPIO2;            /*!< 0x40 - GPIO2 configuration register      (R/W) */
    __IO uint32_t GPIO0;            /*!< 0x44 - GPIO0 configuration register      (R/W) */
    __IO uint32_t GPIO4;            /*!< 0x48 - GPIO4 configuration register      (R/W) */
    __IO uint32_t GPIO16;           /*!< 0x4C - GPIO16 configuration register     (R/W) */
    __IO uint32_t GPIO17;           /*!< 0x50 - GPIO17 configuration register     (R/W) */
    __IO uint32_t SD_DATA2;         /*!< 0x54 - SD_DATA2 configuration register   (R/W) */
    __IO uint32_t SD_DATA3;         /*!< 0x58 - SD_DATA3 configuration register   (R/W) */
    __IO uint32_t SD_CMD;           /*!< 0x5C - SD_CMD configuration register     (R/W) */
    __IO uint32_t SD_CLK;           /*!< 0x60 - SD_CLK configuration register     (R/W) */
    __IO uint32_t SD_DATA0;         /*!< 0x64 - SD_DATA0 configuration register   (R/W) */
    __IO uint32_t SD_DATA1;         /*!< 0x68 - SD_DATA1 configuration register   (R/W) */
    __IO uint32_t GPIO5;            /*!< 0x6C - GPIO5 configuration register      (R/W) */
    __IO uint32_t GPIO18;           /*!< 0x70 - GPIO18 configuration register     (R/W) */
    __IO uint32_t GPIO19;           /*!< 0x74 - GPIO19 configuration register     (R/W) */
         uint32_t RESERVED1;        /*!< 0x78 - Reserved (GPIO20 is only available for ESP32-PICO-V3 and ESP32-PICO-V3-02.)*/
    __IO uint32_t GPIO21;           /*!< 0x7C - GPIO21 configuration register     (R/W) */
    __IO uint32_t GPIO22;           /*!< 0x80 - GPIO22 configuration register     (R/W) */
    __IO uint32_t U0RXD;            /*!< 0x84 - U0RXD configuration register      (R/W) */
    __IO uint32_t U0TXD;            /*!< 0x88 - U0TXD configuration register      (R/W) */
    __IO uint32_t GPIO23;           /*!< 0x8C - GPIO23 configuration register     (R/W) */
} IO_MUX_Type;

#define IO_MUX ((IO_MUX_Type *) IO_MUX_BASE)

#endif /* COMPONENTS_MYHWMAP_REGS_IO_MUX_H_ */
