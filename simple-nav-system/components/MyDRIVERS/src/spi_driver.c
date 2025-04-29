/*
 * spi_driver.c
 *
 *  Created on: 25/04/2025
 *      Author: Diogo
 */

 #include "spi_driver.h"
#include "regs_spi_peripheral.h"
#include "pinconfig.h"
#include "gpio_matrix.h"
#include "spi_hal.h"
#include "io_mux.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/task.h"
#include "pin.h"
#include "pwrAndclockGating.h"



void SPIProtocol_SetMasterMode(GenericSPI_Type *SPIx, int mode) {
    switch (mode) {
        case 0: // SPI Mode 0: CPOL = 0, CPHA = 0
            SPI_HAL_SetClockIdleEdge(SPIx, false); // Clock idle low (CPOL = 0)
            SPI_HAL_SetClockOutEdge(SPIx, false); // Data captured on rising edge (CPHA = 0)
            SPI_HAL_SetMisoDelayMode(SPIx, 2);    // MISO delay mode = 2
            SPI_HAL_SetMisoDelayNum(SPIx, 0);     // MISO delay num = 0
            SPI_HAL_SetMosiDelayMode(SPIx, 0);    // MOSI delay mode = 0
            SPI_HAL_SetMosiDelayNum(SPIx, 0);     // MOSI delay num = 0
            break;

        case 1: // SPI Mode 1: CPOL = 0, CPHA = 1
            SPI_HAL_SetClockIdleEdge(SPIx, false); // Clock idle low (CPOL = 0)
            SPI_HAL_SetClockOutEdge(SPIx, true);  // Data captured on falling edge (CPHA = 1)
            SPI_HAL_SetMisoDelayMode(SPIx, 1);    // MISO delay mode = 1
            SPI_HAL_SetMisoDelayNum(SPIx, 0);     // MISO delay num = 0
            SPI_HAL_SetMosiDelayMode(SPIx, 0);    // MOSI delay mode = 0
            SPI_HAL_SetMosiDelayNum(SPIx, 0);     // MOSI delay num = 0
            break;

        case 2: // SPI Mode 2: CPOL = 1, CPHA = 0
            SPI_HAL_SetClockIdleEdge(SPIx, true);  // Clock idle high (CPOL = 1)
            SPI_HAL_SetClockOutEdge(SPIx, true); // Data captured on rising edge (CPHA = 0)
            SPI_HAL_SetMisoDelayMode(SPIx, 1);    // MISO delay mode = 1
            SPI_HAL_SetMisoDelayNum(SPIx, 0);     // MISO delay num = 0
            SPI_HAL_SetMosiDelayMode(SPIx, 0);    // MOSI delay mode = 0
            SPI_HAL_SetMosiDelayNum(SPIx, 0);     // MOSI delay num = 0
            break;

        case 3: // SPI Mode 3: CPOL = 1, CPHA = 1
            SPI_HAL_SetClockIdleEdge(SPIx, true);  // Clock idle high (CPOL = 1)
            SPI_HAL_SetClockOutEdge(SPIx, false);  // Data captured on falling edge (CPHA = 1)
            SPI_HAL_SetMisoDelayMode(SPIx, 2);    // MISO delay mode = 2
            SPI_HAL_SetMisoDelayNum(SPIx, 0);     // MISO delay num = 0
            SPI_HAL_SetMosiDelayMode(SPIx, 0);    // MOSI delay mode = 0
            SPI_HAL_SetMosiDelayNum(SPIx, 0);     // MOSI delay num = 0
            break;

        default:
            // Invalid mode, handle error if necessary
            printf("Error: Unsupported SPI mode\n");
            break;
    }
}

