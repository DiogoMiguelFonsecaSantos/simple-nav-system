

idf_component_register(SRCS "src/spi_driver.c" "src/mpu9250.c" "src/led.c"
                       INCLUDE_DIRS "inc"
                       REQUIRES MyHAL)