#include "spi_hal.h"
#include "regs_spi_peripheral.h"
#include "pinconfig.h"
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>


/*SPI_CMD_REG (0x0)*/

void SPI_HAL_TriggerOperation(GenericSPI_Type *SPIx) {
    SPIx->CMD |= (1 << 18);
}

bool SPI_HAL_IsBusy(GenericSPI_Type *SPIx) {
    // Check if the SPI is busy
    return (SPIx->CMD & (1 << 18)) != 0;
}

/* SPI_ADDR_REG (0x4) */

// Function to set the transmitting address in SPI_ADDR_REG
void SPI_HAL_SetAddress(GenericSPI_Type *SPIx, uint32_t address) {
    // Write the address to the ADDR register
    SPIx->ADDR = address;
}

// Function to read the transmitting address from SPI_ADDR_REG
uint32_t SPI_HAL_GetAddress(GenericSPI_Type *SPIx) {
    // Read and return the value of the ADDR register
    return SPIx->ADDR;
}

/* SPI_CTRL_REG (0x8) */

// Function to set the bit order for transmitted signals (SPI_WR_BIT_ORDER)
void SPI_HAL_SetWriteBitOrder(GenericSPI_Type *SPIx, bool lsbFirst) {
    if (lsbFirst) {
        SPIx->CTRL |= (1 << 26); // Set SPI_WR_BIT_ORDER to 1 (LSB first)
    } else {
        SPIx->CTRL &= ~(1 << 26); // Clear SPI_WR_BIT_ORDER to 0 (MSB first)
    }
}

// Function to set the bit order for received signals (SPI_RD_BIT_ORDER)
void SPI_HAL_SetReadBitOrder(GenericSPI_Type *SPIx, bool lsbFirst) {
    if (lsbFirst) {
        SPIx->CTRL |= (1 << 25); // Set SPI_RD_BIT_ORDER to 1 (LSB first)
    } else {
        SPIx->CTRL &= ~(1 << 25); // Clear SPI_RD_BIT_ORDER to 0 (MSB first)
    }
}

// Function to enable/disable four-line address writes and data reads (SPI_FREAD_QIO)
void SPI_HAL_EnableFourLineMode(GenericSPI_Type *SPIx, bool enable) {
    if (enable) {
        SPIx->CTRL |= (1 << 24); // Set SPI_FREAD_QIO to 1
    } else {
        SPIx->CTRL &= ~(1 << 24); // Clear SPI_FREAD_QIO to 0
    }
}

// Function to enable/disable two-line address writes and data reads (SPI_FREAD_DIO)
void SPI_HAL_EnableTwoLineMode(GenericSPI_Type *SPIx, bool enable) {
    if (enable) {
        SPIx->CTRL |= (1 << 23); // Set SPI_FREAD_DIO to 1
    } else {
        SPIx->CTRL &= ~(1 << 23); // Clear SPI_FREAD_DIO to 0
    }
}

// Function to set write-protection signal output when SPI is idle (SPI_WP)
void SPI_HAL_SetWriteProtection(GenericSPI_Type *SPIx, bool high) {
    if (high) {
        SPIx->CTRL |= (1 << 21); // Set SPI_WP to 1 (output high)
    } else {
        SPIx->CTRL &= ~(1 << 21); // Clear SPI_WP to 0 (output low)
    }
}

// Function to enable/disable four-line data reads (SPI_FREAD_QUAD)
void SPI_HAL_EnableFourLineDataRead(GenericSPI_Type *SPIx, bool enable) {
    if (enable) {
        SPIx->CTRL |= (1 << 20); // Set SPI_FREAD_QUAD to 1
    } else {
        SPIx->CTRL &= ~(1 << 20); // Clear SPI_FREAD_QUAD to 0
    }
}

// Function to enable/disable two-line data reads (SPI_FREAD_DUAL)
void SPI_HAL_EnableTwoLineDataRead(GenericSPI_Type *SPIx, bool enable) {
    if (enable) {
        SPIx->CTRL |= (1 << 14); // Set SPI_FREAD_DUAL to 1
    } else {
        SPIx->CTRL &= ~(1 << 14); // Clear SPI_FREAD_DUAL to 0
    }
}

// Function to get the bit order for transmitted signals (SPI_WR_BIT_ORDER)
bool SPI_HAL_GetWriteBitOrder(GenericSPI_Type *SPIx) {
    return (SPIx->CTRL & (1 << 26)) != 0; // Return true if LSB first, false if MSB first
}

// Function to get the bit order for received signals (SPI_RD_BIT_ORDER)
bool SPI_HAL_GetReadBitOrder(GenericSPI_Type *SPIx) {
    return (SPIx->CTRL & (1 << 25)) != 0; // Return true if LSB first, false if MSB first
}

// Function to check if four-line address writes and data reads are enabled (SPI_FREAD_QIO)
bool SPI_HAL_IsFourLineModeEnabled(GenericSPI_Type *SPIx) {
    return (SPIx->CTRL & (1 << 24)) != 0; // Return true if enabled, false if disabled
}

// Function to check if two-line address writes and data reads are enabled (SPI_FREAD_DIO)
bool SPI_HAL_IsTwoLineModeEnabled(GenericSPI_Type *SPIx) {
    return (SPIx->CTRL & (1 << 23)) != 0; // Return true if enabled, false if disabled
}

// Function to get the write-protection signal output state (SPI_WP)
bool SPI_HAL_GetWriteProtection(GenericSPI_Type *SPIx) {
    return (SPIx->CTRL & (1 << 21)) != 0; // Return true if high, false if low
}

// Function to check if four-line data reads are enabled (SPI_FREAD_QUAD)
bool SPI_HAL_IsFourLineDataReadEnabled(GenericSPI_Type *SPIx) {
    return (SPIx->CTRL & (1 << 20)) != 0; // Return true if enabled, false if disabled
}

// Function to check if two-line data reads are enabled (SPI_FREAD_DUAL)
bool SPI_HAL_IsTwoLineDataReadEnabled(GenericSPI_Type *SPIx) {
    return (SPIx->CTRL & (1 << 14)) != 0; // Return true if enabled, false if disabled
}

/*SPI_CTRL2_REG (0x14)*/

// Function to set the MOSI delay number (SPI_MOSI_DELAY_NUM)
void SPI_HAL_SetMosiDelayNum(GenericSPI_Type *SPIx, uint8_t delayNum) {
    SPIx->CTRL2 = (SPIx->CTRL2 & ~(0x7 << 28)) | ((delayNum & 0x7) << 28);
}

// Function to set the MOSI delay mode (SPI_MOSI_DELAY_MODE)
void SPI_HAL_SetMosiDelayMode(GenericSPI_Type *SPIx, uint8_t delayMode) {
    SPIx->CTRL2 = (SPIx->CTRL2 & ~(0x3 << 21)) | ((delayMode & 0x3) << 21);
}

// Function to set the MISO delay number (SPI_MISO_DELAY_NUM)
void SPI_HAL_SetMisoDelayNum(GenericSPI_Type *SPIx, uint8_t delayNum) {
    SPIx->CTRL2 = (SPIx->CTRL2 & ~(0x7 << 18)) | ((delayNum & 0x7) << 18);
}

// Function to set the MISO delay mode (SPI_MISO_DELAY_MODE)
void SPI_HAL_SetMisoDelayMode(GenericSPI_Type *SPIx, uint8_t delayMode) {
    SPIx->CTRL2 = (SPIx->CTRL2 & ~(0x3 << 16)) | ((delayMode & 0x3) << 16);
}

// Function to set the CS hold time (SPI_HOLD_TIME)
void SPI_HAL_SetCsHoldTime(GenericSPI_Type *SPIx, uint8_t holdTime) {
    SPIx->CTRL2 = (SPIx->CTRL2 & ~(0xF << 4)) | ((holdTime & 0xF) << 4);
}

// Function to set the CS setup time (SPI_SETUP_TIME)
void SPI_HAL_SetCsSetupTime(GenericSPI_Type *SPIx, uint8_t setupTime) {
    SPIx->CTRL2 = (SPIx->CTRL2 & ~(0xF << 0)) | ((setupTime & 0xF) << 0);
}

// Function to get the MOSI delay number (SPI_MOSI_DELAY_NUM)
uint8_t SPI_HAL_GetMosiDelayNum(GenericSPI_Type *SPIx) {
    return (SPIx->CTRL2 >> 28) & 0x7;
}

// Function to get the MOSI delay mode (SPI_MOSI_DELAY_MODE)
uint8_t SPI_HAL_GetMosiDelayMode(GenericSPI_Type *SPIx) {
    return (SPIx->CTRL2 >> 15) & 0x3;
}

// Function to get the MISO delay number (SPI_MISO_DELAY_NUM)
uint8_t SPI_HAL_GetMisoDelayNum(GenericSPI_Type *SPIx) {
    return (SPIx->CTRL2 >> 21) & 0x7;
}

// Function to get the MISO delay mode (SPI_MISO_DELAY_MODE)
uint8_t SPI_HAL_GetMisoDelayMode(GenericSPI_Type *SPIx) {
    return (SPIx->CTRL2 >> 19) & 0x3;
}

// Function to get the CS hold time (SPI_HOLD_TIME)
uint8_t SPI_HAL_GetCsHoldTime(GenericSPI_Type *SPIx) {
    return (SPIx->CTRL2 >> 7) & 0xF;
}

// Function to get the CS setup time (SPI_SETUP_TIME)
uint8_t SPI_HAL_GetCsSetupTime(GenericSPI_Type *SPIx) {
    return SPIx->CTRL2 & 0xF;
}

