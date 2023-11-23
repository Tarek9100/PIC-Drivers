#include "CCP.h"

static void (*CCP1_InterruptHandler)(void)= NULL;
static void (*CCP2_InterruptHandler)(void) = NULL;

static void CCP1_Mode_Timer_Select(const ccp1_t *ccp1_obj);
static void CCP2_Mode_Timer_Select(const ccp2_t *ccp2_obj);
STD_Return_t CCP1_Init(const ccp1_t *ccp1_obj){
    STD_Return_t ret = STD_NOK;
    if(ccp1_obj){
        ret = STD_OK;
        pin_config_t ccp_pin= {
        .port = PORTC_ID,.pin = PIN2,.logic = LOW    
        };
        #if CCP1_CFG_MODE == CCP_CAPTURE_MODE_SELECT
           switch(ccp1_obj->ccp1_mode){
               case CCP_CAPTURE_MODE_1_RISING_EDGE: CCP1_SET_MODE(CCP_CAPTURE_MODE_1_RISING_EDGE);break;
               case CCP_CAPTURE_MODE_1_FALLING_EDGE: CCP1_SET_MODE(CCP_CAPTURE_MODE_1_FALLING_EDGE);break;
               case CCP_CAPTURE_MODE_4_RISING_EDGE: CCP1_SET_MODE(CCP_CAPTURE_MODE_4_RISING_EDGE);break;
               case CCP_CAPTURE_MODE_16_RISING_EDGE: CCP1_SET_MODE(CCP_CAPTURE_MODE_16_RISING_EDGE);break;
               default: ret = STD_NOK;
           }
           ccp_pin.direction = INPUT;
           CCP1_Mode_Timer_Select(ccp1_obj);
   
        #elif CCP1_CFG_MODE == CCP_COMPARE_MODE_SELECT
          switch(ccp1_obj->ccp1_mode){
               case CCP_COMPARE_MODE_SET_PIN_LOW: CCP1_SET_MODE(CCP_COMPARE_MODE_SET_PIN_LOW);break;
               case CCP_COMPARE_MODE_SET_PIN_HIGH: CCP1_SET_MODE(CCP_COMPARE_MODE_SET_PIN_HIGH);break;
               case CCP_COMPARE_MODE_TOGGLE_ON_MATCH: CCP1_SET_MODE(CCP_COMPARE_MODE_TOGGLE_ON_MATCH);break;
               case CCP_COMPARE_MODE_GEN_SW_INTERRUPT: CCP1_SET_MODE(CCP_COMPARE_MODE_GEN_SW_INTERRUPT);break;
               case CCP_COMPARE_MODE_GEN_EVENT: CCP1_SET_MODE(CCP_COMPARE_MODE_GEN_EVENT);break;
               default: ret = STD_NOK;  
        }
          ccp_pin.direction = OUTPUT;
          CCP1_Mode_Timer_Select(ccp1_obj);
        #elif CCP1_CFG_MODE == CCP_PWM_MODE_SELECT
             CCP1_SET_MODE(CCP_PWM_MODE);
             ccp_pin.direction = OUTPUT;
         PR2 = (uint8)(((float)_XTAL_FREQ / ((float)ccp1_obj->PWM_Frequency * 4.0 * ccp1_obj->timer2_prescalar_value * 
                    ccp1_obj->timer2_postscalar_value)) - 1);
        #endif
        gpio_pin_initialize(&ccp_pin);

        #if INTERNAL_INTERRUPT_CCP1_ENABLE == FEATURE_ENABLE
        CCP1_InterruptEnable();
        CCP1_InterruptFlagClear();
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE == FEATURE_ENABLE
        if(INTERRUPT_LOW_PRIORITY == ccp1_obj->priority){
            CCP1_LowPrioritySet();
            INTERRUPT_GlobalInterruptLowEnable(); 
        }
        else{
            CCP1_HighPrioritySet();
            INTERRUPT_GlobalInterruptHighEnable(); 
        }
        #else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
        #endif
        CCP1_InterruptHandler = ccp1_obj->CCP1_InterruptHandler;
        #endif
          
    }    
    else{
        ret = STD_NULL_POINTER;
    }
    return ret;
}
STD_Return_t CCP1_Deinit(const ccp1_t *ccp1_obj){
    STD_Return_t ret = STD_NOK;
    if(ccp1_obj){
        ret = STD_OK;
        CCP1_SET_MODE(CCP_MODULE_DISABLE);
    #if INTERNAL_INTERRUPT_CCP1_ENABLE == FEATURE_ENABLE
    CCP1_InterruptDisable();
    #endif        
    }
    else{
        ret = STD_NULL_POINTER;
    }
    return ret;
}

