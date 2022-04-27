#include <string.h>
#include <stdio.h>
#include "FREERTOS/FreeRTOS.h"
#include "FREERTOS/task.h"


//======================================================
//sbit lcd_sclk =P3^3;  	//½׃¿¶¨ׂו:lcd_sclk¾ַֺֽLCDµִSCLK   //SCLK½׃µ½¡°D0¡±½ֵ
//sbit lcd_sda  =P3^4;   	//½׃¿¶¨ׂו:lcd_sda¾ַֺֽLCDµִSDA	 //SDIN½׃µ½¡°D1¡±½ֵ
//sbit lcd_reset=P3^0; 	//½׃¿¶¨ׂו:lcd_reset¾ַֺֽLCDµִRESET
//sbit lcd_dc   =P3^1;    //½׃¿¶¨ׂו:lcd_dc¾ַֺֽLCDµִD/C


//sbit lcd_cs1=P3^2;   	//½׃¿¶¨ׂו:lcd_cs1¾ַֺֽLCDµִCS
//sbit key=P2^0;			//¶¨ׂוׂ»¸צ°´¼£÷P2.0¿׃כGNDײ®¼ה½׃ׂ»¸צ°´¼


#define uchar unsigned char
#define uint unsigned int
#define ulong unsigned long


uchar cheng1[]={
/*--  ־ִ׳ײ:  ³ֹ  --*/
/*--  ֻ־ּו23;  ´ֻ׳ײּוֲֿ¶װ׃¦µִµדױף־×£÷¿םx¸=31x31   --*/
/*--  ¸¶ָ²»ַֺ8µִ±¶ֺ‎£¬ֿײµקױ־×£÷¿ם¶ָx¸¶ָ=32x32  --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0C,
0xFC,0xFC,0x88,0x00,0x00,0x1C,0x78,0xF0,0xE0,0x00,0x80,0x80,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0xFF,0xFF,0x83,0x83,0x83,0x83,0x83,0x83,0xC3,0xC3,0x03,0x1F,
0xFF,0xFF,0x83,0x03,0x03,0x03,0xC3,0xF3,0xF3,0x63,0x03,0x03,0x00,0x00,0x00,0x00,
0x00,0x00,0xFC,0xFF,0x3F,0x00,0x80,0x00,0x00,0x80,0xFF,0xFF,0x03,0x00,0x00,0x03,
0x9F,0xFF,0xF8,0xF8,0xBE,0x1F,0x07,0x01,0x00,0x00,0xE0,0x20,0x00,0x00,0x20,0x38,
0x1F,0x07,0x01,0x00,0x00,0x01,0x01,0x07,0x07,0x23,0x31,0x18,0x0C,0x0E,0x07,0x03,
0x01,0x01,0x01,0x03,0x07,0x0F,0x0E,0x1C,0x1F,0x3F,0x30,0x00,0x00,0x00,0x00,0x00};

uchar gong1[]={
/*--  ־ִ׳ײ:  ¹¦  --*/
/*--  ֻ־ּו23;  ´ֻ׳ײּוֲֿ¶װ׃¦µִµדױף־×£÷¿םx¸=31x31   --*/
/*--  ¸¶ָ²»ַֺ8µִ±¶ֺ‎£¬ֿײµקױ־×£÷¿ם¶ָx¸¶ָ=32x32  --*/
0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0xC0,0xC0,0xC0,0x00,
0x00,0x00,0x00,0xFE,0xFC,0x0C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x0C,0x04,0x04,
0x04,0x84,0xFF,0xFF,0x04,0x04,0x04,0x04,0x04,0xFE,0xFE,0x04,0x00,0x00,0x00,0x00,
0xC0,0xC0,0xC0,0xC0,0xE0,0x60,0x7F,0x3F,0x30,0x30,0x10,0x18,0x18,0x88,0xC0,0xF8,
0x7F,0x1F,0x01,0x00,0x00,0x00,0x00,0xF8,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x01,
0x01,0x00,0x00,0x00,0x00,0x20,0x20,0x30,0x18,0x0C,0x0C,0x07,0x03,0x01,0x00,0x04,
0x04,0x0C,0x0C,0x1C,0x38,0x3C,0x1F,0x0F,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00};




//ׁ׃ֺ±
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

//׀´ײ¸ֱמµ½OLEDֿװֺ¾ִ£¿י
void transfer_command(unsigned char data1)
{
	lcd_digitalWrite(PIN_COMMUNICATION_MODE,0);
	lcd_spiWrite(&data1,1);
}

//׀´ֺ‎¾µ½OLEDֿװֺ¾ִ£¿י
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

//OLEDֿװֺ¾ִ£¿י³ץֺ¼»¯
/* DOES NOT WORK, DO NOT USE
 * mascara.jo@toppoplcd.com <mascara.jo@toppoplcd.com>
 */
void initial_lcd()
{
	reset(0);        	//µֽµחֶ½¸´־»
  	delay(500);
  	reset(1);		   	//¸´־»ֽך±ֿ
  	delay(200);

transfer_command(0xae); //Display off
transfer_command(0xa8); //Set MUX ratio
transfer_command(0x7f);//7f
transfer_command(0xa1); //Display start line
transfer_command(0x00);
transfer_command(0xa2); //Set display offset
transfer_command(0x00);	//00
transfer_command(0xa4); //Normal display
transfer_command(0xa0); //Set re-map
transfer_command(0x64);//64

transfer_command(0x87); //Master current control
transfer_command(0x0F);////////////////////////////
transfer_command(0x81); //Set contrast level for R /////////////////
transfer_command(0x75); //Red contrast set
transfer_command(0x82); //Set contrast level for G//////////////////
transfer_command(0x60); //Green contrast set
transfer_command(0x83); //Set contrast level for B /////////////////
transfer_command(0x6a); //Blue contrast set

transfer_command(0xb1); //Phase adjust
transfer_command(0x22);
transfer_command(0xb3); //Set frame rate
transfer_command(0x40);
transfer_command(0xbb); //Set Pre-charge level
transfer_command(0x08);
transfer_command(0xbe); //VCOMH setting	 /////////////////////////////////////////////////
transfer_command(0x3C); //3C
transfer_command(0xb9);
transfer_command(0xaf); //Display on

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ram_address()
{
transfer_command(0x15); //Set Column Address
transfer_data(0x00);//Column Start Address
transfer_data(0x9f); //Column End Address
transfer_command(0x75); //Set Row Address
transfer_data(0x00);//Row Start Address
transfer_data(0x7f); //Row End Address	7f
}
void write_blue_data()
{
int i;
ram_address();
transfer_command(0x5c);
for(i=0;i<20480;i++)
{
   transfer_data(0xf8); //BLUE
   transfer_data(0x00);
}
}

void write_green_data()
{
int i;
ram_address();
transfer_command(0x5c);
for(i=0;i<20480;i++)
{
  transfer_data(0x07); //GREEN
  transfer_data(0xe0);
}
}

void write_red_data()
{
int i;
ram_address();
transfer_command(0x5c);
for(i=0;i<20480;i++)
{
  transfer_data(0x00); //RED
  transfer_data(0x1f);
}
}

void write_white_data()
{
int i;
ram_address();
transfer_command(0x5c);
for(i=0;i<20480;i++)
{
  transfer_data(0xff); //WHITE
  transfer_data(0xff);
}
}

void basic_main(void)
{
  initial_lcd();
	while(1)
	{
	write_red_data();
	write_green_data();
	write_blue_data();
	write_white_data();
	}
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
