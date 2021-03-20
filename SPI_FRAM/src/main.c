// 
// Nathan Bunnell
// nbunnell776@gmail.com
// 03/20/2021
// SPI/src/main.c
//
// Program to read and write data to MB85RS64V FRAM module 
//  via SPI with console feedback
//  
//  Pin mapping:
//  PA2 - USART2 TX
//  PA3 - USART2 RX
//  PA4 - NSS1
//  PA5 - SCK1
//  PA6 - MISO1
//  PA7 - MOSI1
//

/* Include section */
#include "main.h"                           // Function defs and link to headers

/* Function declarations */
// USART2
void USART2_init(void);                     
void USART2_write(char ch);                  
char USART2_read(void);                     
void printLn(char* s);

// SPI1
void SPI1_init(void);
void SPI1_write(unsigned char d);
unsigned char SPI1_read(void);
void SPI1_SS_Set(void);
void SPI1_SS_Clear(void);

// FRAM
void FRAM_write(uint16_t a, char d);
unsigned char FRAM_read(uint16_t a);

// Delay
void delay_ms(uint16_t t);                  // Simple delay func dec

/* Main code */
int main(void)
{
    USART2_init();                          // Initialize USART2
    SPI1_init();                            // Initialize SPI1

    char c;                                 // Read from console

    char headerMsg[] = ("FRAM R/W interface\n"); //Simple header 'UI' for console
    printLn(headerMsg);
    
    int16_t address = 0x00;                 // Starting address
    unsigned char data = 0xFF;              // Starting data value
    
    while(1)
    {
        /* Loop through first 256 bytes of storage and write to them */
        for (address = 0x00; address < 0xFF; address++, data--)
        {
            FRAM_write(address, data);
        }

        /* Loop through first 256 bytes of storage and read them */
        for (address = 0x00; address < 0xFF; address++)
        {
            printLn("Value at addy ");
            USART2_write(address);
            printLn("is ");
            USART2_write(FRAM_read(data));

            delay_ms(100);
        }        
    }

}
