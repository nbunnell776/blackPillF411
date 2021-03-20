#ifndef _UART_MAIN_H
#define _UART_MAIN_H

#include "../device_headers/stm32f411xe.h"  // Device headers

void USART2_init(void)
{
    // Clock enable
    RCC->AHB1ENR |= 1;                      // Enable GPIOA clock
    RCC->APB1ENR |= 0x0020000;              // Enable USART2 clock

    // Cfg for PA2 as USART2 TX
    GPIOA->AFR[0] &= ~0x0F00;               // Cfg alt func register
    GPIOA->AFR[0] |= 0x0700;
    GPIOA->MODER &= ~0x0030;                // Enable alt func register
    GPIOA->MODER |= 0x0020;                 

    // Cfg for PA3 as USART3 TX
    GPIOA->AFR[0] &= ~0xF000;               // Cfg alt func register
    GPIOA->AFR[0] |= 0x7000;
    GPIOA->MODER &= ~0x00C0;                // Enable alt func register
    GPIOA->MODER |= 0x0080;                 

    // USART2 functional cfg
    USART2->BRR = 0x0683;                   // 9600 baud @ 16MHz w/ oversampling by 16
    USART2->CR1 = 0x00AC;                   // Enable Tx, RX, 8 data bits
    USART2->CR2 = 0x0000;                   // 1 stop bit
    USART2->CR3 = 0x0000;                   // No flow control
    USART2->CR1 |= 0x2000;                  // Enable USART2
}

void USART2_write(char ch)
{
    while (!(USART2->SR & 0x0080)) {}       // Wait until TX buffer is empty
    USART2->DR = (ch & 0xFF);
}

char USART2_read(void)
{
    while (!(USART2->SR & 0x0020)) {}       // Wait until RX buffer is not empty
    return USART2->DR;
}

// UNTESTED
void printLn(char* s)
{
    while (*s != '\0')
    {
        USART2_write(*s);
        s++;
    }
}

void SPI1_init(void)
{
    // Clock enable
    RCC->AHB1ENR |= 1;                      // Enable GPIOA clock
    RCC->APB2ENR |= 0x1000;                 // Enable SPI1 clock

    // Cfg for PA4 as NSS1
    GPIOA->MODER &= 0x0300;                 // Clear pin mode
    GPIOA->MODER |= 0x0100;                 // Set to output mode     

    // Cfg for PA5 as SCK1
    GPIOA->MODER &= ~0x07FF;                // Clear pin mode
    GPIOA->MODER |= 0x0800;                 // Set to alt function mode
    GPIOA->AFR[0] &= ~0x00F00000;           // Clear AF mode
    GPIOA->AFR[0] |= 0x00500000;            // Set to mode 5 for SPI1
    
    // Cfg for PA6 as MISO1
    GPIOA->MODER &= ~0x07FF;                // Clear pin mode
    GPIOA->MODER |= 0x0800;                 // Set to alt function mode
    GPIOA->AFR[0] &= ~0x0F000000;           // Clear AF mode
    GPIOA->AFR[0] |= 0x05000000;            // Set to mode 5 for SPI1

    // Cfg for PA7 as MOSI
    GPIOA->MODER &= ~0x07FF;                // Clear pin mode
    GPIOA->MODER |= 0x0800;                 // Set to alt function mode
    GPIOA->AFR[0] &= ~0xF0000000;           // Clear AF mode
    GPIOA->AFR[0] |= 0x50000000;            // Set to mode 5 for SPI1

    // SPI1 functional cfg
    SPI1->CR1 = 0x031C;                     // Set baud rate, 8-bit data size
    SPI1->CR2 = 0;
    SPI1->CR1 |= 0x0040;                    // Enable SPI1
}

void SPI1_write(unsigned char d)
{
    while(!(SPI1->SR & 2)) {}               // Wait until TX buffer is empty
    SPI1->DR = d;                           // Push data to TX buffer
    while(!(SPI1->SR & 0x0080)) {}          // Wait until TX is complete
}

unsigned char SPI1_read(void)
{
    while(!(SPI1->SR & 1)) {}               // Wait until RX buffer has new data
    return SPI1->DR;                        // Return contents of RX buffer
}

void SPI1_SS_Set(void)                      // Wrapper function
{
    GPIOA->BSRR = 0x00100000;               // Assert SS pin
}

void SPI1_SS_Clear(void)                    // Wrapper function
{
    GPIOA->BSRR = 0x0010;                   // Deassert SS pin
}

void FRAM_write(uint16_t a, char d)
{
    /* 
        Write data to FRAM module:
        - Assert SS pin
        - Send WREN command to set write enable latch (0x06)
        - Send WRITE command (0x02)
        - Send 16-bit address (a) and 8-bit data (d)
        - Send WRDI command to clear write enable latch (0x04)
        - Deassert SS pin
    */

   SPI1_SS_Set();
   SPI1_write(0x06);
   SPI1_write(0x02);
   SPI1_write(a);
   SPI1_write(d);
   SPI1_write(0x04);
   SPI1_SS_Clear();
}

unsigned char FRAM_read(uint16_t a)
{
    /* 
        Read data to FRAM module:
        - Assert SS pin
        - Send READ command (0x03)
        - Send 16-bit address (a) to read data (d) from
        - Deassert SS pin
    */

   SPI1_SS_Set();
   SPI1_write(0x03);
   SPI1_write(a);
   unsigned char d = SPI1_read();
   SPI1_SS_Clear();
   return(d);
}

void delay_ms(uint16_t t)                   // Simple delay func def
{
    for (; t > 0; t--)
        for (int i = 0; i < 3195; i++) ;    // 3195 scales msec to 16MHz clock
}

#endif
