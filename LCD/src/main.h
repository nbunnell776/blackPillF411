#ifndef _LCD_MAIN_H
#define _LCD_MAIN_H

#include "../device_headers/stm32f411xe.h"  // Device headers

const uint8_t RS_Pin = 0x0F;                // PC15 used for RS pin
const uint8_t RW_Pin = 0x0E;                // PC14 used for R/W pin
const uint8_t E_Pin = 0x0D;                 // PC13 used for Enable pin (and to blink activity)

#define DELAY 2                             // generic delay in mSec, play with as needed for timing

void lcd_gpio_init(void)
{
    RCC->AHB1ENR |= (1 << 0x05);            // Enable GPIOA & C clock

    /* 

        Clear GPIOC[13..15] mode
        Set GPIOC[13..15] to output mode
        Set GPIOC[13..15] to open drain

        Clear GPIOA[0..7] mode
        Set GPIOA[0..7] to output mode
        Set GPIOA[0..7] to open drain

    */
}

void lcd_write_instruction(uint8_t inst)
{
    delay_ms(DELAY);
    GPIOC->ODR & (~(RS_Pin));               // Signal instruction register
    GPIOC->ODR & (~(RW_Pin));               // Signal write operation
    GPIOC->ODR & (~(E_Pin));                // Clear enable pin
    GPIOA->ODR |= inst;                     // Place instruction on bus
    GPIOC->ODR |= E_Pin;                    // Set enable pin
    GPIOC->ODR & (~(E_Pin));                // Clear enable pin (triggers falling edge)
}

void lcd_write_char(unsigned char c)
{
    delay_ms(DELAY);
    GPIOC->ODR |= RS_Pin;                   // Signal data register
    GPIOC->ODR & (~(RW_Pin));               // Signal write operation
    GPIOC->ODR & (~(E_Pin));                // Clear enable pin
    GPIOA->ODR |= inst;                     // Place data on bus
    GPIOC->ODR |= E_Pin;                    // Set enable pin
    GPIOC->ODR & (~(E_Pin));                // Clear enable pin (triggers falling edge)
}

void lcd_init(void)
{
    delay_ms(DELAY);
    lcd_gpio_init();                        // Initialize GPIO for command lines and data bus
    lcd_write_instruction(0x06);            // Set cursor to increment mode
    lcd_write_instruction(0x0C);            // Turn display on, cursor off
    lcd_write_instruction(0x38);            // Configure to 8-bit data bus mode w/ 2-line display
}

void lcd_clear(void)
{
    delay_ms(2);
    lcd_write_instruction(0x01);            // Clear the display
    lcd_write_instruction(0x02);            // Returns display to initial location if previously shifted
}

void lcd_goto(uint8_t col, uint8_t row)
{
    delay_ms(DELAY);
    
    if (row == 0)
        lcd_write_instruction(0x80 + column);   // Ref data sheet for DDRAM addresses

    if (row == 1)
        lcd_write_instruction(0xC0 + column);   // Ref data sheet for DDRAM addresses
}

void lcd_write_string(char* string)
{
    delay_ms(DELAY);
    while (*string != 0)
    {
        lcd_write_char((*string)++);
    }
}

void delay_ms(uint16_t t)                   // Simple delay func def
{
    for (; t > 0; t--)
        for (int i = 0; i < 3195; i++) ;    // 3195 scales msec to 16MHz clock
}

#endif
