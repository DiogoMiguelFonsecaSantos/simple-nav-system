/*
 * spi_driver.h
 *
 *  Created on: 25/04/2025
 *      Author: Diogo
 */

#ifndef COMPONENTS_MYDRIVERS_INC_SPI_DRIVER_H_
#define COMPONENTS_MYDRIVERS_INC_SPI_DRIVER_H_

#include <stdint.h>
#include <stdbool.h>
#include "spi_hal.h"
#include "regs_spi_peripheral.h"
#include "pinconfig.h"
#include "gpio_matrix.h"
#include "io_mux.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/task.h"

typedef struct {
    // MOSI/DATA0 (Master Out Slave In or Quad SPI Data Line 0)
    union {
        int mosi_stdPin;            // Standard SPI: GPIO for Master Out Slave In
        int data0_quad_octalPin;   // Quad/Octal SPI: GPIO for data line 0
    };

    // MISO/DATA1 (Master In Slave Out or Quad SPI Data Line 1)
    union {
        int miso_stdPin;            // Standard SPI: GPIO for Master In Slave Out
        int data1_quad_octalPin;   // Quad/Octal SPI: GPIO for data line 1
    };

    // Essential Clock Signal
    int sclk_Pin;               // GPIO for SPI Clock signal (required for all modes)

    // Write Protect/DATA2 (Quad SPI only)
    union {
        int quaWriteProtPin;        // Quad SPI: GPIO for Write Protect signal
        int data2_quad_octalPin;   // Quad/Octal SPI: GPIO for data line 2
    };

    // Hold/DATA3 (Quad SPI only)
    union {
        int quadHoldPin;            // Quad SPI: GPIO for Hold signal
        int data3_quad_octalPin;   // Quad/Octal SPI: GPIO for data line 3
    };

    // Additional data lines for Octal SPI (8-bit)
    int data4_octalPin;        // Octal SPI: GPIO for data line 4
    int data5_octalPin;       // Octal SPI: GPIO for data line 5
    int data6_octalPin;      // Octal SPI: GPIO for data line 6
    int data7_octalPin;     // Octal SPI: GPIO for data line 7

    // Transfer Configuration
    int maxSingleTansferSz;    // Maximum single transfer size in bytes:
                              // - Default 4092 with DMA
                             // - SOC_SPI_MAXIMUM_BUFFER_SIZE without DMA

} BusConfigSPI_Type;

/**
 * @brief SPI Device Configuration Structure for MPU9250
 * @note All timings are in SPI clock cycles unless specified
 */
typedef struct {
    // Core SPI Parameters
    uint8_t mode;                           ///< SPI Mode (0-3). MPU9250 uses Mode 0 (CPOL=0, CPHA=0)
    uint32_t clockFreqHz;                  ///< SCK frequency in Hz (max 20MHz for MPU9250)
    uint8_t cmdBits;                      ///< Number of bits for command/register address (8 for MPU9250)
    
    // Chip Select Configuration
    IO_MUX_PINValue csPin;                 ///< GPIO pin for Chip Select (active low)
    uint8_t csSetupCycles;                ///< CS active before SCK starts (min 1)
    uint8_t csHoldCycles;                ///< CS held after transaction (min 1)
    bool csIfActiveHigh;                ///< Set true if CS is active high (rare)
    
    // Timing Parameters
    uint8_t s2mDataInputDelayns;           ///< Slave-to-Master data valid delay (typ 25ns for MPU9250)
    uint8_t dummy_bits;                   ///< Dummy cycles between cmd and data (0 for MPU9250)
    
    // Data Format
    bool lsbFirst;                ///< Data bit order (false = MSB first for MPU9250)
    bool fullDuplex;             ///< true for full-duplex (MPU9250 uses this)
    int queueSZ;              ///< Queue size for transactions
    
    // Advanced Features
    bool usingDMA;              ///< Enable DMA (recommended for >1MHz)
    uint8_t dmaBufSZ;         ///< DMA buffer size in bytes (if use_dma=true)

} DeviceConfigSPI_Type;

/**
 * @brief Simplified SPI Transaction Structure for Register-Based Devices (e.g., MPU9250)
 * @note Optimized for common use cases (register reads/writes)
 */
typedef struct {
    // Transaction Control
    uint32_t flags;     ///< Flags (e.g., SPI_TRANS_USE_RXDATA for small transfers)
    
    // Command Phase
    uint8_t cmd;        ///< Register address (+ read/write bit)
    
    // Data Phase
    union {
        const void *txBuf;  ///< Transmit buffer (for multi-byte writes)
        uint8_t txData;     ///< Single-byte transmit data
    };
    union {
        void *rxBuf;        ///< Receive buffer (for multi-byte reads)
        uint8_t rxData;     ///< Single-byte receive data
    };
    uint16_t dataLen;  ///< Data length in bytes (excluding cmd)
    
} TransferSPI_Type;

typedef struct {

    // Your existing configs
    BusConfigSPI_Type busCfg;
    DeviceConfigSPI_Type devCfg;

} SPIDeviceContext;

typedef SPIDeviceContext* SPI_Handle_t;


void SPIProtocol_SetMasterMode(GenericSPI_Type *SPIx, int mode);

void SPI_PinsConfig();

void SPIProtocol_Init(GenericSPI_Type *SPIx, int len, uint8_t preDivider, uint8_t div, int mode);
void SPI_ISR_Handler(GenericSPI_Type *SPIx);
void SPIProtocol_TriggerOperation(GenericSPI_Type *SPIx);
void SPIProtocol_SendData(GenericSPI_Type *SPIx, const uint8_t *data, uint32_t length);
void SPIProtocol_Transaction(GenericSPI_Type *SPIx, const uint8_t *txData, uint8_t *rxData, uint32_t length);

#endif /* COMPONENTS_MYDRIVERS_INC_SPI_DRIVER_H_ */
