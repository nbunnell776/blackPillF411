#include "main.h"

/*
    Main program
*/

void delay(void);

int main (void)
{
    // Enable GPIOB periphs in 'RCC_AHBENR'
    //RCC->AHBENR |= RCC_AHBENR_GPIOCEN;

    // I/O port C and A clock enable
    RCC->APB2ENR = RCC_APB2ENR_IOPCEN | RCC_APB2ENR_IOPAEN;
    
    // Init GPIO pins
    // Button pin (C14) set to input w/ pulll-up
    //GPIOB->MODER &= ~(0x03 << (BUTTON_PIN * 2));
    //GPIOB->PUPDR &= ~(0x03 << (BUTTON_PIN * 2));
    //GPIOB->PUPDR |= (0x01 << (BUTTON_PIN * 2));

    // LED pin (C13) connected to on-board LED, set to push-pull, low speed 
    //  output
    //GPIOB->MODER &= ~(0x03 << (LED_PIN * 2));
    //GPIOB->MODER |= (0x01 << (LED_PIN * 2));
    //GPIOB->OTYPER &= ~(1 << LED_PIN);
    
    // Track button state
    uint8_t button_down = 0;

    GPIOC->CRH &= ~(GPIO_CRH_MODE13 | GPIO_CRH_CNF13);
    GPIOC->CRH |= GPIO_CRH_MODE13;

    // Main loop
    while(1)
    {
        /*
        // Invert IDR value since we're active low
        uint32_t idr_val = ~GPIOB->IDR;

        if (idr_val & (1 << BUTTON_PIN))
        {
            if (!button_down)
            {
                GPIOB->ODR ^= (1 << LED_PIN);
            }
            button_down = 1;
        }
        else
        {
            button_down = 0;
        }
        */

        GPIOC->BRR |= 1<<13;
        for (int i = 0; i < 1000000; ++i) asm("nop");
        GPIOC->BSRR |= 1<<13;
        for (int i = 0; i <  500000; ++i) asm("nop");


    }
}

void delay(void)
{
    volatile unsigned int i;
    for(i = 0; i < 20000; i++)
        ;
}
