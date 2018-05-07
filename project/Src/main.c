#include "main.h"
#include "stm32f4xx_hal.h"
#include "adc.h"
#include "gpio.h"
int adc_value=0;
void SystemClock_Config(void);
int sayi = 0, rakam = 0, toplam = 0;
int sag1 = 0;
int sag2 = 0;
int sag3 = 0;
int adcbin3=0;
int adcbin2=0;
int adcbin=0;
void controlsag1(int);
void controlsag2(int);
void controlsag3(int);
unsigned int int_to_bin(unsigned int k);

void ADC_IRQHandler(void)
{
  adc_value=HAL_ADC_GetValue(&hadc1);
	  sayi=adc_value;
	int sayici = 0;
	while (sayi > 0) {
            rakam = sayi % 10;
            if (sayici == 0) {
                sag3 = rakam;
            }
            if (sayici == 1) {
                sag2 = rakam;
            }
            if (sayici == 2) {
                sag1 = rakam;
            }
            sayi = sayi / 10;
            sayici++;
        }
	      adcbin=int_to_bin(sag1);
			  adcbin2=int_to_bin(sag2);
	     	adcbin3=int_to_bin(sag3);
				if(adcbin==0 || adcbin2==0 || adcbin3==0){//0
		  HAL_GPIO_WritePin(GPIOA, a_Pin|f_Pin|b_Pin|e_Pin|c_Pin|d_Pin, GPIO_PIN_SET);
	//		HAL_Delay(500);
		}
		if(adcbin==1|| adcbin2==1 || adcbin3==1){//1
		  HAL_GPIO_WritePin(GPIOA, b_Pin|c_Pin, GPIO_PIN_SET);	 
	//		HAL_Delay(500);
		}
		if(adcbin==10 || adcbin2==10 || adcbin3==10){//2
		  HAL_GPIO_WritePin(GPIOA, a_Pin|b_Pin|e_Pin|g_Pin|d_Pin, GPIO_PIN_SET);
		//	HAL_Delay(5000);
		}
		if(adcbin==11 || adcbin2==11 || adcbin3==11){//3
		  HAL_GPIO_WritePin(GPIOA, a_Pin|b_Pin|c_Pin|g_Pin|d_Pin, GPIO_PIN_SET);
		//HAL_Delay(1);
		}
		if(adcbin==100 || adcbin2==100 || adcbin3==100){//4
		  HAL_GPIO_WritePin(GPIOA, b_Pin|c_Pin|g_Pin|f_Pin, GPIO_PIN_SET);
	//	HAL_Delay(1);
		}
		if(adcbin==101 || adcbin2==101 || adcbin3==101){//5
		  HAL_GPIO_WritePin(GPIOA, a_Pin|c_Pin|g_Pin|f_Pin|d_Pin, GPIO_PIN_SET);
	//	HAL_Delay(1);
		}
		if(adcbin==110|| adcbin2==110 || adcbin3==110){//6
		  HAL_GPIO_WritePin(GPIOA, a_Pin|d_Pin|c_Pin|g_Pin|f_Pin|e_Pin, GPIO_PIN_SET);
	//	HAL_Delay(1);
		}
		if(adcbin==111 || adcbin2==111 || adcbin3==111){//7
		  HAL_GPIO_WritePin(GPIOA, a_Pin|b_Pin|c_Pin|g_Pin, GPIO_PIN_SET);
	//	HAL_Delay(1);
		}
		if(adcbin==1000 || adcbin2==1000 || adcbin3==1000){//8
				  HAL_GPIO_WritePin(GPIOA, a_Pin|g_Pin|f_Pin|b_Pin|e_Pin|c_Pin|d_Pin, GPIO_PIN_SET);
	//	HAL_Delay(1);
		}
		if(adcbin==1001|| adcbin2==1001 || adcbin3==1001){//9
				  HAL_GPIO_WritePin(GPIOA, a_Pin|g_Pin|f_Pin|b_Pin|e_Pin|c_Pin, GPIO_PIN_SET);
	//	HAL_Delay(1);
		}
	HAL_ADC_Start_IT(&hadc1);
  HAL_ADC_IRQHandler(&hadc1);
	
	/* USER CODE END ADC_IRQn 0 */
  
  /* USER CODE BEGIN ADC_IRQn 1 */

}

unsigned int int_to_bin(unsigned int k) {
    return (k == 0 || k == 1 ? k : ((k % 2) + 10 * int_to_bin(k / 2)));
}

int main(void)
{
   HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_ADC1_Init();
	  
	   // controlsag1(sag1);
		HAL_ADC_Start_IT(&hadc1);
	HAL_GPIO_WritePin(GPIOC, sag3_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOC, sag2_Pin, GPIO_PIN_SET);
   	    HAL_GPIO_WritePin(GPIOC, sag1_Pin, GPIO_PIN_SET);
	
  while (1)
  {
	//	takethenumbers();
		

  }
  /* USER CODE END 3 */

}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Configure the main internal regulator output voltage 
    */
  __HAL_RCC_PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
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

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
