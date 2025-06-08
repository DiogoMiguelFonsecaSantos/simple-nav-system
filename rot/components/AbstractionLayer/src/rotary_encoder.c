/*
 * rotary_encoder.C
 *
 *  Created on: Jun 5, 2025
 *      Author: diogo
 */

#include "rotary_encoder.h"

#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/portmacro.h"
#include "esp_log.h"
#include "esp_timer.h"
#include "freertos/semphr.h"

#define TAG "ROTARY_ENCODER"

// === Pin definitions (use free pins) ===
#define ENCODER_PIN_CLK GPIO_NUM_14
#define ENCODER_PIN_DT  GPIO_NUM_27
#define ENCODER_PIN_SW  GPIO_NUM_26

// === Button logic constants ===
#define BUTTON_POLL_INTERVAL_MS   20
#define BUTTON_HOLD_TICKS         (1000 / BUTTON_POLL_INTERVAL_MS)   // 1s
#define BUTTON_DOUBLE_CLICK_TICKS (400 / BUTTON_POLL_INTERVAL_MS)    // 400ms

// === Encoder state ===
static volatile int32_t encoder_value = 0;
static SemaphoreHandle_t encoder_mutex = NULL;

// === Button state ===
static uint32_t key_down_ticks = 0;
static uint32_t double_click_ticks = 0;
static encoder_button_event_t button_event = BUTTON_NOT_PRESSED;
static uint32_t last_button_check_time = 0;

static void IRAM_ATTR encoder_isr_handler(void* arg)
{
    int clk = gpio_get_level(ENCODER_PIN_CLK);
    int dt  = gpio_get_level(ENCODER_PIN_DT);

    int direction = (dt != clk) ? 1 : -1;

    if (encoder_mutex && xSemaphoreTakeFromISR(encoder_mutex, NULL)) {
        encoder_value += direction;
        xSemaphoreGiveFromISR(encoder_mutex, NULL);
    }
}

static void button_task(void* arg)
{
    while (1) {
        bool pressed = gpio_get_level(ENCODER_PIN_SW) == 0;
        uint32_t now = esp_timer_get_time() / 1000; // in ms

        if (now - last_button_check_time >= BUTTON_POLL_INTERVAL_MS) {
            last_button_check_time = now;

            if (pressed) {
                key_down_ticks++;
            } else {
                if (key_down_ticks > 0) {
                    if (key_down_ticks >= BUTTON_HOLD_TICKS) {
                        button_event = BUTTON_HELD;
                        double_click_ticks = 0;
                    } else {
                        if (double_click_ticks > 0) {
                            if (double_click_ticks < BUTTON_DOUBLE_CLICK_TICKS) {
                                button_event = BUTTON_DOUBLE_CLICKED;
                                double_click_ticks = 0;
                            }
                        } else {
                            double_click_ticks = BUTTON_DOUBLE_CLICK_TICKS;
                        }
                    }
                    key_down_ticks = 0;
                } else if (double_click_ticks > 0) {
                    double_click_ticks--;
                    if (double_click_ticks == 0) {
                        button_event = BUTTON_CLICKED;
                    }
                }
            }
        }

        vTaskDelay(pdMS_TO_TICKS(BUTTON_POLL_INTERVAL_MS));
    }
}

void rotary_encoder_init(void)
{
    // Create mutex
    encoder_mutex = xSemaphoreCreateMutex();

    // Configure encoder pins
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << ENCODER_PIN_CLK) |
                        (1ULL << ENCODER_PIN_DT) |
                        (1ULL << ENCODER_PIN_SW),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    gpio_config(&io_conf);

    // Enable interrupt on CLK pin
    gpio_set_intr_type(ENCODER_PIN_CLK, GPIO_INTR_ANYEDGE);
    gpio_install_isr_service(0);
    gpio_isr_handler_add(ENCODER_PIN_CLK, encoder_isr_handler, NULL);

    // Start button task
    xTaskCreate(button_task, "button_task", 2048, NULL, 10, NULL);

    ESP_LOGI(TAG, "Rotary encoder initialized.");
}

int32_t rotary_encoder_get_value(void)
{
    int32_t val = 0;
    if (encoder_mutex && xSemaphoreTake(encoder_mutex, pdMS_TO_TICKS(10))) {
        val = encoder_value;
        xSemaphoreGive(encoder_mutex);
    }
    return val;
}

encoder_button_event_t rotary_encoder_get_button(void)
{
    encoder_button_event_t event = button_event;
    button_event = BUTTON_NOT_PRESSED;
    return event;
}
