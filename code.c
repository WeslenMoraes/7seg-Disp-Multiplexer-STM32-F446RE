/**
**===========================================================================
**
**  Pinos Utilizados
**  PA0 = clock do 4017
**	PB0 = seg a, PB1 = seg b, PB2 = seg c, PB3 = seg d, PB4 = seg e, PB5 = seg f, PB6 = seg g
**	PC0 = reset do 4017
**===========================================================================
*/

/* Includes */
#include "stm32f4xx.h"

#define cathode_0                    ((uint32_t)0x03f)
#define cathode_1                    ((uint32_t)0X006)
#define cathode_2                    ((uint32_t)0X05b)
#define cathode_3                    ((uint32_t)0X04f)
#define cathode_4                    ((uint32_t)0X066)
#define cathode_5                    ((uint32_t)0X06d)
#define cathode_6                    ((uint32_t)0X07d)
#define cathode_7                    ((uint32_t)0X007)
#define cathode_8                    ((uint32_t)0X07f)
#define cathode_9                    ((uint32_t)0X06f)
#define cathode_A                    ((uint32_t)0X077)
#define cathode_b                    ((uint32_t)0X07c)
#define cathode_C                    ((uint32_t)0X039)
#define cathode_d                    ((uint32_t)0X05e)
#define cathode_E                    ((uint32_t)0X07b)
#define cathode_F                    ((uint32_t)0X071)

#define TEMPO_TROCA 200


/* Private macro */
/* Private variables */
/* Private function prototypes */
/* Private functions */

/**
**===========================================================================
**
**  Abstract: main program
**
**===========================================================================
*/
int main(void)
{
	uint16_t i = 0;
	uint16_t k = 0;
	uint16_t j[] = {cathode_d,cathode_C,cathode_b,cathode_A};
	uint16_t a[] = {0,0,0,0};
	uint16_t timerTroca = 0;
	uint16_t FtimerTroca = 0;

	//Enabling GPIOS clock
		RCC->AHB1ENR=0X00000087;

	//Enabling TIM10 clock
		RCC->APB2ENR|=RCC_APB2ENR_TIM10EN;

	//Setting UIF overflow time
		TIM10->PSC = 199;
		TIM10->ARR = 399;
		TIM10->CR1|=TIM_CR1_CEN;//starts

	//habilita os pinos do GPIOA como saídas digitais
		GPIOA->MODER|=0x1;				//controla o contador habilitador dos displays

	//habilita os pinos do GPIOB como saídas digitais
		GPIOB->MODER=0x1555;			//controla os segmentos dos catodos

	//habilita os pinos do GPIOC como saídas digitais
		GPIOC->MODER=0x1;				//controla o reset

  /* Infinite loop */
  while (1)
  {

	  if(i == 0){
		  GPIOC->ODR=0x1;
		  GPIOB->ODR = j[i];
	  }
	  else{
		  GPIOB->ODR = j[i];
	  }

	  if(TIM10->SR&TIM_SR_UIF)
	  	{
			TIM10->SR  =~ TIM_SR_UIF;	 //Ok, already seen the overflow
			GPIOC->ODR  = 0x0;

			timerTroca++;

			if(timerTroca == TEMPO_TROCA){
				timerTroca = 0;
				FtimerTroca = 1;
			}

			if (i == 3){
				i = 0;
			}
			else{
				GPIOA->ODR |= 0x1;
				GPIOA->ODR  = 0x0;
				i++;
			}
	  	}

	  if(FtimerTroca){

		  FtimerTroca = 0;

		  for(k = 0; k < 4; k++)
			  a[k] = j[k];

		  j[0] = a[3];
		  j[1] = a[0];
		  j[2] = a[1];
		  j[3] = a[2];

	  }

  }//end of while
}//end of main