/*SPI_CLOCK_REG (0x18)*/

// Function to set SPI clock to system clock or divided clock
void SPI_HAL_SetClockEqualSysClock(GenericSPI_Type *SPIx, bool equalSysClock) {
    if (equalSysClock) {
        SPIx->CLOCK |= (1 << 31); // Set SPI_CLK_EQU_SYSCLK to 1
    } else {
        SPIx->CLOCK &= ~(1 << 31); // Clear SPI_CLK_EQU_SYSCLK to 0
    }
}

// Function to configure the pre-divider value for SPI clock
void SPI_HAL_SetClockPreDivider(GenericSPI_Type *SPIx, uint8_t preDivider) {
    SPIx->CLOCK = (SPIx->CLOCK & ~(0x1FFF << 18)) | ((preDivider & 0x1FFF) << 18);
}

// Function to configure the divider for SPI clock
void SPI_HAL_SetClockDivider(GenericSPI_Type *SPIx, uint8_t divider) {
    SPIx->CLOCK = (SPIx->CLOCK & ~(0x3F << 12)) | ((divider & 0x3F) << 12);
}

// Function to calculate and set SPI_CLKCNT_H and SPI_CLKCNT_L
void SPI_HAL_SetClockHighLow(GenericSPI_Type *SPIx, uint8_t clkcntN) {
    uint8_t clkcntH = (clkcntN + 1) / 2 - 1;
    SPIx->CLOCK = (SPIx->CLOCK & ~((0x3F << 6) | (0x3F << 0))) |
                  ((clkcntH & 0x3F) << 6) |
                  ((clkcntN & 0x3F) << 0);
}

// Function to get the SPI_CLK_EQU_SYSCLK value
bool SPI_HAL_IsClockEqualSysClock(GenericSPI_Type *SPIx) {
    return (SPIx->CLOCK & (1 << 31)) != 0;
}

// Function to get the pre-divider value for SPI clock
uint8_t SPI_HAL_GetClockPreDivider(GenericSPI_Type *SPIx) {
    return (SPIx->CLOCK >> 18) & 0x1FFF;
}

// Function to get the divider value for SPI clock
uint8_t SPI_HAL_GetClockDivider(GenericSPI_Type *SPIx) {
    return (SPIx->CLOCK >> 12) & 0x3F;
}

// Function to get SPI_CLKCNT_H
uint8_t SPI_HAL_GetClockHigh(GenericSPI_Type *SPIx) {
    return (SPIx->CLOCK >> 6) & 0x3F;
}

// Function to get SPI_CLKCNT_L
uint8_t SPI_HAL_GetClockLow(GenericSPI_Type *SPIx) {
    return SPIx->CLOCK & 0x3F;
}





/*SPI_USER_REG (0x1C)*/

// Function to enable or disable the command phase (SPI_USR_COMMAND)
void SPI_HAL_EnableCommandPhase(GenericSPI_Type *SPIx, bool enable) {
    if (enable) {
        SPIx->USER |= (1 << 31); // Set SPI_USR_COMMAND to 1
    } else {
        SPIx->USER &= ~(1 << 31); // Clear SPI_USR_COMMAND to 0
    }
}

// Function to enable or disable the address phase (SPI_USR_ADDR)
void    SPI_HAL_EnableAddressPhase(GenericSPI_Type *SPIx, bool enable) {
    if (enable) {
        SPIx->USER |= (1 << 30); // Set SPI_USR_ADDR to 1
    } else {
        SPIx->USER &= ~(1 << 30); // Clear SPI_USR_ADDR to 0
    }
}

// Function to enable or disable the dummy phase (SPI_USR_DUMMY)
void SPI_HAL_EnableDummyPhase(GenericSPI_Type *SPIx, bool enable) {
    if (enable) {
        SPIx->USER |= (1 << 29); // Set SPI_USR_DUMMY to 1
    } else {
        SPIx->USER &= ~(1 << 29); // Clear SPI_USR_DUMMY to 0
    }
}

// Function to enable or disable the read-data phase (SPI_USR_MISO)
void SPI_HAL_EnableReadPhase(GenericSPI_Type *SPIx, bool enable) {
    if (enable) {
        SPIx->USER |= (1 << 28); // Set SPI_USR_MISO to 1
    } else {
        SPIx->USER &= ~(1 << 28); // Clear SPI_USR_MISO to 0
    }
}

// Function to enable or disable the write-data phase (SPI_USR_MOSI)
void SPI_HAL_EnableWritePhase(GenericSPI_Type *SPIx, bool enable) {
    if (enable) {
        SPIx->USER |= (1 << 27); // Set SPI_USR_MOSI to 1
    } else {
        SPIx->USER &= ~(1 << 27); // Clear SPI_USR_MOSI to 0
    }
}

// Function to enable or disable the SPI clock signal during the dummy phase (SPI_USR_DUMMY_IDLE)
void SPI_HAL_EnableDummyIdle(GenericSPI_Type *SPIx, bool enable) {
    if (enable) {
        SPIx->USER |= (1 << 26); // Set SPI_USR_DUMMY_IDLE to 1 (disable SPI clock during dummy phase)
    } else {
        SPIx->USER &= ~(1 << 26); // Clear SPI_USR_DUMMY_IDLE to 0 (enable SPI clock during dummy phase)
    }
}

// Function to enable or disable storing MOSI data in SPI_W8 ~ SPI_W15 (SPI_USR_MOSI_HIGHPART)
void SPI_HAL_EnableMosiHighPart(GenericSPI_Type *SPIx, bool enable) {
    if (enable) {
        SPIx->USER |= (1 << 25); // Set SPI_USR_MOSI_HIGHPART to 1
    } else {
        SPIx->USER &= ~(1 << 25); // Clear SPI_USR_MOSI_HIGHPART to 0
    }
}

// Function to enable or disable storing MISO data in SPI_W8 ~ SPI_W15 (SPI_USR_MISO_HIGHPART)
void SPI_HAL_EnableMisoHighPart(GenericSPI_Type *SPIx, bool enable) {
    if (enable) {
        SPIx->USER |= (1 << 24); // Set SPI_USR_MISO_HIGHPART to 1
    } else {
        SPIx->USER &= ~(1 << 24); // Clear SPI_USR_MISO_HIGHPART to 0
    }
}

// Function to set the byte order for transmitted signals (SPI_WR_BYTE_ORDER)
void SPI_HAL_SetWriteByteOrder(GenericSPI_Type *SPIx, bool bigEndian) {
    if (bigEndian) {
        SPIx->USER |= (1 << 11); // Set SPI_WR_BYTE_ORDER to 1 (big-endian)
    } else {
        SPIx->USER &= ~(1 << 11); // Clear SPI_WR_BYTE_ORDER to 0 (little-endian)
    }
}

// Function to set the byte order for received signals (SPI_RD_BYTE_ORDER)
void SPI_HAL_SetReadByteOrder(GenericSPI_Type *SPIx, bool bigEndian) {
    if (bigEndian) {
        SPIx->USER |= (1 << 10); // Set SPI_RD_BYTE_ORDER to 1 (big-endian)
    } else {
        SPIx->USER &= ~(1 << 10); // Clear SPI_RD_BYTE_ORDER to 0 (little-endian)
    }
}

// Function to set the SPI_CK_OUT_EDGE bit (valid in master mode)
void SPI_HAL_SetClockOutEdge(GenericSPI_Type *SPIx, bool enable) {
    if (enable) {
        SPIx->USER |= (1 << 7); // Set SPI_CK_OUT_EDGE to 1
    } else {
        SPIx->USER &= ~(1 << 7); // Clear SPI_CK_OUT_EDGE to 0
    }
}

// Function to set the SPI_CK_I_EDGE bit (valid in slave mode)
void SPI_HAL_SetClockInEdge(GenericSPI_Type *SPIx, bool enable) {
    if (enable) {
        SPIx->USER |= (1 << 6); // Set SPI_CK_I_EDGE to 1
    } else {
        SPIx->USER &= ~(1 << 6); // Clear SPI_CK_I_EDGE to 0
    }
}

// Function to enable or disable CS setup delay (SPI_CS_SETUP)
void SPI_HAL_EnableCsSetupDelay(GenericSPI_Type *SPIx, bool enable) {
    if (enable) {
        SPIx->USER |= (1 << 5); // Set SPI_CS_SETUP to 1
    } else {
        SPIx->USER &= ~(1 << 5); // Clear SPI_CS_SETUP to 0
    }
}

// Function to enable or disable CS hold delay (SPI_CS_HOLD)
void SPI_HAL_EnableCsHoldDelay(GenericSPI_Type *SPIx, bool enable) {
    if (enable) {
        SPIx->USER |= (1 << 4); // Set SPI_CS_HOLD to 1
    } else {
        SPIx->USER &= ~(1 << 4); // Clear SPI_CS_HOLD to 0
    }
}

// Function to enable or disable full-duplex communication (SPI_DOUTDIN)
void SPI_HAL_EnableFullDuplex(GenericSPI_Type *SPIx, bool enable) {
    if (enable) {
        SPIx->USER |= (1 << 0); // Set SPI_DOUTDIN to 1
    } else {
        SPIx->USER &= ~(1 << 0); // Clear SPI_DOUTDIN to 0
    }
}

// Function to check if the command phase is enabled (SPI_USR_COMMAND)
bool SPI_HAL_IsCommandPhaseEnabled(GenericSPI_Type *SPIx) {
    return (SPIx->USER & (1 << 31)) != 0;
}

