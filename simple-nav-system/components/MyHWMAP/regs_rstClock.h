/*
 * regs_rstClock.h
 *
 *  Created on: 28/04/2025
 *      Author: Diogo
 */

#ifndef COMPONENTS_MYHWMAP_REGS_RSTCLOCK_H_
#define COMPONENTS_MYHWMAP_REGS_RSTCLOCK_H_

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
#define RSTCLK_REG_SIZE                         32

typedef struct { 
    __IO uint32_t SYSCON_SYSCLK_CONF;    /*!< 0x00 - System Clock Configuration Register (R/W) */
    __IO uint32_t SYSCON_XTAL_TICK_CONF; /*!< 0x04 - XTAL Tick Configuration Register (R/W) */
    __IO uint32_t SYSCON_PLL_TICK_CONF;  /*!< 0x08 - PLL Tick Configuration Register (R/W) */
    __IO uint32_t SYSCON_CK8M_TICK_CONF; /*!< 0x0C - CK8M Tick Configuration Register (R/W) */
         uint32_t reserved0[12];        
    __IO uint32_t SYSCON_APLL_TICK_CONF; /*!< 0x10 - APLL Tick Configuration Register (R/W) */
         uint32_t reserved[15];
    __IO uint32_t SYSCON_DATE;      /*!< 0x20 - Clock Configuration Register (R/W) */
} RSTCLK_Type;

#define RSTCLK ((RSTCLK_Type *) RSTCLK_BASE) /*!< Pointer to the RSTCLK peripheral structure */

#endif /* COMPONENTS_MYHWMAP_REGS_RSTCLOCK_H_ */
