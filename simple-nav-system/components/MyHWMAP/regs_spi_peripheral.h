/*
 * regs_spi_controller.h
 *
 *  Created on: 24/04/2025
 *      Author: Diogo
 */

 #ifndef COMPONENTS_MYHWMAP_REGS_SPI_CONTROLLER_H_
 #define COMPONENTS_MYHWMAP_REGS_SPI_CONTROLLER_H_
 
 #include <stdint.h>
 
 #ifdef __cplusplus
     #define   __I     volatile             /*!< Read-only permissions */
 #else
     #define   __I     volatile const       /*!< Read-only permissions */
 #endif
 #define     __O     volatile             /*!< Write-only permissions */
 #define     __IO    volatile             /*!< Read/write permissions */
 
 /* SPI Controller Base Addresses */
 #define SPI0_BASE                      0x3FF43000  /* Dedicated to flash memory */
 #define SPI1_BASE                      0x3FF42000  /* Master-only */
 #define SPI2_BASE                      0x3FF64000  /* Configurable master/slave (HSPI) */
 #define SPI3_BASE                      0x3FF65000  /* Configurable master/slave (VSPI) */
 
 /**
   * @brief SPI Controller Register Structure
   * 
   * Organized by functional groups:
   *  - Control/Configuration
   *  - Data Handling
   *  - Slave Mode
   *  - DMA
   */
