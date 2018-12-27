#include "stm32f0xx.h"

#define DELAY 100000

void waitForAMoment( int Moment)
{
	volatile int i, j;

	for (i = 0; i < Moment; ++i) {

		j ++;
	}
}

int main(void)
{
	RCC ->AHBENR |= RCC_AHBENR_GPIOCEN;
	GPIOC ->MODER |= GPIO_MODER_MODER6_0;
	GPIOC ->MODER &= ~(GPIO_MODER_MODER6_1);
	GPIOC ->OTYPER &= ~(GPIO_OTYPER_OT_6);
	GPIOC ->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR6;
	GPIOC ->PUPDR &= ~(GPIO_PUPDR_PUPDR6);

	while(1)
	{
		GPIOC ->BSRR |= GPIO_BSRR_BS_6;
		waitForAMoment(DELAY);
		GPIOC ->BRR |= GPIO_BRR_BR_6;
		waitForAMoment(DELAY);
	}
}
