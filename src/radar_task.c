#include "FreeRTOS.h"
#include "task.h"
#include "xgpio.h"
#include "xparameters.h"
#include "../include/radar_task.h"
#include <timers.h>

static TaskHandle_t xRadarTask;
static XGpio radar_trig_pin; 
static XGpio radar_echo_pin;

void prvRadarTask(){

    u32 raw_reading;
    u8 result;

    const TickType_t x1second = pdMS_TO_TICKS( DELAY_1_SECOND );
    const TickType_t x10us = pdMS_TO_TICKS( DELAY_10US );
    init_radar_gpio();

    TickType_t startTick, endTick;
    int pulse = 0;

    int distance;

    

    xil_printf("Reading...\r\n");

    XGpio_DiscreteWrite(&radar_trig_pin, OUTPUTS_CH, TRIG_WRITE_MASK);
    vTaskDelay( x10us );
    XGpio_DiscreteWrite(&radar_trig_pin, OUTPUTS_CH, 0x0);

    for (;;){
        //vTaskDelay( x1second );
                
        raw_reading = XGpio_DiscreteRead(&radar_echo_pin, INPUTS_CH);
        result = (raw_reading >> ECHO_READ_MASK) & 0x01; //only one bit is needed

        if (pulse == 0){
            if (result == 1){
                startTick = xTaskGetTickCount();
                pulse = 1;
                //xil_printf("Radar Sensor State is: %d\r\n", result);
            }
        }
        else{
            if (result == 0){
                endTick = xTaskGetTickCount();
            }
            xil_printf("%d ticks", endTick - startTick);
            distance = ((endTick - startTick) / 100) / 58;
            xil_printf("%d cm", distance);

            vTaskDelete(xRadarTask);
        }
        
        
        //need to resolve the issue of control loop not catching all the pulses
        

    }     

}


int init_radar_gpio(){
    
    int echo_pin_status = XGpio_Initialize(&radar_echo_pin, GPIO_DEVICE_ID);
    int trig_pin_status = XGpio_Initialize(&radar_trig_pin, GPIO_DEVICE_ID);

    if ((echo_pin_status != XST_SUCCESS) || (trig_pin_status != XST_SUCCESS)) {
        xil_printf("Radar Trigger Pin GPIO Initializations Failed\r\n");
        return XST_FAILURE;
    }    
       
    XGpio_SetDataDirection(&radar_echo_pin, INPUTS_CH, 0xFFFFFFF); 
    XGpio_SetDataDirection(&radar_trig_pin, OUTPUTS_CH, 0x0);  

    return XST_SUCCESS;
}


void createRadarTask(UBaseType_t priority){
    xTaskCreate( 	prvRadarTask, 					/* The function that implements the task. */
					( const char * ) "Radar", 		/* Text name for the task, provided to assist debugging only. */
					configMINIMAL_STACK_SIZE, 	/* The stack allocated to the task. */
					NULL, 						/* The task parameter is not used, so set to NULL. */
					priority,			/* The task runs at the idle priority. */
					&xRadarTask );
}