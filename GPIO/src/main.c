#include "../device_headers/stm32f411xe.h"  // Device headers

void delay_ms(uint16_t t);                  // Simple delay func dec

int main(void)
{
    RCC->AHB1ENR |= (1 << 0x2);             // Enable GPIOA clock
    GPIOC->MODER  &= ~(0x3 << 26);          // Clear MODER13
    GPIOC->MODER  |=  (0x1 << 26);          // Set MODER13 to output mode
    GPIOC->OTYPER &= ~(1 << 13);            // Set to Open Drain

    while(1)
    {
        GPIOC->ODR ^= (1 << 13);            // Toggle pin
        delay_ms(500);                      // Delay
    }
}

void delay_ms(uint16_t t)                   // Simple delay func def
{
    for (; t > 0; t--)
        for (int i = 0; i < 3195; i++) ;    // 3195 scales msec to 16MHz clock
}