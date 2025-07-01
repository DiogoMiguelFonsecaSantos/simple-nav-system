#ifndef COMPONENTS_MYHAL_INC_WEACT_H_
#define COMPONENTS_MYHAL_INC_WEACT_H_

#include "driver/gpio.h"
#include "esp_err.h"

// Finalized pin definitions for e-paper module
#define EPAPER_PIN_DC    GPIO_NUM_25
#define EPAPER_PIN_RST   GPIO_NUM_22
#define EPAPER_PIN_BUSY  GPIO_NUM_34  // Input-only (OK)

esp_err_t WEACT_Epaper_Init(void);
void WEACT_Epaper_Reset(void);
void WEACT_Epaper_WaitUntilIdle(void);
esp_err_t WEACT_Epaper_SendCommand(uint8_t cmd);
esp_err_t WEACT_Epaper_SendData(const uint8_t *data, size_t length);
esp_err_t WEACT_Epaper_PaintBlack(void);
esp_err_t WEACT_Epaper_PaintWhite(void);

#endif /* COMPONENTS_MYHAL_INC_WEACT_H_ */
