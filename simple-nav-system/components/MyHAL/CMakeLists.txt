

idf_component_register(SRCS "src/gpio_matrix.c" "src/spi_protocol.c" "src/pin.c" "src/pinconfig.c" "src/clockpwr.c" "src/io_mux.c" 
                       INCLUDE_DIRS "inc"
                       REQUIRES driver esp_system esp_hw_support hal)