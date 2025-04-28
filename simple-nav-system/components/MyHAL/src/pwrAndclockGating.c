/*
 * pwrAndclockGating.c
 *
 *  Created on: 28/04/2025
 *      Author: Diogo
 */

#include "regs_pwr_clkGating.h"
#include "pwrAndclockGating.h"
#include "regs_rstClock.h"
#include "rstClock.h"
#include "regs_spi_peripheral.h"


void PWR_CLKGTING_EnableSPIClk(int spiNum) {
    // Enable the clock for the specified SPI peripheral
    switch (spiNum) {
        case 0:
            DPORT_PERIP_CLK_EN_REG |= (1 << 1); // Enable clock for SPI0
            break;
        case 1:
            DPORT_PERIP_CLK_EN_REG |= (1 << 1); // Enable clock for SPI1
            break;
        case 2:
            DPORT_PERIP_CLK_EN_REG |= (1 << 6); // Enable clock for SPI2
            break;
        case 3:
            DPORT_PERIP_CLK_EN_REG |= (1 << 16); // Enable clock for SPI3
            break;
        default:
            // Invalid SPI number, do nothing
            break;
    }
}

void PWR_CLKGTING_DisableSPIClk(int spiNum) {
    // Disable the clock for the specified SPI peripheral
    switch (spiNum) {
        case 0:
            DPORT_PERIP_CLK_EN_REG &= ~(1 << 1); // Disable clock for SPI0
            break;
        case 1:
            DPORT_PERIP_CLK_EN_REG &= ~(1 << 1); // Disable clock for SPI1
            break;
        case 2:
            DPORT_PERIP_CLK_EN_REG &= ~(1 << 6); // Disable clock for SPI2
            break;
        case 3:
            DPORT_PERIP_CLK_EN_REG &= ~(1 << 16); // Disable clock for SPI3
            break;
        default:
            // Invalid SPI number, do nothing
            break;
    }
}

void PWR_CLKGTING_ResetSPIClk(int spiNum) {
    // Reset the specified SPI peripheral
    switch (spiNum) {
        case 0:
            DPORT_PERIP_RST_EN_REG &= ~(1 << 1);
            DPORT_PERIP_RST_EN_REG |= (1 << 1); 
            DPORT_PERIP_RST_EN_REG &= ~(1 << 1);
            break;
        case 1:
            DPORT_PERIP_RST_EN_REG &= ~(1 << 1);
            DPORT_PERIP_RST_EN_REG |= (1 << 1); 
            DPORT_PERIP_RST_EN_REG &= ~(1 << 1);
            break;
        case 2:
            DPORT_PERIP_RST_EN_REG &= ~(1 << 6);
            DPORT_PERIP_RST_EN_REG |= (1 << 6); 
            DPORT_PERIP_RST_EN_REG &= ~(1 << 6);
            break;
        case 3:
            DPORT_PERIP_RST_EN_REG &= ~(1 << 16);
            DPORT_PERIP_RST_EN_REG |= (1 << 16); 
            DPORT_PERIP_RST_EN_REG &= ~(1 << 16);
            break;
        default:
            // Invalid SPI number, do nothing
            break;
    }
}