void SPI_PinsConfig() {

    PIN_SetPinAsOutput(PIN_GPIO23);
    PIN_Direction(PIN_GPIO19, INPUT); // Set MISO as input
    PIN_SetPinAsOutput(PIN_GPIO18);
    PIN_SetPinAsOutput(PIN_GPIO5); // Chip Select (CS) pin

    PINCONFIG_Function(PIN_GPIO23, F1_VSPID); // Set GPIO23 as VSPI MOSI
    PINCONFIG_Function(PIN_GPIO19, F1_VSPIQ); // Set GPIO19 as VSPI MISO
    PINCONFIG_Function(PIN_GPIO18, F1_VSPICLK); // Set GPIO18 as VSPI SCLK
    PINCONFIG_Function(PIN_GPIO5, F1_VSPICS0);  // Set GPIO5 as VSPI CS

    __IO uint32_t *regCLK  = GPIO_MATRIX_Get_FUNCy_IN_SEL_CFG_REG_ADDR(63); // VSPICLK_in
    __IO uint32_t *regMISO = GPIO_MATRIX_Get_FUNCy_IN_SEL_CFG_REG_ADDR(64); // VSPIQ_in
    __IO uint32_t *regMOSI = GPIO_MATRIX_Get_FUNCy_IN_SEL_CFG_REG_ADDR(65); // VSPID_in
    __IO uint32_t *regCS0  = GPIO_MATRIX_Get_FUNCy_IN_SEL_CFG_REG_ADDR(68); // VSPICS0_in

    GPIO_SelectIfSignalBypass(regCLK,  IO_MPLEX);
    GPIO_SelectIfSignalBypass(regMISO, IO_MPLEX);
    GPIO_SelectIfSignalBypass(regMOSI, IO_MPLEX);
    GPIO_SelectIfSignalBypass(regCS0,  IO_MPLEX);

    PINCONFIG_SetDriveStrength(PIN_GPIO23, MEDIUM);
    PINCONFIG_SetDriveStrength(PIN_GPIO19, MEDIUM);
    PINCONFIG_SetDriveStrength(PIN_GPIO18, MEDIUM);
    PINCONFIG_SetDriveStrength(PIN_GPIO5, MEDIUM);



}

void SPIProtocol_Init(GenericSPI_Type *SPIx, int len, uint8_t preDivider, uint8_t div, int mode) {

    int spiNum;

    if (SPIx == SPI0) {
        spiNum = 0;
    } else if (SPIx == SPI1) {
        spiNum = 1;
    } else if (SPIx == SPI2) {
        spiNum = 2;
    } else if (SPIx == SPI3) {
        spiNum = 3;
    } else {
        // Handle error for unsupported SPI peripheral
        printf("Error: Unsupported SPI peripheral\n");
        return; // Exit the function
    }

    // Enable the clock for the SPI peripheral (e.g., VSPI)
    PWR_CLKGTING_EnableSPIClk(spiNum); // Assuming SPI3 (VSPI) is used

    // Reset the SPI peripheral to ensure a clean state
    PWR_CLKGTING_ResetSPIClk(spiNum); // Assuming SPI3 (VSPI) is used
    
    SPI_PinsConfig();

    SPI_HAL_EnableFullDuplex(SPIx, true);
    SPI_HAL_SetSlaveOrMaster(SPIx,false); // Set SPI to master mode

    // Set data bit lengths (8 bits for MPU9250 communication)
    SPI_HAL_SetMosiDataBitLength(SPIx, len); // 8 bits (0-based index)
    SPI_HAL_SetMisoDataBitLength(SPIx, len); // 8 bits (0-based index)

    SPI_HAL_SetClockEqualSysClock(SPIx, false); 

    // Configure SPI clock (MPU9250 supports up to 1 MHz for initialization, up to 20 MHz for normal operation)
    SPI_HAL_SetClockPreDivider(SPIx, preDivider); // 1 Adjust as needed for 1 MHz 
    SPI_HAL_SetClockDivider(SPIx, div); //39

    SPIProtocol_SetMasterMode(SPIx, mode); // second or third

    // Configure CS setup and hold times
    SPI_HAL_SetCsSetupTime(SPIx, 1); // 1 SPI clock cycle
    SPI_HAL_SetCsHoldTime(SPIx, 1);  // 1 SPI clock cycle

    SPI_HAL_SetCs0Enabled(SPIx, false); // Clear SPI_CS0_DIS to 0 (enable CS0)
    SPI_HAL_SetReadBitOrder(SPIx, false); // Set MSB first for MPU9250 communication
    SPI_HAL_SetWriteBitOrder(SPIx, false); // Set MSB first for MPU9250 communication

    // Enable necessary phases
    SPI_HAL_EnableCommandPhase(SPIx, false); // MPU9250 does not use a command phase
    SPI_HAL_EnableAddressPhase(SPIx, false); // MPU9250 does not use an address phase
    SPI_HAL_EnableReadPhase(SPIx, true);     // Enable read-data phase
    SPI_HAL_EnableWritePhase(SPIx, true);    // Enable write-data phase

    SPI_HAL_SetTransactionDoneInterrupt(SPIx, true);
}

