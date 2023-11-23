/* 
 * File:   USART_cfg.h
 * Author: ENG TAREK
 *
 */

#ifndef USART_CFG_H

/* Section : Includes */
 

/* Section : Macro Declarations */

/*USART mode configuration*/
#define USART_SYNCHRONOUS_MODE                1 
#define USART_ASYNCHRONOUS_MODE               0              
/*Baud rate configuration*/
#define USART_BAUDRATE_ASYNC_8BIT_LOWSPEED    0
#define USART_BAUDRATE_ASYNC_8BIT_HIGHSPEED   1
#define USART_BAUDRATE_ASYNC_16BIT_LOWSPEED   2
#define USART_BAUDRATE_ASYNC_16BIT_HIGHSPEED  3
#define USART_BAUDRATE_SYNC_8BIT              4
#define USART_BAUDRATE_SYNC_16BIT             5
/*Baud rate value*/
#define USART_BAUDRATE_300                    300
#define USART_BAUDRATE_1200                   1200
#define USART_BAUDRATE_2400                   2400
#define USART_BAUDRATE_9600                   9600
#define USART_BAUDRATE_19200                  19200
#define USART_BAUDRATE_57600                  57600
#define USART_BAUDRATE_115200                 115200
#define USART_CUSTOM_BAUDRATE                   0
/********************************************************/

/*Options: 1-USART_SYNCHRONOUS_MODE
 *         2-USART_ASYNCHRONOUS_MODE
 */  
#define USART_MODE          USART_ASYNCHRONOUS_MODE  

/*Options: 1-USART_BAUDRATE_ASYNC_8BIT_LOWSPEED
 *         2-USART_BAUDRATE_ASYNC_8BIT_HIGHSPEED
 *         3-USART_BAUDRATE_ASYNC_16BIT_LOWSPEED
 *         4-USART_BAUDRATE_ASYNC_16BIT_HIGHSPEED
 *         5-USART_BAUDRATE_SYNC_8BIT
 *         6-USART_BAUDRATE_SYNC_16BIT
 */
#define BAUDRATE_CONFIG      USART_BAUDRATE_ASYNC_8BIT_LOWSPEED      

/*Options: 1-USART_BAUDRATE_300
 *         2-USART_BAUDRATE_1200
 *         3-USART_BAUDRATE_2400
 *         4-USART_BAUDRATE_9600
 *         5-USART_BAUDRATE_19200
 *         6-USART_BAUDRATE_57600
 *         7-USART_BAUDRATE_115200
 *         8-USART_CUSTOM_BAUDRATE
 */

#define BAUDRATE_VALUE      USART_BAUDRATE_9600 
/********************************************************/
/* Section : Macro Function Declarations */




/* Section : Data Type Declarations */


/* Section : Function Declarations */

#endif	/* USART_CFG_H */

