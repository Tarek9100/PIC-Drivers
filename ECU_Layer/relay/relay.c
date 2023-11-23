
/* 
 * File:   relay.h
 * Author: ENG TAREK
 *
 */

#include "relay.h"

/**
 * @brief : Initializes the assigned pin to OUTPUT then turns the relay off.
 * @param segment : pointer to the relay module configurations
 * @return Status of the function 
 *        STD_OK : The function done successfully.
 *        STD_NOK : The function had an issue while performing this action.
 *        STD_NULL_POINTER : NULL parameter was passed to the function.
 */
STD_Return_t relay_initialize(const relay_t *relay){
    STD_Return_t ret = STD_NOK;
    if (relay){
        pin_config_t pin_cfg = {.port = relay->relay_port,.pin = relay->relay_pin,.direction = OUTPUT,.logic = LOW };
        gpio_pin_initialize(&pin_cfg);
        }
    else{
        ret = STD_NULL_POINTER;
    }
    return ret;
}

/**
 * @brief : Turns the relays on.
 * @param segment : pointer to the relay module configurations
 * @return Status of the function 
 *        STD_OK : The function done successfully.
 *        STD_NOK : The function had an issue while performing this action.
 *        STD_NULL_POINTER : NULL parameter was passed to the function.
 */
STD_Return_t relay_on(const relay_t *relay){
        STD_Return_t ret = STD_NOK;
    if (relay){
        pin_config_t pin_cfg = {.port = relay->relay_port,.pin = relay->relay_pin,.direction = OUTPUT,.logic = HIGH };
        gpio_pin_write_value(&pin_cfg);
    }
    else{
        ret = STD_NULL_POINTER;
    }
    return ret;
}

/**
 * @brief : Turns the relays off.
 * @param segment : pointer to the relay module configurations
 * @return Status of the function 
 *        STD_OK : The function done successfully.
 *        STD_NOK : The function had an issue while performing this action.
 *        STD_NULL_POINTER : NULL parameter was passed to the function.
 */
STD_Return_t relay_off(const relay_t *relay){
        STD_Return_t ret = STD_NOK;
    if (relay){
        pin_config_t pin_cfg = {.port = relay->relay_port,.pin = relay->relay_pin,.direction = OUTPUT,.logic = LOW };
        gpio_pin_write_value(&pin_cfg);
    }
    else{
        ret = STD_NULL_POINTER;
    }
    return ret;
}
