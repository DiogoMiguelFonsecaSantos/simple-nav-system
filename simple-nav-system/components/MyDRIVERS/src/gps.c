/*
 * gps.c
 *
 *  Created on: 23/06/2025
 *      Author: Diogo
 */

#include "gps.h"
#include "uart.h"
#include "lcd16x2.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define GPS_UART_BUF_SIZE 256

static my_uart_port_t gps_uart_num;
static char last_date[11] = ""; // YYYY-MM-DD

// --- STATIC VARIABLE TO HOLD LAST COG ---
static double last_cog = 0.0;

// --- Helper: Days in month, including leap year logic ---
static int days_in_month(int year, int month) {
    static const int days[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)))
        return 29;
    return days[month - 1];
}

// --- Helper: Increment date string (YYYY-MM-DD) by one day ---
static void increment_date(char *date_str) {
    int year, month, day;
    sscanf(date_str, "%4d-%2d-%2d", &year, &month, &day);
    day++;
    if (day > days_in_month(year, month)) {
        day = 1;
        month++;
        if (month > 12) {
            month = 1;
            year++;
        }
    }
    snprintf(date_str, 11, "%04d-%02d-%02d", year, month, day);
}

static void gps_enable_zda(void) {
    // UBX-CFG-MSG to enable ZDA on UART1
    uint8_t cmd[] = {
        0xB5, 0x62, // UBX sync chars
        0x06, 0x01, // CFG-MSG
        0x08, 0x00, // length = 8
        0xF0, 0x08, // NMEA class, ZDA ID
        0x00,       // I2C
        0x01,       // UART1 (enable)
        0x00,       // UART2
        0x00,       // USB
        0x00,       // SPI
        0x00,       // Reserved
        0x00, 0x00  // Checksum (to be filled)
    };

    // Calculate checksum over payload (from 2 to 13)
    uint8_t ck_a = 0, ck_b = 0;
    for (int i = 2; i < 14; ++i) {
        ck_a += cmd[i];
        ck_b += ck_a;
    }
    cmd[14] = ck_a;
    cmd[15] = ck_b;

    // Send command over UART
    uart_write_bytes(gps_uart_num, (const char*)cmd, sizeof(cmd));
}

const char* cog_to_direction(double cog) {
    if (cog == 0.0) return "";
    if ((cog >= 337.5 && cog <= 360.0) || (cog >= 0.0 && cog < 22.5)) return "N";
    if (cog >= 22.5 && cog < 67.5) return "NE";
    if (cog >= 67.5 && cog < 112.5) return "E";
    if (cog >= 112.5 && cog < 157.5) return "SE";
    if (cog >= 157.5 && cog < 202.5) return "S";
    if (cog >= 202.5 && cog < 247.5) return "SW";
    if (cog >= 247.5 && cog < 292.5) return "W";
    if (cog >= 292.5 && cog < 337.5) return "NW";
    return "";
}

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
    gps_enable_zda(); // Enable $GPZDA output on the GPS module
}

static bool parse_gpgga(const char *sentence, gps_fix_t *fix) {
    char copy[128];
    strncpy(copy, sentence, sizeof(copy));
    copy[sizeof(copy)-1] = 0;

    char *fields[16] = {0};
    char *p = strtok(copy, ",");
    int i = 0;
    while (p && i < 16) {
        fields[i++] = p;
        p = strtok(NULL, ",");
    }

    if (fields[2] && fields[3] && fields[4] && fields[5] && fields[9]) {
        // Parse time from GGA
        if (fields[1] && strlen(fields[1]) >= 6) {
            int hour = (fields[1][0] - '0') * 10 + (fields[1][1] - '0');
            int min  = (fields[1][2] - '0') * 10 + (fields[1][3] - '0');
            int sec  = (fields[1][4] - '0') * 10 + (fields[1][5] - '0');
            // --- ADD 1 HOUR FOR GMT SUMMER TIME (UTC+1) ---
            hour += 1;
            if (hour >= 24) {
                hour -= 24;
                increment_date(last_date); // If we wrapped past midnight, increment the date
            }
            snprintf(fix->timestamp, sizeof(fix->timestamp), "%02d:%02d:%02d", hour, min, sec);
        } else {
            fix->timestamp[0] = 0;
        }
        fix->latitude = nmea_to_decimal(fields[2], fields[3]);
        fix->longitude = nmea_to_decimal(fields[4], fields[5]);
        fix->altitude_msl = atof(fields[9]);
        fix->fix = (fields[6][0] > '0');
        // --- COPY THE LAST COG VALUE INTO THE FIX STRUCTURE ---
        fix->cog = last_cog;
        return true;
    }
    return false;
}

static bool parse_zda(const char *sentence, gps_fix_t *fix) {
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

    if (fields[1] && fields[2] && fields[3] && fields[4]) {
        // Store date as YYYY-MM-DD
        snprintf(last_date, sizeof(last_date), "%s-%s-%s", fields[4], fields[3], fields[2]);
        return true;
    }
    return false;
}

const char* gps_get_last_date(void) {
    return last_date;
}

static bool parse_vtg(const char *sentence, gps_fix_t *fix) {
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

    if (fields[1] && strlen(fields[1]) > 0) {
        last_cog = atof(fields[1]);
        fix->cog = last_cog;
        // --- DISPLAY COG AND DIRECTION ON LCD16x2 ---
        const char* dir = cog_to_direction(last_cog);
        char buf[17];
        if (dir[0])
            snprintf(buf, sizeof(buf), "COG: %.1f %s", last_cog, dir);
        else
            snprintf(buf, sizeof(buf), "COG: %.1f", last_cog);
        lcd_clear();
        lcd_set_cursor(0, 0);
        lcd_write_string(buf);
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
            // --- DEBUG: PRINT EVERY NMEA SENTENCE ---
            printf("NMEA: %s\n", nmea_buf);
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