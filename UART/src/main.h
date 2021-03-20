#ifndef _UART_MAIN_H
#define _UART_MAIN_H

#include "../device_headers/stm32f411xe.h"  // Device headers

void USART2_init(void)
{
    // Clock enable
    RCC->AHB1ENR |= 1;                      // Enable GPIOA clock
    RCC->APB1ENR |= 0x20000;                // Enable USART2 clock

    // Cfg for PA2/ USART2 TX
    GPIOA->AFR[0] &= ~0x0F00;               // Cfg alt func register
    GPIOA->AFR[0] |= 0x0700;
    GPIOA->MODER &= ~0x0030;                // Enable alt func register
    GPIOA->MODER |= 0x0020;                 

    // Cfg for PA3/ USART3 TX
    GPIOA->AFR[0] &= ~0xF000;               // Cfg alt func register
    GPIOA->AFR[0] |= 0x7000;
    GPIOA->MODER &= ~0x00C0;                // Enable alt func register
    GPIOA->MODER |= 0x0080;                 

    // USART functional cfg
    USART2->BRR = 0x0683;                   // 9600 baud @ 16MHz w/ oversampling by 16
    USART2->CR1 = 0x00AC;                   // Enable Tx, RX, 8 data bits
    USART2->CR2 = 0x0000;                   // 1 stop bit
    USART2->CR3 = 0x0000;                   // No flow control
    USART2->CR1 |= 0x2000;                  // Enable USART2
}

void USART2_write(int ch)
{
    while (!(USART2->SR & 0x0080)) {}       // Wait until TX buffer is empty
    USART2->DR = (ch & 0xFF);
}

char USART2_read(void)
{
    while (!(USART2->SR & 0x0020)) {}       // Wait until RX buffer is not empty
    return USART2->DR;
}

void delay_ms(uint16_t t)                   // Simple delay func def
{
    for (; t > 0; t--)
        for (int i = 0; i < 3195; i++) ;    // 3195 scales msec to 16MHz clock
}

#endif
