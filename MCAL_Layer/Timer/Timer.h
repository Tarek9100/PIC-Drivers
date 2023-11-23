/* 
 * File:   Timer.h
 * Author: ENG TAREK
 *
 */

#ifndef TIMER_H
#define	TIMER_H

/* Section : Includes */

#include "../GPIO/gpio.h"
#include "../Interrupt/internal_interrupt.h" 
#include "Timer_cfg.h"
/* Section : Macro Declarations */
#define TIMER_PRESCALAR_ENABLE_CFG            1
#define TIMER_PRESCALAR_DISABLE_CFG           0

#define TIMER_COUNTER_RISING_EDGE_CFG         1
#define TIMER_COUNTER_FALLING_EDGE_CFG        0

#define TIMER_TIMER_MODE                      1
#define TIMER_COUNTER_MODE                    0

#define TIMER_8BIT_REGISTER_MODE              1
#define TIMER_16BIT_REGISTER_MODE             0

#define TIMER1_ASYNC_COUNTER_MODE             1
#define TIMER1_SYNC_COUNTER_MODE              0

#define TIMER1_RW_REG_8BIT_MODE               0
#define TIMER1_RW_REG_16BIT_MODE              1

#define TIMER3_ASYNC_COUNTER_MODE             1
#define TIMER3_SYNC_COUNTER_MODE              0

/* Section : Macro Function Declarations */ 

/******************************Timer0************************************/
#define TIMER0_PRESCALAR_ENABLE()            (T0CONbits.PSA = 0)
#define TIMER0_PRESCALAR_DISABLE()           (T0CONbits.PSA = 1)

#define TIMER0_RISING_EDGE_ENABLE()          (T0CONbits.T0SE = 0)
#define TIMER0_FALLING_EDGE_DISABLE()        (T0CONbits.T0SE = 1)

#define TIMER0_TIMER_MODE_ENABLE()           (T0CONbits.T0CS = 0)
#define TIMER0_COUNTER_MODE_ENABLE()         (T0CONbits.T0CS = 1)

#define TIMER0_8BIT_REGISTER_MODE_ENABLE()   (T0CONbits.T08BIT = 1)
#define TIMER0_16BIT_REGISTER_MODE_ENABLE()  (T0CONbits.T08BIT = 0)

#define TIMER0_ENABLE()                      (T0CONbits.TMR0ON = 1)
#define TIMER0_DISABLE()                     (T0CONbits.TMR0ON = 0)

/******************************Timer1************************************/
#define TIMER1_TIMER_MODE_ENABLE()           (T1CONbits.TMR1CS = 0)
#define TIMER1_COUNTER_MODE_ENABLE()         (T1CONbits.TMR1CS = 1)

#define TIMER1_ENABLE()                      (T1CONbits.TMR1ON = 1)
#define TIMER1_DISABLE()                     (T1CONbits.TMR1ON = 0)

#define TIMER1_ASYNC_COUNTER_MODE_ENABLE()   (T1CONbits.T1SYNC = 1)
#define TIMER1_SYNC_COUNTER_MODE_ENABLE()    (T1CONbits.T1SYNC = 0) 

#define TIMER1_OSCILLATOR_ENABLE()           (T1CONbits.T1OSCEN = 1)   
#define TIMER1_OSCILLATOR_DISABLE()          (T1CONbits.T1OSCEN = 0) 

#define TIMER1_SYSTEM_CLK_STATUS()           (T1CONbits.T1RUN)   

#define TIMER1_RW_REG_16BIT_MODE_ENABLE()    (T1CONbits.RD16 = 1)
#define TIMER1_RW_REG_8BIT_MODE_ENABLE()     (T1CONbits.RD16 = 0)

/******************************Timer2************************************/
#define TIMER2_ENABLE()                        (T2CONbits.TMR2ON = 1)
#define TIMER2_DISABLE()                       (T2CONbits.TMR2ON = 0)

#define TIMER2_PRESCALAR_SELECT(_PRESCALAR)    (T2CONbits.T2CKPS = _PRESCALAR)  

#define TIMER2_POSTSCALAR_SELECT(_POSTSCALAR)  (T2CONbits.TOUTPS = _POSTSCALAR)

/******************************Timer3************************************/
#define TIMER3_TIMER_MODE_ENABLE()           (T3CONbits.TMR3CS = 0)
#define TIMER3_COUNTER_MODE_ENABLE()         (T3CONbits.TMR3CS = 1)

#define TIMER3_ENABLE()                      (T3CONbits.TMR3ON = 1)
#define TIMER3_DISABLE()                     (T3CONbits.TMR3ON = 0)

#define TIMER3_ASYNC_COUNTER_MODE_ENABLE()   (T3CONbits.T3SYNC = 1)
#define TIMER3_SYNC_COUNTER_MODE_ENABLE()    (T3CONbits.T3SYNC = 0) 
   
#define TIMER3_RW_REG_16BIT_MODE_ENABLE()    (T3CONbits.RD16 = 1)
#define TIMER3_RW_REG_8BIT_MODE_ENABLE()     (T3CONbits.RD16 = 0)

#define TIMER3_PRESCALAR_SELECT(_PRESCALAR)  (T3CONbits.T3CKPS = _PRESCALAR)
/* Section : Data Type Declarations */
typedef enum{
    TIMER0_PRESCALAR_DIV_BY_2 = 0,
    TIMER0_PRESCALAR_DIV_BY_4,            
    TIMER0_PRESCALAR_DIV_BY_8,
    TIMER0_PRESCALAR_DIV_BY_16, 
    TIMER0_PRESCALAR_DIV_BY_32,
    TIMER0_PRESCALAR_DIV_BY_64,            
    TIMER0_PRESCALAR_DIV_BY_128,
    TIMER0_PRESCALAR_DIV_BY_256,
    TIMER0_NO_PRESCALAR            
}Timer0_Prescalar_t;

