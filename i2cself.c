/*
 * i2cself.c
 *
 *  Created on: Aug 28, 2022
 *      Author: Samet
 */
#include "i2cself.h"
#include <stdint.h>
#include "stm32f4xx_hal.h"
extern I2C_HandleTypeDef hi2c1;

void lcd_send_byte(uint8_t val, int mode)
{
	uint8_t data_byte[4];
	uint8_t high4 = (val & 0xf0);
	uint8_t low4 = ((val << 4) & 0xf0);

	data_byte[0] = (high4 | 0x0C) | mode;
	data_byte[1] =  (high4 | 0x08) | mode;
	data_byte[2] =  (low4 | 0x0C) | mode;
	data_byte[3] = (low4 | 0x08) | mode;
	HAL_I2C_Master_Transmit(&hi2c1, lcd_addr, data_byte, 4, 100);
}

void lcd_setCursor(int row, int column)
{
	int value = (row == 0) ? (0x80 + column) : (0xC0 + column);
	lcd_send_byte(value, COMMAND);
}

void lcd_clear()
{
	lcd_send_byte(CLEAR_DISPLAY, COMMAND);
	HAL_Delay(2);
}
void lcd_printstr(char *s)
{
	while (*s) {
		lcd_send_byte(*s++, CHARACTER);
	}

}

void lcd_init()
{
	HAL_Delay(50);
	lcd_send_byte(0x30, COMMAND);
	HAL_Delay(5);
	lcd_send_byte(0x30, COMMAND);
	HAL_Delay(1);
	lcd_send_byte(0x30, COMMAND);
	HAL_Delay(10);
	lcd_send_byte(0x20, COMMAND);
	HAL_Delay(10);

	lcd_send_byte(0x28, COMMAND);
	HAL_Delay(1);
	lcd_send_byte(0x08, COMMAND);
	HAL_Delay(1);
	lcd_send_byte(0x01, COMMAND);
	HAL_Delay(2);
	lcd_send_byte(0x06, COMMAND);
	HAL_Delay(1);
	lcd_send_byte(0x0C, COMMAND);
}