// Function to check if the address phase is enabled (SPI_USR_ADDR)
bool SPI_HAL_IsAddressPhaseEnabled(GenericSPI_Type *SPIx) {
    return (SPIx->USER & (1 << 30)) != 0;
}

// Function to check if the dummy phase is enabled (SPI_USR_DUMMY)
bool SPI_HAL_IsDummyPhaseEnabled(GenericSPI_Type *SPIx) {
    return (SPIx->USER & (1 << 29)) != 0;
}

// Function to check if the read-data phase is enabled (SPI_USR_MISO)
bool SPI_HAL_IsReadPhaseEnabled(GenericSPI_Type *SPIx) {
    return (SPIx->USER & (1 << 28)) != 0;
}

// Function to check if the write-data phase is enabled (SPI_USR_MOSI)
bool SPI_HAL_IsWritePhaseEnabled(GenericSPI_Type *SPIx) {
    return (SPIx->USER & (1 << 27)) != 0;
}

// Function to check if the SPI clock signal is disabled during the dummy phase (SPI_USR_DUMMY_IDLE)
bool SPI_HAL_IsDummyIdleEnabled(GenericSPI_Type *SPIx) {
    return (SPIx->USER & (1 << 26)) != 0;
}

// Function to check if MOSI data is stored in SPI_W8 ~ SPI_W15 (SPI_USR_MOSI_HIGHPART)
bool SPI_HAL_IsMosiHighPartEnabled(GenericSPI_Type *SPIx) {
    return (SPIx->USER & (1 << 25)) != 0;
}

// Function to check if MISO data is stored in SPI_W8 ~ SPI_W15 (SPI_USR_MISO_HIGHPART)
bool SPI_HAL_IsMisoHighPartEnabled(GenericSPI_Type *SPIx) {
    return (SPIx->USER & (1 << 24)) != 0;
}

// Function to check the byte order for transmitted signals (SPI_WR_BYTE_ORDER)
bool SPI_HAL_IsWriteByteOrderBigEndian(GenericSPI_Type *SPIx) {
    return (SPIx->USER & (1 << 11)) != 0;
}

// Function to check the byte order for received signals (SPI_RD_BYTE_ORDER)
bool SPI_HAL_IsReadByteOrderBigEndian(GenericSPI_Type *SPIx) {
    return (SPIx->USER & (1 << 10)) != 0;
}

// Function to check if SPI_CK_OUT_EDGE is set (valid in master mode)
bool SPI_HAL_IsClockOutEdgeEnabled(GenericSPI_Type *SPIx) {
    return (SPIx->USER & (1 << 7)) != 0;
}

// Function to check if SPI_CK_I_EDGE is set (valid in slave mode)
bool SPI_HAL_IsClockInEdgeEnabled(GenericSPI_Type *SPIx) {
    return (SPIx->USER & (1 << 6)) != 0;
}

// Function to check if CS setup delay is enabled (SPI_CS_SETUP)
bool SPI_HAL_IsCsSetupDelayEnabled(GenericSPI_Type *SPIx) {
    return (SPIx->USER & (1 << 5)) != 0;
}

// Function to check if CS hold delay is enabled (SPI_CS_HOLD)
bool SPI_HAL_IsCsHoldDelayEnabled(GenericSPI_Type *SPIx) {
    return (SPIx->USER & (1 << 4)) != 0;
}

// Function to check if full-duplex communication is enabled (SPI_DOUTDIN)
bool SPI_HAL_IsFullDuplexEnabled(GenericSPI_Type *SPIx) {
    return (SPIx->USER & (1 << 0)) != 0;
}





/*SPI_USER1_REG (0x20)*/

// Function to get the address bit length (SPI_USR_ADDR_BITLEN)
uint8_t SPI_HAL_GetAddressBitLength(GenericSPI_Type *SPIx) {
    return (SPIx->USER1 >> 26) & 0x3F; // Extract bits [31:26]
}

// Function to set the dummy cycle length (SPI_USR_DUMMY_CYCLELEN)
void SPI_HAL_SetDummyCycleLength(GenericSPI_Type *SPIx, uint8_t cycleLength) {
    SPIx->USER1 = (SPIx->USER1 & ~(0xFF << 0)) | ((cycleLength & 0xFF) << 0); // Set bits [7:0]
}

// Function to get the dummy cycle length (SPI_USR_DUMMY_CYCLELEN)
uint8_t SPI_HAL_GetDummyCycleLength(GenericSPI_Type *SPIx) {
    return SPIx->USER1 & 0xFF; // Extract bits [7:0]
}

/*SPI_USER2_REG (0x24)*/

// Function to set the command bit length (SPI_USR_COMMAND_BITLEN)
void SPI_HAL_SetCommandBitLength(GenericSPI_Type *SPIx, uint8_t bitLength) {
    SPIx->USER2 = (SPIx->USER2 & ~(0xF << 28)) | ((bitLength & 0xF) << 28); // Set bits [31:28]
}

// Function to get the command bit length (SPI_USR_COMMAND_BITLEN)
uint8_t SPI_HAL_GetCommandBitLength(GenericSPI_Type *SPIx) {
    return (SPIx->USER2 >> 28) & 0xF; // Extract bits [31:28]
}

// Function to set the command value (SPI_USR_COMMAND_VALUE)
void SPI_HAL_SetCommandValue(GenericSPI_Type *SPIx, uint16_t commandValue) {
    SPIx->USER2 = (SPIx->USER2 & ~(0xFFFF << 0)) | ((commandValue & 0xFFFF) << 0); // Set bits [15:0]
}

// Function to get the command value (SPI_USR_COMMAND_VALUE)
uint16_t SPI_HAL_GetCommandValue(GenericSPI_Type *SPIx) {
    return SPIx->USER2 & 0xFFFF; // Extract bits [15:0]
}

/*SPI_MOSI_DLEN_REG (0x28)*/

// Function to set the MOSI data bit length (SPI_USR_MOSI_DBITLEN)
void SPI_HAL_SetMosiDataBitLength(GenericSPI_Type *SPIx, uint32_t bitLength) {
    SPIx->MOSI_DLEN = (bitLength & 0xFFFFFF); // Set bits [23:0]
}

// Function to get the MOSI data bit length (SPI_USR_MOSI_DBITLEN)
uint32_t SPI_HAL_GetMosiDataBitLength(GenericSPI_Type *SPIx) {
    return SPIx->MOSI_DLEN & 0xFFFFFF; // Extract bits [23:0]
}

/*SPI_MISO_DLEN_REG (0x2C)*/

// Function to set the MISO data bit length (SPI_USR_MISO_DBITLEN)
void SPI_HAL_SetMisoDataBitLength(GenericSPI_Type *SPIx, uint32_t bitLength) {
    SPIx->MISO_DLEN = (bitLength & 0xFFFFFF); // Set bits [23:0]
}

// Function to get the MISO data bit length (SPI_USR_MISO_DBITLEN)
uint32_t SPI_HAL_GetMisoDataBitLength(GenericSPI_Type *SPIx) {
    return SPIx->MISO_DLEN & 0xFFFFFF; // Extract bits [23:0]
}

/*SPI_SLV_WR_STATUS_REG (0x30)*/

// Function to set the value of SPI_SLV_WR_STATUS_REG
void SPI_HAL_SetSlaveWriteStatus(GenericSPI_Type *SPIx, uint32_t status) {
    SPIx->SLV_WR_STATUS = status; // Write the value to the register
}

// Function to get the value of SPI_SLV_WR_STATUS_REG
uint32_t SPI_HAL_GetSlaveWriteStatus(GenericSPI_Type *SPIx) {
    return SPIx->SLV_WR_STATUS; // Read and return the value of the register
}





/* SPI_PIN_REG (0x34) */

// Function to set the SPI_CS_KEEP_ACTIVE bit
void SPI_HAL_SetCsKeepActive(GenericSPI_Type *SPIx, bool enable) {
    if (enable) {
        SPIx->PIN |= (1 << 30); // Set SPI_CS_KEEP_ACTIVE to 1
    } else {
        SPIx->PIN &= ~(1 << 30); // Clear SPI_CS_KEEP_ACTIVE to 0
    }
}

// Function to check if SPI_CS_KEEP_ACTIVE is enabled
bool SPI_HAL_IsCsKeepActiveEnabled(GenericSPI_Type *SPIx) {
    return (SPIx->PIN & (1 << 30)) != 0;
}

// Function to set the SPI_CK_IDLE_EDGE bit
void SPI_HAL_SetClockIdleEdge(GenericSPI_Type *SPIx, bool highIdle) {
    if (highIdle) {
        SPIx->PIN |= (1 << 29); // Set SPI_CK_IDLE_EDGE to 1 (clock idle high)
    } else {
        SPIx->PIN &= ~(1 << 29); // Clear SPI_CK_IDLE_EDGE to 0 (clock idle low)
    }
}

// Function to check the SPI_CK_IDLE_EDGE bit
bool SPI_HAL_IsClockIdleHigh(GenericSPI_Type *SPIx) {
    return (SPIx->PIN & (1 << 29)) != 0;
}

// Function to enable or disable the SPI CS2 signal (SPI_CS2_DIS)
void SPI_HAL_SetCs2Enabled(GenericSPI_Type *SPIx, bool enable) {
    if (enable) {
        SPIx->PIN &= ~(1 << 2); // Clear SPI_CS2_DIS to 0 (enable CS2)
    } else {
        SPIx->PIN |= (1 << 2); // Set SPI_CS2_DIS to 1 (disable CS2)
    }
}

