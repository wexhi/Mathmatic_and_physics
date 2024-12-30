#include "robot.h"
#include "lcd.h"
#include "MQ2.h"
#include "bsp_dwt.h"

MQ2_Instance *mq2;
static volatile float ppm_log = 0;

void robot_init(void)
{
    // Initialize the robot
    DWT_Init(72);
    lcd_init();
    mq2 = MQ2_init();
}

void robot_task(void)
{
    // Update the MQ2 sensor
    MQ2_update(mq2);
    ppm_log = mq2->ppm;
    lcd_show_num(20, 10, (uint32_t)ppm_log, 5, 32, RED);
    lcd_show_string(140, 10, 200, 100, 32, "ppm", RED);
    drawCurve(ppm_log);
    DWT_Delay_ms(10);
}
