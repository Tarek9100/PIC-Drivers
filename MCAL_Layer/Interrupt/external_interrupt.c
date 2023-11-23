/* 
 * File:   external_interrupt.c
 * Author: Tarek Wael
 */

#include "external_interrupt.h"

static void (*INT0_InterruptHandler)(void) = NULL;
static void (*INT1_InterruptHandler)(void) = NULL;
static void (*INT2_InterruptHandler)(void) = NULL;

static void (*RB4_InterruptHandler_HIGH)(void) = NULL;
static void (*RB4_InterruptHandler_LOW)(void) = NULL;
static void (*RB5_InterruptHandler_HIGH)(void) = NULL;
static void (*RB5_InterruptHandler_LOW)(void) = NULL;
static void (*RB6_InterruptHandler_HIGH)(void) = NULL;
static void (*RB6_InterruptHandler_LOW)(void) = NULL;
static void (*RB7_InterruptHandler_HIGH)(void) = NULL;
static void (*RB7_InterruptHandler_LOW)(void) = NULL;

static STD_Return_t Interrupt_INTx_Enable(const interrupt_INTx_t *int_obj);
static STD_Return_t Interrupt_INTx_Disable(const interrupt_INTx_t *int_obj);
static STD_Return_t Interrupt_INTx_Priority_Config(const interrupt_INTx_t *int_obj);
static STD_Return_t Interrupt_INTx_Edge_Config(const interrupt_INTx_t *int_obj);
static STD_Return_t Interrupt_INTx_Pin_Init(const interrupt_INTx_t *int_obj);
static STD_Return_t Interrupt_INTx_Clear_Flag(const interrupt_INTx_t *int_obj);

static STD_Return_t Interrupt_INTx_SetInterruptHandler(const interrupt_INTx_t *int_obj);
static STD_Return_t INT0_SetInterruptHandler(void (*InterruptHandler)(void));
static STD_Return_t INT1_SetInterruptHandler(void (*InterruptHandler)(void));
static STD_Return_t INT2_SetInterruptHandler(void (*InterruptHandler)(void));

static STD_Return_t Interrupt_RBx_SetInterruptHandler(const interrupt_RBx_t *int_obj);
static STD_Return_t Interrupt_RBx_Enable(const interrupt_RBx_t *int_obj);
static STD_Return_t Interrupt_RBx_Disable(const interrupt_RBx_t *int_obj);
static STD_Return_t Interrupt_RBx_Priority_Config(const interrupt_RBx_t *int_obj);
static STD_Return_t Interrupt_RBx_Pin_Init(const interrupt_RBx_t *int_obj);
/**
 * @brief : Initializes the assigned external interrupt pin
 * @param int_obj : pointer to the external interrupt configuration
 * @return Status of the function 
 *        STD_OK : The function done successfully.
 *        STD_NOK : The function had an issue while performing this action.
 *        STD_NULL_POINTER : NULL parameter was passed to the function.
 */
STD_Return_t Interrupt_INTx_Init(const interrupt_INTx_t *int_obj){
    STD_Return_t ret = STD_NOK;
    if(int_obj){
        ret = STD_OK;
        /*Disable the external interrupt*/
        ret = Interrupt_INTx_Disable(int_obj);
        /*Clear Interrupt flag*/
        ret = Interrupt_INTx_Clear_Flag(int_obj);
        /*Configure external interrupt edge */
        ret = Interrupt_INTx_Edge_Config(int_obj);
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE == FEATURE_ENABLE
        /*Configure external interrupt priority*/
        ret = Interrupt_INTx_Priority_Config(int_obj);
        #endif
        /*Configure external interrupt I/O pins*/
        ret = Interrupt_INTx_Pin_Init(int_obj);
        /*Configure Default Interrupt CallBack*/
        ret = Interrupt_INTx_SetInterruptHandler(int_obj);
        /*Enable the external interrupt*/
        ret = Interrupt_INTx_Enable(int_obj);
    }
    else{
        ret = STD_NULL_POINTER;
    }
    return ret;
}

/**
 * @brief : De-initializes the assigned external interrupt pin
 * @param int_obj : pointer to the external interrupt configuration
 * @return Status of the function 
 *        STD_OK : The function done successfully.
 *        STD_NOK : The function had an issue while performing this action.
 *        STD_NULL_POINTER : NULL parameter was passed to the function.
 */
STD_Return_t Interrupt_INTx_Deinit(const interrupt_INTx_t *int_obj){
    STD_Return_t ret = STD_NOK;
    if(int_obj){
        ret = STD_OK;
        ret = Interrupt_INTx_Disable(int_obj);
    }
    else{
        ret = STD_NULL_POINTER;
    }
    return ret;  
}

