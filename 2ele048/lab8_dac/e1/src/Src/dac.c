/* Includes ------------------------------------------------------------------*/
#include "dac.h"

DAC_HandleTypeDef hdac;

/* DAC init function */
void MX_DAC_Init(void)
{
  DAC_ChannelConfTypeDef sConfig = {0};

  hdac.Instance = DAC;
  if (HAL_DAC_Init(&hdac) != HAL_OK)
  {
    Error_Handler();
  }

  sConfig.DAC_Trigger = DAC_TRIGGER_NONE;
  sConfig.DAC_OutputBuffer = DAC_OUTPUTBUFFER_ENABLE;

  if (HAL_DAC_ConfigChannel(&hdac, &sConfig, DAC_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
}

void HAL_DAC_MspInit(DAC_HandleTypeDef *dacHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if (dacHandle->Instance == DAC)
  {
    __HAL_RCC_DAC_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_InitStruct.Pin = GPIO_PIN_4;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
  }
}

void HAL_DAC_MspDeInit(DAC_HandleTypeDef *dacHandle)
{

  if (dacHandle->Instance == DAC)
  {
    __HAL_RCC_DAC_CLK_DISABLE();

    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_4);
  }
}