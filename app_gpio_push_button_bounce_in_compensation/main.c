

#include "stm32f0xx.h"

int main(void)
{
	RCC ->AHBENR |= RCC_AHBENR_GPIOCEN;
	RCC ->AHBENR |= RCC_AHBENR_GPIOBEN;

	GPIOC ->MODER |= GPIO_MODER_MODER6_0;
	GPIOC ->MODER &= ~(GPIO_MODER_MODER6_1);

	GPIOC ->OTYPER &= ~(GPIO_OTYPER_OT_6);

	GPIOC ->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR6_0 | GPIO_OSPEEDER_OSPEEDR6_1;

	GPIOC ->PUPDR &= ~(GPIO_PUPDR_PUPDR6);

	GPIOB ->MODER &= ~(GPIO_MODER_MODER1);
	GPIOB ->PUPDR &= ~(GPIO_PUPDR_PUPDR1);

	volatile char buttonPressed = 0;
	volatile int buttonPressedConfidenceLevel = 0;
	volatile int buttonReleasedConfidenceLevel = 0;
	volatile int confidenceThreshold = 200;
	volatile char LEDState = 0;

	while(1)
	{

		if (GPIOB ->IDR & GPIO_IDR_1)
		{
			if (buttonPressed == 0)
			{
				if(buttonPressedConfidenceLevel > confidenceThreshold)
				{
					if(LEDState == 0)
					{
						LEDState = 1;
						GPIOC ->BSRR |= GPIO_BSRR_BS_6;
					}
					else
					{
						LEDState = 0;
						GPIOC ->BRR |= GPIO_BSRR_BS_6;
					}
					buttonPressed = 1;
				}
				else
				{
					buttonPressedConfidenceLevel ++;
					buttonReleasedConfidenceLevel = 0;

				}
			}
		}
		else
		{
			if (buttonPressed == 1)
			{
				if(buttonReleasedConfidenceLevel > confidenceThreshold)
				{
					buttonPressed = 0;
				}
				else
				{
					buttonReleasedConfidenceLevel ++;
					buttonPressedConfidenceLevel = 0;
				}
			}
		}
	}
}
