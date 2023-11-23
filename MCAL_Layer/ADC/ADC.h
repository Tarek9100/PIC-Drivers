/* 
 * File:   ADC.h
 * Author: ENG TAREK
 *
 */

#ifndef ADC_H
#define	ADC_H

/* Section : Includes */
#include "ADC_cfg.h"
#include "../GPIO/gpio.h"
#include "../Interrupt/internal_interrupt.h"
/* Section : Macro Declarations */
#define ADC_RES_RIGHT_FORMAT 1
#define ADC_RES_LEFT_FORMAT  0

#define ADC_VREF_ENABLED        1
#define ADC_VREF_DISABLED       0
/* Section : Macro Function Declarations */

#define ADC_CONVERSION_STATUS()     (ADCON0bits.GODONE)
#define ADC_START_CONVERSION()      (ADCON0bits.GODONE = 1)

#define ADC_ENABLE()                (ADCON0bits.ADON = 1)
#define ADC_DISABLE()               (ADCON0bits.ADON = 0)

#define ADC_ENABLE_VREF()           do{ADCON1bits.VCFG0 = 1;\
                                       ADCON1bits.VCFG1 = 1;\
                                       }while(0)
#define ADC_DISABLE_VREF()          do{ADCON1bits.VCFG0 = 0;\
                                       ADCON1bits.VCFG1 = 0;\
                                       }while(0)
#define ADC_PORT_CONFIG(__CONFIG)   (ADCON1bits.PCFG = __CONFIG)

#define ADC_RESULT_RIGHT_FORMAT()   (ADCON2bits.ADFM = 1)
#define ADC_RESULT_LEFT_FORMAT()    (ADCON2bits.ADFM = 0)

/* Section : Data Type Declarations */
typedef enum{
    CHANNEL_AN0 = 0,
    CHANNEL_AN1,
    CHANNEL_AN2,
    CHANNEL_AN3,
    CHANNEL_AN4,
    CHANNEL_AN5,
    CHANNEL_AN6,
    CHANNEL_AN7,
    CHANNEL_AN8,
    CHANNEL_AN9,
    CHANNEL_AN10,
    CHANNEL_AN11,
    CHANNEL_AN12,            
}ADC_Channel_t;

typedef enum{
    ADC_ALL_ANALOG_FUNCTIONALITY = 2,
    ADC_AN0_AN11_ANALOG_FUNCTIONALITY,
    ADC_AN0_AN10_ANALOG_FUNCTIONALITY, 
    ADC_AN0_AN9_ANALOG_FUNCTIONALITY,
    ADC_AN0_AN8_ANALOG_FUNCTIONALITY,
    ADC_AN0_AN7_ANALOG_FUNCTIONALITY,
    ADC_AN0_AN6_ANALOG_FUNCTIONALITY, 
    ADC_AN0_AN5_ANALOG_FUNCTIONALITY,
    ADC_AN0_AN4_ANALOG_FUNCTIONALITY,
    ADC_AN0_AN3_ANALOG_FUNCTIONALITY,
    ADC_AN0_AN2_ANALOG_FUNCTIONALITY, 
    ADC_AN0_AN1_ANALOG_FUNCTIONALITY,
    ADC_AN0_ANALOG_FUNCTIONALITY,
    ADC_ALL_DIGITAL_FUNCTIONALITY
}ADC_Analog_Fn_t;

typedef enum{
  ADC_0_TAD = 0,
  ADC_2_TAD,
  ADC_4_TAD,
  ADC_6_TAD,
  ADC_8_TAD,
  ADC_12_TAD,
  ADC_16_TAD,
  ADC_20_TAD        
}ADC_Acquisition_Time_t;

typedef enum{
    ADC_CLK_FOSC_DIV_2 = 0,
    ADC_CLK_FOSC_DIV_8,
    ADC_CLK_FOSC_DIV_32,
    ADC_CLK_FOSC_DIV_FRC,
    ADC_CLK_FOSC_DIV_4,
    ADC_CLK_FOSC_DIV_16,
    ADC_CLK_FOSC_DIV_64             
}ADC_Clock_t;

typedef struct{
#if INTERNAL_INTERRUPT_ADC_ENABLE == FEATURE_ENABLE
    void (*ADC_InterruptHandler)(void);
    interrupt_priority_levels priority;
#endif    
    ADC_Acquisition_Time_t  Acquisition_Time;
    ADC_Clock_t             Clock;
    ADC_Channel_t           Channel;
    uint8 voltage_reference : 1;
    uint8 result_format     : 1;
    uint8 Reserved          : 6;
}ADC_t;
/* Section : Function Declarations */
STD_Return_t ADC_Init(const ADC_t *adc_obj);
STD_Return_t ADC_Deinit(const ADC_t *adc_obj);
STD_Return_t ADC_SelectChannel(ADC_Channel_t Channel);
STD_Return_t ADC_ConversionResult(const ADC_t *adc_obj, uint16* conversion_result);
STD_Return_t ADC_GetConversion_Blocking(const ADC_t *adc_obj, ADC_Channel_t Channel, uint16* conversion_result);
STD_Return_t ADC_StartConversion_IT(const ADC_t *adc_obj, ADC_Channel_t Channel);
#endif	/* ADC_H */

