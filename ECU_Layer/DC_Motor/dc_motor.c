/* 
 * File:   dc_motor.c
 * Author: Tarek Wael
 */
#include "dc_motor.h"


/**
 * @brief : Initializes the assigned motor control pins to OUTPUT.
 * @param dc_motor : pointer to the motor module configurations
 * @return Status of the function 
 *        STD_OK : The function done successfully.
 *        STD_NOK : The function had an issue while performing this action.
 *        STD_NULL_POINTER : NULL parameter was passed to the function.
 */
STD_Return_t dc_motor_initialize(const dc_motor_t *dc_motor){
    STD_Return_t ret = STD_NOK;
    if (dc_motor){  
     ret = gpio_pin_initialize(&(dc_motor->dc_motor[0]));
     ret = gpio_pin_initialize(&(dc_motor->dc_motor[1]));
    }
    else{
        ret = STD_NULL_POINTER;
    }
    return ret;
}


/**
 * @brief : Turns motor clockwise.
 * @param dc_motor : pointer to the motor module configurations
 * @return Status of the function 
 *        STD_OK : The function done successfully.
 *        STD_NOK : The function had an issue while performing this action.
 *        STD_NULL_POINTER : NULL parameter was passed to the function.
 */
STD_Return_t dc_motor_clockwise( dc_motor_t *dc_motor){
    STD_Return_t ret = STD_NOK;
    if (dc_motor){
         dc_motor->dc_motor[0].logic = HIGH;
         dc_motor->dc_motor[1].logic = LOW;
     ret = gpio_pin_initialize(&(dc_motor->dc_motor[0]));
     ret = gpio_pin_initialize(&(dc_motor->dc_motor[1]));
    }
    else{
        ret = STD_NULL_POINTER;
    }
    return ret;
}  


/**
 * @brief : Turns motor anti-clockwise.
 * @param dc_motor : pointer to the motor module configurations
 * @return Status of the function 
 *        STD_OK : The function done successfully.
 *        STD_NOK : The function had an issue while performing this action.
 *        STD_NULL_POINTER : NULL parameter was passed to the function.
 */
STD_Return_t dc_motor_anticlockwise(dc_motor_t *dc_motor){
    STD_Return_t ret = STD_NOK;
    if (dc_motor){
         dc_motor->dc_motor[0].logic = LOW;
         dc_motor->dc_motor[1].logic = HIGH;
     ret = gpio_pin_initialize(&(dc_motor->dc_motor[0]));
     ret = gpio_pin_initialize(&(dc_motor->dc_motor[1]));
    }
    else{
        ret = STD_NULL_POINTER;
    }
    return ret;
}


/**
 * @brief : Stops motor.
 * @param dc_motor : pointer to the motor module configurations
 * @return Status of the function 
 *        STD_OK : The function done successfully.
 *        STD_NOK : The function had an issue while performing this action.
 *        STD_NULL_POINTER : NULL parameter was passed to the function.
 */
STD_Return_t dc_motor_stop(dc_motor_t *dc_motor){
    STD_Return_t ret = STD_NOK;
    if (dc_motor){
         dc_motor->dc_motor[0].logic = HIGH;
         dc_motor->dc_motor[1].logic = HIGH;
     ret = gpio_pin_initialize(&(dc_motor->dc_motor[0]));
     ret = gpio_pin_initialize(&(dc_motor->dc_motor[1]));
    }
    else{
        ret = STD_NULL_POINTER;
    }
    return ret;
}
