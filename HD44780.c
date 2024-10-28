/*
 * HD44780.c
 *
 *  Created on: Oct 17, 2024
 *      Author: user_normal
 */
#include "HD44780.h"

static unsigned char data_pins[] = { LCD_D0, LCD_D1, LCD_D2, LCD_D3, LCD_D4, LCD_D5, LCD_D6, LCD_D7 };
static long data_pin_configs[] = {LCD_D0_CONFIG, LCD_D1_CONFIG, LCD_D2_CONFIG, LCD_D3_CONFIG, LCD_D4_CONFIG, LCD_D5_CONFIG, LCD_D6_CONFIG, LCD_D7_CONFIG };

static void LCD_Send_Nibble(unsigned char data)
{
    LCD_E_HIGH;
    for (size_t i = 0; i < 4; i++)
    {
        GPIO_writePin(data_pins[i + 4], (data & (1 << i)));
    }
    LCD_E_LOW;
}

static void LCD_Send_Byte(unsigned char data)
{
    LCD_E_HIGH;
    for (size_t i = 0; i < 8; i++)
    {
        GPIO_writePin(data_pins[i], (data & (1 << i)));
    }
    LCD_E_LOW;
    DEVICE_DELAY_US(60);
}

#ifndef LCD_8bit
static void LCD_Send_Byte_Two_Steps(unsigned char data) {
  LCD_Send_Nibble(data >> 4);
  LCD_Send_Nibble(data);
  DEVICE_DELAY_US(60);
}
#endif

static void LCD_Send_Cmd(unsigned char cmd)
{
    LCD_RS_LOW;
#ifndef LCD_8bit
    LCD_Send_Byte_Two_Steps(cmd);
#else
    LCD_Send_Byte(cmd);
#endif
}

static void LCD_Send_Data(unsigned char data)
{
    LCD_RS_HIGH;
#ifndef LCD_8bit
    LCD_Send_Byte_Two_Steps(data);
#else
    LCD_Send_Byte(data);
#endif
}

static void LCD_Init_GPIO(void)
{
    GPIO_setPadConfig(LCD_E, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(LCD_E_CONFIG);
    GPIO_setDirectionMode(LCD_E, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(LCD_RS, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(LCD_RS_CONFIG);
    GPIO_setDirectionMode(LCD_RS, GPIO_DIR_MODE_OUT);
#ifdef LCD_8bit
    for (size_t i = 0; i < 4; i++)
    {
        GPIO_setPadConfig(data_pins[i], GPIO_PIN_TYPE_STD);
        GPIO_setPinConfig(data_pin_configs[i]);
        GPIO_setDirectionMode(data_pins[i], GPIO_DIR_MODE_OUT);
    }
#endif
    for (size_t i = 4; i < 8; i++)
    {
        GPIO_setPadConfig(data_pins[i], GPIO_PIN_TYPE_STD);
        GPIO_setPinConfig(data_pin_configs[i]);
        GPIO_setDirectionMode(data_pins[i], GPIO_DIR_MODE_OUT);
    }

}

void LCD_Init(void)
{
    LCD_Init_GPIO();
    DEVICE_DELAY_US(15000);
    LCD_E_LOW;
    LCD_RS_LOW;
    LCD_Send_Nibble(0x03); // set DB5 & DB4 high
    DEVICE_DELAY_US(4100);
    LCD_Send_Nibble(0x03);
    DEVICE_DELAY_US(100);
    LCD_Send_Nibble(0x03);
    DEVICE_DELAY_US(100); // since we don't check BF, so waiting time needs to be longer than command execution time
#ifndef LCD_8bit
    LCD_Send_Nibble(0x02); // choose 4bit interface
    DEVICE_DELAY_US(100);
    LCD_Send_Cmd(LCD_FUNC | LCD_4_BIT | LCDC_TWO_LINE | LCDC_FONT_5x7);
#else
    LCD_Send_Cmd(LCD_FUNC | LCD_8_BIT | LCDC_TWO_LINE | LCDC_FONT_5x7);
#endif
    LCD_Send_Cmd(LCD_ONOFF | LCD_DISP_ON);
    LCD_Send_Cmd(LCD_CLEAR);
    DEVICE_DELAY_US(5000);
    LCD_Send_Cmd(LCDC_ENTRY_MODE | LCD_EM_SHIFT_CURSOR | LCD_EM_RIGHT);
}

void LCD_Set_Cursor(unsigned char x, unsigned char y)
{
    switch (y)
    {
    case 0:
        LCD_Send_Cmd(LCDC_SET_DDRAM | (LCD_LINE1 + (x & 0x10)));
        break;

    case 1:
        LCD_Send_Cmd(LCDC_SET_DDRAM | (LCD_LINE2 + (x & 0x10)));
        break;
    }
}

void LCD_Write_Str(unsigned char *text)
{
    while (*text)
        LCD_Send_Data(*text++);
}

void LCD_Write_Int(unsigned int num)
{
    char buff[4];
    sprintf(buff, "%d", num);
    LCD_Send_Data(*buff);
}

void LCD_Define_Char(unsigned char addr, char *character)
{
    LCD_Send_Cmd(LCDC_SET_CGRAM | ((addr & 0x7) << 3));
    for (size_t i = 0; i < 8; i++)
    {
        LCD_Send_Data(character[i]);
    }
    LCD_Send_Cmd(LCDC_SET_DDRAM);
}

void LCD_Recall_Char(unsigned char addr)
{
    LCD_Send_Data(addr);
}
