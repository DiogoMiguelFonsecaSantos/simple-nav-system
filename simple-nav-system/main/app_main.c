#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "mpu9250.h"
#include "spi_protocol.h"
#include "led.h"
#include "pin.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_system.h"
#include "esp_err.h"
#include "esp_log.h"
#include "epaper.h"
#include "driver/spi_master.h"
#include "driver/gpio.h"
#include <stdio.h>
#include "uart.h"

#define PAINT_VAL 0x00
#define PAINT_BUFFER_SIZE 50

#define LED_RED 26
#define LED_YELLOW 27
#define LED_GREEN 14
#define LED_BLUE 12

 // spi_protocol.h
 #define MY_SPI_HOST VSPI_HOST   
 #define SPI_CLOCK_SPEED_HZ 1000000 // 1 MHz
 #define SPI_MODE 0 // SPI Mode 0 (CPOL = 0, CPHA = 0)
 #define SPI_QUEUE_SIZE 1
 
 // Pin Definitions
 #define PIN_NUM_MISO GPIO_NUM_19
 #define PIN_NUM_MOSI GPIO_NUM_23
 #define PIN_NUM_CLK GPIO_NUM_18
 #define PIN_NUM_CS_MPU GPIO_NUM_5
 #define PIN_NUM_CS_EPAPER GPIO_NUM_16

 uint8_t who_am_i = 0;

void configLEDS(void)
{
    gpio_reset_pin(LED_RED);
    gpio_reset_pin(LED_YELLOW);
    gpio_reset_pin(LED_GREEN);
    gpio_reset_pin(LED_BLUE);

    PIN_SetDirection(LED_RED, OUTPUT);
    PIN_SetDirection(LED_YELLOW, OUTPUT);
    PIN_SetDirection(LED_GREEN, OUTPUT);
    PIN_SetDirection(LED_BLUE, OUTPUT);
}

