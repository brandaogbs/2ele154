#ifndef MEMS_LIS3DSH_H
#define MEMS_LIS3DSH_H

/* Private includes ----------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include <stdbool.h>
#include <string.h>

/* Private define ------------------------------------------------------------*/
#define LIS3DSH_CTRL_REG4_ADDR               0x20
#define LIS3DSH_CTRL_REG3_ADDR               0x23
#define LIS3DSH_CTRL_REG5_ADDR               0x24

#define LIS3DSH_OUT_X_L_ADDR                 0x28
#define LIS3DSH_OUT_Y_L_ADDR                 0x2A
#define LIS3DSH_OUT_Z_L_ADDR                 0x2C

#define LIS3DSH_DATARATE_25                  ((uint8_t)0x40)
#define LIS3DSH_FULLSCALE_4                  ((uint8_t)0x08)
#define LIS3DSH_FILTER_BW_50                 ((uint8_t)0xC0)
#define LIS3DSH_XYZ_ENABLE                   ((uint8_t)0x07)
#define LIS3DSH_SENSITIVITY_0_06G            0.06

/* Private typedef -----------------------------------------------------------*/
typedef struct
{
    int16_t x;
    int16_t y;
    int16_t z;
}LIS3DSH_DataRaw;

typedef struct
{
    float x;
    float y;
    float z;
}LIS3DSH_DataScaled;

/* Private function prototypes -----------------------------------------------*/
void LIS3DSH_WriteIO(uint8_t reg, uint8_t *dataW, uint8_t size);
void LIS3DSH_ReadIO(uint8_t reg, uint8_t *dataR, uint8_t size);

void LIS3DSH_Init();
LIS3DSH_DataRaw LIS3DSH_GetDataRaw(void);
LIS3DSH_DataScaled LIS3DSH_GetDataScaled(void);

#endif //MEMS_LIS3DSH_H
