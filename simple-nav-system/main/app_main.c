// #include <stdio.h>
// #include "freertos/FreeRTOS.h"
// #include "freertos/task.h"
// #include "mpu9250.h"
// #include "spi_protocol.h"
// #include "led.h"
// #include "pin.h"
// #include "driver/gpio.h"
// #include "esp_log.h"
// #include "esp_system.h"
// #include "esp_err.h"
// #include "esp_log.h"
// #include "epaper.h"
// #include "driver/spi_master.h"
// #include "driver/gpio.h"
// #include <stdio.h>
// #include "uart.h"

// #define PAINT_VAL 0x00
// #define PAINT_BUFFER_SIZE 50

// #define LED_RED 26
// #define LED_YELLOW 27
// #define LED_GREEN 14
// #define LED_BLUE 12

//  // spi_protocol.h
//  #define MY_SPI_HOST VSPI_HOST   
//  #define SPI_CLOCK_SPEED_HZ 1000000 // 1 MHz
//  #define SPI_MODE 0 // SPI Mode 0 (CPOL = 0, CPHA = 0)
//  #define SPI_QUEUE_SIZE 1
 
//  // Pin Definitions
//  #define PIN_NUM_MISO GPIO_NUM_19
//  #define PIN_NUM_MOSI GPIO_NUM_23
//  #define PIN_NUM_CLK GPIO_NUM_18
//  #define PIN_NUM_CS_MPU GPIO_NUM_5
//  #define PIN_NUM_CS_EPAPER GPIO_NUM_16

//  uint8_t who_am_i = 0;

// void configLEDS(void)
// {
//     gpio_reset_pin(LED_RED);
//     gpio_reset_pin(LED_YELLOW);
//     gpio_reset_pin(LED_GREEN);
//     gpio_reset_pin(LED_BLUE);

//     PIN_SetDirection(LED_RED, OUTPUT);
//     PIN_SetDirection(LED_YELLOW, OUTPUT);
//     PIN_SetDirection(LED_GREEN, OUTPUT);
//     PIN_SetDirection(LED_BLUE, OUTPUT);
// }

// void internalBlink(void *pvParameters)
// {   
// 	LED_Off();
//     while (true) {
//         LED_Toggle();
//         vTaskDelay(100 / portTICK_PERIOD_MS);
//     }
// }

// void printInfo(mpu9250_data_t *imuData) {
//     printf("========================================================================\n");
//     printf("WHO_AM_I: 0x%X\n", imuData->who_am_i);
//     printf("Accelerometer: X=%.2f m/s2, Y=%.2f m/s2, Z=%.2f m/s2\n", imuData->accel_x, imuData->accel_y, imuData->accel_z);
//     printf("Gyroscope: X=%.2f rads/s, Y=%.2f rads/s, Z=%.2f rads/s\n", imuData->gyro_x, imuData->gyro_y, imuData->gyro_z);
//     printf("Magnetometer: X=%.2f uT, Y=%.2f uT, Z=%.2f uT\n", imuData->mag_x, imuData->mag_y, imuData->mag_z);
//     printf("Temperature: %.2f degrees Celsius\n", imuData->temperature);
//     printf("Pitch: %.2f degrees, Roll: %.2f degrees\n", imuData->pitch, imuData->roll);
//     printf("========================================================================\n");

// }

// void app_main(void) {

//     LED_Init(false);
// 	// //configLEDS();
	
//     ESP_LOGI("MAIN", "Starting application...");

//     vTaskDelay(pdMS_TO_TICKS(10));

//     if (SPI_PROTOCOLInit() != ESP_OK) {
//         ESP_LOGE("MAIN", "Failed to initialize SPI");
//         return;
//     }

//     if (MPU9250Init() != ESP_OK) {
//         ESP_LOGE("MAIN", "Failed to initialize MPU-9250");
//         return;
//     }

//     printf("MPU-9250 initialized successfully.\n");

//     mpu9250_data_t imuData = {0}; // Initialize all struct fields to 0
//     //Set struct sample time to 20 ms
//     imuData.sample_time = 0.02f; // 20 ms


//     xTaskCreate(&internalBlink, "internalBlink", 2048, NULL, 5, NULL);

//     vTaskDelay(pdMS_TO_TICKS(3000));

//     // // Clear the e-paper display
//     // if (EPAPER_Clear() != ESP_OK) {
//     //     ESP_LOGE("MAIN", "Failed to clear e-paper display");
//     //     return;
//     // }

//     esp_err_t retVal = MPU9250_ReadWhoAmI(&imuData);
//     if (retVal != ESP_OK) {
//         printf("Failed to read WHO_AM_I: %d\n", retVal);
//         return;
//     }

//     // Read AK8963 WHO_AM_I
//     uint8_t ak8963_whoami = 0;
//     retVal = AK8963_ReadWhoAmI(&ak8963_whoami);
//     if (retVal == ESP_OK) {
//         printf("AK8963 WHO_AM_I: 0x%02X\n", ak8963_whoami);
//     } else {
//         printf("Failed to read AK8963 WHO_AM_I: %d\n", retVal);
//     }

