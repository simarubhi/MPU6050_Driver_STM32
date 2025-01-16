/**
 *  @file mpu6050_driver.c
 *	@brief MPU6050 Sensor Driver Library
 *  @date Created on: Jan 16, 2025
 *  @author Author: Simar Singh Ubhi
 *  @version 1.0.0
 *
 */

#include "mpu6050_driver.h"


//**********************Private Variables**********************//
static I2C_HandleTypeDef *phi2c1 = NULL;


//**********************Public API Functions**********************//
/**
 *	@brief Initialization sequence to wake up and configure sensor
 *  @param *hi2c the handle for the I2C lane chosen
 */
void mpu6050_init(I2C_HandleTypeDef *hi2c)
{
	phi2c1 = hi2c; // Assigning handle

	uint8_t verify;

	HAL_I2C_Mem_Read(phi2c1, MPU6050_ADDRESS, 0x75, 1, &verify, 1, HAL_MAX_DELAY);

	if(verify == 0x68)
	{
		uint8_t write_data;

		write_data = 0x08; // Power configuration, disabled temperature sensor for now

		HAL_I2C_Mem_Write(phi2c1, MPU6050_ADDRESS, 0x6b, 1, &write_data, 1, HAL_MAX_DELAY);

		write_data = 0x07; // Set gyroscope output to 1KHz to match accelerometer output

		HAL_I2C_Mem_Write(phi2c1, MPU6050_ADDRESS, 0x19, 1, &write_data, 1, HAL_MAX_DELAY);

		write_data = 0x00; // Lowest gyroscope and accelerometer scale because of slow actions in mind

		HAL_I2C_Mem_Write(phi2c1, MPU6050_ADDRESS, 0x18, 1, &write_data, 1, HAL_MAX_DELAY); // Gyroscope
		HAL_I2C_Mem_Write(phi2c1, MPU6050_ADDRESS, 0x1c, 1, &write_data, 1, HAL_MAX_DELAY); // Accelerometer
	}
}

void mpu6050_get_accel(float accel[3])
{
	uint8_t read_data[6]; // 6 bytes of read data from sensor

	HAL_I2C_Mem_Read(phi2c1, MPU6050_ADDRESS, 0x3b, 1, read_data, 6, HAL_MAX_DELAY); // Reading 6 accelerometer output registers

	int16_t accel_x_raw, accel_y_raw, accel_z_raw; // Signed because values are 2's compliment

	accel_x_raw = (int16_t)((read_data[0] << 8) | read_data[1]);
	accel_y_raw = (int16_t)((read_data[2] << 8) | read_data[3]);
	accel_z_raw = (int16_t)((read_data[4] << 8) | read_data[5]);

	accel[0] = ((float) accel_x_raw) / 16384.0;
	accel[1] = ((float) accel_y_raw) / 16384.0;
	accel[2] = ((float) accel_z_raw) / 16384.0;
}