/**
 * @brief : Initializes the assigned RB interrupt pin
 * @param int_obj : pointer to the external interrupt configuration
 * @return Status of the function 
 *        STD_OK : The function done successfully.
 *        STD_NOK : The function had an issue while performing this action.
 *        STD_NULL_POINTER : NULL parameter was passed to the function.
 */
STD_Return_t Interrupt_RBx_Init(const interrupt_RBx_t *int_obj){
    STD_Return_t ret = STD_NOK;
    if(int_obj){
        ret = STD_OK;
        /*Disable the external interrupt*/
        EXT_RBx_InterruptDisable();
        /*Clear Interrupt flag*/
        EXT_RBx_InterruptFlagClear(); 
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE == FEATURE_ENABLE
        /*Configure external interrupt priority*/
        ret = Interrupt_RBx_Priority_Config(int_obj);
        #endif
        /*Configure external interrupt I/O pins*/
        ret = Interrupt_RBx_Pin_Init(int_obj);
        /*Configure Default Interrupt CallBack*/
        ret = Interrupt_RBx_SetInterruptHandler(int_obj);
        /*Enable the external interrupt*/
        ret = Interrupt_RBx_Enable(int_obj);
    }
    else{
        ret = STD_NULL_POINTER;
    }
    return ret;    
}

/**
 * @brief : De-initializes the assigned RB interrupt pin
 * @param int_obj : pointer to the external interrupt configuration
 * @return Status of the function 
 *        STD_OK : The function done successfully.
 *        STD_NOK : The function had an issue while performing this action.
 *        STD_NULL_POINTER : NULL parameter was passed to the function.
 */
STD_Return_t Interrupt_RBx_Deinit(const interrupt_RBx_t *int_obj){
    STD_Return_t ret = STD_NOK;
    if(int_obj){
        ret = STD_OK;
        EXT_RBx_InterruptDisable();
    }
    else{
        ret = STD_NULL_POINTER;
    }
    return ret;    
}

static STD_Return_t Interrupt_INTx_Enable(const interrupt_INTx_t *int_obj){
    STD_Return_t ret = STD_NOK;
    if(int_obj){
        
        ret = STD_OK;
        switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT0 :
            #if INTERRUPT_PRIORITY_LEVELS_ENABLE == FEATURE_ENABLE
          
                INTERRUPT_GlobalInterruptHighEnable();
            #else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
            #endif    
            EXT_INT0_InterruptEnable();break;
            case INTERRUPT_EXTERNAL_INT1 :
            #if INTERRUPT_PRIORITY_LEVELS_ENABLE == FEATURE_ENABLE
                INTERRUPT_PriorityLevelsEnable();
                if(INTERRUPT_LOW_PRIORITY == int_obj->priority){ 
                    INTERRUPT_GlobalInterruptLowEnable();
                }
                else if(INTERRUPT_HIGH_PRIORITY == int_obj->priority){ 
                    INTERRUPT_GlobalInterruptHighEnable();
                }
            #else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
            #endif    
            EXT_INT1_InterruptEnable();break;
            case INTERRUPT_EXTERNAL_INT2 :
            #if INTERRUPT_PRIORITY_LEVELS_ENABLE == FEATURE_ENABLE
                INTERRUPT_PriorityLevelsEnable();
                if(INTERRUPT_LOW_PRIORITY == int_obj->priority){ 
                    INTERRUPT_GlobalInterruptLowEnable();
                }
                else if(INTERRUPT_HIGH_PRIORITY == int_obj->priority){ 
                    INTERRUPT_GlobalInterruptHighEnable();
                }
            #else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
            #endif    
            EXT_INT2_InterruptEnable();break;
            default: ret = STD_NOK;break;
        }
    }
    else{
        ret = STD_NULL_POINTER;
    }
    return ret;    
}

