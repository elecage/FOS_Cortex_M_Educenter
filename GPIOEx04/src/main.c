/*
 * @file    GPIOEx04/src/main.c
 * @author Hyeon-min Shim
 * @version V1.0
 * @date    26-November-2016
 * @brief   GPIO 사용 예제 1
 */

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"
#include "stm32f4xx_hal.h"		// STM32F4 HAL Library를 사용하기 위한 헤더파일

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
	int i;
	__initialize_hardware();
	__HAL_RCC_GPIOD_CLK_ENABLE();					// GPIOD의 클록을 활성화한다.
	GPIO_InitTypeDef GPIO_InitStruct;				// GPIOD를 초기화하기 위한 구조체 변수를 선언한다.
	GPIO_InitStruct.Pin = (uint16_t)0x00FFU; 		// GPIOD0 ~ GPIOD7 핀 사용
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;		// GPIOD0 ~ GPIOD7 핀 을 출력으로 선택한다.
	GPIO_InitStruct.Pull = GPIO_PULLUP;				// 내부 풀업저항을 사용한다.
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;	// 빠른 클록스피드를 사용한다.
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct); 		// GPIOD0 ~ GPIOD7   핀 설정 실행

	trace_puts("LED blink Example 04");  // 모니터링용 문자열 출력
	HAL_Delay(5000);
 	while (1)
    {
 		for(i = 0 ; i < 8 ; i++)
 		{
 			//GPIOD->ODR = 0x01 << i;
 			GPIOD->BSRR = 0x01 << i;
 			HAL_Delay(500);
 		}
    }
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