// Function to check if SPI CS2 is enabled
bool SPI_HAL_IsCs2Enabled(GenericSPI_Type *SPIx) {
    return (SPIx->PIN & (1 << 2)) == 0; // Return true if CS2 is enabled
}

// Function to enable or disable the SPI CS1 signal (SPI_CS1_DIS)
void SPI_HAL_SetCs1Enabled(GenericSPI_Type *SPIx, bool enable) {
    if (enable) {
        SPIx->PIN &= ~(1 << 1); // Clear SPI_CS1_DIS to 0 (enable CS1)
    } else {
        SPIx->PIN |= (1 << 1); // Set SPI_CS1_DIS to 1 (disable CS1)
    }
}

// Function to check if SPI CS1 is enabled
bool SPI_HAL_IsCs1Enabled(GenericSPI_Type *SPIx) {
    return (SPIx->PIN & (1 << 1)) == 0; // Return true if CS1 is enabled
}

// Function to enable or disable the SPI CS0 signal (SPI_CS0_DIS)
void SPI_HAL_SetCs0Enabled(GenericSPI_Type *SPIx, bool enable) {
    if (enable) {
        SPIx->PIN &= ~(1 << 0); // Clear SPI_CS0_DIS to 0 (enable CS0)
    } else {
        SPIx->PIN |= (1 << 0); // Set SPI_CS0_DIS to 1 (disable CS0)
    }
}

// Function to check if SPI CS0 is enabled
bool SPI_HAL_IsCs0Enabled(GenericSPI_Type *SPIx) {
    return (SPIx->PIN & (1 << 0)) == 0; // Return true if CS0 is enabled
}


/* SPI_SLAVE_REG (0x38) */

// Function to reset the SPI_SYNC_RESET bit
void SPI_HAL_ResetSync(GenericSPI_Type *SPIx) {
    SPIx->SLAVE |= (1 << 31); // Set SPI_SYNC_RESET to 1
    SPIx->SLAVE &= ~(1 << 31); // Clear SPI_SYNC_RESET to 0
}

// Function to set the SPI_SLAVE_MODE bit
void SPI_HAL_SetSlaveOrMaster(GenericSPI_Type *SPIx, bool enable) {
    if (enable) {
        SPIx->SLAVE |= (1 << 30); // Set SPI_SLAVE_MODE to 1 (slave mode)
    } else {
        SPIx->SLAVE &= ~(1 << 30); // Clear SPI_SLAVE_MODE to 0 (master mode)
    }
}

// Function to check if SPI is in slave mode
bool SPI_HAL_IsSlaveMode(GenericSPI_Type *SPIx) {
    return (SPIx->SLAVE & (1 << 30)) != 0;
}

// Function to enable or disable write and read data commands (SPI_SLV_WR_RD_BUF_EN)
void SPI_HAL_SetWriteReadBufferEnabled(GenericSPI_Type *SPIx, bool enable) {
    if (enable) {
        SPIx->SLAVE |= (1 << 29); // Set SPI_SLV_WR_RD_BUF_EN to 1
    } else {
        SPIx->SLAVE &= ~(1 << 29); // Clear SPI_SLV_WR_RD_BUF_EN to 0
    }
}

// Function to check if write and read data commands are enabled
bool SPI_HAL_IsWriteReadBufferEnabled(GenericSPI_Type *SPIx) {
    return (SPIx->SLAVE & (1 << 29)) != 0;
}

// Function to enable or disable write and read status commands (SPI_SLV_WR_RD_STA_EN)
void SPI_HAL_SetWriteReadStatusEnabled(GenericSPI_Type *SPIx, bool enable) {
    if (enable) {
        SPIx->SLAVE |= (1 << 28); // Set SPI_SLV_WR_RD_STA_EN to 1
    } else {
        SPIx->SLAVE &= ~(1 << 28); // Clear SPI_SLV_WR_RD_STA_EN to 0
    }
}

// Function to check if write and read status commands are enabled
bool SPI_HAL_IsWriteReadStatusEnabled(GenericSPI_Type *SPIx) {
    return (SPIx->SLAVE & (1 << 28)) != 0;
}

// Function to get the operation counter (SPI_TRANS_CNT)
uint8_t SPI_HAL_GetTransactionCount(GenericSPI_Type *SPIx) {
    return (SPIx->SLAVE >> 23) & 0xF; // Extract bits [27:23]
}

// Function to get the last state of the SPI state machine (SPI_SLV_LAST_STATE)
uint8_t SPI_HAL_GetLastState(GenericSPI_Type *SPIx) {
    return (SPIx->SLAVE >> 20) & 0x7; // Extract bits [22:19]
}

// Function to enable or disable the SPI_TRANS_DONE interrupt (SPI_TRANS_INTEN)
void SPI_HAL_SetTransactionDoneInterrupt(GenericSPI_Type *SPIx, bool enable) {
    if (enable) {
        SPIx->SLAVE |= (1 << 9); // Set SPI_TRANS_INTEN to 1
    } else {
        SPIx->SLAVE &= ~(1 << 9); // Clear SPI_TRANS_INTEN to 0
    }
}

// Function to check if the SPI_TRANS_DONE interrupt is enabled
bool SPI_HAL_IsTransactionDoneInterruptEnabled(GenericSPI_Type *SPIx) {
    return (SPIx->SLAVE & (1 << 9)) != 0;
}

// Function to enable or disable the SPI_SLV_WR_STA_INT interrupt
void SPI_HAL_SetWriteStatusInterrupt(GenericSPI_Type *SPIx, bool enable) {
    if (enable) {
        SPIx->SLAVE |= (1 << 8); // Set SPI_SLV_WR_STA_INTEN to 1
    } else {
        SPIx->SLAVE &= ~(1 << 8); // Clear SPI_SLV_WR_STA_INTEN to 0
    }
}

// Function to check if the SPI_SLV_WR_STA_INT interrupt is enabled
bool SPI_HAL_IsWriteStatusInterruptEnabled(GenericSPI_Type *SPIx) {
    return (SPIx->SLAVE & (1 << 8)) != 0;
}

// Function to enable or disable the SPI_SLV_RD_STA_INT interrupt
void SPI_HAL_SetReadStatusInterrupt(GenericSPI_Type *SPIx, bool enable) {
    if (enable) {
        SPIx->SLAVE |= (1 << 7); // Set SPI_SLV_RD_STA_INTEN to 1
    } else {
        SPIx->SLAVE &= ~(1 << 7); // Clear SPI_SLV_RD_STA_INTEN to 0
    }
}

// Function to check if the SPI_SLV_RD_STA_INT interrupt is enabled
bool SPI_HAL_IsReadStatusInterruptEnabled(GenericSPI_Type *SPIx) {
    return (SPIx->SLAVE & (1 << 7)) != 0;
}

// Function to enable or disable the SPI_SLV_WR_BUF_INT interrupt
void SPI_HAL_SetWriteBufferInterrupt(GenericSPI_Type *SPIx, bool enable) {
    if (enable) {
        SPIx->SLAVE |= (1 << 6); // Set SPI_SLV_WR_BUF_INTEN to 1
    } else {
        SPIx->SLAVE &= ~(1 << 6); // Clear SPI_SLV_WR_BUF_INTEN to 0
    }
}

// Function to check if the SPI_SLV_WR_BUF_INT interrupt is enabled
bool SPI_HAL_IsWriteBufferInterruptEnabled(GenericSPI_Type *SPIx) {
    return (SPIx->SLAVE & (1 << 6)) != 0;
}

// Function to enable or disable the SPI_SLV_RD_BUF_INT interrupt
void SPI_HAL_SetReadBufferInterrupt(GenericSPI_Type *SPIx, bool enable) {
    if (enable) {
        SPIx->SLAVE |= (1 << 5); // Set SPI_SLV_RD_BUF_INTEN to 1
    } else {
        SPIx->SLAVE &= ~(1 << 5); // Clear SPI_SLV_RD_BUF_INTEN to 0
    }
}

// Function to check if the SPI_SLV_RD_BUF_INT interrupt is enabled
bool SPI_HAL_IsReadBufferInterruptEnabled(GenericSPI_Type *SPIx) {
    return (SPIx->SLAVE & (1 << 5)) != 0;
}

// Function to check if the SPI_TRANS_DONE interrupt is triggered
bool SPI_HAL_IsTransactionDone(GenericSPI_Type *SPIx) {
    return (SPIx->SLAVE & (1 << 4)) != 0; // Check SPI_TRANS_DONE bit
}

// Function to clear the SPI_TRANS_DONE interrupt
void SPI_HAL_ClearTransactionDone(GenericSPI_Type *SPIx) {
    SPIx->SLAVE &= ~(1 << 4); // Clear SPI_TRANS_DONE bit
}

// Function to check if the SPI_SLV_WR_STA_DONE interrupt is triggered
bool SPI_HAL_IsWriteStatusDone(GenericSPI_Type *SPIx) {
    return (SPIx->SLAVE & (1 << 3)) != 0; // Check SPI_SLV_WR_STA_DONE bit
}

// Function to clear the SPI_SLV_WR_STA_DONE interrupt
void SPI_HAL_ClearWriteStatusDone(GenericSPI_Type *SPIx) {
    SPIx->SLAVE &= ~(1 << 3); // Clear SPI_SLV_WR_STA_DONE bit
}

