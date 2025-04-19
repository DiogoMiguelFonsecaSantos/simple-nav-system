/*
 * io_mux.h
 *
 *  Created on: 13/04/2025
 *      Author: Diogo
 */

#ifndef COMPONENTS_MYHAL_INC_IO_MUX_H_
#define COMPONENTS_MYHAL_INC_IO_MUX_H_

#include <stdint.h>
#include <stdbool.h>
#include "regs_io_mux.h"
#include "regs_gpio_matrix.h"

typedef enum{

    GPIO0 = 0,
    U0TXD = 1,
    GPIO2 = 2,
    U0RXD = 3,
    GPIO4 = 4,
    GPIO5 = 5,
    SD_CLK = 6,
    SD_DATA0 = 7,
    SD_DATA1 = 8,
    SD_DATA2 = 9,
    SD_DATA3 = 10,
    SD_CMD = 11,
    MTDI = 12,
    MTCK = 13,
    MTMS = 14,
    MTDO = 15,
    GPIO16 = 16,
    GPIO17 = 17,
    GPIO18 = 18,
    GPIO19 = 19,
    GPIO21 = 21,
    GPIO22 = 22,
    GPIO23 = 23,
    GPIO25 = 25,
    GPIO26 = 26,
    GPIO27 = 27,
    XP_32K = 32,
    XN_32K = 33,
    VDET_1 = 34,
    VDET_2 = 35,
    SENSOR_VP = 36,
    SENSOR_CAPP = 37,
    SENSOR_CAPN = 38,
    SENSOR_VN = 39
}IO_MUX_PINValue;

typedef enum {
    CLK_OUT1 = 0,
    CLK_OUT2 = 1,
    CLK_OUT3 = 2
}IO_MUX_PIN_CTRL_ClockOut;

typedef enum {
    F0_GPIO0 = 0,
    F0_U0TXD = 0,
    F0_GPIO2 = 0,
    F0_U0RXD = 0,
    F0_GPIO4 = 0,
    F0_GPIO5 = 0,
    F0_SD_CLK = 0,
    F0_SD_DATA0 = 0,
    F0_SD_DATA1 = 0,
    F0_SD_DATA2 = 0,
    F0_SD_DATA3 = 0,
    F0_SD_CMD = 0,
    F0_MTDI = 0,
    F0_MTCK = 0,
    F0_MTMS = 0,
    F0_MTDO = 0,
    F0_GPIO16 = 0,
    F0_GPIO17 = 0,
    F0_GPIO18 = 0,
    F0_GPIO19 = 0,
    F0_GPIO21 = 0,
    F0_GPIO22 = 0,
    F0_GPIO23 = 0,
    F0_GPIO25 = 0,
    F0_GPIO26 = 0,
    F0_GPIO27 = 0,
    F0_GPIO32 = 0,
    F0_GPIO33 = 0,
    F0_GPIO34 = 0,
    F0_GPIO35 = 0,
    F0_GPIO36 = 0,
    F0_GPIO37 = 0,
    F0_GPIO38 = 0,
    F0_GPIO39 = 0,
    F1_CLK_OUT1 = 1,
    F1_CLK_OUT3 = 1,
    F1_HSPIWP = 1,
    F1_CLK_OUT2 = 1,
    F1_HSPIHD = 1,
    F1_VSPICS0 = 1,
    F1_SPICLK = 1,
    F1_SPIQ = 1,
    F1_SPID = 1,
    F1_SPIHD = 1,
    F1_SPIWP = 1,
    F1_SPICS0 = 1,
    F1_HSPIQ = 1,
    F1_HSPID = 1,
    F1_HSPICLK = 1,
    F1_HSPICS0 = 1,
    F1_VSPICLK = 1,
    F1_VSPIQ = 1,
    F1_VSPIHD = 1,
    F1_VSPIWP = 1,
    F1_VSPID = 1,
    F2_GPIO = 2,
    F3_HS2_DATA0 = 3,
    F3_HS2_DATA1 = 3,
    F3_HS1_DATA6 = 3,
    F3_HS1_CLK = 3,
    F3_HS1_DATA0 = 3,
    F3_HS1_DATA1 = 3,
    F3_HS1_DATA2 = 3,
    F3_HS1_DATA3 = 3,
    F3_HS1_CMD = 3,
    F3_HS2_DATA2 = 3,
    F3_HS2_DATA3 = 3,
    F3_HS2_CLK = 3,
    F3_HS2_CMD = 3,
    F3_HS1_DATA4 = 3,
    F3_HS1_DATA5 = 3,
    F3_HS1_DATA7 = 3,
    F3_U0CTS = 3,
    F3_U0RTS = 3,
    F3_HS1_STROBE = 3,
    F4_SD_DATA0 = 4,
    F4_SD_DATA1 = 4,
    F4_U1CTS = 4,
    F4_U2RTS = 4,
    F4_U2CTS = 4,
    F4_U1RXD = 4,
    F4_U1TXD = 4,
    F4_U1RTS = 4,
    F4_SD_DATA2 = 4,
    F4_SD_DATA3 = 4,
    F4_SD_CLK = 4,
    F4_SD_CMD = 4,
    F4_U2RXD = 4,
    F4_U2TXD = 4,
    F5_EMAC_TX_CLK = 5,
    F5_EMAC_RXD2 = 5,
    F5_EMAC_TX_ER = 5,
    F5_EMAC_RX_CLK = 5,
    F5_EMAC_TXD3 = 5,
    F5_EMAC_RX_ER = 5,
    F5_EMAC_TXD2 = 5,
    F5_EMAC_RXD3 = 5,
    F5_EMAC_CLK_OUT = 5,
    F5_EMAC_CLK_180 = 5,
    F5_EMAC_TXD0 = 5,
    F5_EMAC_TX_EN = 5,
    F5_EMAC_TXD1 = 5,
    F5_EMAC_RXD0 = 5,
    F5_EMAC_RXD1 = 5,
    F5_EMAC_RX_DV = 5
}IO_MUX_MCU_SEL_FunctionType;

