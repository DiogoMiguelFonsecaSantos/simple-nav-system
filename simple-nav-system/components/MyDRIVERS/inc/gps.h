/*
 * gps.h
 *
 *  Created on: 23/06/2025
 *      Author: Diogo
 */

#ifndef COMPONENTS_MYDRIVERS_INC_GPS_H_
#define COMPONENTS_MYDRIVERS_INC_GPS_H_

#include "uart.h"
#include <stdbool.h>

typedef struct {
    char timestamp[32]; // YYYY-MM-DD HH:MM:SS + null terminator, extra safety
    double latitude;
    double longitude;
    double altitude_msl;
    double cog;
    bool fix;
}  gps_fix_t;

void gps_init(my_uart_port_t uart_num, const my_uart_config_t *cfg);
bool gps_read_fix(gps_fix_t *fix);
const char* cog_to_direction(double cog);
const char* gps_get_last_date(void);

#endif /* COMPONENTS_MYDRIVERS_INC_GPS_H_ */