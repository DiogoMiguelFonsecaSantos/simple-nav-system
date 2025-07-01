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
    double latitude;      // decimal degrees
    double longitude;     // decimal degrees
    double altitude_msl;  // meters above mean sea level
    bool fix;             // true if valid fix
} gps_fix_t;

void gps_init(my_uart_port_t uart_num, const my_uart_config_t *cfg);
bool gps_read_fix(gps_fix_t *fix);

#endif /* COMPONENTS_MYDRIVERS_INC_GPS_H_ */