void SPI_ISR_Handler(GenericSPI_Type *SPIx) {
    if (SPI_HAL_IsTransactionDone(SPIx)) {
        // Handle the completed SPI transaction
        // For example, process the received data

        // Clear the interrupt flag
        SPI_HAL_ClearTransactionDone(SPIx);
    }
}

void SPIProtocol_TriggerOperation(GenericSPI_Type *SPIx) {
    while (SPI_HAL_IsBusy(SPIx)); // Wait until the SPI is not busy
    SPI_HAL_TriggerOperation(SPIx); // Set the SPI_USR bit to start the operation
}

void SPIProtocol_SendData(GenericSPI_Type *SPIx, const uint8_t *data, uint32_t length) {
    while (SPI_HAL_IsBusy(SPIx)); // Esperar até SPI livre

    SPI_HAL_SetMosiDataBitLength(SPIx, length * 8); // Definir comprimento em bits

    uint32_t word = 0;
    for (uint32_t i = 0; i < (length + 3) / 4; i++) { // +3 para arredondar para cima

        word = 0;
        for (int j = 0; j < 4; j++) {
            uint32_t byteIndex = (i * 4) + j;
            if (byteIndex < length) {
                word |= ((uint32_t)data[byteIndex]) << (8 * j);
            }
        }
        SPI_HAL_SetDataBuffer(SPIx, i, word);
    }

    SPI_HAL_EnableWritePhase(SPIx, true);
    SPI_HAL_TriggerOperation(SPIx);

    while (SPI_HAL_IsBusy(SPIx)); // Esperar operação terminar
}

void SPIProtocol_Transaction(GenericSPI_Type *SPIx, const uint8_t *txData, uint8_t *rxData, uint32_t length) {
    while (SPI_HAL_IsBusy(SPIx));

    SPI_HAL_SetMosiDataBitLength(SPIx, length * 8);
    SPI_HAL_SetMisoDataBitLength(SPIx, length * 8);

    uint32_t word = 0;
    for (uint32_t i = 0; i < (length + 3) / 4; i++) {
        word = 0;
        for (int j = 0; j < 4; j++) {
            uint32_t byteIndex = (i * 4) + j;
            if (byteIndex < length) {
                word |= ((uint32_t)txData[byteIndex]) << (8 * j);
            }
        }
        SPI_HAL_SetDataBuffer(SPIx, i, word);
    }

    SPI_HAL_EnableWritePhase(SPIx, true);
    SPI_HAL_EnableReadPhase(SPIx, true);

    SPI_HAL_TriggerOperation(SPIx);

    while (SPI_HAL_IsBusy(SPIx));

    for (uint32_t i = 0; i < (length + 3) / 4; i++) {
        word = SPI_HAL_GetDataBuffer(SPIx, i);
        for (int j = 0; j < 4; j++) {
            uint32_t byteIndex = (i * 4) + j;
            if (byteIndex < length) {
                rxData[byteIndex] = (word >> (8 * j)) & 0xFF;
            }
        }
    }
}
