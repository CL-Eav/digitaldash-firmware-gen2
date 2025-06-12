/*
 * eeprom_24cw.c
 *
 *  Created on: Apr 7, 2025
 *      Author: Matth
 */

#include "eeprom_24cw.h"

#define EEPROM_READ_DELAY_MS 5
#define EEPROM_WRITE_RETRY_COUNT 10
#define EEPROM_READ_TRIAL_COUNT 3
#define EEPROM_READY_TIMEOUT 10
#define EEPROM_WRITE_DELAY_MS 2
#define EEPROM_ADDRESS_SIZE 2
#define CONFIG_EEPROM_7BIT_ADDR 0xA0
#define EEPROM_TIMEOUT 10

// Function to read data from EEPROM
uint8_t eeprom_24cw_read(I2C_HandleTypeDef *eeprom_handle, uint16_t bAdd)
{
    uint8_t rbuf[1];                   // Read buffer

    // Abort if the EEPROM is not present
    //if (HAL_I2C_IsDeviceReady(eeprom_handle, bAdd, EEPROM_READ_TRIAL_COUNT, EEPROM_READY_TIMEOUT) != HAL_OK)
    //    return 0xFF;

    // Perform I2C read operation
    HAL_I2C_Mem_Read(eeprom_handle, CONFIG_EEPROM_7BIT_ADDR, bAdd, EEPROM_ADDRESS_SIZE, rbuf, sizeof(rbuf), EEPROM_TIMEOUT);

    return rbuf[0];
}

// Function to write data to EEPROM with retries
void eeprom_24cw_write(I2C_HandleTypeDef *eeprom_handle, uint16_t bAdd, uint8_t bData)
{
    uint8_t wbuf[1]; // Write buffer

    wbuf[0] = bData;

    // Make sure the EEPROM is ready
	HAL_I2C_IsDeviceReady(eeprom_handle, CONFIG_EEPROM_7BIT_ADDR, EEPROM_WRITE_RETRY_COUNT, EEPROM_TIMEOUT);

	// Perform I2C write operation
	HAL_I2C_Mem_Write(eeprom_handle, CONFIG_EEPROM_7BIT_ADDR, bAdd, EEPROM_ADDRESS_SIZE, wbuf, sizeof(wbuf), EEPROM_TIMEOUT);


    // Wait until EEPROM completes the internal write cycle
    for (int retry = 0; retry < EEPROM_WRITE_RETRY_COUNT; retry++)
    {
        if (HAL_I2C_IsDeviceReady(eeprom_handle, CONFIG_EEPROM_7BIT_ADDR, 1, EEPROM_TIMEOUT) == HAL_OK)
        {
            return; // EEPROM is ready
        }
        HAL_Delay(EEPROM_WRITE_DELAY_MS); // Delay between retries
    }
}

