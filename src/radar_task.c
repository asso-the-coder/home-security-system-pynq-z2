#include "FreeRTOS.h"
#include "task.h"
#include "xgpio.h"
#include "xparameters.h"
#include "../include/radar_task.h"

static TaskHandle_t xRadarTask;
static XGpio radar_trig_pin; 
static XGpio radar_echo_pin;

void prvRadarTask(){

    u32 raw_reading;
    u8 result;
    u32 output_value = ~6; 
    

    const TickType_t x1second = pdMS_TO_TICKS( DELAY_1_SECOND );

    //XGpio_DiscreteWrite(&radar_trig_pin, OUTPUTS_CH, TRIG_WRITE_MASK);


    init_radar_gpio();

    XGpio_DiscreteWrite(&radar_echo_pin, INPUTS_CH, 0x1F);

    xil_printf("Reading...");
    for (;;){
        vTaskDelay( x1second );
        
        //raw_reading = XGpio_DiscreteRead(&radar_echo_pin, INPUTS_CH);
        //result = (raw_reading >> 0x00) & 0x01; //only one bit is needed
        
        //xil_printf("Radar Sensor State is: %d\r\n", result);
        
        
    }     

}


int init_radar_gpio(){
    
    int echo_pin_status = XGpio_Initialize(&radar_echo_pin, GPIO_DEVICE_ID);
    int trig_pin_status = XGpio_Initialize(&radar_trig_pin, GPIO_DEVICE_ID);

    if ((echo_pin_status != XST_SUCCESS) || (trig_pin_status != XST_SUCCESS)) {
        xil_printf("Radar Trigger Pin GPIO Initializations Failed\r\n");
        return XST_FAILURE;
    }    
       
    XGpio_SetDataDirection(&radar_echo_pin, INPUTS_CH, 0x0); 
    //XGpio_SetDataDirection(&radar_trig_pin, OUTPUTS_CH, 0xFFFFFFFF);  

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