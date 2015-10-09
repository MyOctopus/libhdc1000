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

#if !defined (_HDC1000_H_)
#define _HDC1000_H_

/*!
 * \brief Initialize HDC1000 sensor.
 *
 * Initialize I2C bus and configure sensor.
 *
 * \param f_dev I2C device filename, i.e. /dev/i2c-0.
 * \param address I2C device address, i.e. 0x77.
 */
int hdc1000_init(const char *f_dev, unsigned char address);

/*!
 * \brief Read humidity and temperature from HDC1000 sensor.
 *
 * \param humidity Relative humidity (as percentage).
 * \param temperature Temperature in Celsius.
 */
int hdc1000_read(float *humidity, float *temperature);

/*!
 * \brief Release HDC1000 sensor resources.
 *
 * Access to the I2C bus is closed.
 */
int hdc1000_close();

#endif /* _HDC1000_H_ */

/*
 * vim: sw=4:et:ai
 */
