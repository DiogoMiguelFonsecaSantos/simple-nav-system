/*
 * gpio_matrix.h
 *
 *  Created on: 13/04/2025
 *      Author: Diogo
 */

#ifndef COMPONENTS_MYHAL_INC_GPIO_MATRIX_H_
#define COMPONENTS_MYHAL_INC_GPIO_MATRIX_H_

#include <stdint.h>
#include <stdbool.h>
#include "regs_gpio_matrix.h"

typedef enum{
    DISABLE = 0,
    WAKEUP = 1
}WakeUPCPUTypeDef;

typedef enum{
    INTDIS = 0,
    RISING = 1,
    FALLING = 2,
    ANY = 3,
    LOWLEVEL = 4,
    HIGHLEVEL = 5
}PINIntTypeDef;

typedef enum{

    NORMAL_PIN = 0,
    OPENDRAIN_PIN = 1
}PINPadDriverTypeDef;

typedef enum{
    IO_MPLEX = 0,
    GPIO_MTX = 1
}SignalInSelectTypeDef;

typedef enum{
    NINV = 0,
    INVERT = 1
}FunctionInInvSelectTypeDef;

typedef enum{
    GPIO_INPUT_PIN0 = 0,   /*!< Select GPIO Matrix input pin 0 */
    GPIO_INPUT_PIN1 = 1,   /*!< Select GPIO Matrix input pin 1 */
    GPIO_INPUT_PIN2 = 2,   /*!< Select GPIO Matrix input pin 2 */
    GPIO_INPUT_PIN3 = 3,   /*!< Select GPIO Matrix input pin 3 */
    GPIO_INPUT_PIN4 = 4,   /*!< Select GPIO Matrix input pin 4 */
    GPIO_INPUT_PIN5 = 5,   /*!< Select GPIO Matrix input pin 5 */
    GPIO_INPUT_PIN6 = 6,   /*!< Select GPIO Matrix input pin 6 */
    GPIO_INPUT_PIN7 = 7,   /*!< Select GPIO Matrix input pin 7 */
    GPIO_INPUT_PIN8 = 8,   /*!< Select GPIO Matrix input pin 8 */
    GPIO_INPUT_PIN9 = 9,   /*!< Select GPIO Matrix input pin 9 */
    GPIO_INPUT_PIN10 = 10, /*!< Select GPIO Matrix input pin 10 */
    GPIO_INPUT_PIN11 = 11, /*!< Select GPIO Matrix input pin 11 */
    GPIO_INPUT_PIN12 = 12, /*!< Select GPIO Matrix input pin 12 */
    GPIO_INPUT_PIN13 = 13, /*!< Select GPIO Matrix input pin 13 */
    GPIO_INPUT_PIN14 = 14, /*!< Select GPIO Matrix input pin 14 */
    GPIO_INPUT_PIN15 = 15, /*!< Select GPIO Matrix input pin 15 */
    GPIO_INPUT_PIN16 = 16, /*!< Select GPIO Matrix input pin 16 */
    GPIO_INPUT_PIN17 = 17, /*!< Select GPIO Matrix input pin 17 */
    GPIO_INPUT_PIN18 = 18, /*!< Select GPIO Matrix input pin 18 */
    GPIO_INPUT_PIN19 = 19, /*!< Select GPIO Matrix input pin 19 */
    GPIO_INPUT_PIN20 = 20, /*!< Select GPIO Matrix input pin 20 */
    GPIO_INPUT_PIN21 = 21, /*!< Select GPIO Matrix input pin 21 */
    GPIO_INPUT_PIN22 = 22, /*!< Select GPIO Matrix input pin 22 */
    GPIO_INPUT_PIN23 = 23, /*!< Select GPIO Matrix input pin 23 */
    GPIO_INPUT_PIN24 = 24, /*!< Select GPIO Matrix input pin 24 */
    GPIO_INPUT_PIN25 = 25, /*!< Select GPIO Matrix input pin 25 */
    GPIO_INPUT_PIN26 = 26, /*!< Select GPIO Matrix input pin 26 */
    GPIO_INPUT_PIN27 = 27, /*!< Select GPIO Matrix input pin 27 */
    GPIO_INPUT_PIN28 = 28, /*!< Select GPIO Matrix input pin 28 */
    GPIO_INPUT_PIN29 = 29, /*!< Select GPIO Matrix input pin 29 */
    GPIO_INPUT_PIN30 = 30, /*!< Select GPIO Matrix input pin 30 */
    GPIO_INPUT_PIN31 = 31, /*!< Select GPIO Matrix input pin 31 */
    GPIO_INPUT_PIN32 = 32, /*!< Select GPIO Matrix input pin 32 */
    GPIO_INPUT_PIN33 = 33, /*!< Select GPIO Matrix input pin 33 */
    GPIO_INPUT_PIN34 = 34, /*!< Select GPIO Matrix input pin 34 */
    GPIO_INPUT_PIN35 = 35, /*!< Select GPIO Matrix input pin 35 */
    GPIO_INPUT_PIN36 = 36, /*!< Select GPIO Matrix input pin 36 */
    GPIO_INPUT_PIN37 = 37, /*!< Select GPIO Matrix input pin 37 */
    GPIO_INPUT_PIN38 = 38, /*!< Select GPIO Matrix input pin 38 */
    GPIO_INPUT_PIN39 = 39, /*!< Select GPIO Matrix input pin 39 */
    GPIO_INPUT_HIGH = 0x38, /*!< Constant high input */
    GPIO_INPUT_LOW = 0x30   /*!< Constant low input */
}FunctionPeriphInputSelectTypeDef;