//     int i = 0;
//     while (1) {

        

//         retVal = MPU9250ReadAllData(&imuData);
//         if (retVal != ESP_OK) {
//             printf("Failed to read sensor data: %d\n", retVal);
//             continue;
//         }
        
//         if(i < 100){
//             // Delay for a while before reading again
//             vTaskDelay(20 / portTICK_PERIOD_MS);
//             i++;
//         }
//         else{
            
//             printInfo(&imuData);
//             i = 0; 
//         }
        
//     }

// }

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "i2c_protocol.h"
#include "lcd16x2.h"
#include "esp_log.h"
#include "driver/i2c.h"
#include "rotary_encoder.h"
#include "gps.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "storage.h"

#define MAX_SAMPLES 1000
#define SAMPLE_PERIOD_SEC 4

// void i2c_scan(void) {
//     ESP_LOGI("I2C_SCAN", "Scanning I2C bus...");
//     for (uint8_t addr = 1; addr < 127; addr++) {
//         i2c_cmd_handle_t cmd = i2c_cmd_link_create();
//         i2c_master_start(cmd);
//         i2c_master_write_byte(cmd, (addr << 1) | I2C_MASTER_WRITE, true);
//         i2c_master_stop(cmd);
//         esp_err_t ret = i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, pdMS_TO_TICKS(100));
//         i2c_cmd_link_delete(cmd);
//         if (ret == ESP_OK) {
//             ESP_LOGI("I2C_SCAN", "Found device at 0x%02X", addr);
//         }
//     }
// }

