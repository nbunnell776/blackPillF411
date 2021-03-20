// 
// Nathan Bunnell
// nbunnell776@gmail.com
// 03/16/2021
// UART/src/main.c
// Simple USART echo test program implemented over USART2
//  PA2 - USART2 TX
//  PA3 - USART2 RX
//

#include "main.h"                           // Function defs and link to headers

void USART2_init(void);                     // Init func dec
void USART2_write(int ch);                  // Write func dec
char USART2_read(void);                     // Read func dec

void delay_ms(uint16_t t);                  // Simple delay func dec

int main(void)
{
    char c;                                // RX data to echo
    USART2_init();                          // Initialize USART2
    
    while(1)
    {
        c = USART2_read();                  // Get character

        if (c == '\r')                      // I think this is a Unix style line 
        {                                   // ending issue on my dev machine. 
            USART2_write(10);               // To be further researched...
            USART2_write(13);
        }
        else{}
        
        USART2_write(c);                    // Echo on serial port
    }

}
