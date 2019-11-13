/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dac.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

const uint16_t sine_12b[256] = {2048, 2098, 2148, 2199, 2249, 2299, 2348, 2398, 2447, 2497, 2546, 2594, 2642, 2690, 2738, 2785, 2832, 2878, 2923, 2969, 3013, 3057, 3101, 3143, 3186, 3227, 3268, 3308, 3347, 3385, 3423, 3460, 3496, 3531, 3565, 3598, 3631, 3662, 3693, 3722, 3750, 3778, 3804, 3830, 3854, 3877, 3899, 3920, 3940, 3958, 3976, 3992, 4007, 4021, 4034, 4046, 4056, 4065, 4073, 4080, 4086, 4090, 4093, 4095, 4095, 4095, 4093, 4090, 4086, 4080, 4073, 4065, 4056, 4046, 4034, 4021, 4007, 3992, 3976, 3958, 3940, 3920, 3899, 3877, 3854, 3830, 3804, 3778, 3750, 3722, 3693, 3662, 3631, 3598, 3565, 3531, 3496, 3460, 3423, 3385, 3347, 3308, 3268, 3227, 3186, 3143, 3101, 3057, 3013, 2969, 2923, 2878, 2832, 2785, 2738, 2690, 2642, 2594, 2546, 2497, 2447, 2398, 2348, 2299, 2249, 2199, 2148, 2098, 2048, 1998, 1948, 1897, 1847, 1797, 1748, 1698, 1649, 1599, 1550, 1502, 1454, 1406, 1358, 1311, 1264, 1218, 1173, 1127, 1083, 1039, 995, 953, 910, 869, 828, 788, 749, 711, 673, 636, 600, 565, 531, 498, 465, 434, 403, 374, 346, 318, 292, 266, 242, 219, 197, 176, 156, 138, 120, 104, 89, 75, 62, 50, 40, 31, 23, 16, 10, 6, 3, 1, 0, 1, 3, 6, 10, 16, 23, 31, 40, 50, 62, 75, 89, 104, 120, 138, 156, 176, 197, 219, 242, 266, 292, 318, 346, 374, 403, 434, 465, 498, 531, 565, 600, 636, 673, 711, 749, 788, 828, 869, 910, 953, 995, 1039, 1083, 1127, 1173, 1218, 1264, 1311, 1358, 406, 1454, 1502, 1550, 1599, 1649, 1698, 1748, 1797, 1847, 1897, 1948, 1998};

const uint16_t sinc_12b[256] = {583, 606, 631, 656, 682, 709, 737, 765, 793, 821, 850, 878, 905, 932,
                                958, 984, 1008, 1031, 1053, 1073, 1091, 1108, 1122, 1135, 1145, 1153, 1158, 1161,
                                1162, 1160, 1155, 1148, 1138, 1125, 1109, 1091, 1071, 1048, 1022, 994, 964, 932,
                                897, 861, 823, 784, 744, 702, 659, 616, 573, 529, 485, 442, 399, 357,
                                316, 276, 238, 202, 168, 137, 108, 82, 59, 39, 24, 11, 3, 0,
                                0, 4, 13, 27, 46, 70, 98, 132, 171, 214, 263, 316, 375, 438,
                                506, 579, 656, 737, 822, 911, 1004, 1100, 1200, 1302, 1407, 1514, 1623, 1733,
                                1845, 1958, 2072, 2185, 2299, 2412, 2524, 2635, 2744, 2851, 2956, 3058, 3157, 3253,
                                3345, 3433, 3516, 3595, 3669, 3738, 3801, 3859, 3911, 3956, 3996, 4029, 4056, 4076,
                                4089, 4095, 4095, 4089, 4076, 4056, 4029, 3996, 3956, 3911, 3859, 3801, 3738, 3669,
                                3595, 3516, 3433, 3345, 3253, 3157, 3058, 2956, 2851, 2744, 2635, 2524, 2412, 2299,
                                2185, 2072, 1958, 1845, 1733, 1623, 1514, 1407, 1302, 1200, 1100, 1004, 911, 822,
                                737, 656, 579, 506, 438, 375, 316, 263, 214, 171, 132, 98, 70, 46,
                                27, 13, 4, 0, 0, 3, 11, 24, 39, 59, 82, 108, 137, 168,
                                202, 238, 276, 316, 357, 399, 442, 485, 529, 573, 616, 659, 702, 744,
                                784, 823, 861, 897, 932, 964, 994, 1022, 1048, 1071, 1091, 1109, 1125, 1138,
                                1148, 1155, 1160, 1162, 1161, 1158, 1153, 1145, 1135, 1122, 1108, 1091, 1073, 1053,
                                1031, 1008, 984, 958, 932, 905, 878, 850, 821, 793, 765, 737, 709, 682,
                                656, 631, 606, 583};

int main(void)
{

  HAL_Init();

  SystemClock_Config();

  MX_GPIO_Init();
  MX_DMA_Init();
  MX_USART3_UART_Init();
  MX_DAC_Init();
  MX_TIM6_Init();

  HAL_TIM_Base_Start(&htim6);
  HAL_DAC_Start(&hdac, DAC_CHANNEL_1);
  HAL_DAC_Start_DMA(&hdac, DAC_CHANNEL_1, (uint32_t *)sinc_12b, 256, DAC_ALIGN_12B_R);

  while (1)
  {
  }
}

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

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
