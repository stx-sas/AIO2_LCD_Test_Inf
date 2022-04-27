/******************************************************************************
 * @file     Main.c
 * @brief    Easy Start project: reads potentiometer in XMC4800 Hexagon
 *           Application Kit (Port 14.1) and uses this value for changing
 *           the blinking speed of LED located in port 3.9.
 *           ADC is converting continuously Ch1 in group 0 in background source
 *           The different blinking delays are implemented using a
 *           system timer that decrements a counter on each timer overflow
 *           This counter is controlled by the ADC result value (potentiometer)
 * @version  V1.1
 * @date     24 February 2017
 * @note
 * Copyright (C) 2015-2017 Infineon Technologies AG. All rights reserved.
 ******************************************************************************
 * @par
 * Infineon Technologies AG (Infineon) is supplying this software for use with
 * Infineon�s microcontrollers.
 * This file can be freely distributed within development tools that are
 * supporting such microcontrollers.
 * @par
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *****************************************************************************/


#include <XMC4800.h>                    //SFR declarations of the selected device
#include "GPIO.h"
#include "FREERTOS/FreeRTOS.h"
#include "FREERTOS/task.h"
#include "SPI_MASTER/spi_master.h"

#define TICKS_PER_SECOND 1000


void ledblink();
void st7735_demo(void);
void spitest();
void ST7735S(void);
int main(void)
{
	int stat;
	TaskHandle_t t;
	DAVE_Init();
	/* Setup the system timer to tick every 1000us */
	SysTick_Config(SystemCoreClock / TICKS_PER_SECOND);
	stat = xTaskCreate(ledblink, "ledblink", 200/4, 0, 4, &t);
	stat = xTaskCreate(st7735_demo, "demo", 1024/4, 0, 3, &t);
	//	stat = xTaskCreate(spitest, "spitest", 200/4, 0, 3, &t);
//	stat = xTaskCreate(ST7735S, "ST7735S", 1024/4, 0, 3, &t);
	vTaskStartScheduler();
}
void ledblink()
{

	/* Configure P5.9 (LED) */
	// P5.9 is used as GPIO for LED indication. Macros can be find in GPIO.h
	P5_9_set_mode(OUTPUT_PP_GP);
	P5_9_set_driver_strength(STRONG);
	P5_9_reset();
	extern SPI_MASTER_t SPI_MASTER_0;
	while (1)
	{
		unsigned char Send_Data[]={0x81,0xff,0x00,0x81};
		unsigned char rx_data[30];
		vTaskDelay(500);
		P5_9_toggle();  // led

	}
                                       // toggle P3.9 (toggle LED) using GPIO.h macros
}

void spitest()
{


	extern SPI_MASTER_t SPI_MASTER_0;
	P5_4_set(); // data
	while (1)
	{
		unsigned char Send_Data[]={1,0x55,0xaa};
		unsigned char rx_data[30];
		vTaskDelay(500);

		P5_6_reset(); // CS
		SPI_MASTER_Transfer(&SPI_MASTER_0, Send_Data, rx_data,sizeof(Send_Data));
		P5_6_set(); // CS
	}

}

