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

#include <stdio.h>
#include <time.h>

#include "hdc1000.h"

int main() {
    float humidity, temp;
    time_t t;
    hdc1000_init("/dev/i2c-1", 0x43);

    while (1) {
        time(&t);
        hdc1000_read(&humidity, &temp);
        printf("%d: %.4f%% %.4fC\n", t, humidity, temp);
        sleep(1);
    }
    return 0;
}

