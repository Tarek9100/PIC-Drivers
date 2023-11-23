
/* 
 * File:   gpio.c
 * Author: Tarek Wael
 *
 */
#include "gpio.h"

volatile uint8 *tris_registers[]={&TRISA,&TRISB,&TRISC,&TRISD,&TRISE};
volatile uint8 *lat_registers[]={&LATA,&LATB,&LATC,&LATD,&LATE};
volatile uint8 *port_registers[]={&PORTA,&PORTB,&PORTC,&PORTD,&PORTE};

STD_Return_t gpio_pin_initialize(const pin_config_t *pin_config){
    STD_Return_t Local_u8_Return = STD_NOK;
    if((NULL == pin_config))
    {   
        Local_u8_Return = STD_NULL_POINTER;
    }
    else{
        if((pin_config->pin > PIN_MAX_NUM) || (pin_config->port > PORT_MAX_NUM)){
            Local_u8_Return = STD_NOK;
        }
        else{
        Local_u8_Return = STD_OK;
        switch(pin_config->direction){
            case OUTPUT: 
                CLR_BIT(*tris_registers[pin_config->port],pin_config->pin);
                if(pin_config->logic == HIGH){
                    SET_BIT(*lat_registers[pin_config->port],pin_config->pin);
                }
                else{
                    CLR_BIT(*lat_registers[pin_config->port],pin_config->pin);
                }
            break;
                
            case INPUT:  SET_BIT(*tris_registers[pin_config->port],pin_config->pin);break;
            
            default: Local_u8_Return = STD_NOK;
        }
        }              
  
    }

return Local_u8_Return;
}

STD_Return_t gpio_pin_get_value(const pin_config_t *pin_config, logic_t *value){
    STD_Return_t Local_u8_Return = STD_NOK;
    if((NULL == pin_config) || (NULL == value))
    {
         Local_u8_Return = STD_NULL_POINTER;
       
    }
    else{
        if((pin_config->pin > PIN_MAX_NUM) || (pin_config->port > PORT_MAX_NUM)){
            Local_u8_Return = STD_NOK;
        }
        else{
        Local_u8_Return = STD_OK;
        *value = READ_BIT(*port_registers[pin_config->port],pin_config->pin);
        }
    }


return Local_u8_Return;    
}
STD_Return_t gpio_pin_write_value(const pin_config_t *pin_config){
    STD_Return_t Local_u8_Return = STD_NOK;
    if(pin_config)
    {
        if((pin_config->pin > PIN_MAX_NUM) || (pin_config->port > PORT_MAX_NUM)){
            Local_u8_Return = STD_NOK;
        }
        else{
        Local_u8_Return = STD_OK;
        if(pin_config->direction == OUTPUT){
        switch(pin_config->logic){
            case HIGH: 
                SET_BIT(*lat_registers[pin_config->port], pin_config->pin);break;         
            case LOW:
                CLR_BIT(*lat_registers[pin_config->port], pin_config->pin);break;
            default: Local_u8_Return = STD_NOK;
        }
        }
        else{
            Local_u8_Return = STD_NOK;
        }
        }
    }
    else{
        Local_u8_Return = STD_NULL_POINTER;  
    }
return Local_u8_Return;    
}
STD_Return_t gpio_pin_toggle_value(const pin_config_t *pin_config){
    STD_Return_t Local_u8_Return = STD_NOK;
    if(pin_config)
    {
        if((pin_config->pin > PIN_MAX_NUM) || (pin_config->port > PORT_MAX_NUM)){
            Local_u8_Return = STD_NOK;
        }
        else{
        Local_u8_Return = STD_OK;
        if(pin_config->direction == OUTPUT){
 
           TOG_BIT(*lat_registers[pin_config->port], pin_config->pin);
        }
        else{
            Local_u8_Return = STD_NOK;
        }
        }
    }
    else{
        Local_u8_Return = STD_NULL_POINTER;  
    }
return Local_u8_Return;    
}

STD_Return_t gpio_port_direction_initialize(port_ID_t port, direction_t direction){
    STD_Return_t Local_u8_Return = STD_NOK;
    if((port > PORT_MAX_NUM) || (direction > 1))
    {   
        Local_u8_Return = STD_NOK;
    }
    else{
        Local_u8_Return = STD_OK;
        switch(direction){
            case OUTPUT: 
               *tris_registers[port] = 0x00;
               *lat_registers[port] = 0x00;
            break;
                
            case INPUT:  *tris_registers[port] = 0xFF; 
            break;
            
            default: Local_u8_Return = STD_NOK;
        }           
    }
return Local_u8_Return;
}
STD_Return_t gpio_port_get_value(port_ID_t port, uint8 *value){
    STD_Return_t Local_u8_Return = STD_NOK;
    if((port > PORT_MAX_NUM))
    {
         Local_u8_Return = STD_NOK;  
    }
    else{
        Local_u8_Return = STD_OK;
        *value = *port_registers[port];
        }
return Local_u8_Return;    
}
STD_Return_t gpio_port_write_value(port_ID_t port, uint8 value){
STD_Return_t Local_u8_Return = STD_NOK;
    if(port > PORT_MAX_NUM)
    {
    Local_u8_Return = STD_NOK;
    }
        else{
        Local_u8_Return = STD_OK;
        *lat_registers[port] = value;
        }
return Local_u8_Return;    
}
STD_Return_t gpio_port_toggle_value(port_ID_t port){
STD_Return_t Local_u8_Return = STD_NOK;
    if(port > PORT_MAX_NUM)
    {
        Local_u8_Return = STD_NOK;
    }
    else{
      Local_u8_Return = STD_OK;  
      (*lat_registers[port])^= 0xFF;         
        }

return Local_u8_Return;    
}