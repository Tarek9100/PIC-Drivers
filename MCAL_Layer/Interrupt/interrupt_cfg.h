/* 
 * File:   interrupt_cfg.h
 * Author: ENG TAREK
 *
 */

#ifndef INTERRUPT_CFG_H
#define	INTERRUPT_CFG_H

/* Section : Includes */
#include "../std_types.h"
#include <pic18f4620.h>
#include "../device_config.h"
#include "interrupt_gen_cfg.h"
#include "../GPIO/gpio.h"
/* Section : Macro Declarations */
#define INTERRUPT_ENABLE     1
#define INTERRUPT_DISABLE    0 

#define INTERRUPT_PRIORITY_ENABLE     1
#define INTERRUPT_PRIORITY_DISABLE    0 
/* Section : Macro Function Declarations */
#if INTERRUPT_PRIORITY_LEVELS_ENABLE ==  FEATURE_ENABLE
#define INTERRUPT_PriorityLevelsEnable()     (RCONbits.IPEN = 1)
#define INTERRUPT_PriorityLevelsDisable()    (RCONbits.IPEN = 0)

#define INTERRUPT_GlobalInterruptHighEnable()   (INTCONbits.GIEH = 1)
#define INTERRUPT_GlobalInterruptLowEnable()    (INTCONbits.GIEL = 1)

#define INTERRUPT_GlobalInterruptHighDisable()   (INTCONbits.GIEH = 0)
#define INTERRUPT_GlobalInterruptLowDisable()    (INTCONbits.GIEL = 0)

#else
#define INTERRUPT_GlobalInterruptEnable()     (INTCONbits.GIE = 1)
#define INTERRUPT_GlobalInterruptDisable()    (INTCONbits.GIE = 0)

#define INTERRUPT_PeripheralInterruptEnable()     (INTCONbits.PEIE = 1)
#define INTERRUPT_PeripheralInterruptDisable()    (INTCONbits.PEIE = 0)

#endif


/* Section : Data Type Declarations */
typedef enum{
    INTERRUPT_LOW_PRIORITY,
    INTERRUPT_HIGH_PRIORITY      
}interrupt_priority_levels;
/* Section : Function Declarations */



#endif	/* INTERRUPT_CFG_H */

