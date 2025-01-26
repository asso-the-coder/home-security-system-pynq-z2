/*****************************************************************************
 *	Project:  PYNQ Smart Home Security System                                *
 *	Author:   asso-the-coder                                                 *
 *                                                                           *
 *	Purpose:  Main processing system side code                               *
 *	                                                                         *
 *	Usage:                                                                   *
 *	                                                                         *
 *	Revision History:                                                        *
 *	                                                                         *
 *	Known Issues:                                                            *
 *	                                                                         *
 *****************************************************************************/

/* FreeRTOS includes */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "FreeRTOSConfig.h"

/* Xilinx includes (standard + platform-dependent) */
#include "xil_printf.h"
#include "xparameters.h"
#include "xgpio.h" //AXI GPIO API


/* Task function prototypes */
static void prvMotionSensorTask( void *pvParameters );
static void prvRadarSensorTask( void *pvParameters );
static void prvRxTask ( void *pvParameters );

/* Task definitions */
static TaskHandle_t xRadarSensorTask;
static TaskHandle_t xRxTask;
static QueueHandle_t xQueue = NULL;
static TimerHandle_t xTimer = NULL;


int main (int argc, char *argv[]){

    xil_printf("Home Security System Initalized.\r\n");

    createMotionSensorTask(tskIDLE_PRIORITY + 1);
    //createRadarTask(tskIDLE_PRIORITY);    
    
    vTaskStartScheduler();
    
    return XST_SUCCESS; 
}



/*** FUNCTIONS TBR
// initalizing priorities with references in case the vTaskChangePriority() API is ever called
    int* xMotionSensorTaskPriority = 0;
    xil_printf("%d", *xMotionSensorTaskPriority);

//const TickType_t x1second = pdMS_TO_TICKS( DELAY_1_SECOND );

//check HW fcn

***/



