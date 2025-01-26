#include "FreeRTOS.h"
#include "task.h"
#include "xgpio.h"
#include "xparameters.h"
#include "../include/motion_sensor_task.h"

static TaskHandle_t xMotionSensorTask;
XGpio motion_sensor_pin; 

static void prvMotionSensorTask(){
    
    u32 raw_reading;
    u8 result;
    const TickType_t x1second = pdMS_TO_TICKS( DELAY_1_SECOND );

    init_motion_sensor_gpio();

    for (;;){
        vTaskDelay( x1second );
        
        raw_reading = XGpio_DiscreteRead(&motion_sensor_pin, INPUTS_CH);
        result = (raw_reading >> MOTION_SNSR_MASK) & 0x01; //only one bit is needed
        xil_printf("Motion Sensor State is: %d\r\n", result);
    } 
}


int init_motion_sensor_gpio(){
    
    int pin_status = XGpio_Initialize(&motion_sensor_pin, GPIO_DEVICE_ID);
    
    if (pin_status != XST_SUCCESS) {
        xil_printf("Motion Sensor GPIO Initialization Failed\r\n");
        return XST_FAILURE;
    }    
    
    XGpio_SetDataDirection(&motion_sensor_pin, INPUTS_CH, 0xFFFFFFFF);  
    
    return XST_SUCCESS;
}
    

void createMotionSensorTask(UBaseType_t priority){
    xTaskCreate( 	prvMotionSensorTask, 					/* The function that implements the task. */
					( const char * ) "MotionSnsr", 		/* Text name for the task, provided to assist debugging only. */
					configMINIMAL_STACK_SIZE, 	/* The stack allocated to the task. */
					NULL, 						/* The task parameter is not used, so set to NULL. */
					priority,			/* The task runs at the idle priority. */
					&xMotionSensorTask );
}