#include "xparameters.h"
#include "xspips.h"
#include "xil_printf.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

extern QueueHandle_t xRadarToSPIQueue;

static XSpiPs SpiInstance;
static TaskHandle_t xSPITask;

void prvSPITask() {
    int Status;
    XSpiPs_Config *SpiConfig;

    // Init SPI
    SpiConfig = XSpiPs_LookupConfig(SPI_DEVICE_ID);
    if (SpiConfig == NULL) {
        xil_printf("SPI config lookup failed.\r\n");
        vTaskDelete(xSPITask);
    }

    Status = XSpiPs_CfgInitialize(&SpiInstance, SpiConfig, SpiConfig->BaseAddress);
    if (Status != XST_SUCCESS) {
        xil_printf("SPI init failed.\r\n");
        vTaskDelete(xSPITask);
    }

    XSpiPs_SetOptions(&SpiInstance, XSPIPS_MASTER_OPTION | XSPIPS_FORCE_SSELECT_OPTION);
    XSpiPs_SetClkPrescaler(&SpiInstance, XSPIPS_CLK_PRESCALE_64);
    XSpiPs_SetSlaveSelect(&SpiInstance, SPI_SS);

    u8 sendData[1];
    u8 recvData[1];

    for (;;) {
        // Block until data is received from Radar task
        if (xQueueReceive(xRadarToSPIQueue, sendData, portMAX_DELAY) == pdPASS) {
            recvData[0] = 0;

            // Send the byte over SPI
            Status = XSpiPs_Transfer(&SpiInstance, sendData, recvData, 1);

            if (Status == XST_SUCCESS) {
                xil_printf("SPI sent: 0x%02X, recv: 0x%02X\r\n", sendData[0], recvData[0]);
            } else {
                xil_printf("SPI transfer failed.\r\n");
            }
        }
    }
}


void createRadarTask(UBaseType_t priority){
    xTaskCreate( 	prvSPITask, 					/* The function that implements the task. */
					( const char * ) "SPI", 		/* Text name for the task, provided to assist debugging only. */
					configMINIMAL_STACK_SIZE, 	/* The stack allocated to the task. */
					NULL, 						/* The task parameter is not used, so set to NULL. */
					priority,			/* The task runs at the idle priority. */
					&xSPITask );
}