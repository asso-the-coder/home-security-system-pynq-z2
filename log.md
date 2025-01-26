# Project Logs

| Date        | Log |
| ----------- | ----------- |
| 7/1/2025    | Initalized repo and dependencies & ordered all the sensors                |
| 8/1/2025    | Created the block design in Vivado to ultimately set up FreeRTOS in Vitis |
| 9/1/2025    | Set up FreeRTOS in Vitis and ran some UART tasks for testing              |
| 11/1/2025   | Sensors came in today! Tested them electrically                           |
| 12/1/2025   | Running RTOS tasks for sensor readings and control loop building blocks   |
| 15/1/2025   | Verifying doppler effect sensor using Pynq-Z2 pins                        |
| 23/1/2025   | Full FreeRTOS implementation of doppler effect sensor reading             |
| 24/1/2025   | Cleaning up codebase with encapsulation                                   |
| 25/1/2025   | Queueing in between sensor tasks and adding RPi SPI + Eth                 |
Detailed Log Notes:

8/1/2025
- Connected the PL with the Zynq PS via the AXI, and added a GPIO IP Block to the PL also via AXI 
- Vivado neatly generates Verilog code from the block design, which gets synthesized and implemented
- Before generating the bitstream, I assigned the GPIO blocks to the PMOD connectors using XDC constraints, to read the sensor data
- Generated the bitstream file and exported the HW's configuration to Vitis (as an XSA file) for FreeRTOS to run on top of
- TODO: Will need to add SPI or CAN IP blocks and re-generate the XSA file to achieve low-latency comms with future parts in the project
           
![image](https://github.com/user-attachments/assets/be97235a-b5ff-4f5b-a520-f1850c1d4cea) 



9/1/2025
 - Adjusted the Block Design by adding a timer, which is required for FreeRTOS interrupt ticks to run properly
 - Used the new XSA to create the "platform component" in Vitis; this is the HW layer that the FreeRTOS app is built upon
 - Built the FreeRTOS app on this platform, and ran Xilinx's Hello World template, which uses RTOS tasks to communicate to my PC over USB (verified on PuTTy)
   
![image](https://github.com/user-attachments/assets/1b163854-8cd3-4c9e-bc59-1813740df4d0)
