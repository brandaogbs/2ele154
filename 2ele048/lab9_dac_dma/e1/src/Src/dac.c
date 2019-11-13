/* Includes ------------------------------------------------------------------*/
#include "dac.h"

DAC_HandleTypeDef hdac;
DMA_HandleTypeDef hdma_dac1;

void MX_DAC_Init(void)
{
  DAC_ChannelConfTypeDef sConfig = {0};

  hdac.Instance = DAC;
  if (HAL_DAC_Init(&hdac) != HAL_OK)
  {
    Error_Handler();
  }
  sConfig.DAC_Trigger = DAC_TRIGGER_T6_TRGO;
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

    hdma_dac1.Instance = DMA1_Stream5;
    hdma_dac1.Init.Channel = DMA_CHANNEL_7;
    hdma_dac1.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_dac1.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_dac1.Init.MemInc = DMA_MINC_ENABLE;
    hdma_dac1.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
    hdma_dac1.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
    hdma_dac1.Init.Mode = DMA_CIRCULAR;
    hdma_dac1.Init.Priority = DMA_PRIORITY_LOW;
    hdma_dac1.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&hdma_dac1) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(dacHandle, DMA_Handle1, hdma_dac1);
  }
}

void HAL_DAC_MspDeInit(DAC_HandleTypeDef *dacHandle)
{

  if (dacHandle->Instance == DAC)
  {
    __HAL_RCC_DAC_CLK_DISABLE();

    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_4);

    HAL_DMA_DeInit(dacHandle->DMA_Handle1);
  }
}