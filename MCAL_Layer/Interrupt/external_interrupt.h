/* 
 * File:   external_interrupt.h
 * Author: ENG TAREK
 */

#ifndef EXTERNAL_INTERRUPT_H
#define	EXTERNAL_INTERRUPT_H

/* Section : Includes */
#include "interrupt_cfg.h"

/* Section : Macro Declarations */

/* Section : Macro Function Declarations */
#if EXTERNAL_INTERRUPT_INTX_ENABLE == FEATURE_ENABLE
#define EXT_INT0_InterruptEnable()           (INTCONbits.INT0IE = 1)
#define EXT_INT0_InterruptDisable()          (INTCONbits.INT0IE = 0)
#define EXT_INT0_InterruptFlagClear()        (INTCONbits.INT0IF = 0)
#define EXT_INT0_RisingEdgeSet()             (INTCON2bits.INTEDG0 = 1)
#define EXT_INT0_FallingEdgeSet()            (INTCON2bits.INTEDG0 = 0)

#define EXT_INT1_InterruptEnable()           (INTCON3bits.INT1IE = 1)
#define EXT_INT1_InterruptDisable()          (INTCON3bits.INT1IE = 0)
#define EXT_INT1_InterruptFlagClear()        (INTCON3bits.INT1IF = 0)
#define EXT_INT1_RisingEdgeSet()             (INTCON2bits.INTEDG1 = 1)
#define EXT_INT1_FallingEdgeSet()            (INTCON2bits.INTEDG1 = 0)

#define EXT_INT2_InterruptEnable()           (INTCON3bits.INT2IE = 1)
#define EXT_INT2_InterruptDisable()          (INTCON3bits.INT2IE = 0)
#define EXT_INT2_InterruptFlagClear()        (INTCON3bits.INT2IF = 0)
#define EXT_INT2_RisingEdgeSet()             (INTCON2bits.INTEDG2 = 1)
#define EXT_INT2_FallingEdgeSet()            (INTCON2bits.INTEDG2 = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == FEATURE_ENABLE

#define EXT_INT1_HighPrioritySet()           (INTCON3bits.INT1IP = 1)
#define EXT_INT1_LowPrioritySet()            (INTCON3bits.INT1IP = 0)
#define EXT_INT2_HighPrioritySet()           (INTCON3bits.INT2IP = 1)
#define EXT_INT2_LowPrioritySet()            (INTCON3bits.INT2IP = 0)

#endif


#endif
#if EXTERNAL_INTERRUPT_ONCHANGE_ENABLE == FEATURE_ENABLE

#define EXT_RBx_InterruptEnable()           (INTCONbits.RBIE = 1)
#define EXT_RBx_InterruptDisable()          (INTCONbits.RBIE = 0)
#define EXT_RBx_InterruptFlagClear()        (INTCONbits.RBIF = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == FEATURE_ENABLE

#define EXT_RBx_HighPrioritySet()           (INTCON2bits.RBIP = 1)
#define EXT_RBX_LowPrioritySet()            (INTCON2bits.RBIP = 0)

#endif

#endif
/* Section : Data Type Declarations */
typedef enum{
    INTERRUPT_FALLING_EDGE,
    INTERRUPT_RISING_EDGE        
}interrupt_INTx_edge;
typedef enum{
    INTERRUPT_EXTERNAL_INT0,
    INTERRUPT_EXTERNAL_INT1,
    INTERRUPT_EXTERNAL_INT2        
}interrupt_INTx_src;

typedef struct{
    void (*EXT_InterruptHandler)(void);
    pin_config_t pin;
    interrupt_INTx_edge edge;
    interrupt_INTx_src  source;
    interrupt_priority_levels priority;
}interrupt_INTx_t;

typedef struct{
    void (*EXT_InterruptHandler_HIGH)(void);
    void (*EXT_InterruptHandler_LOW)(void);
    pin_config_t pin;
    interrupt_priority_levels priority;
}interrupt_RBx_t;

/* Section : Function Declarations */
STD_Return_t Interrupt_INTx_Init(const interrupt_INTx_t *int_obj);
STD_Return_t Interrupt_INTx_Deinit(const interrupt_INTx_t *int_obj);
STD_Return_t Interrupt_RBx_Init(const interrupt_RBx_t *int_obj);
STD_Return_t Interrupt_RBx_Deinit(const interrupt_RBx_t *int_obj);

#endif	/* EXTERNAL_INTERRUPT_H */

