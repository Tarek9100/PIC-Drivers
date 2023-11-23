
#include "Timer.h"

static void (*TIMER0_InterruptHandler)(void) = NULL;
static void (*TIMER1_InterruptHandler)(void) = NULL;
static void (*TIMER2_InterruptHandler)(void) = NULL;
static void (*TIMER3_InterruptHandler)(void) = NULL;

static uint16 timer0_preload = 0;
static uint16 timer1_preload = 0;
static uint8  timer2_preload = 0;
static uint16 timer3_preload = 0;

static STD_Return_t TIMER0_Prescalar_Config(const Timer0_t *timer_obj);
static STD_Return_t TIMER0_Mode_Config(const Timer0_t *timer_obj);
static STD_Return_t TIMER0_Register_Size_Config(const Timer0_t *timer_obj);

static STD_Return_t TIMER1_Prescalar_Config(const Timer1_t *timer_obj);
static STD_Return_t TIMER1_Mode_Config(const Timer1_t *timer_obj);

static STD_Return_t TIMER3_Mode_Config(const Timer3_t *timer_obj);
STD_Return_t TIMER0_Init(const Timer0_t *timer_obj){
    STD_Return_t ret = STD_NOK;
    if(timer_obj){
    TIMER0_DISABLE();    
    TIMER0_Prescalar_Config(timer_obj);
    TIMER0_Mode_Config(timer_obj);
    TIMER0_Register_Size_Config(timer_obj);
    TMR0H = (uint8)(timer_obj->timer0_preload_value>>8);
    TMR0L = (uint8)(timer_obj->timer0_preload_value);
    timer0_preload = timer_obj->timer0_preload_value;
    #if INTERNAL_INTERRUPT_TIMER0_ENABLE == FEATURE_ENABLE
        TIMER0_InterruptEnable();
        TIMER0_InterruptFlagClear();
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE == FEATURE_ENABLE
        if(INTERRUPT_LOW_PRIORITY == timer_obj->priority){
            TIMER0_LowPrioritySet();
            INTERRUPT_GlobalInterruptLowEnable(); 
        }
        else{
            TIMER0_HighPrioritySet();
            INTERRUPT_GlobalInterruptHighEnable(); 
        }
        #else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
        #endif
        TIMER0_InterruptHandler = timer_obj->TIMER0_InterruptHandler;        
    #endif

        TIMER0_ENABLE();
    }
    else{
     ret = STD_NULL_POINTER;   
    }
     return ret;     
}

STD_Return_t TIMER1_Init(const Timer1_t *timer_obj){
    STD_Return_t ret = STD_NOK;
    if(timer_obj){
    TIMER1_DISABLE();    
    TIMER1_Prescalar_Config(timer_obj);
    TIMER1_Mode_Config(timer_obj);
    TMR1H = (uint8)(timer_obj->timer1_preload_value>>8);
    TMR1L = (uint8)(timer_obj->timer1_preload_value);
    timer1_preload = timer_obj->timer1_preload_value;
    #if INTERNAL_INTERRUPT_TIMER1_ENABLE == FEATURE_ENABLE
        TIMER1_InterruptEnable();
        TIMER1_InterruptFlagClear();
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE == FEATURE_ENABLE
        if(INTERRUPT_LOW_PRIORITY == timer_obj->priority){
            TIMER1_LowPrioritySet();
            INTERRUPT_GlobalInterruptLowEnable(); 
        }
        else{
            TIMER1_HighPrioritySet();
            INTERRUPT_GlobalInterruptHighEnable(); 
        }
        #else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
        #endif
        TIMER1_InterruptHandler = timer_obj->TIMER1_InterruptHandler;        
    #endif

        TIMER1_ENABLE();
    }
    else{
     ret = STD_NULL_POINTER;   
    }
     return ret;     
}