typedef enum{
    TIMER1_NO_PRESCALAR =0,
    TIMER1_PRESCALAR_DIV_BY_2,
    TIMER1_PRESCALAR_DIV_BY_4,            
    TIMER1_PRESCALAR_DIV_BY_8             
}Timer1_Prescalar_t;

typedef enum{
    TIMER2_NO_PRESCALAR =0,
    TIMER2_PRESCALAR_DIV_BY_4,            
    TIMER2_PRESCALAR_DIV_BY_16             
}Timer2_Prescalar_t;


typedef enum{
    TIMER2_NO_POSTSCALAR =0,
    TIMER2_POSTCALAR_DIV_BY_2,            
    TIMER2_POSTCALAR_DIV_BY_3,
    TIMER2_POSTCALAR_DIV_BY_4,            
    TIMER2_POSTCALAR_DIV_BY_5,
    TIMER2_POSTCALAR_DIV_BY_6,            
    TIMER2_POSTCALAR_DIV_BY_7,
    TIMER2_POSTCALAR_DIV_BY_8,            
    TIMER2_POSTCALAR_DIV_BY_9,
    TIMER2_POSTCALAR_DIV_BY_10,            
    TIMER2_POSTCALAR_DIV_BY_11,
    TIMER2_POSTCALAR_DIV_BY_12,            
    TIMER2_POSTCALAR_DIV_BY_13,
    TIMER2_POSTCALAR_DIV_BY_14,            
    TIMER2_POSTCALAR_DIV_BY_15,
    TIMER2_POSTCALAR_DIV_BY_16            
}Timer2_Postscalar_t;

typedef enum{
    TIMER3_NO_PRESCALAR =0,
    TIMER3_PRESCALAR_DIV_BY_2,
    TIMER3_PRESCALAR_DIV_BY_4,            
    TIMER3_PRESCALAR_DIV_BY_8             
}Timer3_Prescalar_t;

typedef struct{
    #if INTERNAL_INTERRUPT_TIMER0_ENABLE == FEATURE_ENABLE
    void (*TIMER0_InterruptHandler)(void);
    interrupt_priority_levels priority;  
    #endif
    Timer0_Prescalar_t Prescalar_Value;
    uint16 timer0_preload_value;
    uint8 timer0_edge : 1;
    uint8 timer0_mode  : 1;
    uint8 timer0_register_size : 1;
    uint8 Reserved : 5;
}Timer0_t;

typedef struct{
    #if INTERNAL_INTERRUPT_TIMER1_ENABLE == FEATURE_ENABLE
    void (*TIMER1_InterruptHandler)(void);
    interrupt_priority_levels priority;  
    #endif
    uint16 timer1_preload_value;
    uint8 timer1_prescalar_value :2;
    uint8 timer1_counter_mode  : 1;
    uint8 timer1_osc_cfg  : 1;
    uint8 timer1_mode  : 1;
    uint8 timer1_reg_rw_mode :1;
    uint8 Reserved : 2;
}Timer1_t;

typedef struct{
    #if INTERNAL_INTERRUPT_TIMER2_ENABLE == FEATURE_ENABLE
    void (*TIMER2_InterruptHandler)(void);
    interrupt_priority_levels priority;  
    #endif
    uint8 timer2_preload_value;
    uint8 timer2_prescalar_value :2;
    uint8 timer2_postscalar_value :4;
    uint8 Reserved : 2;
}Timer2_t;

typedef struct{
    #if INTERNAL_INTERRUPT_TIMER3_ENABLE == FEATURE_ENABLE
    void (*TIMER3_InterruptHandler)(void);
    interrupt_priority_levels priority;  
    #endif
    uint16 timer3_preload_value;
    uint8 timer3_prescalar_value :2;
    uint8 timer3_counter_mode  : 1;
    uint8 timer3_mode  : 1;
    uint8 timer3_reg_rw_mode :1;    
    uint8 Reserved : 3;
}Timer3_t;
/* Section : Function Declarations */
STD_Return_t TIMER0_Init(const Timer0_t *timer_obj);
STD_Return_t TIMER0_Deinit(const Timer0_t *timer_obj);
STD_Return_t TIMER0_Write_Value(const Timer0_t *timer_obj, uint16 value);
STD_Return_t TIMER0_Read_Value(const Timer0_t *timer_obj, uint16* value);

STD_Return_t TIMER1_Init(const Timer1_t *timer_obj);
STD_Return_t TIMER1_Deinit(const Timer1_t *timer_obj);
STD_Return_t TIMER1_Write_Value(const Timer1_t *timer_obj, uint16 value);
STD_Return_t TIMER1_Read_Value(const Timer1_t *timer_obj, uint16* value);

STD_Return_t TIMER2_Init(const Timer2_t *timer_obj);
STD_Return_t TIMER2_Deinit(const Timer2_t *timer_obj);
STD_Return_t TIMER2_Write_Value(const Timer2_t *timer_obj, uint8 value);
STD_Return_t TIMER2_Read_Value(const Timer2_t *timer_obj, uint8* value);

STD_Return_t TIMER3_Init(const Timer3_t *timer_obj);
STD_Return_t TIMER3_Deinit(const Timer3_t *timer_obj);
STD_Return_t TIMER3_Write_Value(const Timer3_t *timer_obj, uint16 value);
STD_Return_t TIMER3_Read_Value(const Timer3_t *timer_obj, uint16* value);

#endif	/* TIMER_H */

