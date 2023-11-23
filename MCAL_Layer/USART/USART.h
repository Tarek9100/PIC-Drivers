/* 
 * File:   USART.h
 * Author: ENG TAREK
 *
 */

#ifndef USART_H
#define	USART_H

/* Section : Includes */
#include "../GPIO/gpio.h"
#include "../Interrupt/internal_interrupt.h" 
#include "USART_cfg.h"

/* Section : Macro Declarations */  
#define USART_16BIT_BAUDRATE_GEN                      1
#define USART_8BIT_BAUDRATE_GEN                       0

#define USART_ASYNCHRONOUS_HIGH_SPEED                 1 
#define USART_ASYNCHRONOUS_LOW_SPEED                  0

#define USART_ASYNCHRONOUS_TX_ENABLE                  1
#define USART_ASYNCHRONOUS_TX_DISABLE                 0

#define USART_ASYNCHRONOUS_9BIT_TX_ENABLE             1
#define USART_ASYNCHRONOUS_9BIT_TX_DISABLE            0

#define USART_ASYNCHRONOUS_INTERRUPT_TX_ENABLE        1
#define USART_ASYNCHRONOUS_INTERRUPT_TX_DISABLE       0

#define USART_ASYNCHRONOUS_RX_ENABLE                  1
#define USART_ASYNCHRONOUS_RX_DISABLE                 0

#define USART_ASYNCHRONOUS_9BIT_RX_ENABLE             1
#define USART_ASYNCHRONOUS_9BIT_RX_DISABLE            0

#define USART_ASYNCHRONOUS_INTERRUPT_RX_ENABLE        1
#define USART_ASYNCHRONOUS_INTERRUPT_RX_DISABLE       0

#define USART_FRAMING_ERROR_DETECTED                  1
#define USART_FRAMING_ERROR_CLEARED                   0

#define USART_OVERRUN_ERROR_DETECTED                  1
#define USART_OVERRUN_ERROR_CLEARED                   0
/* Section : Macro Function Declarations */

#define USART_ENABLE()                                (RCSTAbits.SPEN = 1)
#define USART_DISABLE()                               (RCSTAbits.SPEN = 0)  


/* Section : Data Type Declarations */


typedef struct{
   uint8  Reserved : 4;
   uint8 USART_TX_Enable : 1;
   uint8 USART_TX_Interrupt_Enable : 1;
   uint8 USART_TX_9bit_Enable : 1;  
   uint8 USART_TX_Interrupt_Priority : 1;
}usart_tx_cfg_t;

typedef struct{
   uint8  Reserved : 4;
   uint8 USART_RX_Enable : 1;
   uint8 USART_RX_Interrupt_Enable : 1;
   uint8 USART_RX_9bit_Enable : 1; 
   uint8 USART_RX_Interrupt_Priority : 1;
}usart_rx_cfg_t;

typedef union{
    struct{
      uint8 Reserved : 5;
      uint8 USART_FERR : 1;
      uint8 USART_OERR : 1;
      uint8 USART_Error_Interrupt_Priority : 1;      
    }; 
    uint8 Status;
}USART_Error_Status_t;

typedef struct{
  uint32 custom_baudrate;
  usart_tx_cfg_t usart_tx_cfg;
  usart_rx_cfg_t usart_rx_cfg;
  USART_Error_Status_t Error_Status;
  void (*USART_TxDefaultInterruptHandler)(void);
  void (*USART_RxDefaultInterruptHandler)(void);
}USART_t;
/* Section : Function Declarations */
STD_Return_t USART_Init(const USART_t *usart_obj);
STD_Return_t USART_Deinit(const USART_t *usart_obj);
STD_Return_t USART_WriteByte(uint8 data);
STD_Return_t USART_WriteString(uint8 *data, uint16 str_length);
STD_Return_t USART_ReadByte(uint8 *data);
STD_Return_t USART_ASYNC_RX_Restart(void);
#endif	/* USART_H */