STD_Return_t TIMER2_Init(const Timer2_t *timer_obj){
    STD_Return_t ret = STD_NOK;
    if(timer_obj){
    TIMER2_DISABLE();    
    TIMER2_PRESCALAR_SELECT(timer_obj->timer2_prescalar_value);
    TIMER2_POSTSCALAR_SELECT(timer_obj->timer2_postscalar_value);
    TMR2 = timer_obj->timer2_preload_value;
    timer2_preload = timer_obj->timer2_preload_value;
    #if INTERNAL_INTERRUPT_TIMER2_ENABLE == FEATURE_ENABLE
        TIMER2_InterruptEnable();
        TIMER2_InterruptFlagClear();
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE == FEATURE_ENABLE
        if(INTERRUPT_LOW_PRIORITY == timer_obj->priority){
            TIMER2_LowPrioritySet();
            INTERRUPT_GlobalInterruptLowEnable(); 
        }
        else{
            TIMER2_HighPrioritySet();
            INTERRUPT_GlobalInterruptHighEnable(); 
        }
        #else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
        #endif
        TIMER2_InterruptHandler = timer_obj->TIMER2_InterruptHandler;        
    #endif

        TIMER2_ENABLE();
    }
    else{
     ret = STD_NULL_POINTER;   
    }
     return ret;     
}

STD_Return_t TIMER3_Init(const Timer3_t *timer_obj){
    STD_Return_t ret = STD_NOK;
    if(timer_obj){
    TIMER3_DISABLE();    
    TIMER3_PRESCALAR_SELECT(timer_obj->timer3_prescalar_value);
    TIMER3_Mode_Config(timer_obj);
    TMR3H = (uint8)(timer_obj->timer3_preload_value>>8);
    TMR3L = (uint8)(timer_obj->timer3_preload_value);
    timer3_preload = timer_obj->timer3_preload_value;
    #if INTERNAL_INTERRUPT_TIMER1_ENABLE == FEATURE_ENABLE
        TIMER3_InterruptEnable();
        TIMER3_InterruptFlagClear();
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE == FEATURE_ENABLE
        if(INTERRUPT_LOW_PRIORITY == timer_obj->priority){
            TIMER3_LowPrioritySet();
            INTERRUPT_GlobalInterruptLowEnable(); 
        }
        else{
            TIMER3_HighPrioritySet();
            INTERRUPT_GlobalInterruptHighEnable(); 
        }
        #else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
        #endif
        TIMER3_InterruptHandler = timer_obj->TIMER3_InterruptHandler;        
    #endif

        TIMER3_ENABLE();
    }
    else{
     ret = STD_NULL_POINTER;   
    }
     return ret;     
}

STD_Return_t TIMER0_Deinit(const Timer0_t *timer_obj){
    STD_Return_t ret = STD_NOK;
    if(timer_obj){
     TIMER0_DISABLE();  
    #if INTERNAL_INTERRUPT_TIMER0_ENABLE == FEATURE_ENABLE
    TIMER0_InterruptDisable();
    #endif
    }
    else{
     ret = STD_NULL_POINTER;   
    }
     return ret;    
}

STD_Return_t TIMER1_Deinit(const Timer1_t *timer_obj){
    STD_Return_t ret = STD_NOK;
    if(timer_obj){
     TIMER1_DISABLE();  
    #if INTERNAL_INTERRUPT_TIMER1_ENABLE == FEATURE_ENABLE
    TIMER1_InterruptDisable();
    #endif
    }
    else{
     ret = STD_NULL_POINTER;   
    }
     return ret;    
}

STD_Return_t TIMER2_Deinit(const Timer2_t *timer_obj){
    STD_Return_t ret = STD_NOK;
    if(timer_obj){
     TIMER2_DISABLE();  
    #if INTERNAL_INTERRUPT_TIMER2_ENABLE == FEATURE_ENABLE
    TIMER2_InterruptDisable();
    #endif
    }
    else{
     ret = STD_NULL_POINTER;   
    }
     return ret;    
}

STD_Return_t TIMER3_Deinit(const Timer3_t *timer_obj){
    STD_Return_t ret = STD_NOK;
    if(timer_obj){
     TIMER3_DISABLE();  
    #if INTERNAL_INTERRUPT_TIMER3_ENABLE == FEATURE_ENABLE
    TIMER3_InterruptDisable();
    #endif
    }
    else{
     ret = STD_NULL_POINTER;   
    }
     return ret;    
}

