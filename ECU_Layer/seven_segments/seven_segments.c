/* 
 * File:   seven_segments.h
 * Author: ENG TAREK
 *
 */

#include "seven_segments.h"

/**
 * @brief : Initializes the assigned pins to OUTPUT then turns the 7-segments off.
 * @param segment : pointer to the 7-segments module configurations
 * @return Status of the function 
 *        STD_OK : The function done successfully.
 *        STD_NOK : The function had an issue while performing this action.
 *        STD_NULL_POINTER : NULL parameter was passed to the function.
 */
STD_Return_t seven_segment_initialize(const segment_t *segment){
    STD_Return_t ret = STD_NOK;
    if (segment){
    ret = gpio_pin_initialize(&(segment->segment_pins[0]));
    ret = gpio_pin_initialize(&(segment->segment_pins[1]));  
    ret = gpio_pin_initialize(&(segment->segment_pins[2]));   
    ret = gpio_pin_initialize(&(segment->segment_pins[3]));
     }
    else{
        ret = STD_NULL_POINTER;
    }
    return ret;
}

/**
 * @brief : Writes a number to the 7-segments to be displayed.
 * @param segment : pointer to the 7-segments module configurations
 * @param number : number written on 7-segments
 * @return Status of the function 
 *        STD_OK : The function done successfully.
 *        STD_NOK : The function had an issue while performing this action.
 *        STD_NULL_POINTER : NULL parameter was passed to the function.
 */
STD_Return_t seven_segment_write_number(segment_t *segment,const uint8 number){
        STD_Return_t ret = STD_NOK;
    if (segment){
        if(number <= SEGMENT_MAX_NUMBER){
        ret = STD_OK;   
        uint8 i = 0;
        for(;i<4;i++){
            if (HIGH == ((number >> i) & 1)){
                segment->segment_pins[i].logic = HIGH;
            }
            else{
               segment->segment_pins[i].logic = LOW; 
            }
    
            gpio_pin_write_value(&(segment->segment_pins[i]));
        }
        }
    }
    else{
        ret = STD_NULL_POINTER;
    }
    return ret;
}
