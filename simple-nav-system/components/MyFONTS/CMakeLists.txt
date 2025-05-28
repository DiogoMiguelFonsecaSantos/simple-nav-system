idf_component_register(SRCS "src/epaper_font.c" "src/epaper-29-ws.c" "src/u8g2_fonts.c"
                       INCLUDE_DIRS "inc"
                       REQUIRES driver esp_system esp_hw_support hal)