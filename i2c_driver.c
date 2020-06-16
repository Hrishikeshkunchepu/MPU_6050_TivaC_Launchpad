#include <stdint.h>
#include "inc/tm4c123gh6pm.h"


#define I2C_MCS_ACK             0x00000008  // Data Acknowledge Enable
#define I2C_MCS_DATACK          0x00000008  // Acknowledge Data
#define I2C_MCS_ADRACK          0x00000004  // Acknowledge Address
#define I2C_MCS_STOP            0x00000004  // Generate STOP
#define I2C_MCS_START           0x00000002  // Generate START
#define I2C_MCS_ERROR           0x00000002  // Error
#define I2C_MCS_RUN             0x00000001  // I2C Master Enable
#define I2C_MCS_BUSY            0x00000001  // I2C Busy
#define I2C_MCR_MFE             0x00000010  // I2C Master Function Enable


void I2C_Init(void){
  SYSCTL_RCGCI2C_R |= 0x0001;           // activate I2C0
  SYSCTL_RCGCGPIO_R |= 0x0002;          // activate port B
  while((SYSCTL_PRGPIO_R&0x0002) == 0){};// ready?

  GPIO_PORTB_AFSEL_R |= 0x0C;           // 3) enable alt funct on PB2,3
  GPIO_PORTB_ODR_R |= 0x08;             // 4) enable open drain on PB3 only
  GPIO_PORTB_DEN_R |= 0x0C;             // 5) enable digital I/O on PB2,3
                                        // 6) configure PB2,3 as I2C
  GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R&0xFFFF00FF)+0x00003300;
  GPIO_PORTB_AMSEL_R &= ~0x0C;          // 7) disable analog functionality on PB2,3
  I2C0_MCR_R = I2C_MCR_MFE;      // 9) master function enable
  I2C0_MTPR_R = 24;              // 8) configure for 100 kbps clock
  // 20*(TPR+1)*20ns = 10us, with TPR=248
}



void begin_transmission(uint8_t slaveaddress, uint8_t rs){
	while(I2C0_MCS_R == I2C_MCS_BUSY){}
	I2C0_MSA_R = (slaveaddress << 1) + rs;
	
}




static uint8_t I2C0_WriteByte(uint8_t data, uint8_t start, uint8_t run, uint8_t stop)
{
    uint8_t error;
    I2C0_MDR_R = data;
    
    // If start bit sent, check if I2C Bus for busy bit
    // If busy, wait until it is busy
    if(start)
    {
        while(I2C0_MCS_R & 0x40);
    }
    
    I2C0_MCS_R = ( (run << 0) | (start << 1) | (stop << 2) );
    
    while(I2C0_MCS_R & 0x01){};
    
    error = (I2C0_MCS_R & 0x02) >> 1;
    
    return error;
}

uint8_t I2C0_WriteData(uint8_t slaveaddress, uint8_t regAddress, uint8_t data)
{
    uint8_t error = 0;
    begin_transmission(slaveaddress, 0);        //  Set slave address to write to
    error = I2C0_WriteByte(regAddress, 1, 1, 0);    //  Set register address to write to
    if(error != 0)
    {
        error = 1;
        return error;
    }
    
    error = I2C0_WriteByte(data, 0, 1, 1);          //  Send data to specified register address of slave device 
        if(error != 0)
    {
        error = 2;
        return error;
    }
    
    return error;
}

void busy_wait(){	
while(I2C0_MCS_R&0x00000001){};
}


void ReadData(uint8_t slaveAddress, uint8_t regAddress)
{
   
    begin_transmission(slaveAddress, 0);        //  Set slave address to read from
    I2C0_WriteByte(regAddress, 1, 1, 0); 
	
}


void repeat_start(uint8_t slaveAddress){
	begin_transmission(slaveAddress, 1);
	I2C0_MCS_R = (0
                         | I2C_MCS_ACK      // positive data ack
                       //  & ~I2C_MCS_STOP    // no stop
                         | I2C_MCS_START    // generate start/restart
                         | I2C_MCS_RUN);
	 
	
	
	busy_wait();
	
	
}

uint8_t read(){
	uint8_t value;
	value = (I2C0_MDR_R&0xFF);
	return value;
}
