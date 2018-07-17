
/* Includes */
#include "stm32f4xx.h"

//REVISAR ISSO!(ABCD estão certos)

#define cathode_0                    ((uint32_t)0x03fc)
#define cathode_1                    ((uint32_t)0X0060)
#define cathode_2                    ((uint32_t)0X05b0)
#define cathode_3                    ((uint32_t)0X04f0)
#define cathode_4                    ((uint32_t)0X0660)
#define cathode_5                    ((uint32_t)0X06d0)
#define cathode_6                    ((uint32_t)0X07d0)
#define cathode_7                    ((uint32_t)0X0070)
#define cathode_8                    ((uint32_t)0X07fc)
#define cathode_9                    ((uint32_t)0X06f0)
#define cathode_A                    ((uint32_t)0X077)
#define cathode_b                    ((uint32_t)0X07c)
#define cathode_C                    ((uint32_t)0X039)
#define cathode_d                    ((uint32_t)0X05e)
#define cathode_E                    ((uint32_t)0X07b)
#define cathode_F                    ((uint32_t)0X071)

#define disp0_ENABLE                 ((uint32_t)0X0400)
#define disp1_ENABLE                 ((uint32_t)0X1000)
#define disp2_ENABLE                 ((uint32_t)0X4000)
#define disp3_ENABLE                 ((uint32_t)0X1000)


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

	//Enabling GPIOS clock
		RCC->AHB1ENR=0X00000087;

	//Enabling TIM10 clock
		RCC->APB2ENR|=RCC_APB2ENR_TIM10EN;

	//Setting UIF overflow time
		TIM10->PSC = 159;
		TIM10->ARR = 279;
		TIM10->CR1|=TIM_CR1_CEN;//starts

	//habilita os pinos do GPIOA como saídas digitais
		GPIOA->MODER|=0x1;				//controla o contador habilitador dos displays

	//habilita os pinos do GPIOB como saídas digitais
		GPIOB->MODER=0x5555;			//controla os segmentos dos catodos

	//habilita os pinos do GPIOC como saídas digitais
		GPIOC->MODER=0x1;				//controla o reset

  /* Infinite loop */
  while (1)
  {

	  switch(i)
	  	  {
	  		  case 0:
	  			  GPIOC->ODR=0x1;
	  			  GPIOB->ODR = cathode_d;
	  		  break;
	  	  	  case 1:
	  	  	  	  GPIOB->ODR = cathode_C;
	  	  	  break;
	  	  	  case 2:
	  	  	  	  GPIOB->ODR = cathode_b;
	  	  	  break;
	  	  	  case 3:
	  	  	   	  GPIOB->ODR = cathode_A;
	  	  	  break;
	  	  }

	  if(TIM10->SR&TIM_SR_UIF)
	  	{
			TIM10->SR  =~ TIM_SR_UIF;	 //Ok, already seen the overflow
			GPIOC->ODR  = 0x0;
			if (i == 3){
				i = 0;
			}
			else{
				GPIOA->ODR |= 0x1;
				GPIOA->ODR  = 0x0;
				i++;
			}
	  	}

  }//end of while
}//end of main
