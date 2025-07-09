idf_component_register(
    SRCS "src/rotary_encoder.c"
         "src/mpu9250.c"
         "src/led.c"
         "src/epaper.c"
         "src/gps.c"
         "src/lcd16x2.c"
         "src/lcd16x2_hw.c"
         "src/storage.c"
         "src/ring_buffer.c"
    INCLUDE_DIRS "inc"
    REQUIRES MyHAL MyDRIVERS MyFONTS nvs_flash spiffs esp_timer
)