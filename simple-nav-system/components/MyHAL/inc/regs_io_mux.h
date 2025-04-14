/*
 * regs_io_mux.h
 *
 *  Created on: 14/04/2025
 *      Author: Diogo
 */

#ifndef COMPONENTS_MYHAL_INC_REGS_IO_MUX_H_
#define COMPONENTS_MYHAL_INC_REGS_IO_MUX_H_


#define IO_MUX_BASE                             0x3FF49000
#define IO_MUX_REG_SIZE                         32


#define IO_MUX_PIN_CTRL                         0x3FF49000    // 0x00 - GPIO pin control register         (R/W) 
#define IO_MUX_GPIO36_REG                       0x3FF49004    // 0x04 - GPIO36 configuration register     (R/W)
#define IO_MUX_GPIO37_REG                       0x3FF49008    // 0x08 - GPIO37 configuration register     (R/W)
#define IO_MUX_GPIO38_REG                       0x3FF4900C    // 0x0C - GPIO38 configuration register     (R/W)
#define IO_MUX_GPIO39_REG                       0x3FF49010    // 0x10 - GPIO39 configuration register     (R/W)
#define IO_MUX_GPIO34_REG                       0x3FF49014    // 0x14 - GPIO34 configuration register     (R/W)
#define IO_MUX_GPIO35_REG                       0x3FF49018    // 0x18 - GPIO35 configuration register     (R/W)
#define IO_MUX_GPIO32_REG                       0x3FF4901C    // 0x1C - GPIO32 configuration register     (R/W)
#define IO_MUX_GPIO33_REG                       0x3FF49020    // 0x20 - GPIO33 configuration register     (R/W)
#define IO_MUX_GPIO25_REG                       0x3FF49024    // 0x24 - GPIO25 configuration register     (R/W)
#define IO_MUX_GPIO26_REG                       0x3FF49028    // 0x28 - GPIO26 configuration register     (R/W)
#define IO_MUX_GPIO27_REG                       0x3FF4902C    // 0x2C - GPIO27 configuration register     (R/W)
#define IO_MUX_MTMS_REG                         0x3FF49030    // 0x30 - MTMS configuration register       (R/W)
#define IO_MUX_MTDI_REG                         0x3FF49034    // 0x34 - MTDI configuration register       (R/W)
#define IO_MUX_MTCK_REG                         0x3FF49038    // 0x38 - MTCK configuration register       (R/W)
#define IO_MUX_MTDO_REG                         0x3FF4903C    // 0x3C - MTDO configuration register       (R/W)
#define IO_MUX_GPIO2_REG                        0x3FF49040    // 0x40 - GPIO2 configuration register      (R/W)
#define IO_MUX_GPIO0_REG                        0x3FF49044    // 0x44 - GPIO0 configuration register      (R/W)
#define IO_MUX_GPIO4_REG                        0x3FF49048    // 0x48 - GPIO4 configuration register      (R/W)
#define IO_MUX_GPIO16_REG                       0x3FF4904C    // 0x4C - GPIO16 configuration register     (R/W)
#define IO_MUX_GPIO17_REG                       0x3FF49050    // 0x50 - GPIO17 configuration register     (R/W)
#define IO_MUX_SD_DATA2_REG                     0x3FF49054    // 0x54 - SD_DATA2 configuration register   (R/W)
#define IO_MUX_SD_DATA3_REG                     0x3FF49058    // 0x58 - SD_DATA3 configuration register   (R/W)
#define IO_MUX_SD_CMD_REG                       0x3FF4905C    // 0x5C - SD_CMD configuration register     (R/W)
#define IO_MUX_SD_CLK_REG                       0x3FF49060    // 0x60 - SD_CLK configuration register     (R/W)
#define IO_MUX_SD_DATA0_REG                     0x3FF49064    // 0x64 - SD_DATA0 configuration register   (R/W)
#define IO_MUX_SD_DATA1_REG                     0x3FF49068    // 0x68 - SD_DATA1 configuration register   (R/W)
#define IO_MUX_GPIO5_REG                        0x3FF4906C    // 0x6C - GPIO5 configuration register      (R/W)
#define IO_MUX_GPIO18_REG                       0x3FF49070    // 0x70 - GPIO18 configuration register     (R/W)
#define IO_MUX_GPIO19_REG                       0x3FF49074    // 0x74 - GPIO19 configuration register     (R/W)
#define IO_MUX_GPIO21_REG                       0x3FF4907C    // 0x7C - GPIO21 configuration register     (R/W)
#define IO_MUX_GPIO22_REG                       0x3FF49080    // 0x80 - GPIO22 configuration register     (R/W)
#define IO_MUX_U0RXD_REG                        0x3FF49084    // 0x84 - U0RXD configuration register      (R/W)
#define IO_MUX_U0TXD_REG                        0x3FF49088    // 0x88 - U0TXD configuration register      (R/W)
#define IO_MUX_GPIO23_REG                       0x3FF4908C    // 0x8C - GPIO23 configuration register     (R/W)

#endif /* COMPONENTS_MYHAL_INC_REGS_IO_MUX_H_ */
