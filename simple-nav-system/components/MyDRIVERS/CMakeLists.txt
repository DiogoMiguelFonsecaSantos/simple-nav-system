idf_component_register(
    SRCS "src/spi_driver.c"
         "src/mpu9250.c"
         "src/led.c"
         "src/epaper.c"
    INCLUDE_DIRS "inc"
    REQUIRES MyHAL MyDRIVERS MyFONTS
)