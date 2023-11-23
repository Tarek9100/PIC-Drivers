#include "USART.h"

static void (*USART_TX_InterruptHandler)(void) = NULL;
static void (*USART_RX_InterruptHandler)(void) = NULL;

uint8 temp_data;
static STD_Return_t USART_Baudrate_Calculate(const USART_t *usart_obj);
static STD_Return_t USART_ASYNC_TX_Init(const USART_t *usart_obj);
static STD_Return_t USART_ASYNC_RX_Init(const USART_t *usart_obj);

STD_Return_t USART_Init(const USART_t *usart_obj){
    STD_Return_t ret = STD_NOK;
    if(usart_obj){
        USART_DISABLE();
        ret = USART_Baudrate_Calculate(usart_obj);
        TRISCbits.TRISC7 = 1;
        TRISCbits.TRISC6 = 1;
    #if USART_MODE == USART_SYNCHRONOUS_MODE

        
    #elif  USART_MODE == USART_ASYNCHRONOUS_MODE   
            ret = USART_ASYNC_TX_Init(usart_obj);
            ret = USART_ASYNC_RX_Init(usart_obj);    
    #endif
        USART_ENABLE();        
    }
    else{
     ret = STD_NULL_POINTER;   
    }
     return ret;     
}
STD_Return_t USART_Deinit(const USART_t *usart_obj){
    STD_Return_t ret = STD_NOK;
    if(usart_obj){
        USART_DISABLE();
    }
    else{
     ret = STD_NULL_POINTER;   
    }
     return ret;     
}
STD_Return_t USART_WriteByte(uint8 data){
    STD_Return_t ret = STD_OK;
    while(!TXSTAbits.TRMT);
#if USART_TX_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE        
        USART_TX_InterruptEnable(); 
#endif        
        TXREG = data;
        return ret;     
}
STD_Return_t USART_WriteString(uint8 *data, uint16 str_length){
    STD_Return_t ret = STD_NOK;
    uint16 i =0;
    if(data){
       for(i=0;i<str_length;i++){
           USART_WriteByte(data[i]);
       } 
    }
    else{
     ret = STD_NULL_POINTER;   
    }
     return ret;     
}
STD_Return_t USART_ReadByte(uint8 *data){
    STD_Return_t ret = STD_NOK;
    if(data){
    if(PIR1bits.RCIF==1){
    *data = RCREG;
    } 
    }
    else{
        ret = STD_NULL_POINTER;         
    }
     return ret;     
}

STD_Return_t USART_ASYNC_RX_Restart(void){
    STD_Return_t ret = STD_OK;
    RCSTAbits.CREN = 0; /* Disables receiver */
    RCSTAbits.CREN = 1; /* Enables receiver */
    return ret;
}

static STD_Return_t USART_Baudrate_Calculate(const USART_t *usart_obj){
    STD_Return_t ret = STD_NOK;
    float BaudRate_Temp = 0;
    if(usart_obj){
#if BAUDRATE_CONFIG == USART_BAUDRATE_ASYNC_8BIT_LOWSPEED
        TXSTAbits.SYNC = USART_ASYNCHRONOUS_MODE;
        TXSTAbits.BRGH = USART_ASYNCHRONOUS_LOW_SPEED;
        BAUDCONbits.BRG16 = USART_8BIT_BAUDRATE_GEN;
        #if BAUDRATE_VALUE == USART_CUSTOM_BAUDRATE
        BaudRate_Temp = ((_XTAL_FREQ / (float)usart_obj->custom_baudrate)/ 64) - 1;
        #else
        BaudRate_Temp = ((_XTAL_FREQ / (float)BAUDRATE_VALUE)/ 64) - 1;
        #endif
#elif BAUDRATE_CONFIG == USART_BAUDRATE_ASYNC_8BIT_HIGHSPEED
        TXSTAbits.SYNC = USART_ASYNCHRONOUS_MODE;
        TXSTAbits.BRGH = USART_ASYNCHRONOUS_HIGH_SPEED;
        BAUDCONbits.BRG16 = USART_8BIT_BAUDRATE_GEN; 
        #if BAUDRATE_VALUE == USART_CUSTOM_BAUDRATE
        BaudRate_Temp = ((_XTAL_FREQ / (float)usart_obj->custom_baudrate)/ 16) - 1;
        #else
        BaudRate_Temp = ((_XTAL_FREQ / (float)BAUDRATE_VALUE)/ 16) - 1;
        #endif      
#elif BAUDRATE_CONFIG == USART_BAUDRATE_ASYNC_16BIT_LOWSPEED
        TXSTAbits.SYNC = USART_ASYNCHRONOUS_MODE;
        TXSTAbits.BRGH = USART_ASYNCHRONOUS_LOW_SPEED;
        BAUDCONbits.BRG16 = USART_16BIT_BAUDRATE_GEN;
        #if BAUDRATE_VALUE == USART_CUSTOM_BAUDRATE
        BaudRate_Temp = ((_XTAL_FREQ / (float)usart_obj->custom_baudrate)/ 16) - 1;
        #else
        BaudRate_Temp = ((_XTAL_FREQ / (float)BAUDRATE_VALUE)/ 16) - 1;
        #endif      
#elif BAUDRATE_CONFIG == USART_BAUDRATE_ASYNC_16BIT_HIGHSPEED
        TXSTAbits.SYNC = USART_ASYNCHRONOUS_MODE;
        TXSTAbits.BRGH = USART_ASYNCHRONOUS_HIGH_SPEED;
        BAUDCONbits.BRG16 = USART_16BIT_BAUDRATE_GEN;
        #if BAUDRATE_VALUE == USART_CUSTOM_BAUDRATE
        BaudRate_Temp = ((_XTAL_FREQ / (float)usart_obj->custom_baudrate)/ 4) - 1;
        #else
        BaudRate_Temp = ((_XTAL_FREQ / (float)BAUDRATE_VALUE)/ 4) - 1;
        #endif      
#elif BAUDRATE_CONFIG == USART_BAUDRATE_SYNC_8BIT
        TXSTAbits.SYNC = USART_SYNCHRONOUS_MODE;
        BAUDCONbits.BRG16 = USART_8BIT_BAUDRATE_GEN;
        #if BAUDRATE_VALUE == USART_CUSTOM_BAUDRATE
        BaudRate_Temp = ((_XTAL_FREQ / (float)usart_obj->custom_baudrate)/ 4) - 1;
        #else
        BaudRate_Temp = ((_XTAL_FREQ / (float)BAUDRATE_VALUE)/ 4) - 1;
        #endif   
#elif BAUDRATE_CONFIG == USART_BAUDRATE_SYNC_16BIT
        TXSTAbits.SYNC = USART_SYNCHRONOUS_MODE;
        BAUDCONbits.BRG16 = USART_16BIT_BAUDRATE_GEN;
        #if BAUDRATE_VALUE == USART_CUSTOM_BAUDRATE        
        BaudRate_Temp = ((_XTAL_FREQ / (float)usart_obj->custom_baudrate)/ 4) - 1;
        #else
        BaudRate_Temp = ((_XTAL_FREQ / (float)BAUDRATE_VALUE)/ 4) - 1;
        #endif  
#else  #error Unknown baudrate configuration 
            
#endif 
    SPBRG = (uint8)((uint32)BaudRate_Temp); 
    SPBRGH = (uint8)(((uint32)BaudRate_Temp >> 8));
    }
    else{
     ret = STD_NULL_POINTER;   
    }
     return ret;  
}

