// /*
//  * rstClock.h
//  *
//  *  Created on: 28/04/2025
//  *      Author: Diogo
//  */

// #ifndef COMPONENTS_MYHAL_INC_RSTCLOCK_H_
// #define COMPONENTS_MYHAL_INC_RSTCLOCK_H_

// #include <stdint.h>
// #include "regs_rstClock.h"

// /**
//  * @brief Configures the CPU clock divider when the CPU clock source is XTL or RCFAST.
//  * 
//  * @param divider Divider value (must be in the range 0x0 to 0x3FF).
//  */
// void RSTCLK_ConfigDivWhenCPUisXTLorRCFAST(uint16_t divider);

// /**
//  * @brief Retrieves the CPU clock divider when the CPU clock source is XTL or RCFAST.
//  * 
//  * @return The current divider value (0x0 to 0x3FF).
//  */
// uint16_t RSTCLK_GetDivWhenCPUisXTLorRCFAST(void);

// /**
//  * @brief Configures the REF_TICK clock divider when the APB clock source is XTL.
//  * 
//  * @param divider Divider value (must be in the range 0x0 to 0xFF).
//  */
// void RSTCLK_ConfigDivREF_TICKWhenAPBisXTL(uint8_t divider);

// /**
//  * @brief Retrieves the REF_TICK clock divider when the APB clock source is XTL.
//  * 
//  * @return The current divider value (0x0 to 0xFF).
//  */
// uint8_t RSTCLK_GetDivREF_TICKWhenAPBisXTL(void);

// /**
//  * @brief Configures the REF_TICK clock divider when the APB clock source is PLL.
//  * 
//  * @param divider Divider value (must be in the range 0x0 to 0xFF).
//  */
// void RSTCLK_ConfigDivREF_TickWhenAPBisPLL(uint8_t divider);

// /**
//  * @brief Retrieves the REF_TICK clock divider when the APB clock source is PLL.
//  * 
//  * @return The current divider value (0x0 to 0xFF).
//  */
// uint8_t RSTCLK_GetDivREF_TickWhenAPBisPLL(void);

// /**
//  * @brief Configures the REF_TICK clock divider when the APB clock source is FOSC.
//  * 
//  * @param divider Divider value (must be in the range 0x0 to 0xFF).
//  */
// void RSTCLK_ConfigDivREF_TickAPBisFOSC(uint8_t divider);

// /**
//  * @brief Retrieves the REF_TICK clock divider when the APB clock source is FOSC.
//  * 
//  * @return The current divider value (0x0 to 0xFF).
//  */
// uint8_t RSTCLK_GetDivREF_TickAPBisFOSC(void);

// /**
//  * @brief Configures the REF_TICK clock divider when the APB clock source is APLL.
//  * 
//  * @param divider Divider value (must be in the range 0x0 to 0xFF).
//  */
// void RSTCLK_ConfigDivREF_TickWhenAPBisAPLL(uint8_t divider);

// /**
//  * @brief Retrieves the REF_TICK clock divider when the APB clock source is APLL.
//  * 
//  * @return The current divider value (0x0 to 0xFF).
//  */
// uint8_t RSTCLK_GetDivREF_TickWhenAPBisAPLL(void);

// #endif /* COMPONENTS_MYHAL_INC_RSTCLOCK_H_ */
