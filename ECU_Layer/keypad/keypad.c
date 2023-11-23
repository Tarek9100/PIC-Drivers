/* 
 * File:   keypad.c
 * Author: Tarek Wael
 */


#include "keypad.h"
static const uint8 kpd_values[KEYPAD_ROW_NUMBER][KEYPAD_COLUMN_NUMBER] ={
    {'7','8','9','/'},
    {'4','5','6','*'},
    {'1','2','3','-'},
    {'#','0','=','+'}
};
/**
 * @brief : Initializes the assigned keypad pins.
 * @param relay : pointer to the keypad module configurations
 * @return Status of the function 
 *        STD_OK : The function done successfully.
 *        STD_NOK : The function had an issue while performing this action.
 *        STD_NULL_POINTER : NULL parameter was passed to the function.
 */
STD_Return_t keypad_initialize(const keypad_t *keypad){
    
STD_Return_t ret = STD_NOK;
uint8 counter = 0;
    if (keypad){
        for(counter=0;counter < KEYPAD_ROW_NUMBER; counter++)
        ret = gpio_pin_initialize(&(keypad->keypad_row_pins[counter]));
        for(counter=0;counter < KEYPAD_COLUMN_NUMBER; counter++)
        ret = gpio_pin_initialize(&(keypad->keypad_col_pins[counter]));
    }
    else{
        ret = STD_NULL_POINTER;
    }
    return ret;
}

/**
 * @brief : Get the value that has been pressed.
 * @param keypad : pointer to the keypad module configurations of type keypad_t
 * @param value : the value returned of type uint8
 * @return Status of the function 
 *        STD_OK : The function done successfully.
 *        STD_NOK : The function had an issue while performing this action.
 *        STD_NULL_POINTER : NULL parameter was passed to the function.
 */
STD_Return_t keypad_get_value(keypad_t *keypad, uint8 *value){
STD_Return_t ret = STD_NOK;
logic_t column_logic=0;
uint8 counter1=0, counter2 =0, counter3 =0;
    if ((NULL == keypad) || (NULL == value)){
        ret = STD_NULL_POINTER;
    }
    else{
        for(counter1=0;counter1<KEYPAD_ROW_NUMBER;counter1++){
            for(counter2=0;counter2<KEYPAD_ROW_NUMBER;counter2++){
                keypad->keypad_row_pins[counter2].logic = LOW;
                ret = gpio_pin_write_value(&(keypad->keypad_row_pins[counter2]));
            }
                keypad->keypad_row_pins[counter1].logic = HIGH;
                ret = gpio_pin_write_value(&(keypad->keypad_row_pins[counter1]));
                
        
        for(counter3=0;counter3<KEYPAD_COLUMN_NUMBER;counter3++){
            ret = gpio_pin_get_value(&(keypad->keypad_col_pins[counter3]),&column_logic);
            if(HIGH == column_logic){
                *value = kpd_values[counter1][counter3];
            }   
        }
    }
    }
    return ret;    
}