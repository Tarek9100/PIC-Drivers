/* 
 * File:   button.h
 * Author: Tarek Wael
 */

#ifndef BUTTON_H
#define	BUTTON_H
#include "../../MCAL_Layer/GPIO/gpio.h"


/* Section : Macro Declarations */



/* Section : Macro Function Declarations */




/* Section : Data Type Declarations */
typedef enum {
  BUTTON_PRESSED,
  BUTTON_RELEASED
}button_state_t;

typedef enum{
    BUTTON_ACTIVE_LOW,
    BUTTON_ACTIVE_HIGH
}button_active_t;
typedef struct{
    uint8 port_name : 3;
    uint8 btn_pin : 3;
    uint8 btn_status : 1;
    uint8 btn_connection : 1;
}button_t;
/* Section : Function Declarations */

/* Section : Function Declarations */
STD_Return_t button_initialize(const button_t *btn);
STD_Return_t button_read_state(button_t *btn);


#endif	/* BUTTON_H */

