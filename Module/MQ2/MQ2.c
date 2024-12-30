#include "MQ2.h"
#include "adc.h"
#include "dma.h"
#include "memory.h"
#include "string.h"
#include "math.h"

#define RL 0.5  // 负载电阻，单位：kΩ
#define Vc 5.0  // 电源电压，单位：V
#define R0 6.64 // 在洁净空气中的传感器电阻，单位：kΩ

MQ2_Instance *MQ2_init(void)
{
    MQ2_Instance *mq2 = (MQ2_Instance *)malloc(sizeof(MQ2_Instance));
    memset(mq2, 0, sizeof(MQ2_Instance));

    // Initialize the MQ2 sensor
    HAL_ADC_Start_DMA(&hadc1, (uint32_t *)mq2->adc_buffer, 12);

    return mq2;
}

static float Calculate_PPM(float Vrl)
{
    float Rs    = ((Vc - Vrl) * RL) / Vrl;               // 计算 Rs
    float ratio = Rs / R0;                               // Rs/R0 比值
    float ppm   = pow((ratio / 11.5428), (1 / -0.6549)); // 根据公式计算 ppm
    return ppm;
}

void MQ2_update(MQ2_Instance *mq2)
{
    // Calculate the average value of the sensor
    uint32_t sum = 0;
    for (int i = 0; i < 12; i++) {
        sum += mq2->adc_buffer[i];
    }
    mq2->adc_value = sum / 12;
    mq2->voltage   = (float)mq2->adc_value / 4095.0 * Vc;
    mq2->ppm       = Calculate_PPM(mq2->voltage);
}