void app_main(void)
{
    ESP_LOGI("MAIN", "Inicializando SPIFFS...");
    if (!gps_storage_init()) {
        ESP_LOGE("MAIN", "Falha ao montar SPIFFS!");
        return;
    }

    rotary_encoder_init();

    // Print history before writing new sample (apenas 10 para não ocupar stack)
    gps_sample_t buffer[10];
    size_t n = gps_storage_read_last(buffer, 10);
    ESP_LOGI("MAIN", "Histórico encontrado após reboot (%d amostras):", (int)n);
    for (size_t i = 0; i < n; ++i) {
        ESP_LOGI("MAIN", "%s, %.6f, %.6f, %.2f, %.2f",
            buffer[i].timestamp, buffer[i].latitude, buffer[i].longitude, buffer[i].altitude, buffer[i].heading);
    }

    // Inicializar GPS (ajuste os parâmetros conforme necessário)
    my_uart_config_t gps_uart_cfg = {
        .baud_rate = 9600,
        .tx_pin = 17, // ajuste para o seu hardware
        .rx_pin = 16  // ajuste para o seu hardware
    };
    gps_init(UART_NUM_2, &gps_uart_cfg);

    TickType_t last_sample = xTaskGetTickCount();

    while (1) {
        if (xTaskGetTickCount() - last_sample >= pdMS_TO_TICKS(SAMPLE_PERIOD_SEC * 1000)) {
            last_sample = xTaskGetTickCount();
            gps_fix_t fix = {0};
            if (gps_read_fix(&fix) && fix.fix) {
                gps_sample_t sample;
                strncpy(sample.timestamp, fix.timestamp, sizeof(sample.timestamp));
                sample.timestamp[sizeof(sample.timestamp)-1] = 0;
                sample.latitude = fix.latitude;
                sample.longitude = fix.longitude;
                sample.altitude = fix.altitude_msl;
                sample.heading = fix.heading; // <-- Store heading

                // --- FILTER LOGIC START ---
                gps_sample_t last5[5];
                size_t n5 = gps_storage_read_last(last5, 5);
                double mean_lat = 0, mean_lon = 0;
                if (n5 > 0) {
                    for (size_t i = 0; i < n5; ++i) {
                        mean_lat += last5[i].latitude;
                        mean_lon += last5[i].longitude;
                    }
                    mean_lat /= n5;
                    mean_lon /= n5;
                    if (fabs(sample.latitude - mean_lat) > 0.005 || fabs(sample.longitude - mean_lon) > 0.005) {
                        ESP_LOGW("MAIN", "GPS sample rejected (jump too large): %.6f, %.6f (mean: %.6f, %.6f)",
                            sample.latitude, sample.longitude, mean_lat, mean_lon);
                        continue; // Don't store this sample
                    }
                }
                // --- FILTER LOGIC END ---

                gps_storage_append(&sample);
                ESP_LOGI("MAIN", "GPS salvo: %s, %.6f, %.6f, %.2f, %.2f",
                    sample.timestamp, sample.latitude, sample.longitude, sample.altitude, sample.heading);
            } else {
                ESP_LOGW("MAIN", "Sem fix válido do GPS.");
            }
        }

        // Button logic (non-blocking)
        encoder_button_event_t btn = rotary_encoder_get_button();
        if (btn == BUTTON_CLICKED) {
            gps_sample_t *history = malloc(sizeof(gps_sample_t) * MAX_SAMPLES);
            if (!history) {
                printf("Failed to allocate memory for history!\n");
            } else {
                n = gps_storage_read_last(history, MAX_SAMPLES);
                printf("=== GPS HISTORY (last %d) ===\n", (int)n);
                for (size_t i = 0; i < n; ++i) {
                    printf("%4d: %s, %.6f, %.6f, %.2f, %.2f\n",
                        (int)(i + 1),
                        history[i].timestamp, history[i].latitude, history[i].longitude, history[i].altitude, history[i].heading);
                }
                printf("=== END ===\n");
                free(history);
            }
        } else if (btn == BUTTON_HELD) {
            if (gps_storage_clear()) {
                printf("GPS log cleared!\n");
            } else {
                printf("Failed to clear GPS log!\n");
            }
        }

        vTaskDelay(pdMS_TO_TICKS(50));
    }
}

    // ESP_LOGI(TAG, "Initializing I2C...");
    // if (i2c_protocol_init() != ESP_OK) {
    //     ESP_LOGE(TAG, "Failed to initialize I2C");
    //     return;
    // }
    
    // ESP_LOGI(TAG, "I2C scan completed. Proceeding with LCD initialization...");
    // ESP_LOGI(TAG, "Initializing LCD...");
    // lcd_init();
    // rotary_encoder_init();

    // ESP_LOGI(TAG, "Writing to LCD...");

    //int32_t last_val = 0;

    // lcd_clear();
    // lcd_set_cursor(0, 0);
    // lcd_write_char('D');
    // vTaskDelay(pdMS_TO_TICKS(700));
    // lcd_set_cursor(1, 0);
    // lcd_write_char('I');
    // vTaskDelay(pdMS_TO_TICKS(700));
    // lcd_set_cursor(2, 0);
    // lcd_write_char('O');
    // vTaskDelay(pdMS_TO_TICKS(700));
    // lcd_set_cursor(3, 0);
    // lcd_write_char('G');
    // vTaskDelay(pdMS_TO_TICKS(700));
    // lcd_set_cursor(4, 0);
    // lcd_write_char('O');
    // vTaskDelay(pdMS_TO_TICKS(700));
    // lcd_set_cursor(5, 0);
    // lcd_write_char(' ');
    // vTaskDelay(pdMS_TO_TICKS(700));
    // lcd_set_cursor(6, 0);
    // lcd_write_char('S');
    // vTaskDelay(pdMS_TO_TICKS(700));
    // lcd_set_cursor(7, 0);
    // lcd_write_char('A');
    // vTaskDelay(pdMS_TO_TICKS(700));
    // lcd_set_cursor(8, 0);
    // lcd_write_char('N');
    // vTaskDelay(pdMS_TO_TICKS(700));
    // lcd_set_cursor(9, 0);
    // lcd_write_char('T');
    // vTaskDelay(pdMS_TO_TICKS(700));
    // lcd_set_cursor(10, 0);
    // lcd_write_char('O');
    // vTaskDelay(pdMS_TO_TICKS(700));
    // lcd_set_cursor(11, 0);
    // lcd_write_char('S');
    // vTaskDelay(pdMS_TO_TICKS(700));


    // while (1) {
    //     int32_t val = rotary_encoder_get_value();
    //     if (val != last_val) {
    //         char buf[17];
    //         if (val % 2 == 0) { // Detect even/odd for formatting
    //             snprintf(buf, sizeof(buf), "Encoder: %d", (int)val);
    //         } else {
    //             snprintf(buf, sizeof(buf), "\nEncoder: %d", (int)val);
    //         }
    //         lcd_clear();
    //         lcd_write_string(buf);
    //         last_val = val;
    //     }

    //     static int32_t btn_timeout = 0;
    //     encoder_button_event_t btn = rotary_encoder_get_button();
    //     if (btn != BUTTON_NOT_PRESSED) {
    //         const char* names[] = {
    //         "Button: NOT PRESSED", "Button: CLICKED", "Button: DOUBLE\nCLICKED", "Button: HELD"
    //         };
    //         lcd_clear();
    //         lcd_set_cursor(1, 0);
    //         lcd_write_string(names[btn]);
    //         btn_timeout = 0; // reset timeout on button event
    //     } else {
    //         btn_timeout += 50;
    //         if (btn_timeout >= 2000) {
    //         char buf[17];
    //         snprintf(buf, sizeof(buf), "Encoder: %" PRId32, val);
    //         lcd_clear();
    //         lcd_set_cursor(0, 0);
    //         lcd_write_string(buf);
    //         btn_timeout = 0;
    //         }
    //     }

    //     vTaskDelay(pdMS_TO_TICKS(50));
    // }
// }