typedef struct {

    /*------------------ Control/Configuration Registers ------------------*/
    __IO uint32_t CMD;         /*!< SPI Command Register 0x3FF43000 */
    __IO uint32_t ADDR;        /*!< SPI Address Register 0x3FF43004 */
    __IO uint32_t CTRL;        /*!< Control Register 0x3FF43008 */
         uint32_t CTRL1_REG;  /*!< Reserved 0x3FF4300C-0x3FF4300c */
         uint32_t RD_STATUS_RSVD; /*!< Reserved 0x3FF43010-0x3FF43010 */     
    __IO uint32_t CTRL2;       /*!< Control Register 2 0x3FF43014 */
    __IO uint32_t CLOCK;       /*!< Clock Configuration 0x3FF43018 */
    __IO uint32_t USER;        /*!< User Control 0x3FF4301C */
    __IO uint32_t USER1;       /*!< User Control 1 0x3FF43020 */
    __IO uint32_t USER2;       /*!< User Control 2 0x3FF43024 */
    __IO uint32_t MOSI_DLEN;   /*!< MOSI Data Length 0x3FF43028 */
    __IO uint32_t MISO_DLEN;   /*!< MISO Data Length 0x3FF4302C */
    __IO uint32_t SLV_WR_STATUS; /*!< Slave Write Status 0x3FF43030 */
    
    /*---------------------- Slave Mode Registers ----------------------*/
    __IO uint32_t PIN;         /*!< Pin Control 0x3FF43034 */
    __IO uint32_t SLAVE;       /*!< Slave Control 0x3FF43038 */
    __IO uint32_t SLAVE1;      /*!< Slave Control 1 0x3FF4303C */
    __IO uint32_t SLAVE2;      /*!< Slave Control 2 0x3FF43040 */
         uint32_t SLAVE3_RSVD;        /*!< Reserved 0x3FF43044 */
    __IO uint32_t SLV_WRBUF_DLEN; /*!< Slave Write Buffer Length 0x3FF43048 */
    __IO uint32_t SLV_RDBUF_DLEN; /*!< Slave Read Buffer Length 0x3FF4304C */

     /*---------------------- Data Registers ----------------------*/
         uint32_t reservedbuf[5];        /*!< Reserved 0x3FF43050-0x3FF43064 */
    // Data and DMA Registers (0x3FF43064 - 0x3FF4314C)
    __IO uint32_t SLV_RD_BIT;  /*!< Slave Read Bit 0x3FF43064 */
         uint32_t reserved0_data[6];         /*!< Reserved 0x3FF43068-0x3FF4307C */
    
     /* Data buffer registers (0x80-0xBC) */
    __IO uint32_t W0;          /*!< Data Buffer 0 0x3FF43080 */
    __IO uint32_t W1;          /*!< Data Buffer 1 0x3FF43084 */
    __IO uint32_t W2;          /*!< Data Buffer 2 0x3FF43088 */
    __IO uint32_t W3;          /*!< Data Buffer 3 0x3FF4308C */
    __IO uint32_t W4;          /*!< Data Buffer 4 0x3FF43090 */
    __IO uint32_t W5;          /*!< Data Buffer 5 0x3FF43094 */
    __IO uint32_t W6;          /*!< Data Buffer 6 0x3FF43098 */
    __IO uint32_t W7;          /*!< Data Buffer 7 0x3FF4309C */
    __IO uint32_t W8;          /*!< Data Buffer 8 0x3FF430A0 */
    __IO uint32_t W9;          /*!< Data Buffer 9 0x3FF430A4 */
    __IO uint32_t W10;         /*!< Data Buffer 10 0x3FF430A8 */
    __IO uint32_t W11;         /*!< Data Buffer 11 0x3FF430AC */
    __IO uint32_t W12;         /*!< Data Buffer 12 0x3FF430B0 */
    __IO uint32_t W13;         /*!< Data Buffer 13 0x3FF430B4 */
    __IO uint32_t W14;         /*!< Data Buffer 14 0x3FF430B8 */
    __IO uint32_t W15;         /*!< Data Buffer 15 0x3FF430BC */

    /*---------------------- CRC/Extended Registers ----------------------*/    
         uint32_t TX_CRC_RSVD; /*!< TX CRC 0x3FF430C0 */
         uint32_t RESERVED[12];       /*!< Reserved 0x3FF430C4-0x3FF430F4 */
    __IO uint32_t EXT2;      /*!< Extended Control 2 0x3FF430F8 */
         uint32_t RESERVED0;         /*!< Reserved 0x3FF430FC */

    /*------------------------ DMA Registers ------------------------*/
    __IO uint32_t DMA_CONF;    /*!< DMA Configuration 0x3FF43100 */
    __IO uint32_t DMA_OUT_LINK;/*!< DMA Out Link 0x3FF43104 */
    __IO uint32_t DMA_IN_LINK; /*!< DMA In Link 0x3FF43108 */
    __I  uint32_t DMA_STATUS;  /*!< DMA Status 0x3FF4310C */
    __IO  uint32_t DMA_INT_ENA; /*!< DMA Interrupt Enable 0x3FF43110 */
    __I  uint32_t DMA_INT_RAW; /*!< DMA Interrupt Raw 0x3FF43114 */
    __I  uint32_t DMA_INT_ST;  /*!< DMA Interrupt Status 0x3FF43118 */
    __IO  uint32_t DMA_INT_CLR; /*!< DMA Interrupt Clear 0x3FF4311C */
    __I  uint32_t IN_ERR_EOF_DES_ADDR; /*!< In Error EOF Descriptor Address 0x3FF43120 */
    __I  uint32_t IN_SUC_EOF_DES_ADDR; /*!< In Success EOF Descriptor Address 0x3FF43124 */
    __I  uint32_t INLINK_DSCR; /*!< In Link Descriptor 0x3FF43128 */
    __I  uint32_t INLINK_DSCR_BF0; /*!< In Link Descriptor Buffer 0 0x3FF4312C */
    __I  uint32_t INLINK_DSCR_BF1; /*!< In Link Descriptor Buffer 1 0x3FF43130 */
    __I  uint32_t OUT_EOF_BFR_DES_ADDR; /*!< Out EOF Before Descriptor Address 0x3FF43134 */
    __I  uint32_t OUT_EOF_DES_ADDR; /*!< Out EOF Descriptor Address 0x3FF43138 */
    __I  uint32_t OUTLINK_DSCR; /*!< Out Link Descriptor 0x3FF4313C */
    __I  uint32_t OUTLINK_DSCR_BF0; /*!< Out Link Descriptor Buffer 0 0x3FF43140 */
    __I  uint32_t OUTLINK_DSCR_BF1; /*!< Out Link Descriptor Buffer 1 0x3FF43144 */
    __I  uint32_t DMA_RSTATUS; /*!< DMA Read Status 0x3FF43148 */
    __I  uint32_t DMA_TSTATUS; /*!< DMA Write Status 0x3FF4314C */
} GenericSPI_Type;

// Define pointers to the four SPI modules
#define SPI0 ((GenericSPI_Type *)SPI0_BASE)
#define SPI1 ((GenericSPI_Type *)SPI1_BASE)
#define SPI2 ((GenericSPI_Type *)SPI2_BASE)
#define SPI3 ((GenericSPI_Type *)SPI3_BASE)

#endif /* COMPONENTS_MYHWMAP_REGS_SPI_CONTROLLER_H_ */