STD_Return_t TIMER0_Write_Value(const Timer0_t *timer_obj, uint16 value){
    STD_Return_t ret = STD_NOK;
    if(timer_obj){
    TMR0H = (uint8)(value>>8);
    TMR0L = (uint8)(value);
    timer0_preload = value;   
    }
    else{
     ret = STD_NULL_POINTER;   
    }
     return ret;     
}

STD_Return_t TIMER1_Write_Value(const Timer1_t *timer_obj, uint16 value){
    STD_Return_t ret = STD_NOK;
    if(timer_obj){
    TMR1H = (uint8)(value>>8);
    TMR1L = (uint8)(value);
    timer1_preload = value;   
    }
    else{
     ret = STD_NULL_POINTER;   
    }
     return ret;     
}

STD_Return_t TIMER2_Write_Value(const Timer2_t *timer_obj, uint8 value){
    STD_Return_t ret = STD_NOK;
    if(timer_obj){

    TMR2 = value;
    timer2_preload = value;   
    }
    else{
     ret = STD_NULL_POINTER;   
    }
     return ret;     
}
STD_Return_t TIMER3_Write_Value(const Timer3_t *timer_obj, uint16 value){
    STD_Return_t ret = STD_NOK;
    if(timer_obj){
    TMR3H = (uint8)(value>>8);
    TMR3L = (uint8)(value);
    timer3_preload = value;   
    }
    else{
     ret = STD_NULL_POINTER;   
    }
     return ret;     
}

STD_Return_t TIMER0_Read_Value(const Timer0_t *timer_obj, uint16* value){
    STD_Return_t ret = STD_NOK;
    uint8 Local_u8_TMRL=0,Local_u8_TMRH=0;
    if((NULL == timer_obj) || (NULL == value)){
        ret = STD_NULL_POINTER;
    }
    else{
        Local_u8_TMRL = TMR0L;
        Local_u8_TMRH = TMR0H;
        *value =(uint16)((Local_u8_TMRH << 8) + Local_u8_TMRL);
    }
    return ret;    
}

STD_Return_t TIMER1_Read_Value(const Timer1_t *timer_obj, uint16* value){
    STD_Return_t ret = STD_NOK;
    uint8 Local_u8_TMRL=0,Local_u8_TMRH=0;    
    if((NULL == timer_obj) || (NULL == value)){
        ret = STD_NULL_POINTER;
    }
    else{
        Local_u8_TMRL = TMR1L;
        Local_u8_TMRH = TMR1H;
        *value =(uint16)((Local_u8_TMRH << 8) + Local_u8_TMRL);
    }
    return ret;    
}

STD_Return_t TIMER2_Read_Value(const Timer2_t *timer_obj, uint8* value){
    STD_Return_t ret = STD_NOK;  
    if((NULL == timer_obj) || (NULL == value)){
        ret = STD_NULL_POINTER;
    }
    else{
        *value = TMR2;
    }
    return ret;    
}
STD_Return_t TIMER3_Read_Value(const Timer3_t *timer_obj, uint16* value){
    STD_Return_t ret = STD_NOK;
    uint8 Local_u8_TMRL=0,Local_u8_TMRH=0;    
    if((NULL == timer_obj) || (NULL == value)){
        ret = STD_NULL_POINTER;
    }
    else{
        Local_u8_TMRL = TMR3L;
        Local_u8_TMRH = TMR3H;
        *value =(uint16)((Local_u8_TMRH << 8) + Local_u8_TMRL);
    }
    return ret;    
}


void TIMER0_ISR(void){
    TIMER0_InterruptFlagClear();
    TMR0H = (uint8)(timer0_preload>>8);
    TMR0L = (uint8)(timer0_preload);
    if(TIMER0_InterruptHandler)
    TIMER0_InterruptHandler();
}

void TIMER1_ISR(void){
    TIMER1_InterruptFlagClear();
    TMR1H = (uint8)(timer1_preload>>8);
    TMR1L = (uint8)(timer1_preload);
    if(TIMER1_InterruptHandler)
    TIMER1_InterruptHandler();
}
void TIMER2_ISR(void){
    TIMER2_InterruptFlagClear();
    TMR2 = timer2_preload;
    if(TIMER2_InterruptHandler)
    TIMER2_InterruptHandler();
}
void TIMER3_ISR(void){
    TIMER3_InterruptFlagClear();
    TMR3H = (uint8)(timer3_preload>>8);
    TMR3L = (uint8)(timer3_preload);
    if(TIMER3_InterruptHandler)
    TIMER3_InterruptHandler();
}

