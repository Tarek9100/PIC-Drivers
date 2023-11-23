/* 
 * File:   CCP.h
 * Author: ENG TAREK
 *
 */

#ifndef CCP_H
#define	CCP_H

/* Section : Includes */

#include "../GPIO/gpio.h"
#include "../Interrupt/internal_interrupt.h" 
#include "CCP_cfg.h"
#include "../Timer/Timer.h"


/* Section : Macro Declarations */

#define CCP_MODULE_DISABLE                    ((uint8)0x00)
#define CCP_CAPTURE_MODE_1_FALLING_EDGE       ((uint8)0x04)
#define CCP_CAPTURE_MODE_1_RISING_EDGE        ((uint8)0x05)
#define CCP_CAPTURE_MODE_4_RISING_EDGE        ((uint8)0x06)
#define CCP_CAPTURE_MODE_16_RISING_EDGE       ((uint8)0x07)
#define CCP_COMPARE_MODE_SET_PIN_LOW          ((uint8)0x08)
#define CCP_COMPARE_MODE_SET_PIN_HIGH         ((uint8)0x09)
#define CCP_COMPARE_MODE_TOGGLE_ON_MATCH      ((uint8)0x02)
#define CCP_COMPARE_MODE_GEN_SW_INTERRUPT     ((uint8)0x0A)
#define CCP_COMPARE_MODE_GEN_EVENT            ((uint8)0x0B)
#define CCP_PWM_MODE                          ((uint8)0X0C)

#define CCP_CAPTURE_NOT_READY                 0
#define CCP_CAPTURE_READY                     1

#define CCP_COMPARE_NOT_READY                 0
#define CCP_COMPARE_READY                     1

/* Timer2 Input Clock Post-scaler */
#define CCP_TIMER2_POSTSCALER_DIV_BY_1       1
#define CCP_TIMER2_POSTSCALER_DIV_BY_2       2
#define CCP_TIMER2_POSTSCALER_DIV_BY_3       3
#define CCP_TIMER2_POSTSCALER_DIV_BY_4       4
#define CCP_TIMER2_POSTSCALER_DIV_BY_5       5
#define CCP_TIMER2_POSTSCALER_DIV_BY_6       6
#define CCP_TIMER2_POSTSCALER_DIV_BY_7       7
#define CCP_TIMER2_POSTSCALER_DIV_BY_8       8
#define CCP_TIMER2_POSTSCALER_DIV_BY_9       9
#define CCP_TIMER2_POSTSCALER_DIV_BY_10      10
#define CCP_TIMER2_POSTSCALER_DIV_BY_11      11
#define CCP_TIMER2_POSTSCALER_DIV_BY_12      12
#define CCP_TIMER2_POSTSCALER_DIV_BY_13      13
#define CCP_TIMER2_POSTSCALER_DIV_BY_14      14
#define CCP_TIMER2_POSTSCALER_DIV_BY_15      15
#define CCP_TIMER2_POSTSCALER_DIV_BY_16      16

/* Timer2 Input Clock Pre-scaler */
#define CCP_TIMER2_PRESCALER_DIV_BY_1        1
#define CCP_TIMER2_PRESCALER_DIV_BY_4        4
#define CCP_TIMER2_PRESCALER_DIV_BY_16       16
/* Section : Macro Function Declarations */
#define CCP1_SET_MODE(_CONFIG)              (CCP1CONbits.CCP1M = _CONFIG)
#define CCP2_SET_MODE(_CONFIG)              (CCP2CONbits.CCP2M = _CONFIG)


/* Section : Data Type Declarations */
typedef union{
    struct{
       uint8 ccpr_low;
       uint8 ccpr_high;
    };
    uint16 ccpr_16Bit;
}CCP_REG_T;

typedef enum{
    CCP1_CCP2_TIMER3 = 0,
    CCP1_TIMER1_CCP2_TIMER3,
    CCP1_CCP2_TIMER1
}ccp_capture_compare_timer_t;

typedef struct{
    
uint8 ccp1_mode;  
ccp_capture_compare_timer_t ccp_capture_compare_timer;  
#if (CCP1_CFG_MODE==CCP_PWM_MODE_SELECT)
uint32 PWM_Frequency;
uint8 timer2_preload_value;
uint8 timer2_postscalar_value : 4;
uint8  timer2_prescalar_value : 2;
#endif
#if INTERNAL_INTERRUPT_CCP1_ENABLE == FEATURE_ENABLE
    void (*CCP1_InterruptHandler)(void);
    interrupt_priority_levels priority;
#endif    
}ccp1_t;

typedef struct{
uint8 ccp2_mode;
ccp_capture_compare_timer_t ccp_capture_compare_timer;  
#if (CCP2_CFG_MODE==CCP_PWM_MODE_SELECT)  
uint32 PWM_Frequency;
uint8 timer2_preload_value;
uint8 timer2_postscalar_value : 4;
uint8  timer2_prescalar_value : 2;

#endif
#if INTERNAL_INTERRUPT_CCP1_ENABLE == FEATURE_ENABLE
    void (*CCP2_InterruptHandler)(void);
    interrupt_priority_levels priority;
#endif
   
}ccp2_t;
/* Section : Function Declarations */

STD_Return_t CCP1_Init(const ccp1_t *ccp1_obj);
STD_Return_t CCP1_Deinit(const ccp1_t *ccp1_obj);

STD_Return_t CCP2_Init(const ccp2_t *ccp2_obj);
STD_Return_t CCP2_Deinit(const ccp2_t *ccp2_obj);

#if (CCP1_CFG_MODE==CCP_CAPTURE_MODE_SELECT)
STD_Return_t CCP1_IsCapturedDataReady(uint8* capture_status);
STD_Return_t CCP1_Capture_Mode_Read_Value(uint16* capture_value);
#elif (CCP1_CFG_MODE==CCP_COMPARE_MODE_SELECT)
STD_Return_t CCP1_IsCompareComplete(uint8* compare_status);
STD_Return_t CCP1_Compare_Mode_Set_Value(uint16 compare_value);
#elif (CCP1_CFG_MODE==CCP_PWM_MODE_SELECT)
STD_Return_t CCP1_PWM_Set_DutyCycle(const uint8 dutycycle); 
STD_Return_t CCP1_PWM_Start(void);
STD_Return_t CCP1_PWM_Stop(void);
#endif

#if (CCP2_CFG_MODE==CCP_CAPTURE_MODE_SELECT)
STD_Return_t CCP2_IsCapturedDataReady(uint8* capture_status);
STD_Return_t CCP2_Capture_Mode_Read_Value(uint16* capture_value);
#elif (CCP2_CFG_MODE==CCP_COMPARE_MODE_SELECT)
STD_Return_t CCP2_IsCompareComplete(uint8* compare_status);
STD_Return_t CCP2_Compare_Mode_Set_Value(uint16 compare_value);
#elif (CCP2_CFG_MODE==CCP_PWM_MODE_SELECT)
STD_Return_t CCP2_PWM_Set_DutyCycle(const uint8 dutycycle); 
STD_Return_t CCP2_PWM_Start(void);
STD_Return_t CCP2_PWM_Stop(void);
#endif
#endif	/* CCP_H */

