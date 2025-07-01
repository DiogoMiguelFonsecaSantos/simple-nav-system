idf_component_register(
    SRCS "src/rotary_encoder.c"
         "src/mpu9250.c"
         "src/led.c"
         "src/epaper.c"
         "src/gps.c"
         "src/ring_buffer.c"
         "src/flash_store.c"
         "src/lcd16x2.c"
         "src/lcd16x2_hw.c"
         ""
    INCLUDE_DIRS "inc"
    REQUIRES MyHAL MyDRIVERS MyFONTS nvs_flash esp_timer
)