/*
 * @file   TimerEx01/src/main.c
 * @author Hyeon-min Shim
 * @version V1.0
 * @date    28-Feburary-2017
 * @brief   타이머 사용 예제 1. 타이머를 이용하여 정확히 1초에 한번씩 LED가 깜빡인다.
 */
// ----------------------------------------------------------------------------

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"
#include "stm32f4xx_hal.h"


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
void __initialize_hardware(void);	// __initialze_hardware.c에 있는 초기화 함수

/**
 * @brief 	SysTick 인터럽트 핸들러. 이 예제에서는 반드시 필요한 것은 아님
 * @param 	None
 * @retval 	None
 */
void SysTick_Handler(void)
{
  HAL_IncTick();
}

/**
 * @brief 	Main 함수
 * @param 	None
 * @retval 	None
 */
int main(int argc, char* argv[])
{
	  __initialize_hardware();

	  /* Timer 초기화 */
	  __HAL_RCC_TIM2_CLK_ENABLE();	// Timer 2 클록 활성화

	  TIM_HandleTypeDef htim;
	  htim.Instance = TIM2;
	  TIM_Base_InitTypeDef TIM2_InitStruct;
	  TIM2_InitStruct.Period = 10000 - 1;			// 10kHz를 1000까지 카운트한 후 0으로 -> 1초
	  TIM2_InitStruct.Prescaler = 18000; 			// 180MHz를 18000분주한다. --> 10kHz
	  TIM2_InitStruct.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	  TIM2_InitStruct.CounterMode = TIM_COUNTERMODE_UP;// 상승 카운터 모드
	  TIM2_InitStruct.RepetitionCounter = 0;
	  htim.Init = TIM2_InitStruct;
	  HAL_TIM_Base_Init(&htim);

	  __HAL_RCC_GPIOG_CLK_ENABLE();					// GPIOG의 클록을 활성화한다.
	  GPIO_InitTypeDef GPIO_InitStruct;				// GPIOG를 초기화하기 위한 구조체 변수를 선언한다.
	  GPIO_InitStruct.Pin = GPIO_PIN_13;			// GPIOG의 13번핀을 선택한다.
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;	// GPIOG의 13번핀을 출력으로 선택한다.
	  GPIO_InitStruct.Pull = GPIO_PULLUP;			// 내부 풀업저항을 사용한다.
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;	// 빠른 클록스피드를 사용한다.
	  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct); 		// GPIOG13 핀 설정 실행


	  HAL_TIM_Base_Start(&htim);

	  trace_puts("LED blink by Timer\n");  			// 모니터링용 문자열 출력

	  while (1)
	  {

       int timerCount = __HAL_TIM_GET_COUNTER(&htim);
       if(timerCount == 0)							// 타이머가 0일 때 LED를 끈다.
       {
    	   HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, GPIO_PIN_RESET);
       }
       if(timerCount == 5000)						// 타이머가 0.5초일 때 LED를 켠다.
       {
    	   HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, GPIO_PIN_SET);
       }
	  }
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
