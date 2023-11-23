#include "ADC.h"

#if INTERNAL_INTERRUPT_ADC_ENABLE == FEATURE_ENABLE
static void (*ADC_InterruptHandler)(void) = NULL;
#endif
static STD_Return_t ADC_Port_Config(ADC_t *adc_obj);
static STD_Return_t ADC_Select_Format(ADC_t *adc_obj);
static STD_Return_t ADC_Configure_VREF(ADC_t *adc_obj);

STD_Return_t ADC_Init(const ADC_t *adc_obj){
    STD_Return_t ret = STD_NOK;
    if(adc_obj){
        ADC_DISABLE();
        ADCON2bits.ACQT = adc_obj->Acquisition_Time;    
        ADCON2bits.ADCS = adc_obj->Clock;
        ADCON0bits.CHS = adc_obj->Channel;
        #if INTERNAL_INTERRUPT_ADC_ENABLE == FEATURE_ENABLE
        ADC_InterruptEnable();
        ADC_InterruptFlagClear();
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE == FEATURE_ENABLE
        if(INTERRUPT_LOW_PRIORITY == adc_obj->priority){
            ADC_LowPrioritySet();
            INTERRUPT_GlobalInterruptLowEnable(); 
        }
        else{
            ADC_HighPrioritySet();
            INTERRUPT_GlobalInterruptHighEnable(); 
        }
        #else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
        #endif
        ADC_InterruptHandler = adc_obj->ADC_InterruptHandler;
        #endif 
        ret = ADC_SelectChannel(adc_obj->Channel);
        ret = ADC_Select_Format(adc_obj);
        ret = ADC_Configure_VREF(adc_obj);
        ADC_ENABLE();
    }
    else{
     ret = STD_NULL_POINTER;   
    }
     return ret;    
}
STD_Return_t ADC_Deinit(const ADC_t *adc_obj){
    STD_Return_t ret = STD_NOK;
    if(adc_obj){
     ADC_DISABLE();  
    #if INTERNAL_INTERRUPT_ADC_ENABLE == FEATURE_ENABLE
    ADC_InterruptDisable();
    #endif
    }
    else{
     ret = STD_NULL_POINTER;   
    }
     return ret;       
}
STD_Return_t ADC_SelectChannel(ADC_Channel_t Channel){
    STD_Return_t ret = STD_OK;
        ADCON0bits.CHS = Channel;
        switch(Channel){
            case CHANNEL_AN0:SET_BIT(TRISA, _TRISA_RA0_POSITION); break;
            case CHANNEL_AN1:SET_BIT(TRISA, _TRISA_RA1_POSITION); break;
            case CHANNEL_AN2:SET_BIT(TRISA, _TRISA_RA2_POSITION); break;
            case CHANNEL_AN3:SET_BIT(TRISA, _TRISA_RA3_POSITION); break;
            case CHANNEL_AN4:SET_BIT(TRISA, _TRISA_RA5_POSITION); break;
            case CHANNEL_AN5:SET_BIT(TRISE, _TRISE_RE0_POSITION); break;
            case CHANNEL_AN6:SET_BIT(TRISE, _TRISE_RE1_POSITION); break;
            case CHANNEL_AN7:SET_BIT(TRISE, _TRISE_RE2_POSITION); break;
            case CHANNEL_AN8:SET_BIT(TRISB, _TRISB_RB2_POSITION); break;
            case CHANNEL_AN9:SET_BIT(TRISB, _TRISB_RB3_POSITION); break;
            case CHANNEL_AN10:SET_BIT(TRISB, _TRISB_RB1_POSITION); break;
            case CHANNEL_AN11:SET_BIT(TRISB, _TRISB_RB4_POSITION); break;
            case CHANNEL_AN12:SET_BIT(TRISB, _TRISB_RB0_POSITION); break;
            default:ret = STD_NOK; break;
        }
     return ret;       
}
  

STD_Return_t ADC_ConversionResult(const ADC_t *adc_obj, uint16* conversion_result){
    STD_Return_t ret = STD_NOK;
    if((NULL == adc_obj) || (NULL == conversion_result)){
        ret = STD_NULL_POINTER;
    }
    else{
        if(ADC_RES_LEFT_FORMAT == adc_obj->result_format){
            *conversion_result = (uint16)((ADRESH << 2) + (ADRESL >> 6));
        }
        else{
            *conversion_result = (uint16)(ADRESL + (ADRESH << 8));
        }        
    }
    return ret;    
}
STD_Return_t ADC_GetConversion_Blocking(const ADC_t *adc_obj, ADC_Channel_t Channel, uint16* conversion_result){
    STD_Return_t ret = STD_NOK;
    if((NULL == adc_obj) || (NULL == conversion_result)){
        ret = STD_NULL_POINTER;
    }
    else{
        ret = ADC_SelectChannel(Channel);
        ADC_START_CONVERSION();
        while(ADC_CONVERSION_STATUS());
        ret = ADC_ConversionResult(adc_obj,conversion_result);
    }
    return ret;    
}
STD_Return_t ADC_StartConversion_IT(const ADC_t *adc_obj, ADC_Channel_t Channel){
    STD_Return_t ret = STD_NOK;
    if(adc_obj){
        ret = ADC_SelectChannel(Channel);
        ADC_START_CONVERSION();
    }
    else{
     ret = STD_NULL_POINTER;   
    }
     return ret; 
}

static STD_Return_t ADC_Select_Format(ADC_t *adc_obj){
    STD_Return_t ret = STD_NOK;
    if(adc_obj){
        if(adc_obj->result_format == ADC_RES_LEFT_FORMAT){
            ADC_RESULT_LEFT_FORMAT();
        }
        else{
            ADC_RESULT_RIGHT_FORMAT();
        }
    }
    else{
     ret = STD_NULL_POINTER;   
    }
     return ret;     
}

static STD_Return_t ADC_Configure_VREF(ADC_t *adc_obj){
    STD_Return_t ret = STD_NOK;
    if(adc_obj){
        if(adc_obj->voltage_reference == ADC_VREF_ENABLED){
            ADC_ENABLE_VREF();
        }
        else{
            ADC_DISABLE_VREF();
        }
    }
    else{
     ret = STD_NULL_POINTER;   
    }
     return ret;     
}

void ADC_ISR(void){
    ADC_InterruptFlagClear();
    if(ADC_InterruptHandler)
    ADC_InterruptHandler();
}