typedef enum {
    LOWEST = 0,
    LOW = 1,
    MEDIUM = 2,
    HIGH = 3
}IO_MUX_FUN_DRV_StrengthType;

typedef enum {
    IPIN_DIS = 0,
    IPIN_EN = 1
}IO_MUX_FUN_IEnableType;

typedef enum {
    INTPUP_DIS = 0,
    INTPUP_EN = 1
}IO_MUX_FUN_WPU_PinType;

typedef enum {
    INTPDN_DIS = 0,
    INTPDN_EN = 1
}IO_MUX_FUN_WPD_PinType;

typedef enum {
    SLEEP_LOWEST = 0,
    SLEEP_LOW = 1,
    SLEEP_MEDIUM = 2,
    SLEEP_HIGH = 3
}IO_MUX_MCU_DRV_StrengthType;

typedef enum {
    SLEEP_IPIN_DIS = 0,
    SLEEP_IPIN_EN = 1
}IO_MUX_MCU_IEnableType;

typedef enum {
    SLEEP_INTPUP_DIS = 0,
    SLEEP_INTPUP_EN = 1
}IO_MUX_MCU_WPU_PinType;

typedef enum {
    SLEEP_INTPDN_DIS = 0,
    SLEEP_INTPDN_EN = 1
}IO_MUX_MCU_WPD_PinType;

typedef enum {
    AWAKE = 0,
    SLEEP = 1
}IO_MUX_SLP_SELMode;

typedef enum {
    OPIN_DIS = 0,
    OPIN_EN = 1
}IO_MUX_MCU_OEnableType;

void IO_MUX_PIN_CTRL_OutCLK_I2S0(IO_MUX_PIN_CTRL_ClockOut clk_out);
void IO_MUX_PIN_CTRL_OutCLK_I2S1(IO_MUX_PIN_CTRL_ClockOut clk_out);
void IO_MUX_PIN_CTRL_OutCLK_APPL(IO_MUX_PIN_CTRL_ClockOut clk_out);

void IO_MUX_MCU_SEL_FunctionCFG(__IO uint32_t *reg,IO_MUX_MCU_SEL_FunctionType function);
void IO_MUX_FUN_DRV_StrengthCFG(__IO uint32_t *reg,IO_MUX_FUN_DRV_StrengthType strength);
void IO_MUX_FUN_IEnableCFG(__IO uint32_t *reg, IO_MUX_FUN_IEnableType iEnable);
void IO_MUX_FUN_WPU_PinCFG(__IO uint32_t *reg, IO_MUX_FUN_WPU_PinType wpuPin);
void IO_MUX_FUN_WPD_PinCFG(__IO uint32_t *reg, IO_MUX_FUN_WPD_PinType wpdPin);
void IO_MUX_SLP_SELModeCFG(__IO uint32_t *reg, IO_MUX_SLP_SELMode slpSelMode);
void IO_MUX_MCU_DRV_StrengthCFG(__IO uint32_t *reg, IO_MUX_MCU_DRV_StrengthType sleepStrength);
void IO_MUX_MCU_IEnableCFG(__IO uint32_t *reg, IO_MUX_MCU_IEnableType sleepIEnable);
void IO_MUX_MCU_WPU_PinCFG(__IO uint32_t *reg, IO_MUX_MCU_WPU_PinType sleepWpuPin);
void IO_MUX_MCU_WPD_PinCFG(__IO uint32_t *reg, IO_MUX_MCU_WPD_PinType sleepWpdPin);
void IO_MUX_MCU_OEnableCFG(__IO uint32_t *reg, IO_MUX_MCU_OEnableType sleepOEnable);


void IO_MUX_CustomRegisterCFG(__IO uint32_t *reg, IO_MUX_MCU_SEL_FunctionType function, IO_MUX_FUN_DRV_StrengthType strength, 
    IO_MUX_FUN_IEnableType iEnable, IO_MUX_FUN_WPU_PinType wpuPin, IO_MUX_FUN_WPD_PinType wpdPin, 
    IO_MUX_SLP_SELMode slpSelMode, IO_MUX_MCU_DRV_StrengthType sleepStrength, 
    IO_MUX_MCU_IEnableType sleepIEnable, IO_MUX_MCU_WPU_PinType sleepWpuPin, IO_MUX_MCU_WPD_PinType sleepWpdPin, 
    IO_MUX_MCU_OEnableType sleepOEnable);
    __IO uint32_t * IO_MUX_FindRegThroughPinId(uint8_t pinId);

#endif /* COMPONENTS_MYHAL_INC_IO_MUX_H_ */