STD_Return_t CCP2_Init(const ccp2_t *ccp2_obj){
    STD_Return_t ret = STD_NOK;
    if(ccp2_obj){
    pin_config_t ccp_pin= {
        .port = PORTC_ID,.pin = PIN1,.logic = LOW    
        };    
        ret = STD_OK;
        #if CCP2_CFG_MODE == CCP_CAPTURE_MODE_SELECT
           switch(ccp2_obj->ccp2_mode){
               case CCP_CAPTURE_MODE_1_RISING_EDGE: CCP2_SET_MODE(CCP_CAPTURE_MODE_1_RISING_EDGE);break;
               case CCP_CAPTURE_MODE_1_FALLING_EDGE: CCP2_SET_MODE(CCP_CAPTURE_MODE_1_FALLING_EDGE);break;
               case CCP_CAPTURE_MODE_4_RISING_EDGE: CCP2_SET_MODE(CCP_CAPTURE_MODE_4_RISING_EDGE);break;
               case CCP_CAPTURE_MODE_16_RISING_EDGE: CCP2_SET_MODE(CCP_CAPTURE_MODE_16_RISING_EDGE);break;
               default: ret = STD_NOK;
           }
           ccp_pin.direction = INPUT;
           CCP2_Mode_Timer_Select(ccp2_obj);
        #elif CCP2_CFG_MODE == CCP_COMPARE_MODE_SELECT
          switch(ccp2_obj->ccp2_mode){
               case CCP_COMPARE_MODE_SET_PIN_LOW: CCP2_SET_MODE(CCP_COMPARE_MODE_SET_PIN_LOW);break;
               case CCP_COMPARE_MODE_SET_PIN_HIGH: CCP2_SET_MODE(CCP_COMPARE_MODE_SET_PIN_HIGH);break;
               case CCP_COMPARE_MODE_TOGGLE_ON_MATCH: CCP2_SET_MODE(CCP_COMPARE_MODE_TOGGLE_ON_MATCH);break;
               case CCP_COMPARE_MODE_GEN_SW_INTERRUPT: CCP2_SET_MODE(CCP_COMPARE_MODE_GEN_SW_INTERRUPT);break;
               case CCP_COMPARE_MODE_GEN_EVENT: CCP2_SET_MODE(CCP_COMPARE_MODE_GEN_EVENT);break;
               default: ret = STD_NOK;  
        }
          ccp_pin.direction = OUTPUT;
          CCP2_Mode_Timer_Select(ccp2_obj);
        #elif CCP2_CFG_MODE == CCP_PWM_MODE_SELECT
             CCP2_SET_MODE(CCP_PWM_MODE);
             ccp_pin.direction = OUTPUT;        
         PR2 = (uint8)(((float)_XTAL_FREQ / ((float)ccp2_obj->PWM_Frequency * 4.0 * ccp2_obj->timer2_prescalar_value * ccp2_obj->timer2_postscalar_value)) - 1);
        #endif 
        gpio_pin_initialize(&ccp_pin);
        
        #if INTERNAL_INTERRUPT_CCP2_ENABLE == FEATURE_ENABLE
        CCP2_InterruptEnable();
        CCP2_InterruptFlagClear();
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE == FEATURE_ENABLE
        if(INTERRUPT_HIGH_PRIORITY == ccp2_obj->priority){
            CCP2_LowPrioritySet();
            INTERRUPT_GlobalInterruptLowEnable(); 
        }
        else{
            CCP2_HighPrioritySet();
            INTERRUPT_GlobalInterruptHighEnable(); 
        }
        #else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
        #endif
        CCP2_InterruptHandler = ccp2_obj->CCP2_InterruptHandler;
        #endif 
    }
    else{
        ret = STD_NULL_POINTER;
    }
    return ret;
}
STD_Return_t CCP2_Deinit(const ccp2_t *ccp2_obj){
    STD_Return_t ret = STD_NOK;
    if(ccp2_obj){
        ret = STD_OK;
        CCP2_SET_MODE(CCP_MODULE_DISABLE);
    #if INTERNAL_INTERRUPT_CCP2_ENABLE == FEATURE_ENABLE
    CCP2_InterruptDisable();
    #endif         
    }
    else{
        ret = STD_NULL_POINTER;
    }
    return ret;
}

