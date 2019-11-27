#include <spi.h>
#include "lis3dsh.h"

#define _LIS3DHS_CS_ENBALE        HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_RESET);
#define _LIS3DHS_CS_DISABLE        HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_SET);

void LIS3DSH_WriteIO(uint8_t reg, uint8_t *dataW, uint8_t size)
{
    uint8_t spiReg = reg;
    _LIS3DHS_CS_ENBALE;

    HAL_SPI_Transmit(&hspi1, &spiReg, 1, 10);
    HAL_SPI_Transmit(&hspi1, dataW, size, 10);

    _LIS3DHS_CS_DISABLE;
}

void LIS3DSH_ReadIO(uint8_t reg, uint8_t *dataR, uint8_t size)
{
    uint8_t spiBuf[4];
    spiBuf[0] = reg | 0x80;

    _LIS3DHS_CS_ENBALE;

    HAL_SPI_Transmit(&hspi1, spiBuf, 1, 10);
    HAL_SPI_Receive(&hspi1, spiBuf, size, 10);

    _LIS3DHS_CS_DISABLE;

    for (uint8_t i = 0; i < (size & 0x3); i++)
    {
        dataR[i] = spiBuf[i];
    }
}

void LIS3DSH_Init()
{
    uint8_t spiData = 0;

    spiData |= (LIS3DSH_XYZ_ENABLE & 0x07);             //Enable Axes
    spiData |= (LIS3DSH_DATARATE_25 & 0xF0);            //Output Data Rate
    LIS3DSH_WriteIO(LIS3DSH_CTRL_REG4_ADDR, &spiData, 1);

    spiData = 0;
    spiData |= (LIS3DSH_FILTER_BW_50 & 0xC0);           //Anti-aliasing BW
    spiData |= (LIS3DSH_FULLSCALE_4 & 0x38);            //Full-Scale
    LIS3DSH_WriteIO(LIS3DSH_CTRL_REG5_ADDR, &spiData, 1);

    spiData = 0x88;                                     //Interrupt0
    LIS3DSH_WriteIO(LIS3DSH_CTRL_REG3_ADDR, &spiData, 1);

    _LIS3DHS_CS_DISABLE;
}

LIS3DSH_DataRaw LIS3DSH_GetDataRaw(void)
{
    uint8_t spiBuf[2];
    LIS3DSH_DataRaw tempDataRaw;

    LIS3DSH_ReadIO(LIS3DSH_OUT_X_L_ADDR, spiBuf, 2);
    tempDataRaw.x = ((spiBuf[1] << 8) + spiBuf[0]);

    LIS3DSH_ReadIO(LIS3DSH_OUT_Y_L_ADDR, spiBuf, 2);
    tempDataRaw.y = ((spiBuf[1] << 8) + spiBuf[0]);

    LIS3DSH_ReadIO(LIS3DSH_OUT_Z_L_ADDR, spiBuf, 2);
    tempDataRaw.z = ((spiBuf[1] << 8) + spiBuf[0]);

    return tempDataRaw;

}

LIS3DSH_DataScaled LIS3DSH_GetDataScaled(void)
{
    LIS3DSH_DataRaw tempRawData = LIS3DSH_GetDataRaw();;
    LIS3DSH_DataScaled tempScaledData;
    tempScaledData.x =
            tempRawData.x * LIS3DSH_SENSITIVITY_0_06G;

    tempScaledData.y =
            tempRawData.y * LIS3DSH_SENSITIVITY_0_06G;

    tempScaledData.z =
            tempRawData.z * LIS3DSH_SENSITIVITY_0_06G;

    return tempScaledData;
}