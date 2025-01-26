#ifndef RADAR_TASK_H
#define RADAR_TASK_H

/* Prototypes */
int init_radar_gpio();
void createRadarTask();

/* Macros */
#define GPIO_DEVICE_ID XPAR_AXI_GPIO_0_BASEADDR
#define INPUTS_CH 1
#define OUTPUTS_CH 2
#define TRIG_WRITE_MASK 0x00   //PMOD B pin 1
#define ECHO_READ_MASK 0x02    //PMOD A pin 3
#define DELAY_1_SECOND 1000UL

#endif