// Function to check if the SPI_SLV_RD_STA_DONE interrupt is triggered
bool SPI_HAL_IsReadStatusDone(GenericSPI_Type *SPIx) {
    return (SPIx->SLAVE & (1 << 2)) != 0; // Check SPI_SLV_RD_STA_DONE bit
}

// Function to clear the SPI_SLV_RD_STA_DONE interrupt
void SPI_HAL_ClearReadStatusDone(GenericSPI_Type *SPIx) {
    SPIx->SLAVE &= ~(1 << 2); // Clear SPI_SLV_RD_STA_DONE bit
}

// Function to check if the SPI_SLV_WR_BUF_DONE interrupt is triggered
bool SPI_HAL_IsWriteBufferDone(GenericSPI_Type *SPIx) {
    return (SPIx->SLAVE & (1 << 1)) != 0; // Check SPI_SLV_WR_BUF_DONE bit
}

// Function to clear the SPI_SLV_WR_BUF_DONE interrupt
void SPI_HAL_ClearWriteBufferDone(GenericSPI_Type *SPIx) {
    SPIx->SLAVE &= ~(1 << 1); // Clear SPI_SLV_WR_BUF_DONE bit
}

// Function to check if the SPI_SLV_RD_BUF_DONE interrupt is triggered
bool SPI_HAL_IsReadBufferDone(GenericSPI_Type *SPIx) {
    return (SPIx->SLAVE & (1 << 0)) != 0; // Check SPI_SLV_RD_BUF_DONE bit
}

// Function to clear the SPI_SLV_RD_BUF_DONE interrupt
void SPI_HAL_ClearReadBufferDone(GenericSPI_Type *SPIx) {
    SPIx->SLAVE &= ~(1 << 0); // Clear SPI_SLV_RD_BUF_DONE bit
}






/* SPI_SLAVE1_REG (0x3C) */

// Function to set the SPI_SLV_STATUS_BITLEN
void SPI_HAL_SetSlaveStatusBitLength(GenericSPI_Type *SPIx, uint8_t bitLength) {
    SPIx->SLAVE1 = (SPIx->SLAVE1 & ~(0x1F << 27)) | ((bitLength & 0x1F) << 27); // Set bits [31:27]
}

// Function to get the SPI_SLV_STATUS_BITLEN
uint8_t SPI_HAL_GetSlaveStatusBitLength(GenericSPI_Type *SPIx) {
    return (SPIx->SLAVE1 >> 27) & 0x1F; // Extract bits [31:27]
}

// Function to set the SPI_SLV_RD_ADDR_BITLEN
void SPI_HAL_SetSlaveReadAddressBitLength(GenericSPI_Type *SPIx, uint8_t bitLength) {
    SPIx->SLAVE1 = (SPIx->SLAVE1 & ~(0x3F << 10)) | ((bitLength & 0x3F) << 10); // Set bits [15:10]
}

// Function to get the SPI_SLV_RD_ADDR_BITLEN
uint8_t SPI_HAL_GetSlaveReadAddressBitLength(GenericSPI_Type *SPIx) {
    return (SPIx->SLAVE1 >> 10) & 0x3F; // Extract bits [15:10]
}

// Function to set the SPI_SLV_WR_ADDR_BITLEN
void SPI_HAL_SetSlaveWriteAddressBitLength(GenericSPI_Type *SPIx, uint8_t bitLength) {
    SPIx->SLAVE1 = (SPIx->SLAVE1 & ~(0x3F << 4)) | ((bitLength & 0x3F) << 4); // Set bits [9:4]
}

// Function to get the SPI_SLV_WR_ADDR_BITLEN
uint8_t SPI_HAL_GetSlaveWriteAddressBitLength(GenericSPI_Type *SPIx) {
    return (SPIx->SLAVE1 >> 4) & 0x3F; // Extract bits [9:4]
}

// Function to enable or disable the SPI_SLV_WRSTA_DUMMY_EN bit
void SPI_HAL_SetWriteStatusDummyEnabled(GenericSPI_Type *SPIx, bool enable) {
    if (enable) {
        SPIx->SLAVE1 |= (1 << 3); // Set SPI_SLV_WRSTA_DUMMY_EN to 1
    } else {
        SPIx->SLAVE1 &= ~(1 << 3); // Clear SPI_SLV_WRSTA_DUMMY_EN to 0
    }
}

// Function to check if SPI_SLV_WRSTA_DUMMY_EN is enabled
bool SPI_HAL_IsWriteStatusDummyEnabled(GenericSPI_Type *SPIx) {
    return (SPIx->SLAVE1 & (1 << 3)) != 0;
}

// Function to enable or disable the SPI_SLV_RDSTA_DUMMY_EN bit
void SPI_HAL_SetReadStatusDummyEnabled(GenericSPI_Type *SPIx, bool enable) {
    if (enable) {
        SPIx->SLAVE1 |= (1 << 2); // Set SPI_SLV_RDSTA_DUMMY_EN to 1
    } else {
        SPIx->SLAVE1 &= ~(1 << 2); // Clear SPI_SLV_RDSTA_DUMMY_EN to 0
    }
}

// Function to check if SPI_SLV_RDSTA_DUMMY_EN is enabled
bool SPI_HAL_IsReadStatusDummyEnabled(GenericSPI_Type *SPIx) {
    return (SPIx->SLAVE1 & (1 << 2)) != 0;
}

// Function to enable or disable the SPI_SLV_WRBUF_DUMMY_EN bit
void SPI_HAL_SetWriteBufferDummyEnabled(GenericSPI_Type *SPIx, bool enable) {
    if (enable) {
        SPIx->SLAVE1 |= (1 << 1); // Set SPI_SLV_WRBUF_DUMMY_EN to 1
    } else {
        SPIx->SLAVE1 &= ~(1 << 1); // Clear SPI_SLV_WRBUF_DUMMY_EN to 0
    }
}

// Function to check if SPI_SLV_WRBUF_DUMMY_EN is enabled
bool SPI_HAL_IsWriteBufferDummyEnabled(GenericSPI_Type *SPIx) {
    return (SPIx->SLAVE1 & (1 << 1)) != 0;
}

// Function to enable or disable the SPI_SLV_RDBUF_DUMMY_EN bit
void SPI_HAL_SetReadBufferDummyEnabled(GenericSPI_Type *SPIx, bool enable) {
    if (enable) {
        SPIx->SLAVE1 |= (1 << 0); // Set SPI_SLV_RDBUF_DUMMY_EN to 1
    } else {
        SPIx->SLAVE1 &= ~(1 << 0); // Clear SPI_SLV_RDBUF_DUMMY_EN to 0
    }
}

// Function to check if SPI_SLV_RDBUF_DUMMY_EN is enabled
bool SPI_HAL_IsReadBufferDummyEnabled(GenericSPI_Type *SPIx) {
    return (SPIx->SLAVE1 & (1 << 0)) != 0;
}




/* SPI_SLAVE2_REG (0x40) */

// Function to set the SPI_SLV_WRBUF_DUMMY_CYCLELEN
void SPI_HAL_SetWriteBufferDummyCycleLength(GenericSPI_Type *SPIx, uint8_t cycleLength) {
    SPIx->SLAVE2 = (SPIx->SLAVE2 & ~(0xFF << 24)) | ((cycleLength & 0xFF) << 24); // Set bits [31:24]
}

// Function to get the SPI_SLV_WRBUF_DUMMY_CYCLELEN
uint8_t SPI_HAL_GetWriteBufferDummyCycleLength(GenericSPI_Type *SPIx) {
    return (SPIx->SLAVE2 >> 24) & 0xFF; // Extract bits [31:24]
}

// Function to set the SPI_SLV_RDBUF_DUMMY_CYCLELEN
void SPI_HAL_SetReadBufferDummyCycleLength(GenericSPI_Type *SPIx, uint8_t cycleLength) {
    SPIx->SLAVE2 = (SPIx->SLAVE2 & ~(0xFF << 16)) | ((cycleLength & 0xFF) << 16); // Set bits [23:16]
}

// Function to get the SPI_SLV_RDBUF_DUMMY_CYCLELEN
uint8_t SPI_HAL_GetReadBufferDummyCycleLength(GenericSPI_Type *SPIx) {
    return (SPIx->SLAVE2 >> 16) & 0xFF; // Extract bits [23:16]
}

// Function to set the SPI_SLV_WRSTA_DUMMY_CYCLELEN
void SPI_HAL_SetWriteStatusDummyCycleLength(GenericSPI_Type *SPIx, uint8_t cycleLength) {
    SPIx->SLAVE2 = (SPIx->SLAVE2 & ~(0xFF << 8)) | ((cycleLength & 0xFF) << 8); // Set bits [15:8]
}

// Function to get the SPI_SLV_WRSTA_DUMMY_CYCLELEN
uint8_t SPI_HAL_GetWriteStatusDummyCycleLength(GenericSPI_Type *SPIx) {
    return (SPIx->SLAVE2 >> 8) & 0xFF; // Extract bits [15:8]
}

// Function to set the SPI_SLV_RDSTA_DUMMY_CYCLELEN
void SPI_HAL_SetReadStatusDummyCycleLength(GenericSPI_Type *SPIx, uint8_t cycleLength) {
    SPIx->SLAVE2 = (SPIx->SLAVE2 & ~(0xFF << 0)) | ((cycleLength & 0xFF) << 0); // Set bits [7:0]
}

// Function to get the SPI_SLV_RDSTA_DUMMY_CYCLELEN
uint8_t SPI_HAL_GetReadStatusDummyCycleLength(GenericSPI_Type *SPIx) {
    return SPIx->SLAVE2 & 0xFF; // Extract bits [7:0]
}






