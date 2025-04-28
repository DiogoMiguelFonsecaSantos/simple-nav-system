/*
 * spi_driver.c
 *
 *  Created on: 25/04/2025
 *      Author: Diogo
 */

 #include "spi_driver.h"
#include "regs_spi_controller.h"
#include "pinconfig.h"
#include "gpio_matrix.h"
#include "spi_hal.h"
#include "io_mux.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/task.h"
#include "pin.h"
#include "pinconfig.h"


void SPIProtocol_SetMode(GenericSPI_Type *SPIx, int mode) {
    switch (mode) {
        case 0: // SPI Mode 0: CPOL = 0, CPHA = 0
            SPI_HAL_SetClockIdleEdge(SPIx, false); // Clock idle low (CPOL = 0)
            SPI_HAL_SetClockOutEdge(SPIx, false); // Data captured on rising edge (CPHA = 0)
            break;

        case 1: // SPI Mode 1: CPOL = 0, CPHA = 1
            SPI_HAL_SetClockIdleEdge(SPIx, false); // Clock idle low (CPOL = 0)
            SPI_HAL_SetClockOutEdge(SPIx, true);  // Data captured on falling edge (CPHA = 1)
            break;

        case 2: // SPI Mode 2: CPOL = 1, CPHA = 0
            SPI_HAL_SetClockIdleEdge(SPIx, true);  // Clock idle high (CPOL = 1)
            SPI_HAL_SetClockOutEdge(SPIx, false); // Data captured on rising edge (CPHA = 0)
            break;

        case 3: // SPI Mode 3: CPOL = 1, CPHA = 1
            SPI_HAL_SetClockIdleEdge(SPIx, true);  // Clock idle high (CPOL = 1)
            SPI_HAL_SetClockOutEdge(SPIx, true);  // Data captured on falling edge (CPHA = 1)
            break;

        default:
            // Invalid mode, handle error if necessary
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

    PINCONFIG_SetDriveStrength(PIN_GPIO23, MEDIUM);
    PINCONFIG_SetDriveStrength(PIN_GPIO19, MEDIUM);
    PINCONFIG_SetDriveStrength(PIN_GPIO18, MEDIUM);
    PINCONFIG_SetDriveStrength(PIN_GPIO5, MEDIUM);

}

void SPIProtocol_Init(GenericSPI_Type *SPIx, int len, uint8_t preDivider, uint8_t div, int mode) {

    int spiNum;

    switch (SPIx) {

        case SPI0:
            spiNum = 0;
            break;
        case SPI1:
            spiNum = 1;
            break;
        case SPI2:
            spiNum = 2;
            break;
        case SPI3:
            spiNum = 3;
            break;
        default:
            // Handle error for unsupported SPI peripheral
            break;
    }

    // Enable the clock for the SPI peripheral (e.g., VSPI)
    PWR_CLKGTING_EnableSPIClk(spiNum); // Assuming SPI3 (VSPI) is used

    // Reset the SPI peripheral to ensure a clean state
    PWR_CLKGTING_ResetSPIClk(spiNum); // Assuming SPI3 (VSPI) is used
    
    SPI_PinsConfig();

    SPI_HAL_EnableFullDuplex(GenericSPI_Type *SPIx, bool enable);

    // Set data bit lengths (8 bits for MPU9250 communication)
    SPI_HAL_SetMosiDataBitLength(SPIx, len); // 8 bits (0-based index)
    SPI_HAL_SetMisoDataBitLength(SPIx, len); // 8 bits (0-based index)

    // Configure SPI clock (MPU9250 supports up to 1 MHz for initialization, up to 20 MHz for normal operation)
    SPI_HAL_SetClockPreDivider(SPIx, preDivider); // Adjust as needed for 1 MHz
    SPI_HAL_SetClockDivider(SPIx, div);

    SPIProtocol_SetMode(SPIx, mode);

    // Configure CS setup and hold times
    SPI_HAL_SetCsSetupTime(SPIx, 1); // 1 SPI clock cycle
    SPI_HAL_SetCsHoldTime(SPIx, 1);  // 1 SPI clock cycle

    // Configure MOSI and MISO delays
    SPI_HAL_SetMosiDelayNum(SPIx, 0); // No delay for MOSI
    SPI_HAL_SetMisoDelayNum(SPIx, 0); // No delay for MISO

    // Enable necessary phases
    SPI_HAL_EnableCommandPhase(SPIx, false); // MPU9250 does not use a command phase
    SPI_HAL_EnableAddressPhase(SPIx, false); // MPU9250 does not use an address phase
    SPI_HAL_EnableReadPhase(SPIx, true);     // Enable read-data phase
    SPI_HAL_EnableWritePhase(SPIx, true);    // Enable write-data phase

}

void SPIProtocol_TriggerOperation(GenericSPI_Type *SPIx) {
    while (SPI_HAL_IsBusy(SPIx)); // Wait until the SPI is not busy
    SPI_HAL_TriggerOperation(SPIx); // Set the SPI_USR bit to start the operation
}