#if (CCP1_CFG_MODE==CCP_CAPTURE_MODE_SELECT)
STD_Return_t CCP1_IsCapturedDataReady(uint8* capture_status){
    STD_Return_t ret = STD_NOK;
    if(capture_status){
        ret = STD_OK;
        if( CCP_CAPTURE_READY == PIR1bits.CCP1IF){
            *capture_status =  CCP_CAPTURE_READY;
    }
        else{
            *capture_status =  CCP_CAPTURE_NOT_READY; 
    }
    }
    else{
        ret = STD_NULL_POINTER;
    }
    return ret;
}

STD_Return_t CCP1_Capture_Mode_Read_Value(uint16* capture_value){
    STD_Return_t ret = STD_NOK;
    CCP_REG_T temp_value={.ccpr_low=0,.ccpr_high=0};
    if(capture_value){
        ret = STD_OK;
        temp_value.ccpr_low = CCPR1L;
        temp_value.ccpr_high = CCPR1H;
        *capture_value = temp_value.ccpr_16Bit;
    }
    else{
        ret = STD_NULL_POINTER;
    }
    return ret;
}
#elif (CCP1_CFG_MODE==CCP_COMPARE_MODE_SELECT)
STD_Return_t CCP1_IsCompareComplete(uint8* compare_status){
    STD_Return_t ret = STD_NOK;
    if(compare_status){
        ret = STD_OK;

    }
    else{
        ret = STD_NULL_POINTER;
    }
    return ret;
}
STD_Return_t CCP1_Compare_Mode_Set_Value(uint16 compare_value){
    STD_Return_t ret = STD_OK;
    CCP_REG_T temp_value= {.ccpr_low=0,.ccpr_high=0};
    temp_value.ccpr_16Bit = compare_value;
    CCPR1L = temp_value.ccpr_low;
    CCPR1H = temp_value.ccpr_high;
    return ret;
}
#elif (CCP1_CFG_MODE==CCP_PWM_MODE_SELECT)
STD_Return_t CCP1_PWM_Set_DutyCycle(const uint8 dutycycle){
    STD_Return_t ret = STD_OK;
    uint16 temp = 0;
    temp =(uint16)(4 * ((float)PR2 + 1.0) * ((float)dutycycle / 100.0));
    CCP1CONbits.DC1B = (uint8)(temp & 0x0003);
    CCPR1L = (uint8)(temp >> 2);
    return ret;
}
STD_Return_t CCP1_PWM_Start(void){
    STD_Return_t ret = STD_OK;
    CCP1_SET_MODE(CCP_PWM_MODE);
    return ret;
}
STD_Return_t CCP1_PWM_Stop(void){
    STD_Return_t ret = STD_OK;
    CCP1_SET_MODE(CCP_MODULE_DISABLE);
    return ret;
}
#endif