/* SPI_SLV_WRBUF_DLEN_REG (0x48) */

// Function to set the SPI_SLV_WRBUF_DBITLEN
void SPI_HAL_SetWriteBufferDataBitLength(GenericSPI_Type *SPIx, uint32_t bitLength) {
    SPIx->SLV_WRBUF_DLEN = (bitLength & 0xFFFFFF); // Set bits [23:0]
}

// Function to get the SPI_SLV_WRBUF_DBITLEN
uint32_t SPI_HAL_GetWriteBufferDataBitLength(GenericSPI_Type *SPIx) {
    return SPIx->SLV_WRBUF_DLEN & 0xFFFFFF; // Extract bits [23:0]
}




/* SPI_SLV_RDBUF_DLEN_REG (0x4C) */

// Function to set the SPI_SLV_RDBUF_DBITLEN
void SPI_HAL_SetReadBufferDataBitLength(GenericSPI_Type *SPIx, uint32_t bitLength) {
    SPIx->SLV_RDBUF_DLEN = (bitLength & 0xFFFFFF); // Set bits [23:0]
}

// Function to get the SPI_SLV_RDBUF_DBITLEN
uint32_t SPI_HAL_GetReadBufferDataBitLength(GenericSPI_Type *SPIx) {
    return SPIx->SLV_RDBUF_DLEN & 0xFFFFFF; // Extract bits [23:0]
}



/* SPI_SLV_RD_BIT_REG (0x64) */

// Function to set the SPI_SLV_RDATA_BIT
void SPI_HAL_SetReadDataBitLength(GenericSPI_Type *SPIx, uint32_t bitLength) {
    SPIx->SLV_RD_BIT = (bitLength & 0xFFFFFF); // Set bits [23:0]
}

// Function to get the SPI_SLV_RDATA_BIT
uint32_t SPI_HAL_GetReadDataBitLength(GenericSPI_Type *SPIx) {
    return SPIx->SLV_RD_BIT & 0xFFFFFF; // Extract bits [23:0]
}





/* SPI_Wn_REG (0x80 + 4 * n) */

// Function to set the value of a specific SPI_Wn_REG
void SPI_HAL_SetDataBuffer(GenericSPI_Type *SPIx, uint8_t index, uint32_t value) {
    SPIx->W0 = value; // Write the value to the appropriate SPI_Wn_REG.
}

// Function to get the value of a specific SPI_Wn_REG
uint32_t SPI_HAL_GetDataBuffer(GenericSPI_Type *SPIx, uint8_t index) {
    if (index < 16) { // Ensure the index is within the valid range (0–15)
        return *((&SPIx->W0) + index); // Adding index to &SPIx->W0 effectively moves the pointer by index * sizeof(uint32_t) bytes.
    }
    return 0; // Return 0 if the index is out of range
}




/* SPI_EXT2_REG (0xF8) */   

// Function to get the current state of the SPI state machine (SPI_ST)
uint8_t SPI_HAL_GetState(GenericSPI_Type *SPIx) {
    return SPIx->EXT2 & 0x7; // Extract bits [2:0]
}

// Function to check if the SPI is in a specific state
bool SPI_HAL_IsState(GenericSPI_Type *SPIx, uint8_t state) {
    return (SPIx->EXT2 & 0x7) == state; // Compare bits [2:0] with the given state
}




/* SPI_DMA_CONF_REG (0x100) */

// Function to enable or disable SPI DMA continuous TX/RX mode (SPI_DMA_CONTINUE)
void SPI_HAL_SetDmaContinue(GenericSPI_Type *SPIx, bool enable) {
    if (enable) {
        SPIx->DMA_CONF |= (1 << 16); // Set SPI_DMA_CONTINUE to 1
    } else {
        SPIx->DMA_CONF &= ~(1 << 16); // Clear SPI_DMA_CONTINUE to 0
    }
}

// Function to check if SPI DMA continuous TX/RX mode is enabled
bool SPI_HAL_IsDmaContinueEnabled(GenericSPI_Type *SPIx) {
    return (SPIx->DMA_CONF & (1 << 16)) != 0;
}

// Function to stop SPI DMA TX in continuous mode (SPI_DMA_TX_STOP)
void SPI_HAL_SetDmaTxStop(GenericSPI_Type *SPIx, bool stop) {
    if (stop) {
        SPIx->DMA_CONF |= (1 << 15); // Set SPI_DMA_TX_STOP to 1
    } else {
        SPIx->DMA_CONF &= ~(1 << 15); // Clear SPI_DMA_TX_STOP to 0
    }
}

// Function to stop SPI DMA RX in continuous mode (SPI_DMA_RX_STOP)
void SPI_HAL_SetDmaRxStop(GenericSPI_Type *SPIx, bool stop) {
    if (stop) {
        SPIx->DMA_CONF |= (1 << 14); // Set SPI_DMA_RX_STOP to 1
    } else {
        SPIx->DMA_CONF &= ~(1 << 14); // Clear SPI_DMA_RX_STOP to 0
    }
}

// Function to enable or disable SPI DMA burst mode for data (SPI_OUT_DATA_BURST_EN)
void SPI_HAL_SetOutDataBurstEnabled(GenericSPI_Type *SPIx, bool enable) {
    if (enable) {
        SPIx->DMA_CONF |= (1 << 12); // Set SPI_OUT_DATA_BURST_EN to 1
    } else {
        SPIx->DMA_CONF &= ~(1 << 12); // Clear SPI_OUT_DATA_BURST_EN to 0
    }
}

// Function to check if SPI DMA burst mode for data is enabled
bool SPI_HAL_IsOutDataBurstEnabled(GenericSPI_Type *SPIx) {
    return (SPIx->DMA_CONF & (1 << 12)) != 0;
}

// Function to enable or disable SPI DMA burst mode for inlink descriptor (SPI_INDSCR_BURST_EN)
void SPI_HAL_SetInDescriptorBurstEnabled(GenericSPI_Type *SPIx, bool enable) {
    if (enable) {
        SPIx->DMA_CONF |= (1 << 11); // Set SPI_INDSCR_BURST_EN to 1
    } else {
        SPIx->DMA_CONF &= ~(1 << 11); // Clear SPI_INDSCR_BURST_EN to 0
    }
}

// Function to enable or disable SPI DMA burst mode for outlink descriptor (SPI_OUTDSCR_BURST_EN)
void SPI_HAL_SetOutDescriptorBurstEnabled(GenericSPI_Type *SPIx, bool enable) {
    if (enable) {
        SPIx->DMA_CONF |= (1 << 10); // Set SPI_OUTDSCR_BURST_EN to 1
    } else {
        SPIx->DMA_CONF &= ~(1 << 10); // Clear SPI_OUTDSCR_BURST_EN to 0
    }
}

// Function to set the SPI_OUT_EOF_MODE
void SPI_HAL_SetOutEofMode(GenericSPI_Type *SPIx, bool mode) {
    if (mode) {
        SPIx->DMA_CONF |= (1 << 9); // Set SPI_OUT_EOF_MODE to 1
    } else {
        SPIx->DMA_CONF &= ~(1 << 9); // Clear SPI_OUT_EOF_MODE to 0
    }
}

// Function to reset SPI DMA AHB master (SPI_AHBM_RST)
void SPI_HAL_ResetAhbMaster(GenericSPI_Type *SPIx) {
    SPIx->DMA_CONF |= (1 << 5); // Set SPI_AHBM_RST to 1
    SPIx->DMA_CONF &= ~(1 << 5); // Clear SPI_AHBM_RST to 0
}

// Function to reset SPI DMA AHB master FIFO pointer (SPI_AHBM_FIFO_RST)
void SPI_HAL_ResetAhbMasterFifo(GenericSPI_Type *SPIx) {
    SPIx->DMA_CONF |= (1 << 4); // Set SPI_AHBM_FIFO_RST to 1
    SPIx->DMA_CONF &= ~(1 << 4); // Clear SPI_AHBM_FIFO_RST to 0
}

// Function to reset DMA out-FSM and out-data FIFO pointer (SPI_OUT_RST)
void SPI_HAL_ResetOutFsm(GenericSPI_Type *SPIx) {
    SPIx->DMA_CONF |= (1 << 3); // Set SPI_OUT_RST to 1
    SPIx->DMA_CONF &= ~(1 << 3); // Clear SPI_OUT_RST to 0
}

// Function to reset DMA in-FSM and in-data FIFO pointer (SPI_IN_RST)
void SPI_HAL_ResetInFsm(GenericSPI_Type *SPIx) {
    SPIx->DMA_CONF |= (1 << 2); // Set SPI_IN_RST to 1
    SPIx->DMA_CONF &= ~(1 << 2); // Clear SPI_IN_RST to 0
}


/* SPI_DMA_OUT_LINK_REG (0x104) */

// Function to set the SPI_OUTLINK_RESTART bit
void SPI_HAL_SetOutlinkRestart(GenericSPI_Type *SPIx, bool enable) {
    if (enable) {
        SPIx->DMA_OUT_LINK |= (1 << 30); // Set SPI_OUTLINK_RESTART to 1
    } else {
        SPIx->DMA_OUT_LINK &= ~(1 << 30); // Clear SPI_OUTLINK_RESTART to 0
    }
}

// Function to check if SPI_OUTLINK_RESTART is set
bool SPI_HAL_IsOutlinkRestartEnabled(GenericSPI_Type *SPIx) {
    return (SPIx->DMA_OUT_LINK & (1 << 30)) != 0;
}

