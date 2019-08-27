/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __tim_H
#define __tim_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

extern TIM_HandleTypeDef htim4;

void MX_TIM4_Init(void);
                        
void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);
                    
#ifdef __cplusplus
}
#endif
#endif /*__ tim_H */
