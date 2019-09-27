/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#define THRESHOLD 60
#define SETPOINT  600

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

uint32_t i = 0;
uint32_t soma = 0;

uint32_t uiADC;
char pBufferTx[20];
float fADC;

int main(void){
  
  /* MCU Configuration--------------------------------------------------------*/
  HAL_Init();
  
  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM4_Init();

  MX_USART2_UART_Init();
  MX_USART3_UART_Init();

  MX_ADC1_Init();


  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);

  HAL_ADC_Start_IT(&hadc1);

  while (1)
  {

  }
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
  
  i++;

  uiADC = HAL_ADC_GetValue(hadc);
  fADC = (3000* uiADC)/4096;
  uiADC = (int) fADC;
  
  soma += uiADC;

  if(i == 10000/2)
  {
    uiADC = soma/i;

    soma = 0;
    i = 0;

    if(uiADC < SETPOINT - THRESHOLD)
    {
      HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);
    }
    else if(uiADC > SETPOINT)
    {
      HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET);    
    }

    pBufferTx[6] = '\n';

    pBufferTx[5] = uiADC%10 + '0';
    uiADC /= 10;

    pBufferTx[4] = '.';
    
    pBufferTx[3] = uiADC%10 + '0';
    uiADC /= 10;
    
    pBufferTx[2] = uiADC%10 + '0';
    uiADC /= 10;
    
    pBufferTx[1] = ':';
    pBufferTx[0] = 'T';

    HAL_UART_Transmit_IT(&huart3, pBufferTx, 7);
  }

}

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

void Error_Handler(void)
{

}

#ifdef  USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line)
{ 
}
#endif /* USE_FULL_ASSERT */