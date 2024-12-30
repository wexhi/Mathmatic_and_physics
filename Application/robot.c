#include "robot.h"
#include "MQ2.h"

MQ2_Instance *mq2;
static volatile float ppm_log = 0;

void robot_init(void)
{
    // Initialize the robot
    mq2 = MQ2_init();
}

void robot_task(void)
{
    // Update the MQ2 sensor
    MQ2_update(mq2);
    ppm_log = mq2->ppm;
}