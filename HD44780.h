/*
 * HD44780.h
 *
 *  Created on: Oct 17, 2024
 *      Author: user_normal
 */

#ifndef HD44780_H_
#define HD44780_H_
#include "device.h"
#include "driverlib.h"
#include <stdlib.h>
#include <stdio.h>

// Uncomment if you want to use LCD in 8 bit mode
#define LCD_8bit 1

#define LCD_E 33
#define LCD_RS 12
#define LCD_D0 32
#define LCD_D1 14
#define LCD_D2 15
#define LCD_D3 26
#define LCD_D4 3
#define LCD_D5 2
#define LCD_D6 7
#define LCD_D7 6

#define LCD_E_CONFIG GPIO_33_GPIO33
#define LCD_RS_CONFIG GPIO_12_GPIO12
#define LCD_D0_CONFIG GPIO_32_GPIO32
#define LCD_D1_CONFIG GPIO_14_GPIO14
#define LCD_D2_CONFIG GPIO_15_GPIO15
#define LCD_D3_CONFIG GPIO_26_GPIO26
#define LCD_D4_CONFIG GPIO_3_GPIO3
#define LCD_D5_CONFIG GPIO_2_GPIO2
#define LCD_D6_CONFIG GPIO_7_GPIO7
#define LCD_D7_CONFIG GPIO_6_GPIO6

#define LCD_E_HIGH GPIO_writePin(LCD_E, 1)
#define LCD_E_LOW GPIO_writePin(LCD_E, 0)
#define LCD_RS_LOW GPIO_writePin(LCD_RS, 0)
#define LCD_RS_HIGH GPIO_writePin(LCD_RS, 1)

#define LCD_CLEAR 0x01
#define LCD_HOME 0x02
#define LCDC_ENTRY_MODE 0x04
#define LCD_EM_SHIFT_CURSOR 0x00
#define LCD_EM_SHIFT_DISPLAY 0x01
#define LCD_EM_LEFT 0x00
#define LCD_EM_RIGHT 0x02
#define LCD_ONOFF 0x08
#define LCD_DISP_ON 0x04
#define LCD_CURSOR_ON 0x02
#define LCDC_CURSOR_OFF 0x00
#define LCDC_BLINK_ON 0x01
#define LCDC_BLINK_OFF 0x00
#define LCD_SHIFT 0x10
#define LCDC_SHIFT_DISP 0x08
#define LCDC_SHIFT_CURSOR 0x00
#define LCDC_SHIFT_RIGHT 0x04
#define LCDC_SHIFT_LEFT 0x00
#define LCD_FUNC 0x20
#define LCD_8_BIT 0x10
#define LCD_4_BIT 0x00
#define LCDC_TWO_LINE 0x08
#define LCDC_FONT_5x10 0x04
#define LCDC_FONT_5x7 0x00
#define LCDC_SET_CGRAM 0x40
#define LCDC_SET_DDRAM 0x80

#define LCD_LINE1 0x00
#define LCD_LINE2 0x40

void LCD_Init(void);
void LCD_Set_Cursor(unsigned char x, unsigned char y);
void LCD_Write_Str(unsigned char *text);
void LCD_Write_Int(unsigned int num);
void LCD_Define_Char(unsigned char addr, char *character);
void LCD_Recall_Char(unsigned char addr);

#endif /* HD44780_H_ */
