#include <stm32f10x_it.h>
#include "stm32f10x_rcc.h"

int main(void) {

    SysTick_Config(720);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC, ENABLE);
    GPIO_InitTypeDef gpioInitTypeDef;
    gpioInitTypeDef.GPIO_Mode = GPIO_Mode_Out_PP;
    gpioInitTypeDef.GPIO_Pin = GPIO_Pin_13;
    gpioInitTypeDef.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOC, &gpioInitTypeDef);

    gpioInitTypeDef.GPIO_Mode = GPIO_Mode_Out_PP;
    gpioInitTypeDef.GPIO_Pin = GPIO_Pin_6;
    gpioInitTypeDef.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOA, &gpioInitTypeDef);
    GPIOA->BSRR |= GPIO_Pin_6 << 16; // Pin_6 to low state

    gpioInitTypeDef.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    gpioInitTypeDef.GPIO_Pin = GPIO_Pin_7;
    gpioInitTypeDef.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOA, &gpioInitTypeDef);

    uint32_t data;
    while (1) {

        while (GPIOA->IDR & GPIO_Pin_7); // Wait the low state on DOUT
        time_10us = 1;
        while (time_10us); // Wait 10 us before sending PD_SCK
        for (uint8_t i = 0; i < 25; ++i) {
            GPIOA->BSRR |= GPIO_Pin_6; // PD_SCK High
            time_10us = 1;
            while (time_10us); // Wait 10 us

            data |= ((GPIOA->IDR & GPIO_Pin_7) >> 7) << (24-i);

            GPIOA->BSRR |= GPIO_Pin_6 << 16; // PD_SCK Low
            time_10us = 1;
            while (time_10us); // Wait 10 us
        }
        data >>= 10;
        time_10us = 1000;
        while (time_10us);
        data = 0;
    }
}
