/* 
 * File:   dc_motor.h
 * Author: Tarek Wael
 */

#ifndef DC_MOTOR_H
#define	DC_MOTOR_H
#include "../../MCAL_Layer/GPIO/gpio.h"


/* Section : Macro Declarations */


/* Section : Macro Function Declarations */




/* Section : Data Type Declarations */
typedef enum{
 MOTOR_ON,
 MOTOR_OFF
}dc_motor_status_t;



typedef struct{
   pin_config_t dc_motor[2];
}dc_motor_t;
/* Section : Function Declarations */

STD_Return_t dc_motor_initialize(const dc_motor_t *dc_motor);
STD_Return_t dc_motor_clockwise(dc_motor_t *dc_motor);
STD_Return_t dc_motor_anticlockwise(dc_motor_t *dc_motor);
STD_Return_t dc_motor_stop(dc_motor_t *dc_motor);



#endif	/* DC_MOTOR_H */

