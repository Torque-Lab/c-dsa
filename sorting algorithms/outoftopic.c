#define GPIO_BASE 0x40020000
#define RCC_BASE  0x40021000

#define RCC_AHB1ENR (*(volatile unsigned long *)(RCC_BASE + 0x30))
#define GPIO_MODER  (*(volatile unsigned long *)(GPIO_BASE + 0x00))
#define GPIO_ODR    (*(volatile unsigned long *)(GPIO_BASE + 0x14))

void delay(volatile unsigned int time) {
    while (time--) {}
}

int main(void) {
    // Enable clock to GPIO port
    RCC_AHB1ENR |= (1 << 0);  // Enable GPIOA clock

    // Set GPIO pin mode to output
    GPIO_MODER |= (1 << 10);  // Set PA5 to output

    while (1) {
        // Toggle the LED
        GPIO_ODR ^= (1 << 5);  // Toggle PA5
        delay(1000000);        // Delay
    }

    return 0;
}
