// 
// Nathan Bunnell
// nbunnell776@gmail.com
// 03/16/2021
// UART/src/main.c
// Simple USART echo test program implemented over USART2
//  PA2 - USART2 TX
//  PA3 - USART2 RX
//

#include "../device_headers/stm32f411xe.h"  // Device headers

void USART2_init(void);                     // Init func dec
void USART2_write(int ch);                  // Write func dec
void USART2_read(void);                     // Read func dec

void delay_ms(uint16_t t);                  // Simple delay func dec

int main(void)
{
    USART2_init();                          // Initialize USART2
    
    while(1)
    {
        USART2_write('0');                  // Echo back value
        USART2_write('x');                  // Echo back value
        USART2_write('D');                  // Echo back value
        USART2_write('E');                  // Echo back value
        USART2_write('A');                  // Echo back value
        USART2_write('D');                  // Echo back value
        USART2_write('B');                  // Echo back value
        USART2_write('E');                  // Echo back value
        USART2_write('E');                  // Echo back value
        USART2_write('F');                  // Echo back value
        USART2_write(13);                   // Echo a carriage return
        USART2_write(10);                   // Echo a line feed
        
        delay_ms(500);                      // Short delay
    }
}

void USART2_init(void)
{
    RCC->AHB1ENR |= 1;                      // Enable GPIOA clock
    RCC->APB1ENR |= 0x20000;                // Enable USART2 clock

    GPIOA->AFR[0] &= ~0x0F00;               // Cfg alt func register
    GPIOA->AFR[0] |= 0x0700;
    GPIOA->MODER &= ~0x0030;
    GPIOA->MODER |= 0x0020;                  // Enable alt func register

    USART2->BRR = 0x0683;                    // 9600 baud @ 16MHz
    USART2->CR1 = 0x0008;                    // Enable Tx, 8 data bits
    USART2->CR2 = 0x0000;                    // 1 stop bit
    USART2->CR3 = 0x0000;                    // No flow control
    USART2->CR1 |= 0x2000;                   // Enable USART2
}

void USART2_write(int ch)
{
    while (!(USART2->SR & 0x0080)) {}        // Wait until TX buffer is empty
    USART2->DR = (ch & 0xFF);
}

void delay_ms(uint16_t t)                   // Simple delay func def
{
    for (; t > 0; t--)
        for (int i = 0; i < 3195; i++) ;    // 3195 scales msec to 16MHz clock
}