typedef enum{
    NINV_OUTEN = 0,
    INVERT_OUTEN = 1
}FunctionOEnableInvSelectTypeDef;

typedef enum{
    OEN_PERIPHERAL = 0,
    EN_REGn = 1
}SourceForOutputEnableTypeDef;

typedef enum{
    NINV_OUT = 0,
    INVERT_OUT = 1
}FunctionOutputValInvSelectTypeDef;

void GPIO_OverwriteEnable(uint8_t gpio);
void GPIO_EnableOutput(uint8_t gpio);
void GPIO_DisableOutput(uint8_t gpio);
void GPIO_OverwriteOutput(uint8_t gpio);
void GPIO_SetOutput(uint8_t gpio);
void GPIO_ClearOutput(uint8_t gpio);
bool GPIO_ReadOutput(uint8_t gpio);
bool GPIO_ReadInput(uint8_t gpio);

uint8_t GPIO_GetBootConfig(void);
uint32_t GPIO_GetStatus(void);
uint32_t GPIO_GetStatus1(void);
void GPIO_OverwriteInterruptStatus(uint32_t status);
void GPIO_CLRStatInterruptFlag(uint8_t pin);
void GPIO_SetStatInterruptFlag(uint8_t pin);

uint32_t GPIO_GetAPPCPUInterruptStatus(void);
uint32_t GPIO_GetAPPCPU_NMI_InterruptStatus(void);

uint32_t GPIO_GetPROPCUInterruptStatus(void);
uint32_t GPIO_GetPROPCU_NMI_InterruptStatus(void);

uint8_t GPIO_GetAPPCPU_INT_InterruptStatus(void);
uint8_t GPIO_GetAPPCPU_NMIINT_InterruptStatus(void);

uint8_t GPIO_GetPROPCPU_INT_InterruptStatus(void);
uint8_t GPIO_GetPROPCPU_NMIINT_InterruptStatus(void);

void GPIO_PINn_INT_EnableCFG(__IO uint32_t *reg, uint8_t bits);
void GPIO_PINWAKEUP_EnableCFG(__IO uint32_t *reg, WakeUPCPUTypeDef valToWakeUp);
void GPIO_PINn_INTTypeCFG(__IO uint32_t *reg,PINIntTypeDef valIntType);
void GPIO_PINn_PadDriverCFG(__IO uint32_t *reg, PINPadDriverTypeDef value);

void GPIO_PINnCustomConfigure(__IO uint32_t *reg, uint8_t bits, WakeUPCPUTypeDef value, PINIntTypeDef valIntType,PINPadDriverTypeDef valuePadDriver);


void GPIO_SelectIfSignalBypass(__IO uint32_t *reg, SignalInSelectTypeDef where);
void GPIO_SelectIfInvertInSignal(__IO uint32_t *reg, FunctionInInvSelectTypeDef invbit);
void GPIO_PeripheralInputSelectionControl(__IO uint32_t *reg, FunctionPeriphInputSelectTypeDef whichgpiopin);

void GPIO_FunctionInSelect_CustomRegConfig(__IO uint32_t *reg, SignalInSelectTypeDef where, FunctionInInvSelectTypeDef invbit, 
    FunctionPeriphInputSelectTypeDef whichgpiopin); 


void GPIO_SelectIfInvertOutENSignal(__IO uint32_t *reg, FunctionOEnableInvSelectTypeDef invbit);
void GPIO_ForceOEnableSignalSource(__IO uint32_t *reg,SourceForOutputEnableTypeDef source);
void GPIO_SelectIfInvertOutSignal(__IO uint32_t *reg,FunctionOutputValInvSelectTypeDef invbit);
void GPIO_FuncOutputControlSelection(__IO uint32_t *reg, uint16_t s );

void GPIO_FunctionOutSelect_CustomRegConfig(__IO uint32_t *reg, FunctionOEnableInvSelectTypeDef invbit, SourceForOutputEnableTypeDef source, 
    FunctionOutputValInvSelectTypeDef invbit2, uint8_t s);

__IO uint32_t * GPIO_MATRIX_Get_GPIO_PINn_REG_ADDR(uint8_t pinId);

__IO uint32_t * GPIO_MATRIX_Get_FUNCy_IN_SEL_CFG_REG_ADDR(uint8_t funcY);

__IO uint32_t * GPIO_MATRIX_Get_FUNCn_OUT_SEL_CFG_REG_ADDR(uint8_t pinId);

#endif /* COMPONENTS_MYHAL_INC_GPIO_MATRIX_H_ */
