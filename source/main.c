#include <stm32f10x_it.h>
#include "stm32f10x_rcc.h"

int main(void) {

    SysTick_Config(72000); // Configure systick interruption every 1kHz

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE); // Enable GPIOC clock

    GPIO_InitTypeDef gpioInitTypeDef;
    gpioInitTypeDef.GPIO_Mode = GPIO_Mode_Out_PP;
    gpioInitTypeDef.GPIO_Pin = GPIO_Pin_13;
    gpioInitTypeDef.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOC,&gpioInitTypeDef);


    while (1) {
        GPIOC->BSRR |= GPIO_Pin_13;
        time_1kHz = 500;
        while(time_1kHz);
        GPIOC->BSRR |= GPIO_Pin_13 << 16;
        time_1kHz = 500;
        while(time_1kHz);
    }
}
