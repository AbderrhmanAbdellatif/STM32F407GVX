#include "main.h"
#include "stm32f4xx_hal.h"
#include "adc.h"
#include "usart.h"
#include "gpio.h"
uint16_t r_data=0;
uint16_t t_data=0;
void SystemClock_Config(void);
void ADC_IRQHandler(void)
{ 
	//adc_value=HAL_ADC_GetValue(&hadc1);
	t_data=HAL_ADC_GetValue(&hadc1);
	HAL_UART_Transmit_IT(&huart2, (uint8_t*) &t_data, 2);
	HAL_ADC_IRQHandler(&hadc1);
}
void USART2_IRQHandler(void)
{
	HAL_UART_Receive_IT(&huart2,(uint8_t*)&r_data, 2);
	//HAL_UART_Transmit_IT(&huart2, (uint8_t*) &t_data, 2);
	HAL_UART_IRQHandler(&huart2);   
}

void Reset_leds(){
	HAL_GPIO_WritePin(Red_GPIO_Port,Red_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Blue_GPIO_Port,Blue_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Orange_GPIO_Port,Orange_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Green_GPIO_Port,Green_Pin,GPIO_PIN_RESET);
}
int gelenveri=0;
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{  
	gelenveri++;
}



int main(void)
{
	
//	HAL_ADC_Start_IT(&hadc1);
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_ADC1_Init();
  MX_USART2_UART_Init();
  while (1)
  {
  if(r_data<256){
	  HAL_GPIO_WritePin(GPIOD, Red_Pin , GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOD, Orange_Pin|Blue_Pin|Green_Pin , GPIO_PIN_RESET);
	}
	else if(r_data<512){
	  HAL_GPIO_WritePin(GPIOD, Orange_Pin , GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOD, Red_Pin|Blue_Pin|Green_Pin , GPIO_PIN_RESET);
	}
	else if(r_data<768){
	  HAL_GPIO_WritePin(GPIOD, Blue_Pin , GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOD, Orange_Pin|Red_Pin|Green_Pin , GPIO_PIN_RESET);
	}
	else if(r_data<1001){
	  HAL_GPIO_WritePin(GPIOD, Green_Pin , GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOD, Orange_Pin|Blue_Pin|Red_Pin , GPIO_PIN_RESET);
	}
	else if(r_data>1000){ 
	  HAL_GPIO_WritePin(GPIOD, Orange_Pin|Blue_Pin|Red_Pin|Green_Pin , GPIO_PIN_SET);
		HAL_Delay(200);
		HAL_GPIO_WritePin(GPIOD, Orange_Pin|Blue_Pin|Red_Pin|Green_Pin , GPIO_PIN_RESET);
    HAL_Delay(200);
	}
	HAL_Delay(500);
			HAL_ADC_Start_IT(&hadc1);
 
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
#endif /* USE_FULL_ASSERT */

