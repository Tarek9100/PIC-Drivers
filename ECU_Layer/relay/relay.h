/* 
 * File:   relay.h
 * Author: ENG TAREK
 *
 */

#ifndef RELAY_H
#define	RELAY_H



/* Section : Includes */

#include "../../MCAL_Layer/GPIO/gpio.h"

/* Section : Macro Declarations */



/* Section : Macro Function Declarations */




/* Section : Data Type Declarations */
typedef enum{
 RELAY_ON,
 RELAY_OFF
}relay_status_t;
typedef struct{
    uint8 relay_port : 4;
    uint8 relay_pin : 3;
    uint8 relay_status : 1;
}relay_t;

/* Section : Function Declarations */
STD_Return_t relay_initialize(const relay_t *relay);
STD_Return_t relay_on(const relay_t *relay);
STD_Return_t relay_off(const relay_t *relay);



#endif	/* RELAY_H */


