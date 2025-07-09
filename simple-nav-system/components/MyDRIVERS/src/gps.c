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
        // Do NOT parse/store time here!
        fix->latitude = nmea_to_decimal(fields[2], fields[3]);
        fix->longitude = nmea_to_decimal(fields[4], fields[5]);
        fix->altitude_msl = atof(fields[9]);
        fix->fix = (fields[6][0] > '0');
        return true;
    }
    return false;
}

static bool parse_zda(const char *sentence, gps_fix_t *fix) {
    // Example: $GPZDA,hhmmss.ss,dd,mm,yyyy,xx,yy*CC
    char copy[128];
    strncpy(copy, sentence, sizeof(copy));
    copy[sizeof(copy)-1] = 0;

    char *fields[8] = {0};
    char *p = strtok(copy, ",");
    int i = 0;
    while (p && i < 8) {
        fields[i++] = p;
        p = strtok(NULL, ",");
    }
    if (i < 5) return false;

    if (fields[1] && fields[2] && fields[3] && fields[4]) {
        // Parse hour, add 1 for GMT+1
        int hour = 0, min = 0, sec = 0;
        if (strlen(fields[1]) >= 6) {
            hour = (fields[1][0] - '0') * 10 + (fields[1][1] - '0');
            min  = (fields[1][2] - '0') * 10 + (fields[1][3] - '0');
            sec  = (fields[1][4] - '0') * 10 + (fields[1][5] - '0');
            hour += 1; // GMT+1
            if (hour >= 24) hour -= 24;
        }
        snprintf(fix->timestamp, sizeof(fix->timestamp), "%s-%s-%s %02d:%02d:%02d",
            fields[4], fields[3], fields[2], hour, min, sec);
        return true;
    }
    return false;
}

static bool parse_vtg(const char *sentence, gps_fix_t *fix) {
    // Example: $GPVTG,227.15,T,,M,0.004,N,0.008,K,A*23
    // Field 1: Track (degrees True)
    char copy[128];
    strncpy(copy, sentence, sizeof(copy));
    copy[sizeof(copy)-1] = 0;

    char *fields[10] = {0};
    char *p = strtok(copy, ",");
    int i = 0;
    while (p && i < 10) {
        fields[i++] = p;
        p = strtok(NULL, ",");
    }
    if (i < 2) return false;

    if (fields[1]) {
        fix->heading = atof(fields[1]);
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
            } else if (strstr(nmea_buf, "$GPVTG")) {
                parse_vtg(nmea_buf, fix);
            } else if (strstr(nmea_buf, "$GPZDA")) {
                parse_zda(nmea_buf, fix);
            }
            nmea_pos = 0;
        } else if (nmea_pos < GPS_UART_BUF_SIZE - 1) {
            nmea_buf[nmea_pos++] = byte;
        }
    }
    return false;
}