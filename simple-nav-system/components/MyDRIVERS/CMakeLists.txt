

idf_component_register(SRCS  "src/led.c" "src/mpu9250.c" "src/spi_driver.c"
                       INCLUDE_DIRS "inc"
                       REQUIRES MyHAL driver)