static STD_Return_t USART_ASYNC_TX_Init(const USART_t *usart_obj){
    STD_Return_t ret = STD_NOK;
    if(usart_obj){
        TXSTAbits.TXEN = usart_obj->usart_tx_cfg.USART_TX_Enable;
        PIE1bits.TXIE = usart_obj->usart_tx_cfg.USART_TX_Interrupt_Enable;
        TXSTAbits.TX9 = usart_obj->usart_tx_cfg.USART_TX_9bit_Enable;
        if(usart_obj->usart_tx_cfg.USART_TX_Interrupt_Enable == USART_ASYNCHRONOUS_INTERRUPT_TX_ENABLE){
        #if INTERNAL_INTERRUPT_USART_TX_ENABLE == FEATURE_ENABLE
        USART_TX_InterruptEnable();
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE == FEATURE_ENABLE
        if(INTERRUPT_LOW_PRIORITY == usart_obj->usart_tx_cfg.USART_TX_Interrupt_Priority){
            USART_TX_LowPrioritySet();
            INTERRUPT_GlobalInterruptLowEnable(); 
        }
        else{
            USART_TX_HighPrioritySet();
            INTERRUPT_GlobalInterruptHighEnable(); 
        }
        #else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
        #endif
        USART_TX_InterruptHandler = usart_obj->USART_TxDefaultInterruptHandler;
        #endif
        }
    }
    else{
     ret = STD_NULL_POINTER;   
    }
     return ret;     
}

static STD_Return_t USART_ASYNC_RX_Init(const USART_t *usart_obj){
    STD_Return_t ret = STD_NOK;
    if(usart_obj){
       RCSTAbits.CREN = usart_obj->usart_rx_cfg.USART_RX_Enable; 
       PIE1bits.RCIE = usart_obj->usart_rx_cfg.USART_RX_Interrupt_Enable;
       RCSTAbits.RX9 = usart_obj->usart_rx_cfg.USART_RX_9bit_Enable;
        if(usart_obj->usart_rx_cfg.USART_RX_Interrupt_Enable == USART_ASYNCHRONOUS_INTERRUPT_RX_ENABLE){
        #if INTERNAL_INTERRUPT_USART_RX_ENABLE == FEATURE_ENABLE
        USART_RX_InterruptEnable();
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE == FEATURE_ENABLE
        if(INTERRUPT_LOW_PRIORITY == usart_obj->usart_rx_cfg.USART_RX_Interrupt_Priority){
            USART_RX_LowPrioritySet();
            INTERRUPT_GlobalInterruptLowEnable(); 
        }
        else{
            USART_RX_HighPrioritySet();
            INTERRUPT_GlobalInterruptHighEnable(); 
        }
        #else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
        #endif
        USART_RX_InterruptHandler = usart_obj->USART_RxDefaultInterruptHandler;
        #endif       
    }
    }
    else{
     ret = STD_NULL_POINTER;   
    }
     return ret;     
}

void USART_TX_ISR(void){
    USART_TX_InterruptDisable();
    if(USART_TX_InterruptHandler)
    USART_TX_InterruptHandler();
}
void USART_RX_ISR(void){
    STD_Return_t ret = STD_OK;
    if(USART_RX_InterruptHandler)
    USART_RX_InterruptHandler();
    if(RCSTAbits.FERR == 1)
    temp_data = RCREG;
    if(RCSTAbits.OERR == 1)
    ret = USART_ASYNC_RX_Restart();    
}