// Function to set the SPI_OUTLINK_START bit
void SPI_HAL_SetOutlinkStart(GenericSPI_Type *SPIx, bool enable) {
    if (enable) {
        SPIx->DMA_OUT_LINK |= (1 << 29); // Set SPI_OUTLINK_START to 1
    } else {
        SPIx->DMA_OUT_LINK &= ~(1 << 29); // Clear SPI_OUTLINK_START to 0
    }
}

// Function to check if SPI_OUTLINK_START is set
bool SPI_HAL_IsOutlinkStartEnabled(GenericSPI_Type *SPIx) {
    return (SPIx->DMA_OUT_LINK & (1 << 29)) != 0;
}

// Function to set the SPI_OUTLINK_STOP bit
void SPI_HAL_SetOutlinkStop(GenericSPI_Type *SPIx, bool enable) {
    if (enable) {
        SPIx->DMA_OUT_LINK |= (1 << 28); // Set SPI_OUTLINK_STOP to 1
    } else {
        SPIx->DMA_OUT_LINK &= ~(1 << 28); // Clear SPI_OUTLINK_STOP to 0
    }
}

// Function to check if SPI_OUTLINK_STOP is set
bool SPI_HAL_IsOutlinkStopEnabled(GenericSPI_Type *SPIx) {
    return (SPIx->DMA_OUT_LINK & (1 << 28)) != 0;
}

// Function to set the SPI_OUTLINK_ADDR
void SPI_HAL_SetOutlinkAddress(GenericSPI_Type *SPIx, uint32_t address) {
    SPIx->DMA_OUT_LINK = (SPIx->DMA_OUT_LINK & ~0xFFFFF) | (address & 0xFFFFF); // Set bits [19:0]
}

// Function to get the SPI_OUTLINK_ADDR
uint32_t SPI_HAL_GetOutlinkAddress(GenericSPI_Type *SPIx) {
    return SPIx->DMA_OUT_LINK & 0xFFFFF; // Extract bits [19:0]
}




/* SPI_DMA_IN_LINK_REG (0x108) */

// Function to set the SPI_INLINK_RESTART bit
void SPI_HAL_SetInlinkRestart(GenericSPI_Type *SPIx, bool enable) {
    if (enable) {
        SPIx->DMA_IN_LINK |= (1 << 30); // Set SPI_INLINK_RESTART to 1
    } else {
        SPIx->DMA_IN_LINK &= ~(1 << 30); // Clear SPI_INLINK_RESTART to 0
    }
}

// Function to check if SPI_INLINK_RESTART is set
bool SPI_HAL_IsInlinkRestartEnabled(GenericSPI_Type *SPIx) {
    return (SPIx->DMA_IN_LINK & (1 << 30)) != 0;
}

// Function to set the SPI_INLINK_START bit
void SPI_HAL_SetInlinkStart(GenericSPI_Type *SPIx, bool enable) {
    if (enable) {
        SPIx->DMA_IN_LINK |= (1 << 29); // Set SPI_INLINK_START to 1
    } else {
        SPIx->DMA_IN_LINK &= ~(1 << 29); // Clear SPI_INLINK_START to 0
    }
}

// Function to check if SPI_INLINK_START is set
bool SPI_HAL_IsInlinkStartEnabled(GenericSPI_Type *SPIx) {
    return (SPIx->DMA_IN_LINK & (1 << 29)) != 0;
}

// Function to set the SPI_INLINK_STOP bit
void SPI_HAL_SetInlinkStop(GenericSPI_Type *SPIx, bool enable) {
    if (enable) {
        SPIx->DMA_IN_LINK |= (1 << 28); // Set SPI_INLINK_STOP to 1
    } else {
        SPIx->DMA_IN_LINK &= ~(1 << 28); // Clear SPI_INLINK_STOP to 0
    }
}

// Function to check if SPI_INLINK_STOP is set
bool SPI_HAL_IsInlinkStopEnabled(GenericSPI_Type *SPIx) {
    return (SPIx->DMA_IN_LINK & (1 << 28)) != 0;
}

// Function to set the SPI_INLINK_AUTO_RET bit
void SPI_HAL_SetInlinkAutoRet(GenericSPI_Type *SPIx, bool enable) {
    if (enable) {
        SPIx->DMA_IN_LINK |= (1 << 20); // Set SPI_INLINK_AUTO_RET to 1
    } else {
        SPIx->DMA_IN_LINK &= ~(1 << 20); // Clear SPI_INLINK_AUTO_RET to 0
    }
}

// Function to check if SPI_INLINK_AUTO_RET is set
bool SPI_HAL_IsInlinkAutoRetEnabled(GenericSPI_Type *SPIx) {
    return (SPIx->DMA_IN_LINK & (1 << 20)) != 0;
}

// Function to set the SPI_INLINK_ADDR
void SPI_HAL_SetInlinkAddress(GenericSPI_Type *SPIx, uint32_t address) {
    SPIx->DMA_IN_LINK = (SPIx->DMA_IN_LINK & ~0xFFFFF) | (address & 0xFFFFF); // Set bits [19:0]
}

// Function to get the SPI_INLINK_ADDR
uint32_t SPI_HAL_GetInlinkAddress(GenericSPI_Type *SPIx) {
    return SPIx->DMA_IN_LINK & 0xFFFFF; // Extract bits [19:0]
}





/* SPI_DMA_STATUS_REG (0x10C) */

// Function to check if SPI DMA write-data is enabled (SPI_DMA_TX_EN)
bool SPI_HAL_IsDmaWriteEnabled(GenericSPI_Type *SPIx) {
    return (SPIx->DMA_STATUS & (1 << 1)) != 0; // Check bit 1
}

// Function to check if SPI DMA read-data is enabled (SPI_DMA_RX_EN)
bool SPI_HAL_IsDmaReadEnabled(GenericSPI_Type *SPIx) {
    return (SPIx->DMA_STATUS & (1 << 0)) != 0; // Check bit 0
}




/* SPI_DMA_INT_RAW_REG  (0x114)*/

// Function to check the raw status of the SPI_OUT_TOTAL_EOF_INT interrupt
bool SPI_HAL_IsOutTotalEofInterruptRaw(GenericSPI_Type *SPIx) {
    return (SPIx->DMA_INT_RAW & (1 << 8)) != 0; // Check bit 8
}

// Function to check the raw status of the SPI_OUT_EOF_INT interrupt
bool SPI_HAL_IsOutEofInterruptRaw(GenericSPI_Type *SPIx) {
    return (SPIx->DMA_INT_RAW & (1 << 7)) != 0; // Check bit 7
}

// Function to check the raw status of the SPI_OUT_DONE_INT interrupt
bool SPI_HAL_IsOutDoneInterruptRaw(GenericSPI_Type *SPIx) {
    return (SPIx->DMA_INT_RAW & (1 << 6)) != 0; // Check bit 6
}

// Function to check the raw status of the SPI_IN_SUC_EOF_INT interrupt
bool SPI_HAL_IsInSucEofInterruptRaw(GenericSPI_Type *SPIx) {
    return (SPIx->DMA_INT_RAW & (1 << 5)) != 0; // Check bit 5
}

// Function to check the raw status of the SPI_IN_ERR_EOF_INT interrupt
bool SPI_HAL_IsInErrEofInterruptRaw(GenericSPI_Type *SPIx) {
    return (SPIx->DMA_INT_RAW & (1 << 4)) != 0; // Check bit 4
}

// Function to check the raw status of the SPI_IN_DONE_INT interrupt
bool SPI_HAL_IsInDoneInterruptRaw(GenericSPI_Type *SPIx) {
    return (SPIx->DMA_INT_RAW & (1 << 3)) != 0; // Check bit 3
}

// Function to check the raw status of the SPI_INLINK_DSCR_ERROR_INT interrupt
bool SPI_HAL_IsInlinkDscrErrorInterruptRaw(GenericSPI_Type *SPIx) {
    return (SPIx->DMA_INT_RAW & (1 << 2)) != 0; // Check bit 2
}

// Function to check the raw status of the SPI_OUTLINK_DSCR_ERROR_INT interrupt
bool SPI_HAL_IsOutlinkDscrErrorInterruptRaw(GenericSPI_Type *SPIx) {
    return (SPIx->DMA_INT_RAW & (1 << 1)) != 0; // Check bit 1
}

// Function to check the raw status of the SPI_INLINK_DSCR_EMPTY_INT interrupt
bool SPI_HAL_IsInlinkDscrEmptyInterruptRaw(GenericSPI_Type *SPIx) {
    return (SPIx->DMA_INT_RAW & (1 << 0)) != 0; // Check bit 0
}




/* SPI_DMA_INT_ST_REG */

// Function to check the masked status of the SPI_OUT_TOTAL_EOF_INT interrupt
bool SPI_HAL_IsOutTotalEofInterruptMasked(GenericSPI_Type *SPIx) {
    return (SPIx->DMA_INT_ST & (1 << 8)) != 0; // Check bit 8
}

// Function to check the masked status of the SPI_OUT_EOF_INT interrupt
bool SPI_HAL_IsOutEofInterruptMasked(GenericSPI_Type *SPIx) {
    return (SPIx->DMA_INT_ST & (1 << 7)) != 0; // Check bit 7
}

// Function to check the masked status of the SPI_OUT_DONE_INT interrupt
bool SPI_HAL_IsOutDoneInterruptMasked(GenericSPI_Type *SPIx) {
    return (SPIx->DMA_INT_ST & (1 << 6)) != 0; // Check bit 6
}

