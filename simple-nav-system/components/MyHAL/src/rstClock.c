// /*
//  * rstClock.c
//  *
//  *  Created on: 28/04/2025
//  *      Author: Diogo
//  */

// #include "rstClock.h"

// void RSTCLK_ConfigDivWhenCPUisXTLorRCFAST(uint16_t divider) {
//     // Validate the divider value (must be in the range 0x0 to 0x3FF)
//     if (divider > 0x3FF) {
//         return;
    
//     // Set the SYSCON_PRE_DIV_CNT field
//     RSTCLK->SYSCON_SYSCLK_CONF = (RSTCLK->SYSCON_SYSCLK_CONF & ~0x3FF) | 
//     (divider & 0x3FF);
// }

// uint16_t RSTCLK_GetDivWhenCPUisXTLorRCFAST(void) {
//     // Read the SYSCON_PRE_DIV_CNT field and return the divider value
//     return (uint16_t)(RSTCLK->SYSCON_SYSCLK_CONF & 0x3FF);
// }

// void RSTCLK_ConfigDivREF_TICKWhenAPBisXTL(uint8_t divider) {
//     // Validate the divider value (must be in the range 0x0 to 0xFF)
//     if (divider > 0xFF) {
//         return; // Invalid value, do nothing
//     }

//     // Set the SYSCON_XTAL_TICK_NUM field
//     RSTCLK->SYSCON_XTAL_TICK_CONF = (RSTCLK->SYSCON_XTAL_TICK_CONF & ~0xFF) | 
//                                     (divider & 0xFF);
// }

// uint8_t RSTCLK_GetDivREF_TICKWhenAPBisXTL(void) {
//     // Read the SYSCON_XTAL_TICK_NUM field and return the divider value
//     return (uint8_t)(RSTCLK->SYSCON_XTAL_TICK_CONF & 0xFF);
// }

// void RSTCLK_ConfigDivREF_TickWhenAPBisPLL(uint8_t divider) {
//     // Validate the divider value (must be in the range 0x0 to 0xFF)
//     if (divider > 0xFF) {
//         return; // Invalid value, do nothing
//     }

//     // Set the SYSCON_PLL_TICK_NUM field
//     RSTCLK->SYSCON_PLL_TICK_CONF = (RSTCLK->SYSCON_PLL_TICK_CONF & ~0xFF) | 
//                                    (divider & 0xFF);
// }

// uint8_t RSTCLK_GetDivREF_TickWhenAPBisPLL(void) {
//     // Read the SYSCON_PLL_TICK_NUM field and return the divider value
//     return (uint8_t)(RSTCLK->SYSCON_PLL_TICK_CONF & 0xFF);
// }

// void RSTCLK_ConfigDivREF_TickAPBisFOSC(uint8_t divider) {
//     // Validate the divider value (must be in the range 0x0 to 0xFF)
//     if (divider > 0xFF) {
//         return; // Invalid value, do nothing
//     }

//     // Set the SYSCON_CK8M_TICK_NUM field
//     RSTCLK->SYSCON_CK8M_TICK_CONF = (RSTCLK->SYSCON_CK8M_TICK_CONF & ~0xFF) | 
//                                     (divider & 0xFF);
// }

// uint8_t RSTCLK_GetDivREF_TickAPBisFOSC(void) {
//     // Read the SYSCON_CK8M_TICK_NUM field and return the divider value
//     return (uint8_t)(RSTCLK->SYSCON_CK8M_TICK_CONF & 0xFF);
// }

// void RSTCLK_ConfigDivREF_TickWhenAPBisAPLL(uint8_t divider) {
//     // Validate the divider value (must be in the range 0x0 to 0xFF)
//     if (divider > 0xFF) {
//         return; // Invalid value, do nothing
//     }

//     // Set the SYSCON_APLL_TICK_NUM field
//     RSTCLK->SYSCON_APLL_TICK_CONF = (RSTCLK->SYSCON_APLL_TICK_CONF & ~0xFF) | 
//                                     (divider & 0xFF);
// }

// uint8_t RSTCLK_GetDivREF_TickWhenAPBisAPLL(void) {
//     // Read the SYSCON_APLL_TICK_NUM field and return the divider value
//     return (uint8_t)(RSTCLK->SYSCON_APLL_TICK_CONF & 0xFF);
// }

