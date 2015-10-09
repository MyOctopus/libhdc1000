/*
 * libhdc1000 - HDC1000 humidity sensor library
 *
 * Copyright (C) 2015 by Artur Wroblewski <wrobell@pld-linux.org>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <unistd.h>

#ifdef HDC1000_DEBUG
#include <stdio.h>
#define DEBUG_LOG(fmt, ...) fprintf(stderr, fmt, ##__VA_ARGS__)
#else
#define DEBUG_LOG(fmt, ...)
#endif

/* 65536.0 / 165.0 */
#define DIV_TEMP 397.1878787878788
#define DIV_HUMIDITY 655.36

/* i2c file descriptor */
static int i2c_fd;

/*
 * Public API implementation.
 */

int hdc1000_init(const char *f_dev, unsigned char address) {
    int r, i;

    if ((i2c_fd = open(f_dev, O_RDWR)) < 0)
        return -1;

    /* set the port options and set the address of the device */
    if (ioctl(i2c_fd, I2C_SLAVE, address) < 0)
        return -1;

    /* write config:
     * - heater on (bit 13)
     * - temperature and humidity acquisition mode (bit 12)
     */
    r = write(i2c_fd, (unsigned char[]) {0x02, 0x30, 0x00}, 3);
    if (r != 1)
        return -1;

    return 0;
}

int hdc1000_read(float *humidity, float *temperature) {
    int r;
    uint8_t data[4];

    write(i2c_fd, (unsigned char[]) {0x00}, 1);
    usleep(15000); /* time needed for 14-bit conversion */
    r = read(i2c_fd, data, 4);
    if (r != 4)
        return -1;

    *temperature = ((data[0] << 8) + data[1]) / DIV_TEMP - 40.0;
    *humidity = ((data[2] << 8) + data[3]) / DIV_HUMIDITY;

    DEBUG_LOG("hdc1000 data (temp): [%x %x] = %.4f\n", data[0], data[1], *temperature);
    DEBUG_LOG("hdc1000 data (humidity): [%x %x] = %.4f\n", data[2], data[3], *humidity);
    return 0;
}

int hdc1000_close() {
    close(i2c_fd);
}

/*
 * vim: sw=4:et:ai
 */