// Function to check the masked status of the SPI_IN_SUC_EOF_INT interrupt
bool SPI_HAL_IsInSucEofInterruptMasked(GenericSPI_Type *SPIx) {
    return (SPIx->DMA_INT_ST & (1 << 5)) != 0; // Check bit 5
}

// Function to check the masked status of the SPI_IN_ERR_EOF_INT interrupt
bool SPI_HAL_IsInErrEofInterruptMasked(GenericSPI_Type *SPIx) {
    return (SPIx->DMA_INT_ST & (1 << 4)) != 0; // Check bit 4
}

// Function to check the masked status of the SPI_IN_DONE_INT interrupt
bool SPI_HAL_IsInDoneInterruptMasked(GenericSPI_Type *SPIx) {
    return (SPIx->DMA_INT_ST & (1 << 3)) != 0; // Check bit 3
}

// Function to check the masked status of the SPI_INLINK_DSCR_ERROR_INT interrupt
bool SPI_HAL_IsInlinkDscrErrorInterruptMasked(GenericSPI_Type *SPIx) {
    return (SPIx->DMA_INT_ST & (1 << 2)) != 0; // Check bit 2
}

// Function to check the masked status of the SPI_OUTLINK_DSCR_ERROR_INT interrupt
bool SPI_HAL_IsOutlinkDscrErrorInterruptMasked(GenericSPI_Type *SPIx) {
    return (SPIx->DMA_INT_ST & (1 << 1)) != 0; // Check bit 1
}

// Function to check the masked status of the SPI_INLINK_DSCR_EMPTY_INT interrupt
bool SPI_HAL_IsInlinkDscrEmptyInterruptMasked(GenericSPI_Type *SPIx) {
    return (SPIx->DMA_INT_ST & (1 << 0)) != 0; // Check bit 0
}



/* SPI_DMA_INT_CLR_REG */

// Function to clear the SPI_OUT_TOTAL_EOF_INT interrupt
void SPI_HAL_ClearOutTotalEofInterrupt(GenericSPI_Type *SPIx) {
    SPIx->DMA_INT_CLR |= (1 << 8); // Set bit 8 to clear the interrupt
}

// Function to clear the SPI_OUT_EOF_INT interrupt
void SPI_HAL_ClearOutEofInterrupt(GenericSPI_Type *SPIx) {
    SPIx->DMA_INT_CLR |= (1 << 7); // Set bit 7 to clear the interrupt
}

// Function to clear the SPI_OUT_DONE_INT interrupt
void SPI_HAL_ClearOutDoneInterrupt(GenericSPI_Type *SPIx) {
    SPIx->DMA_INT_CLR |= (1 << 6); // Set bit 6 to clear the interrupt
}

// Function to clear the SPI_IN_SUC_EOF_INT interrupt
void SPI_HAL_ClearInSucEofInterrupt(GenericSPI_Type *SPIx) {
    SPIx->DMA_INT_CLR |= (1 << 5); // Set bit 5 to clear the interrupt
}

// Function to clear the SPI_IN_ERR_EOF_INT interrupt
void SPI_HAL_ClearInErrEofInterrupt(GenericSPI_Type *SPIx) {
    SPIx->DMA_INT_CLR |= (1 << 4); // Set bit 4 to clear the interrupt
}

// Function to clear the SPI_IN_DONE_INT interrupt
void SPI_HAL_ClearInDoneInterrupt(GenericSPI_Type *SPIx) {
    SPIx->DMA_INT_CLR |= (1 << 3); // Set bit 3 to clear the interrupt
}

// Function to clear the SPI_INLINK_DSCR_ERROR_INT interrupt
void SPI_HAL_ClearInlinkDscrErrorInterrupt(GenericSPI_Type *SPIx) {
    SPIx->DMA_INT_CLR |= (1 << 2); // Set bit 2 to clear the interrupt
}

// Function to clear the SPI_OUTLINK_DSCR_ERROR_INT interrupt
void SPI_HAL_ClearOutlinkDscrErrorInterrupt(GenericSPI_Type *SPIx) {
    SPIx->DMA_INT_CLR |= (1 << 1); // Set bit 1 to clear the interrupt
}

// Function to clear the SPI_INLINK_DSCR_EMPTY_INT interrupt
void SPI_HAL_ClearInlinkDscrEmptyInterrupt(GenericSPI_Type *SPIx) {
    SPIx->DMA_INT_CLR |= (1 << 0); // Set bit 0 to clear the interrupt
}



/* SPI_IN_ERR_EOF_DES_ADDR_REG (0x120) */

// Function to get the inlink descriptor address when SPI DMA encountered an error in receiving data
uint32_t SPI_HAL_GetInErrEofDescriptorAddress(GenericSPI_Type *SPIx) {
    return SPIx->IN_ERR_EOF_DES_ADDR; // Read and return the value of the register
}




/* SPI_IN_SUC_EOF_DES_ADDR_REG (0x124) */

// Function to get the last inlink descriptor address when SPI DMA encountered EOF
uint32_t SPI_HAL_GetInSucEofDescriptorAddress(GenericSPI_Type *SPIx) {
    return SPIx->IN_SUC_EOF_DES_ADDR; // Read and return the value of the register
}



/* SPI_INLINK_DSCR_REG (0x128) */

// Function to get the address of the current inlink descriptor
uint32_t SPI_HAL_GetCurrentInlinkDescriptorAddress(GenericSPI_Type *SPIx) {
    return SPIx->INLINK_DSCR; // Read and return the value of the register
}





/* SPI_INLINK_DSCR_BFO_REG (0x12C) */

// Function to get the address of the next inlink descriptor
uint32_t SPI_HAL_GetNextInlinkDescriptorAddress(GenericSPI_Type *SPIx) {
    return SPIx->INLINK_DSCR_BF0; // Read and return the value of the register
}





/* SPI_INLINK_DSCR_BF1_REG (0x130) */

// Function to get the address of the next inlink data buffer
uint32_t SPI_HAL_GetNextInlinkDataBufferAddress(GenericSPI_Type *SPIx) {
    return SPIx->INLINK_DSCR_BF1; // Read and return the value of the register
}



/* SPI_OUT_EOF_BFR_DES_ADDR_REG (0x134) */

// Function to get the buffer address corresponding to the outlink descriptor that produces EOF
uint32_t SPI_HAL_GetOutEofBufferDescriptorAddress(GenericSPI_Type *SPIx) {
    return SPIx->OUT_EOF_BFR_DES_ADDR; // Read and return the value of the register
}





/* SPI_OUT_EOF_DES_ADDR_REG (0x138) */

// Function to get the last outlink descriptor address when SPI DMA encountered EOF
uint32_t SPI_HAL_GetOutEofDescriptorAddress(GenericSPI_Type *SPIx) {
    return SPIx->OUT_EOF_DES_ADDR; // Read and return the value of the register
}



/* SPI_OUTLINK_DSCR_REG (0x13C) */

// Function to get the address of the current outlink descriptor
uint32_t SPI_HAL_GetCurrentOutlinkDescriptorAddress(GenericSPI_Type *SPIx) {
    return SPIx->OUTLINK_DSCR; // Read and return the value of the register
}




/* SPI_OUTLINK_DSCR_BFO_REG (0x140) */

// Function to get the address of the next outlink descriptor
uint32_t SPI_HAL_GetNextOutlinkDescriptorAddress(GenericSPI_Type *SPIx) {
    return SPIx->OUTLINK_DSCR_BF0; // Read and return the value of the register
}




/* SPI_OUTLINK_DSCR_BF1_REG (0x144) */

// Function to get the address of the next outlink data buffer
uint32_t SPI_HAL_GetNextOutlinkDataBufferAddress(GenericSPI_Type *SPIx) {
    return SPIx->OUTLINK_DSCR_BF1; // Read and return the value of the register
}



/* SPI_DMA_RSTATUS_REG (0x148) */

// Function to check if the SPI DMA TX FIFO is empty
bool SPI_HAL_IsTxFifoEmpty(GenericSPI_Type *SPIx) {
    return (SPIx->DMA_RSTATUS & (1 << 31)) != 0; // Check bit 31
}

// Function to check if the SPI DMA TX FIFO is full
bool SPI_HAL_IsTxFifoFull(GenericSPI_Type *SPIx) {
    return (SPIx->DMA_RSTATUS & (1 << 30)) != 0; // Check bit 30
}

// Function to get the LSB of the SPI DMA outlink descriptor address
uint32_t SPI_HAL_GetTxDescriptorAddress(GenericSPI_Type *SPIx) {
    return SPIx->DMA_RSTATUS & 0xFFFFF; // Extract bits [19:0]
}



/* SPI_DMA_TSTATUS_REG (0x14C) */

// Function to check if the SPI DMA RX FIFO is empty
bool SPI_HAL_IsRxFifoEmpty(GenericSPI_Type *SPIx) {
    return (SPIx->DMA_TSTATUS & (1 << 31)) != 0; // Check bit 31
}

// Function to check if the SPI DMA RX FIFO is full
bool SPI_HAL_IsRxFifoFull(GenericSPI_Type *SPIx) {
    return (SPIx->DMA_TSTATUS & (1 << 30)) != 0; // Check bit 30
}

// Function to get the LSB of the SPI DMA inlink descriptor address
uint32_t SPI_HAL_GetRxDescriptorAddress(GenericSPI_Type *SPIx) {
    return SPIx->DMA_TSTATUS & 0xFFFFF; // Extract bits [19:0]
}