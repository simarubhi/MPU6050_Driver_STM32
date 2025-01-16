/**
 *  @file mpu6050_driver.c
 *	@brief MPU6050 Sensor Driver Library
 *  @date Created on: Jan 16, 2025
 *  @author Author: Simar Singh Ubhi
 *  @version 1.0.0
 *
 */

#ifndef INC_MPU6050_DRIVER_H_
#define INC_MPU6050_DRIVER_H_

#include "stm32f4xx_hal.h"  // Include the HAL I2C header to define I2C_HandleTypeDef

#define MPU6050_ADDRESS (0x68 << 1) // Adjust as needed depending on specific model and AD0 pin

// Public API
void mpu6050_init(I2C_HandleTypeDef *hi2c);
void mpu6050_get_accel(float accel[3]);

#endif /* INC_MPU6050_DRIVER_H_ */
