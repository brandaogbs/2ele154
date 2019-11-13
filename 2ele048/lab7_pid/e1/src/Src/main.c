/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#define THRESHOLD 00
#define SETPOINT 80
#define KP 20
#define KI 0.1
#define KD 10
#define DT 0.1

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);


volatile uint32_t uiADC;
volatile int32_t uiPWM;

float fSoma = 0;
float fErro = 0;
float fADC = 0;

float fErroPrev = 0;
float fADCPrev = 0;

int32_t uiProp  = 0;
int32_t uiInteg = 0;
int32_t uiDeriv = 0;

uint32_t i = 0;

char pBufferTx[200];

int main(void)
{
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

  HAL_ADC_Start_IT(&hadc1);

  PID();
  
  while (1)
  {
  }
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{

  i++;

  uiADC = HAL_ADC_GetValue(hadc);
  fADC = (300 * uiADC) / 4096;

  fSoma += fADC;

  if (i == 2000)
  {
    fADCPrev = fADC;
    fADC = fSoma / i;

    fSoma = 0;
    i = 0;

    PID(fADC);

    pkgDataUART(pBufferTx);
    HAL_UART_Transmit_IT(&huart3, pBufferTx, 4);
  }
}

// Calibrate the slope between Temp vs. PWM
void PID(float temp)
{
  float pulseLow = 10;
  float pulseHigh = 30;

  float tempLow = 61;
  float tempHigh = 108;

  float coefA = (pulseLow - pulseHigh) / (tempLow - tempHigh);
  float coefB = pulseHigh - (coefA * tempHigh);

  fErroPrev = fErro;
  fErro = (SETPOINT - fADC);


  uiInteg = (uiInteg + (int32_t)( ((0.5*fErro + 0.5*fErroPrev)*KI)*DT ))%100;

  uiDeriv = (int32_t)( ((fErro - fErroPrev)*KD)/DT );

  uiProp  = (int32_t)(coefB + coefA * (fErro*KP));
  
  if (fErro < 0)
  {
    fErro = 0;
  }

  uiPWM = (uiProp + uiInteg + uiDeriv)%100;

  if (uiPWM < 0)
  {
    uiPWM = 3;
  }

  __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, uiPWM);
}

// Convert uint32 ADC data to str for uart
void pkgDataUART(char *pBufferTx) 
{
  uiADC = (uint32_t)(fADC * 10);

  pBufferTx[3] = '\n';

  pBufferTx[2] = uiADC % 10 + '0';
  uiADC /= 10;

  pBufferTx[1] = uiADC % 10 + '0';
  uiADC /= 10;

  pBufferTx[0] = uiADC % 10 + '0';
  uiADC /= 10;
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
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
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

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line)
{
}
#endif /* USE_FULL_ASSERT */