void internalBlink(void *pvParameters)
{   
	LED_Off();
    while (true) {
        LED_Toggle();
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

void printInfo(mpu9250_data_t *imuData) {
    printf("========================================================================\n");
    printf("WHO_AM_I: 0x%X\n", imuData->who_am_i);
    printf("Accelerometer: X=%.2f m/s2, Y=%.2f m/s2, Z=%.2f m/s2\n", imuData->accel_x, imuData->accel_y, imuData->accel_z);
    printf("Gyroscope: X=%.2f rads, Y=%.2f rads, Z=%.2f rads\n", imuData->gyro_x, imuData->gyro_y, imuData->gyro_z);
    printf("Magnetometer: X=%.2f uT, Y=%.2f uT, Z=%.2f uT\n", imuData->mag_x, imuData->mag_y, imuData->mag_z);
    printf("Temperature: %.2f degrees Celsius\n", imuData->temperature);
    printf("Pitch: %.2f degrees, Roll: %.2f degrees\n", imuData->pitch, imuData->roll);
    printf("========================================================================\n");

}

void app_main(void) {

    // my_uart_config_t gps_uart_cfg = {
    //     .tx_pin = 17,    // opcional, o GPS não usa
    //     .rx_pin = 16,    // ligação física GPS TX → ESP32 GPIO21
    //     .baud_rate = 9600
    // };

    // my_uart_init(MY_UART_NUM_2, &gps_uart_cfg);

    // uint8_t buf[128];
    // while (1) {
    // int len = my_uart_read_bytes(MY_UART_NUM_2, buf, sizeof(buf) - 1, pdMS_TO_TICKS(1000));
    // if (len > 0) {
    //     printf("len: %d\n", len);
    //     for (int i = 0; i < len; i++) {
    //         putchar(buf[i]); // imprime byte a byte
    //     }
    //     putchar('\n');
    // } else {
    //     printf("Sem dados do GPS\n");
    // }



    LED_Init(false);
	// //configLEDS();
	
    ESP_LOGI("MAIN", "Starting application...");

    vTaskDelay(pdMS_TO_TICKS(10));

    if (SPI_PROTOCOLInit() != ESP_OK) {
        ESP_LOGE("MAIN", "Failed to initialize SPI");
        return;
    }

    if (MPU9250Init() != ESP_OK) {
        ESP_LOGE("MAIN", "Failed to initialize MPU-9250");
        return;
    }

    printf("MPU-9250 initialized successfully.\n");

    mpu9250_data_t imuData = {0}; // Initialize all struct fields to 0
    //Set struct sample time to 20 ms
    imuData.sample_time = 0.02f; // 20 ms

    // gpio_set_level(EPAPER_RST_PIN, 0); 
    // vTaskDelay(pdMS_TO_TICKS(10));
    // gpio_set_level(EPAPER_RST_PIN, 1);
    // vTaskDelay(pdMS_TO_TICKS(10));

    // printf("EPAPER reset done.\n");
    // vTaskDelay(pdMS_TO_TICKS(1000));

    // EPAPER_WriteCMD(0x12); // SWRESET command
    // printf("EPAPER SWRESET command sent.\n");
    // vTaskDelay(pdMS_TO_TICKS(1000));
    // vTaskDelay(pdMS_TO_TICKS(10));

    // EPAPER_WriteCMD(0x01);
    // printf("EPAPER Driver Output Control command sent.\n");
    // vTaskDelay(pdMS_TO_TICKS(1000));

    // EPAPER_WriteCMD(0x11);
    // printf("EPAPER Data Entry Mode command sent.\n");
    // vTaskDelay(pdMS_TO_TICKS(1000));

    // uint8_t val = 0x03;
    // EPAPER_WriteData(&val, 1);
    // printf("EPAPER Data Entry Mode set to 0x03.\n");
    // vTaskDelay(pdMS_TO_TICKS(1000));

    // EPAPER_WriteCMD(0x44);
    // printf("EPAPER Set RAM X address start/end command sent.\n");
    // vTaskDelay(pdMS_TO_TICKS(1000));

    // uint8_t val1 = 0x00;
    // EPAPER_WriteData(&val1, 1);
    // printf("EPAPER RAM X address start set to 0x00.\n");
    // vTaskDelay(pdMS_TO_TICKS(1000));

    // uint8_t val2 = 0x15;
    // EPAPER_WriteData(&val2, 1);
    // printf("EPAPER RAM X address end set to 0x15.\n");
    // vTaskDelay(pdMS_TO_TICKS(1000));

    // EPAPER_WriteCMD(0x45);
    // printf("EPAPER Set RAM Y address start/end command sent.\n");
    // vTaskDelay(pdMS_TO_TICKS(1000));

    // uint8_t val3 = 0x00;
    // EPAPER_WriteData(&val3, 1);
    // printf("EPAPER RAM Y address start set to 0x00.\n");
    // vTaskDelay(pdMS_TO_TICKS(1000));

    // uint8_t val4 = 0x00;
    // EPAPER_WriteData(&val4, 1);
    // printf("EPAPER RAM Y address end set to 0x00.\n");
    // vTaskDelay(pdMS_TO_TICKS(1000));

    // uint8_t val5 = 0x27;
    // EPAPER_WriteData(&val5, 1);
    // printf("EPAPER RAM Y address end set to 0x27.\n");
    // vTaskDelay(pdMS_TO_TICKS(1000));

    // uint8_t val6 = 0x01;
    // EPAPER_WriteData(&val6, 1);
    // printf("EPAPER Set RAM X address start to 0x01.\n");
    // vTaskDelay(pdMS_TO_TICKS(1000));

    // EPAPER_WriteCMD(0x3C);
    // printf("EPAPER Border Waveform Control command sent.\n");
    // vTaskDelay(pdMS_TO_TICKS(1000));

    // uint8_t val7 = 0xC0;
    // EPAPER_WriteData(&val7, 1);
    // printf("EPAPER Border Waveform Control set to 0xC0.\n");
    // vTaskDelay(pdMS_TO_TICKS(1000));


    // EPAPER_WriteCMD(0x18);
    // printf("EPAPER Temperature Sensor Control command sent.\n");
    // vTaskDelay(pdMS_TO_TICKS(1000));

    // uint8_t val8 = 0x48;
    // EPAPER_WriteData(&val8, 1);
    // printf("EPAPER Temperature Sensor Control set to 0x48.\n");
    // vTaskDelay(pdMS_TO_TICKS(1000));


    // EPAPER_WriteCMD(0x22);
    // printf("EPAPER Display Update Sequence Option command sent.\n");
    // vTaskDelay(pdMS_TO_TICKS(1000));

    // uint8_t val9 = 0xFF;
    // EPAPER_WriteData(&val9, 1);
    // printf("EPAPER Display Update Sequence Option set to 0xFF.\n");
    // vTaskDelay(pdMS_TO_TICKS(1000));


    // EPAPER_WriteCMD(0x20);
    // printf("EPAPER Master Activation command sent.\n");
    // vTaskDelay(pdMS_TO_TICKS(1000));

    // while (gpio_get_level(EPAPER_BUSY_PIN) == 1) {
    //     vTaskDelay(pdMS_TO_TICKS(10));
    // }

    // EPAPER_WriteCMD(0x4E);
    // printf("EPAPER Set RAM X address command sent.\n");
    // vTaskDelay(pdMS_TO_TICKS(1000));

    // uint8_t val10 = 0x00;
    // EPAPER_WriteData(&val10, 1);
    // printf("EPAPER RAM X address set to 0x00.\n");
    // vTaskDelay(pdMS_TO_TICKS(1000));


    // EPAPER_WriteCMD(0x4F);
    // printf("EPAPER Set RAM Y address command sent.\n");
    // vTaskDelay(pdMS_TO_TICKS(1000));

    // uint8_t val11 = 0x00;
    // EPAPER_WriteData(&val11, 1);
    // printf("EPAPER RAM Y address set to 0x00.\n");
    // vTaskDelay(pdMS_TO_TICKS(1000));

    // uint8_t val12 = 0x00;
    // EPAPER_WriteData(&val12, 1);
    // printf("EPAPER RAM Y address set to 0x00.\n");
    // vTaskDelay(pdMS_TO_TICKS(1000));

    // EPAPER_WriteCMD(0x24);
    // printf("EPAPER Write RAM command sent.\n");
    // vTaskDelay(pdMS_TO_TICKS(1000));

    // // Fill the display with black (0x00)
    // uint8_t framebuffer[EPAPER_BUFFER_SIZE];
    // memset(framebuffer, 0x00, EPAPER_BUFFER_SIZE);
    // EPAPER_WriteData(framebuffer, EPAPER_BUFFER_SIZE);
    // printf("EPAPER Write RAM data sent.\n");
    // vTaskDelay(pdMS_TO_TICKS(1000));

    // EPAPER_WriteCMD(0x22);
    // printf("EPAPER Display Update Sequence Option command sent.\n");
    // vTaskDelay(pdMS_TO_TICKS(1000));

    // uint8_t disp_update = 0xC7;
    // EPAPER_WriteData(&disp_update, 1);
    // printf("EPAPER Display Update Sequence Option set to 0xC7.\n");
    // vTaskDelay(pdMS_TO_TICKS(1000));

    // EPAPER_WriteCMD(0x20);
    // printf("EPAPER Master Activation command sent.\n");
    // vTaskDelay(pdMS_TO_TICKS(1000));

    // EPAPER_WriteCMD(0x0C);
    // printf("EPAPER Booster Soft Start command sent.\n");
    // vTaskDelay(pdMS_TO_TICKS(1000));
    
    // uint8_t val14 = 0x8B;
    // EPAPER_WriteData(&val14, 1);
    // printf("EPAPER Booster Soft Start set to 0x8B.\n");
    // vTaskDelay(pdMS_TO_TICKS(1000));

    // uint8_t val15 = 0x9C;
    // EPAPER_WriteData(&val15, 1);
    // printf("EPAPER Booster Soft Start set to 0x9C.\n");
    // vTaskDelay(pdMS_TO_TICKS(1000));

    // uint8_t val16 = 0x96;
    // EPAPER_WriteData(&val16, 1);
    // printf("EPAPER Booster Soft Start set to 0x96.\n");
    // vTaskDelay(pdMS_TO_TICKS(1000));

    // uint8_t val17 = 0x0F;
    // EPAPER_WriteData(&val17, 1);
    // printf("EPAPER Booster Soft Start set to 0x0F.\n");
    // vTaskDelay(pdMS_TO_TICKS(1000));

    // EPAPER_WriteCMD(0x22);
    // printf("EPAPER Display Update Sequence Option command sent.\n");
    // vTaskDelay(pdMS_TO_TICKS(1000));

    // uint8_t val18 = 0xC7;
    // EPAPER_WriteData(&val18, 1);
    // printf("EPAPER Display Update Sequence Option set to 0xC7.\n");
    // vTaskDelay(pdMS_TO_TICKS(1000));
    
    // EPAPER_WriteCMD(0x20);
    // printf("EPAPER Master Activation command sent.\n");
    // vTaskDelay(pdMS_TO_TICKS(1000));

    // while (gpio_get_level(EPAPER_BUSY_PIN) == 1) {
    //     vTaskDelay(pdMS_TO_TICKS(10));
    // }

    // ----------------------------------------------------------------------------------

    // // Initialize the e-paper display
    // if (EPAPER_Init() != ESP_OK) {
    //     ESP_LOGE("MAIN", "Failed to initialize e-paper display");
    //     return;
    // }

    // printf("EPAPER initialized successfully.\n");

    xTaskCreate(&internalBlink, "internalBlink", 2048, NULL, 5, NULL);

    vTaskDelay(pdMS_TO_TICKS(3000));

    // // Clear the e-paper display
    // if (EPAPER_Clear() != ESP_OK) {
    //     ESP_LOGE("MAIN", "Failed to clear e-paper display");
    //     return;
    // }

    esp_err_t retVal = MPU9250_ReadWhoAmI(&imuData);

    int i = 0;
    while (1) {
        retVal = MPU9250ReadAllData(&imuData);
        if (retVal != ESP_OK) {
            printf("Failed to read sensor data: %d\n", retVal);
            continue;
        }
        
        if(i < 100){
            // Delay for a while before reading again
            vTaskDelay(20 / portTICK_PERIOD_MS);
            i++;
        }
        else{
            printInfo(&imuData);
            i = 0; 
        }
        
    }

}
