/*
 * regs_pwr_clkGating.h
 *
 *  Created on: 28/04/2025
 *      Author: Diogo
 */

#ifndef COMPONENTS_MYHWMAP_REGS_PWR_CLKGATING_H_
#define COMPONENTS_MYHWMAP_REGS_PWR_CLKGATING_H_

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

#define RSTCLK_BASE                             0x00000000
#define DPORT_PERIP_CLK_EN_REG_ADDR             0x3FF000C0 /*!< Peripheral Clock Enable Register */
#define DPORT_PERIP_RST_EN_REG_ADDR             0x3FF000C4 /*!< Peripheral Reset Enable Register */
#define DPORT_PERIP_CLK_EN_REG (*(volatile uint32_t *)DPORT_PERIP_CLK_EN_REG_ADDR)
#define DPORT_PERIP_RST_EN_REG (*(volatile uint32_t *)DPORT_PERIP_RST_EN_REG_ADDR)
#define RSTCLK_REG_SIZE                         32



#endif /* COMPONENTS_MYHWMAP_REGS_PWR_CLKGATING_H_ */
