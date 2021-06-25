#include "main.h"

// LCD code
void lcd_gpio_init(void);
void lcd_write_instruction(uint8_t inst);
void lcd_write_char(unsigned char c);
void lcd_init(void);
void lcd_clear(void);
void lcd_goto(uint8_t col, uint8_t row);
void lcd_write_string(char* string);

void delay_ms(uint16_t t);

void main(void)
{
    lcd_init();
    lcd_clear();

    while(1)
    {
        lcd_goto(0, 0);
        lcd_write_string("Hello");
        delay_ms(1000);

        lcd_goto(4, 1);
        lcd_write_string("World!!!");
        delay_ms(1000);

        lcd_clear();
        delay_ms(1000);
    }
}