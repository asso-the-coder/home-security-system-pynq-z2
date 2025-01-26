#ifndef MOTION_SENSOR_TASK_H
#define MOTION_SENSOR_TASK_H


/* Prototypes */
int init_motion_sensor_gpio();
void createMotionSensorTask();

/* Macros */
#define GPIO_DEVICE_ID XPAR_AXI_GPIO_0_BASEADDR
#define INPUTS_CH 1
#define MOTION_SNSR_MASK 0x00   //PMOD A pin 1
#define DELAY_1_SECOND 1000UL

#endif