static STD_Return_t Interrupt_INTx_Disable(const interrupt_INTx_t *int_obj){
    STD_Return_t ret = STD_NOK;
    if(int_obj){
        ret = STD_OK;
        switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT0 :  EXT_INT0_InterruptDisable(); break;
            case INTERRUPT_EXTERNAL_INT1 :  EXT_INT1_InterruptDisable(); break;
            case INTERRUPT_EXTERNAL_INT2 :  EXT_INT2_InterruptDisable(); break;
            default: ret = STD_NOK;break;
        }
    }
    else{
        ret = STD_NULL_POINTER;
    }
    return ret;   
}

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == FEATURE_ENABLE
static STD_Return_t Interrupt_INTx_Priority_Config(const interrupt_INTx_t *int_obj){
    STD_Return_t ret = STD_NOK;
    if(int_obj){
        ret = STD_OK;
        switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT0 :break;
            case INTERRUPT_EXTERNAL_INT1 : (INTCON3bits.INT1IP = int_obj->priority);break;
            case INTERRUPT_EXTERNAL_INT2 : (INTCON3bits.INT2IP = int_obj->priority);break;
            default: ret = STD_NOK;break;
        }        
    }
    else{
        ret = STD_NULL_POINTER;
    }
    return ret;    
}
#endif
static STD_Return_t Interrupt_INTx_Edge_Config(const interrupt_INTx_t *int_obj){
    STD_Return_t ret = STD_NOK;
    if(int_obj){
        ret = STD_OK;
        switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT0 : (INTCON2bits.INTEDG0 = int_obj->edge);break;
            case INTERRUPT_EXTERNAL_INT1 : (INTCON2bits.INTEDG1 = int_obj->edge);break;
            case INTERRUPT_EXTERNAL_INT2 : (INTCON2bits.INTEDG2 = int_obj->edge);break;
            default: ret = STD_NOK;break;
        }        
    }
    else{
        ret = STD_NULL_POINTER;
    }
    return ret;    
}

static STD_Return_t Interrupt_INTx_Pin_Init(const interrupt_INTx_t *int_obj){
    STD_Return_t ret = STD_NOK;
    if(int_obj){
        ret = STD_OK;
        ret = gpio_pin_initialize(&(int_obj->pin));
    }
    else{
        ret = STD_NULL_POINTER;
    }
    return ret;    
}
static STD_Return_t Interrupt_INTx_Clear_Flag(const interrupt_INTx_t *int_obj){
    STD_Return_t ret = STD_NOK;
    if(int_obj){
        ret = STD_OK;
       switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT0 : EXT_INT0_InterruptFlagClear();break;
            case INTERRUPT_EXTERNAL_INT1 : EXT_INT1_InterruptFlagClear();break;
            case INTERRUPT_EXTERNAL_INT2 : EXT_INT2_InterruptFlagClear();break;
            default: ret = STD_NOK;break;
        }
       
    }
    else{
        ret = STD_NULL_POINTER;
    }
    return ret;      
}


static STD_Return_t INT0_SetInterruptHandler(void (*InterruptHandler)(void)){
    STD_Return_t ret = STD_NOK;
    if(InterruptHandler){
        ret = STD_OK;
        INT0_InterruptHandler = InterruptHandler;
       
       
    }
    else{
        ret = STD_NULL_POINTER;
    }
    return ret;      
}
static STD_Return_t INT1_SetInterruptHandler(void (*InterruptHandler)(void)){
    STD_Return_t ret = STD_NOK;
    if(InterruptHandler){
        ret = STD_OK;
        INT1_InterruptHandler = InterruptHandler;
       
       
    }
    else{
        ret = STD_NULL_POINTER;
    }
    return ret; 
}
static STD_Return_t INT2_SetInterruptHandler(void (*InterruptHandler)(void)){
    STD_Return_t ret = STD_NOK;
    if(InterruptHandler){
        ret = STD_OK;
        INT2_InterruptHandler = InterruptHandler;
       
       
    }
    else{
        ret = STD_NULL_POINTER;
    }
    return ret;     
}
static STD_Return_t Interrupt_INTx_SetInterruptHandler(const interrupt_INTx_t *int_obj){
        STD_Return_t ret = STD_NOK;
    if(int_obj){
        ret = STD_OK;
       switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT0 : INT0_SetInterruptHandler(int_obj->EXT_InterruptHandler);break;
            case INTERRUPT_EXTERNAL_INT1 : INT1_SetInterruptHandler(int_obj->EXT_InterruptHandler);break;
            case INTERRUPT_EXTERNAL_INT2 : INT2_SetInterruptHandler(int_obj->EXT_InterruptHandler);break;
            default: ret = STD_NOK;break;
        }
       
    }
    else{
        ret = STD_NULL_POINTER;
    }
    return ret;      
}
static STD_Return_t Interrupt_RBx_Enable(const interrupt_RBx_t *int_obj){
    STD_Return_t ret = STD_NOK;
    if(int_obj){
        
        ret = STD_OK;

            #if INTERRUPT_PRIORITY_LEVELS_ENABLE == FEATURE_ENABLE
                INTERRUPT_PriorityLevelsEnable();
                if(INTERRUPT_LOW_PRIORITY == int_obj->priority){ 
                    INTERRUPT_GlobalInterruptLowEnable();
                }
                else if(INTERRUPT_HIGH_PRIORITY == int_obj->priority){ 
                    INTERRUPT_GlobalInterruptHighEnable();
                }
            #else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
            #endif    
            EXT_RBx_InterruptEnable();
    }
    else{
        ret = STD_NULL_POINTER;
    }
    return ret;    
}
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == FEATURE_ENABLE
static STD_Return_t Interrupt_RBx_Priority_Config(const interrupt_RBx_t *int_obj){
    STD_Return_t ret = STD_NOK;
    if(int_obj){
        ret = STD_OK;
        (INTCON2bits.RBIP = int_obj->priority);
    }        
 
    else{
        ret = STD_NULL_POINTER;
    }
    return ret;    
}
#endif

