/* 
 * File:  keypad.h
 * Author: Tarek Wael
 */

#ifndef KEYPAD_H
#define	KEYPAD_H
#include "../../MCAL_Layer/GPIO/gpio.h"
#include "keypad_cfg.h"

/* Section : Macro Declarations */



/* Section : Macro Function Declarations */




/* Section : Data Type Declarations */

typedef struct{
    pin_config_t keypad_row_pins[KEYPAD_ROW_NUMBER];
    pin_config_t keypad_col_pins[KEYPAD_COLUMN_NUMBER];
}keypad_t;
/* Section : Function Declarations */

/* Section : Function Declarations */
STD_Return_t keypad_initialize(const keypad_t *keypad);
STD_Return_t keypad_get_value(keypad_t *keypad, uint8 *value);


#endif	/* KEYPAD_H */


