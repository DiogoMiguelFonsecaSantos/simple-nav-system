/*
 * gps.c
 *
 *  Created on: 23/06/2025
 *      Author: Diogo
 */

#include "gps.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define GPS_UART_BUF_SIZE 256

static my_uart_port_t gps_uart_num;

static double nmea_to_decimal(const char *nmea, const char *dir) {
    // NMEA: ddmm.mmmm or dddmm.mmmm
    double val = atof(nmea);
    int deg = (dir[0] == 'N' || dir[0] == 'S') ? (int)(val / 100) : (int)(val / 100);
    double min = val - deg * 100;
    double dec = deg + min / 60.0;
    if (dir[0] == 'S' || dir[0] == 'W') dec = -dec;
    return dec;
}

void gps_init(my_uart_port_t uart_num, const my_uart_config_t *cfg) {
    gps_uart_num = uart_num;
    my_uart_init(uart_num, cfg);
}

static bool parse_gpgga(const char *sentence, gps_fix_t *fix) {
    // Example: $GPGGA,hhmmss.ss,llll.ll,a,yyyyy.yy,a,x,xx,x.x,x.x,M,x.x,M,x.x,xxxx*hh
    char copy[128];
    strncpy(copy, sentence, sizeof(copy));
    copy[sizeof(copy)-1] = 0;

    char *fields[15] = {0};
    char *p = strtok(copy, ",");
    int i = 0;
    while (p && i < 15) {
        fields[i++] = p;
        p = strtok(NULL, ",");
    }
    if (i < 10) return false;

    if (fields[2] && fields[3] && fields[4] && fields[5] && fields[9]) {
        fix->latitude = nmea_to_decimal(fields[2], fields[3]);
        fix->longitude = nmea_to_decimal(fields[4], fields[5]);
        fix->altitude_msl = atof(fields[9]);
        fix->fix = (fields[6][0] > '0');
        return true;
    }
    return false;
}

bool gps_read_fix(gps_fix_t *fix) {
    static char nmea_buf[GPS_UART_BUF_SIZE];
    static int nmea_pos = 0;
    uint8_t byte;
    while (my_uart_read_bytes(gps_uart_num, &byte, 1, 0) == 1) {
        if (byte == '$') {
            nmea_pos = 0;
            nmea_buf[nmea_pos++] = byte;
        } else if (byte == '\n' && nmea_pos > 6) {
            nmea_buf[nmea_pos] = 0;
            if (strstr(nmea_buf, "$GPGGA")) {
                return parse_gpgga(nmea_buf, fix);
            }
            nmea_pos = 0;
        } else if (nmea_pos < GPS_UART_BUF_SIZE - 1) {
            nmea_buf[nmea_pos++] = byte;
        }
    }
    return false;
}