static STD_Return_t TIMER0_Prescalar_Config(const Timer0_t *timer_obj){
    STD_Return_t ret = STD_NOK;
    if(timer_obj){
        if(timer_obj->Prescalar_Value == TIMER0_NO_PRESCALAR){
          TIMER0_PRESCALAR_DISABLE();  
        }
        else{
          TIMER0_PRESCALAR_ENABLE();
          T0CONbits.T0PS = timer_obj->Prescalar_Value;
        }
    }
    else{
     ret = STD_NULL_POINTER;   
    }
     return ret;
}

static STD_Return_t TIMER0_Mode_Config(const Timer0_t *timer_obj){
    STD_Return_t ret = STD_NOK;
    if(timer_obj){
        if(timer_obj->timer0_mode == TIMER_TIMER_MODE){
          TIMER0_TIMER_MODE_ENABLE();
        }
        else if(timer_obj->timer0_mode == TIMER_COUNTER_MODE){
          TIMER0_COUNTER_MODE_ENABLE();
        if(TIMER_COUNTER_FALLING_EDGE_CFG == timer_obj->timer0_edge){
            TIMER0_FALLING_EDGE_DISABLE();
          }
          else{
            TIMER0_RISING_EDGE_ENABLE();    
          }
        }
        else{
            ret = STD_NOK;
        }
    }
    else{
     ret = STD_NULL_POINTER;   
    }
     return ret;
}

static STD_Return_t TIMER0_Register_Size_Config(const Timer0_t *timer_obj){
    STD_Return_t ret = STD_NOK;
    if(timer_obj){
        if(timer_obj->timer0_register_size == TIMER_8BIT_REGISTER_MODE){
          TIMER0_8BIT_REGISTER_MODE_ENABLE();  
        }
        else{
          TIMER0_16BIT_REGISTER_MODE_ENABLE();
        }
    }
    else{
     ret = STD_NULL_POINTER;   
    }
     return ret;
}

static STD_Return_t TIMER1_Prescalar_Config(const Timer1_t *timer_obj){
    STD_Return_t ret = STD_NOK;
    if(timer_obj){

          T1CONbits.T1CKPS = timer_obj->timer1_prescalar_value;
      
    }
    else{
     ret = STD_NULL_POINTER;   
    }
     return ret;
}

static STD_Return_t TIMER1_Mode_Config(const Timer1_t *timer_obj){
    STD_Return_t ret = STD_NOK;
    if(timer_obj){
        if(timer_obj->timer1_mode == TIMER_TIMER_MODE){
          TIMER1_TIMER_MODE_ENABLE();
        }
        else if(timer_obj->timer1_mode == TIMER_COUNTER_MODE){
          TIMER1_COUNTER_MODE_ENABLE();
          if(timer_obj->timer1_counter_mode == TIMER1_ASYNC_COUNTER_MODE)
          TIMER1_ASYNC_COUNTER_MODE_ENABLE();
          else 
          TIMER1_SYNC_COUNTER_MODE_ENABLE();
        }
        else{
            ret = STD_NOK;
        }
    }
    else{
     ret = STD_NULL_POINTER;   
    }
     return ret;
}
static STD_Return_t TIMER3_Mode_Config(const Timer3_t *timer_obj){
    STD_Return_t ret = STD_NOK;
    if(timer_obj){
        if(timer_obj->timer3_mode == TIMER_TIMER_MODE){
          TIMER3_TIMER_MODE_ENABLE();
        }
        else if(timer_obj->timer3_mode == TIMER_COUNTER_MODE){
          TIMER3_COUNTER_MODE_ENABLE();
          if(timer_obj->timer3_counter_mode == TIMER3_ASYNC_COUNTER_MODE)
          TIMER3_ASYNC_COUNTER_MODE_ENABLE();
          else 
          TIMER3_SYNC_COUNTER_MODE_ENABLE();
        }
        else{
            ret = STD_NOK;
        }
    }
    else{
     ret = STD_NULL_POINTER;   
    }
     return ret;
}

