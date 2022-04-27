#include <string.h>
#include <stdio.h>
#include "FREERTOS/FreeRTOS.h"
#include "FREERTOS/task.h"


#define uchar unsigned char
#define uint unsigned int
#define ulong unsigned long




void delay(int i)
{
	vTaskDelay(1);
}
void Delay(int i)
{
	vTaskDelay(i);
}
#define PIN_COMMUNICATION_MODE 4 /* command 0, data 1 */
#define PIN_RESET              5
void lcd_digitalWrite(unsigned short int pin, unsigned char value);
void lcd_spiWrite(unsigned char* buffer, size_t length);

void transfer_command(unsigned char data1)
{
	lcd_digitalWrite(PIN_COMMUNICATION_MODE,0);
	lcd_spiWrite(&data1,1);
}

void transfer_data(unsigned char data1)
{
	lcd_digitalWrite(PIN_COMMUNICATION_MODE,1);
	lcd_spiWrite(&data1,1);
}

void WriteComm(unsigned char data1)
{
	transfer_command(data1);
}
void WriteData(unsigned char data1)
{
	transfer_data(data1);
}
void reset(int data1)
{
	lcd_digitalWrite(PIN_RESET,data1);
}


//************* Start Initial Sequence **********//
/*
 * www.laurellcd.com
 * CHINA-LCD Pearl Wang <china-lcd@szonline.net>
 * CT0177N6M128160-320
 * http://www.ece.ucf.edu/~zakhia17/EEL4742/Data_Sheet_LCD_Controller.pdf
 */
void ST7735S(void)
{
	reset(0);        	//µֽµחֶ½¸´־»
	delay(500);
	reset(1);		   	//¸´־»ֽך±ֿ
	delay(200);
	WriteComm(0x11); //Sleep out
	Delay(120); //Delay 120ms
	//------------------------------------ST7735S Frame Rate-----------------------------------------//
	WriteComm(0xB1);
	WriteData(0x05);
	WriteData(0x3A);
	WriteData(0x3A);
	WriteComm(0xB2);
	WriteData(0x05);
	WriteData(0x3A);
	WriteData(0x3A);
	WriteComm(0xB3);
	WriteData(0x05);
	WriteData(0x3A);
	WriteData(0x3A);
	WriteData(0x05);
	WriteData(0x3A);
	WriteData(0x3A);
	//------------------------------------End ST7735S Frame Rate-----------------------------------------//
	WriteComm(0xB4); //Dot inversion
	WriteData(0x03);
	//------------------------------------ST7735S Power Sequence-----------------------------------------//
	WriteComm(0xC0);
	WriteData(0x28);
	WriteData(0x08);
	WriteData(0x84);
	WriteComm(0xC1);
	WriteData(0XC0);
	WriteComm(0xC2);
	WriteData(0x0D);
	WriteData(0x00);
	WriteComm(0xC3);
	WriteData(0x8D);
	WriteData(0x2A);
	WriteComm(0xC4);
	WriteData(0x8D);
	WriteData(0xEE);
	//---------------------------------End ST7735S Power Sequence-------------------------------------//
	WriteComm(0xC5); //VCOM
	WriteData(0x0C);
	WriteComm(0x36); //MX, MY, RGB mode
	WriteData(0x08);//0x08
	//------------------------------------ST7735S Gamma Sequence-----------------------------------------//
	WriteComm(0xE0);
	WriteData(0x05);
	WriteData(0x1A);
	WriteData(0x0C);
	WriteData(0x0E);
	WriteData(0x3A);
	WriteData(0x34);
	WriteData(0x2D);
	WriteData(0x2F);
	WriteData(0x2D);
	WriteData(0x2A);
	WriteData(0x2F);
	WriteData(0x3C);
	WriteData(0x00);
	WriteData(0x01);
	WriteData(0x02);
	WriteData(0x10);
	WriteComm(0xE1);
	WriteData(0x04);
	WriteData(0x1B);
	WriteData(0x0D);
	WriteData(0x0E);
	WriteData(0x2D);
	WriteData(0x29);
	WriteData(0x24);
	WriteData(0x29);
	WriteData(0x28);
	WriteData(0x26);
	WriteData(0x31);
	WriteData(0x3B);
	WriteData(0x00);
	WriteData(0x00);
	WriteData(0x03);
	WriteData(0x12);
	//------------------------------------End ST7735S Gamma Sequence-----------------------------------------//
	WriteComm(0xFC); //Enable Gate Pump Clock Frequency Variable
	WriteData(0x8C);
	WriteComm(0x3A); //65k mode
	WriteData(0x05);
	WriteComm(0x29); //Display on
	WriteComm(0x2C);
}
