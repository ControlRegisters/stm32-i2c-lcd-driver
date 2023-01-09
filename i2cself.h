/*
 * i2cself.h
 *
 *  Created on: Aug 28, 2022
 *      Author: Samet
 */

#ifndef INC_I2CSELF_H_
#define INC_I2CSELF_H_
#include <stdint.h>
#define lcd_addr (0x27<<1)
#define COMMAND 0
#define CHARACTER 1
#define CLEAR_DISPLAY 0x01


void lcd_send_byte(uint8_t value , int mode);
void lcd_setCursor(int row,int column);
void lcd_clear(void);
void lcd_printstr(char *s);
void lcd_init(void);




#endif /* INC_I2CSELF_H_ */
