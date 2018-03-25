#include "main.h"
#include "stm32f4xx_hal.h"
#include "adc.h"
#include "gpio.h"
void SystemClock_Config(void);
static void MX_NVIC_Init(void);
int adcvalue=0;
void EXTI0_IRQHandler(void)
{
  HAL_ADC_Start_IT(&hadc1);
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
	if(adcvalue < 250 && adcvalue > 0 ){
	HAL_GPIO_WritePin(GPIOA, led1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, led3_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, led4_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, led2_Pin, GPIO_PIN_RESET);
	}
	else if(adcvalue < 500 && adcvalue > 250 ){
	HAL_GPIO_WritePin(GPIOA, led2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, led1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, led3_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, led4_Pin, GPIO_PIN_RESET);
	}
	else if(adcvalue < 750 && adcvalue > 500 ){
	HAL_GPIO_WritePin(GPIOA, led3_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, led2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, led1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, led4_Pin, GPIO_PIN_RESET);
	}
	else if( adcvalue > 750 ){
	HAL_GPIO_WritePin(GPIOA, led4_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, led2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, led1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, led3_Pin, GPIO_PIN_RESET);
	}
	}
	void ADC_IRQHandler(void)
{
  adcvalue=HAL_ADC_GetValue(&hadc1);
  HAL_ADC_IRQHandler(&hadc1);
}
int main(void){
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_ADC1_Init();
  MX_NVIC_Init();
  while (1)
  {
  }
}
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  __HAL_RCC_PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}
static void MX_NVIC_Init(void)
{
  HAL_NVIC_SetPriority(ADC_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(ADC_IRQn);
  HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}
void _Error_Handler(char *file, int line)
{
  while(1)
  {
  }
}
#ifdef  USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line)
{ 
}
#endif 