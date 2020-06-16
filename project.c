#include <stdarg.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "i2c_driver.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "utils/uartstdio.c"
#include <string.h>
#include "driverlib/uart.h"
#include "inc/hw_uart.h"





#define ACCEL_SLAVE_ADDR 0x68
#define first_register 0x3B
#define sensor_on 0x6B


float Acc_x,Acc_y,Acc_z,Temperature,Gyro_x,Gyro_y,Gyro_z;
void Output_Init(void); 
 

  
  



int main(void)
{
    // Set the clocking to run directly from the external crystal/oscillator.
    //SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_PLL | SYSCTL_OSC_INT | SYSCTL_XTAL_16MHZ);
		
		Output_Init();              // initialize output device
  printf("This program calculates areas of square-shaped rooms\n");
    I2C_Init();
		I2C0_WriteData(ACCEL_SLAVE_ADDR , sensor_on, 0);
	while(1){
		ReadData(0x68, 0x3B);
		repeat_start(0x68);
		Acc_x = (((int)read()<<8) | (int)read());
		Acc_y = (((int)read()<<8) | (int)read());
		Acc_z = (((int)read()<<8) | (int)read());
		//Temperature = (((int)read()<<8) | (int)read());  //optional for gyro and temperature 
		//Gyro_x = (((int)read()<<8) | (int)read());
		//Gyro_y = (((int)read()<<8) | (int)read());
	  //Gyro_z = (((int)read()<<8) | (int)read());
		
		
		

		printf("x-axis = %d, Acc_x);
		printf("y-axis = %d, Acc_y);
		printf("z-axis = %d, Acc_z);
		
		
		
		};
}


