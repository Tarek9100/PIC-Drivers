/* 
 * File:   led.h
 * Author: ENG TAREK
 *
 */

#ifndef LED_H
#define	LED_H

/* Section : Includes */
#include "../../MCAL_Layer/GPIO/gpio.h"
/* Section : Macro Declarations */



/* Section : Macro Function Declarations */




/* Section : Data Type Declarations */
typedef enum{
 LED_ON,
 LED_OFF
}led_status_t;
typedef struct{
    uint8 port_name : 4;
    uint8 pin : 3;
    uint8 led_status : 1;
}led_t;

/* Section : Function Declarations */
STD_Return_t led_initialize(const led_t *led);
STD_Return_t led_on(const led_t *led);
STD_Return_t led_off(const led_t *led);
STD_Return_t led_toggle(const led_t *led);


#endif	/* LED_H */
