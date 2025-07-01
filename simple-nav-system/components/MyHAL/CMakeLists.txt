

idf_component_register(SRCS "src/spi_protocol.c" 
                            "src/pin.c"
                            "src/pinconfig.c"
                            "src/clockpwr.c"
                            "src/uart.c"
                            "src/i2c_protocol.c"
                       INCLUDE_DIRS "inc"
                       REQUIRES driver esp_system esp_hw_support hal)