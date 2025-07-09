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
    char timestamp[24]; // YYYY-MM-DD HH:MM:SS
    double latitude;
    double longitude;
    double altitude_msl;
    double heading;
    bool fix;             // true if valid fix
}  gps_fix_t;

void gps_init(my_uart_port_t uart_num, const my_uart_config_t *cfg);
bool gps_read_fix(gps_fix_t *fix);
const char* heading_to_str(double heading);

#endif /* COMPONENTS_MYDRIVERS_INC_GPS_H_ */