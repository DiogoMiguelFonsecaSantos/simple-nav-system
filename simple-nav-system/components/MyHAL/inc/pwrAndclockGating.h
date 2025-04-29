/*
 * pwrAndclockGating.h
 *
 *  Created on: 28/04/2025
 *      Author: Diogo
 */

#ifndef COMPONENTS_MYHAL_INC_PWRANDCLOCKGATING_H_
#define COMPONENTS_MYHAL_INC_PWRANDCLOCKGATING_H_

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
 
 
void PWR_CLKGTING_EnableSPIClk(int spiNum);
void PWR_CLKGTING_DisableSPIClk(int spiNum);
void PWR_CLKGTING_ResetSPIClk(int spiNum);



#endif /* COMPONENTS_MYHAL_INC_PWRANDCLOCKGATING_H_ */