static STD_Return_t Interrupt_RBx_Pin_Init(const interrupt_RBx_t *int_obj){
    STD_Return_t ret = STD_NOK;
    if(int_obj){
        ret = STD_OK;
        ret = gpio_pin_initialize(&(int_obj->pin));
    }
    else{
        ret = STD_NULL_POINTER;
    }
    return ret;    
}

static STD_Return_t Interrupt_RBx_SetInterruptHandler(const interrupt_RBx_t *int_obj){
        STD_Return_t ret = STD_NOK;
    if(int_obj){
        ret = STD_OK;
       switch(int_obj->pin.pin){
            case PIN4 : RB4_InterruptHandler_HIGH = int_obj->EXT_InterruptHandler_HIGH;
                        RB4_InterruptHandler_LOW = int_obj->EXT_InterruptHandler_LOW;
                        break;
            case PIN5 : RB5_InterruptHandler_HIGH = int_obj->EXT_InterruptHandler_HIGH;
                        RB5_InterruptHandler_LOW = int_obj->EXT_InterruptHandler_LOW;
                        break;
            case PIN6 : RB6_InterruptHandler_HIGH = int_obj->EXT_InterruptHandler_HIGH;
                        RB6_InterruptHandler_LOW = int_obj->EXT_InterruptHandler_LOW;
                        break;
            case PIN7 : RB7_InterruptHandler_HIGH = int_obj->EXT_InterruptHandler_HIGH;
                        RB7_InterruptHandler_LOW = int_obj->EXT_InterruptHandler_LOW;
                        break;            
            default: ret = STD_NOK;break;
        }
       
    }
    else{
        ret = STD_NULL_POINTER;
    }
    return ret;      
}
void INT0_ISR(void){
    EXT_INT0_InterruptFlagClear();
    if(INT0_InterruptHandler)
    INT0_InterruptHandler();
}
void INT1_ISR(void){
    EXT_INT1_InterruptFlagClear();
    if(INT1_InterruptHandler)
    INT1_InterruptHandler();
}
void INT2_ISR(void){
    EXT_INT2_InterruptFlagClear();
    if(INT2_InterruptHandler)
    INT2_InterruptHandler();
}

void RB4_ISR(uint8 RB_Source){
    EXT_RBx_InterruptFlagClear();
    if(RB_Source){
     if(RB4_InterruptHandler_HIGH) RB4_InterruptHandler_HIGH();   
}
    else{
     if(RB4_InterruptHandler_LOW) RB4_InterruptHandler_LOW();    
    }
}

void RB5_ISR(uint8 RB_Source){
    EXT_RBx_InterruptFlagClear();
    if(RB_Source){
     if(RB5_InterruptHandler_HIGH) RB5_InterruptHandler_HIGH();   
}
    else{
     if(RB5_InterruptHandler_LOW) RB5_InterruptHandler_LOW();    
    }
}

void RB6_ISR(uint8 RB_Source){
    EXT_RBx_InterruptFlagClear();
    if(RB_Source){
     if(RB6_InterruptHandler_HIGH) RB6_InterruptHandler_HIGH();   
}
    else{
     if(RB6_InterruptHandler_LOW) RB6_InterruptHandler_LOW();    
    }
}

void RB7_ISR(uint8 RB_Source){
    EXT_RBx_InterruptFlagClear();
    if(RB_Source){
     if(RB7_InterruptHandler_HIGH) RB7_InterruptHandler_HIGH();   
}
    else{
     if(RB7_InterruptHandler_LOW) RB7_InterruptHandler_LOW();    
    }
}


