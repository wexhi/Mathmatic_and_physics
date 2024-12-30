#pragma once

#include "stdint.h"
#include "stdlib.h"

typedef struct
{
    uint16_t adc_buffer[12];
    uint16_t adc_value;
    volatile float voltage;
    volatile float ppm;
} MQ2_Instance;

MQ2_Instance *MQ2_init(void);
void MQ2_update(MQ2_Instance *mq2);