#if (CCP2_CFG_MODE==CCP_CAPTURE_MODE_SELECT)
STD_Return_t CCP2_IsCapturedDataReady(uint8* capture_status){
    STD_Return_t ret = STD_NOK;
    if(capture_status){
        ret = STD_OK;
    if( CCP_CAPTURE_READY == PIR2bits.CCP2IF){
        *capture_status =  CCP_CAPTURE_READY;
    }
    }
    else{
        ret = STD_NULL_POINTER;
    }
    return ret;
}
STD_Return_t CCP2_Capture_Mode_Read_Value(uint16* capture_value){
    STD_Return_t ret = STD_NOK;
    CCP_REG_T temp_value = {.ccpr_low=0,.ccpr_high=0};
    if(capture_value){
        ret = STD_OK;
        temp_value.ccpr_low = CCPR2L;
        temp_value.ccpr_high = CCPR2H;
        *capture_value = temp_value.ccpr_16Bit;
    }
    else{
        ret = STD_NULL_POINTER;
    }
    return ret;
}
#elif (CCP2_CFG_MODE==CCP_COMPARE_MODE_SELECT)
STD_Return_t CCP2_IsCompareComplete(uint8* compare_status){
    STD_Return_t ret = STD_NOK;
    if(compare_status){
        ret = STD_OK;
    if( CCP_CAPTURE_READY == PIR2bits.CCP2IF){
        *compare_status =  CCP_COMPARE_READY;
    }
    }
    else{
        ret = STD_NULL_POINTER;
    }
    return ret;
}
STD_Return_t CCP2_Compare_Mode_Set_Value(uint16 compare_value){
    STD_Return_t ret = STD_OK;
    CCP_REG_T temp_value= {.ccpr_low=0,.ccpr_high=0};
    temp_value.ccpr_16Bit = compare_value;
    CCPR2L = temp_value.ccpr_low;
    CCPR2H = temp_value.ccpr_high;
    return ret;
}
#elif (CCP2_CFG_MODE==CCP_PWM_MODE_SELECT)
STD_Return_t CCP2_PWM_Set_DutyCycle(const uint8 dutycycle){
    STD_Return_t ret = STD_OK;
    uint16 temp = 0;
    temp =(uint16)(4 * ((float)PR2 + 1.0) * ((float)dutycycle / 100.0));
    CCPR2L = (uint8)(temp >> 2);
    CCP2CONbits.DC2B = (uint8)(temp & 0x0003);
    return ret;
}
STD_Return_t CCP2_PWM_Start(void){
    STD_Return_t ret = STD_OK;
    CCP2_SET_MODE(CCP_PWM_MODE);
    return ret;
}
STD_Return_t CCP2_PWM_Stop(void){
    STD_Return_t ret = STD_OK;
    CCP2_SET_MODE(CCP_MODULE_DISABLE);
    return ret;
}
#endif

static void CCP1_Mode_Timer_Select(const ccp1_t *ccp1_obj){
    if(CCP1_CCP2_TIMER3 == ccp1_obj->ccp_capture_compare_timer){
        /* Timer3 is the capture/compare clock source for the CCP modules */
        T3CONbits.T3CCP1 = 0; 
        T3CONbits.T3CCP2 = 1;
    }
    else if(CCP1_TIMER1_CCP2_TIMER3 == ccp1_obj->ccp_capture_compare_timer){
        /* Timer3 is the capture/compare clock source for CCP2 */
        /* Timer1 is the capture/compare clock source for CCP1 */
        T3CONbits.T3CCP1 = 1;
        T3CONbits.T3CCP2 = 0;
    }
    else if(CCP1_CCP2_TIMER1 == ccp1_obj->ccp_capture_compare_timer){
        /* Timer1 is the capture/compare clock source for the CCP modules */
        T3CONbits.T3CCP1 = 0;
        T3CONbits.T3CCP2 = 0;
    }
    else{ /* Nothing */ }
}
static void CCP2_Mode_Timer_Select(const ccp2_t *ccp2_obj){
    if(CCP1_CCP2_TIMER3 == ccp2_obj->ccp_capture_compare_timer){
        /* Timer3 is the capture/compare clock source for the CCP modules */
        T3CONbits.T3CCP1 = 0; 
        T3CONbits.T3CCP2 = 1;
    }
    else if(CCP1_TIMER1_CCP2_TIMER3 == ccp2_obj->ccp_capture_compare_timer){
        /* Timer3 is the capture/compare clock source for CCP2 */
        /* Timer1 is the capture/compare clock source for CCP1 */
        T3CONbits.T3CCP1 = 1;
        T3CONbits.T3CCP2 = 0;
    }
    else if(CCP1_CCP2_TIMER1 == ccp2_obj->ccp_capture_compare_timer){
        /* Timer1 is the capture/compare clock source for the CCP modules */
        T3CONbits.T3CCP1 = 0;
        T3CONbits.T3CCP2 = 0;
    }
    else{ /* Nothing */ }
}

void CCP1_ISR(void){
    CCP1_InterruptFlagClear();
    if(CCP1_InterruptHandler)
    CCP1_InterruptHandler();
}

void CCP2_ISR(void){
    CCP2_InterruptFlagClear();
    if(CCP2_InterruptHandler)
    CCP2_InterruptHandler();
}