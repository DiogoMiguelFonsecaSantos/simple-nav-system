#include <stdio.h>
#include "esp_adc/adc_oneshot.h"  // Novo driver ADC
#include "esp_adc/adc_cali.h"
#include "esp_adc/adc_cali_scheme.h"
#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#ifdef __cplusplus
extern "C" {
#endif
uint8_t temprature_sens_read(); // Declaração correta da função
#ifdef __cplusplus
}
#endif

void app_main() {
    while (1) {
        // Obtém a temperatura interna do ESP32
        uint8_t temp_f = temprature_sens_read();
        float temp_c = (temp_f - 32) / 1.8;

        // Exibe a temperatura no terminal
        printf("Temperature: %.2f C\n", temp_c);

        vTaskDelay(pdMS_TO_TICKS(5000)); // Aguarda 5 segundos
    }
}
