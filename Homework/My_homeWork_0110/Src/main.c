
#include "main.h"
#include "stm32f4xx_hal.h"
#include "adc.h"
#include "gpio.h"
int adc_value=0;
void SystemClock_Config(void);
	static void MX_NVIC_Init(void);

	void ADC_IRQHandler(void)
	{
		adc_value=HAL_ADC_GetValue(&hadc1);
		HAL_ADC_IRQHandler(&hadc1);
	}

int main(void)
{
HAL_Init();

SystemClock_Config();
MX_GPIO_Init();
MX_ADC1_Init();
MX_NVIC_Init();

	
while (1)
{
		HAL_ADC_Start_IT(&hadc1);
		if(adc_value<255){
		  HAL_GPIO_WritePin(Red_Led_GPIO_Port,Red_Led_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(Blue_led_GPIO_Port,Blue_led_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(orange_led_GPIO_Port,orange_led_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(Green_led_GPIO_Port,Green_led_Pin,GPIO_PIN_RESET);
			HAL_Delay(500);
		  }else if (adc_value>256 && adc_value<511){
		  HAL_GPIO_WritePin(Red_Led_GPIO_Port,Red_Led_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(Blue_led_GPIO_Port,Blue_led_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(orange_led_GPIO_Port,orange_led_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(Green_led_GPIO_Port,Green_led_Pin,GPIO_PIN_RESET);
			HAL_Delay(500);
			}else if (adc_value>512 && adc_value<767){
		  HAL_GPIO_WritePin(Red_Led_GPIO_Port,Red_Led_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(Blue_led_GPIO_Port,Blue_led_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(orange_led_GPIO_Port,orange_led_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(Green_led_GPIO_Port,Green_led_Pin,GPIO_PIN_RESET);
			HAL_Delay(500);
			}else if (adc_value>767){
		  HAL_GPIO_WritePin(Red_Led_GPIO_Port,Red_Led_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(Blue_led_GPIO_Port,Blue_led_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(orange_led_GPIO_Port,orange_led_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(Green_led_GPIO_Port,Green_led_Pin,GPIO_PIN_SET);
			HAL_Delay(500);
			}
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
  HAL_NVIC_SetPriority(PVD_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(PVD_IRQn);
  HAL_NVIC_SetPriority(EXTI1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI1_IRQn);
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