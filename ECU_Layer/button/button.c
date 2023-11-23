/* 
 * File:   button.h
 * Author: Tarek Wael
 */
#include "button.h"

STD_Return_t button_initialize(const button_t *btn){
  STD_Return_t ret = STD_NOK;
if(btn){
    ret = STD_OK;
     pin_config_t pin_cfg ={
    .port = btn->port_name,
    .pin = btn->btn_pin,
    .direction = INPUT,
    .logic = LOW
    };
    ret = gpio_pin_initialize(&pin_cfg);
}  
else{
    ret = STD_NULL_POINTER;
}
  return ret;
}
STD_Return_t button_read_state(button_t *btn){
   STD_Return_t ret = STD_NOK;
   logic_t value;
if(btn){
    ret = STD_OK;
     pin_config_t pin_cfg ={
    .port = btn->port_name,
    .pin = btn->btn_pin,
    .direction = INPUT,
    .logic = LOW
    };
    ret = gpio_pin_get_value(&pin_cfg,&value);
    if(btn->btn_connection == BUTTON_ACTIVE_HIGH){
        if(HIGH == value){
            btn->btn_status = BUTTON_PRESSED;
        }
        else{
            btn->btn_status = BUTTON_RELEASED;
        }
    }
    else if(btn->btn_connection == BUTTON_ACTIVE_LOW){
              if(HIGH == value){
            btn->btn_status = BUTTON_RELEASED;      
        }
        else{
            btn->btn_status = BUTTON_PRESSED;
        } 
        }    
}  
else{
    ret = STD_NULL_POINTER;
}
  return ret;
}  

