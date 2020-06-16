#ifndef i2cdriver_H
#define i2cdriver_H

#include <stdint.h>

void I2C_Init(void);
uint8_t I2C0_WriteData(uint8_t slaveAddress, uint8_t regAddress, uint8_t data);
uint8_t ReadData(uint8_t slaveAddress, uint8_t regAddress);
void begin_transmission(uint8_t slaveaddress, uint8_t rs);
static uint8_t I2C0_WriteByte(uint8_t data, uint8_t start, uint8_t run, uint8_t stop);
void repeat_start(uint8_t slaveAddress);
uint8_t read();
#endif
