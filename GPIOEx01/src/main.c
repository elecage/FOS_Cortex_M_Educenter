/*
 * @file    GPIOEx01/src/main.c
 * @author Hyeon-min Shim
 * @version V1.0
 * @date    26-November-2016
 * @brief   GPIO 사용 예제 1. 1초에 한번씩 LED가 깜빡인다.
 */

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

/* Private functions ---------------------------------------------------------*/
/**
 * @brief 	SysTick 인터럽트 핸들러
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
  __HAL_RCC_GPIOG_CLK_ENABLE();					// GPIOG의 클록을 활성화한다.
  GPIO_InitTypeDef GPIO_InitStruct;				// GPIOG를 초기화하기 위한 구조체 변수를 선언한다.
  GPIO_InitStruct.Pin = GPIO_PIN_13;			// GPIOG의 13번핀을 선택한다.
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;	// GPIOG의 13번핀을 출력으로 선택한다.
  GPIO_InitStruct.Pull = GPIO_PULLUP;			// 내부 풀업저항을 사용한다.
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;	// 빠른 클록스피드를 사용한다.
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct); 		// GPIOG13 핀 설정 실행

  trace_puts("LED blink Example 01");  			// 모니터링용 문자열 출력

  while (1)
    {
	  HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, GPIO_PIN_SET); 	// LED ON
	  //for(int i = 0 ; i < 10000000 ; i++);
	  HAL_Delay(500);										// 500 msec 대기
	  HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, GPIO_PIN_RESET);// LED OFF
	  //for(int i = 0 ; i < 10000000 ; i++);
	  HAL_Delay(500);										// 500 msec 대기
    }
}

#pragma GCC diagnostic pop
