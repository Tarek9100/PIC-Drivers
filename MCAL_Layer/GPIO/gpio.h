/* 
 * File:   gpio.h
 * Author: Tarek Wael
 *
 */

#ifndef GPIO_H
#define	GPIO_H

/* Section : Includes */
#include "../std_types.h"
#include <pic18f4620.h>
#include "../device_config.h"

/* Section : Macro Declarations */
#define PIN_MAX_NUM         7
#define PORT_MAX_NUM        4

/* Section : Macro Function Declarations */

#define HWREG8(_X)   (*((volatile uint8 *)(_X)))   

#define SET_BIT(REG,POS)           (REG |= (1 << POS))
#define CLR_BIT(REG,POS)           (REG &= ~(1 << POS))
#define TOG_BIT(REG,POS)           (REG ^= (1 << POS))
#define READ_BIT(REG,POS)           ((REG >> POS) & 1)


/* Section : Data Type Declarations */
typedef enum{
    LOW=0,
    HIGH
}logic_t;
typedef enum{
    OUTPUT=0,
    INPUT
}direction_t;
typedef enum{
   PIN0=0,
   PIN1,   
   PIN2,
   PIN3,
   PIN4,
   PIN5,
   PIN6,
   PIN7,
}pin_ID_t;
typedef enum{
   PORTA_ID=0,
   PORTB_ID,
   PORTC_ID,
   PORTD_ID,
   PORTE_ID,        
}port_ID_t;

typedef struct{
   uint8 port:3;
   uint8 pin:3;
   uint8 direction:1;
   uint8 logic:1;
}pin_config_t;
/* Section : Function Declarations */
STD_Return_t gpio_pin_initialize(const pin_config_t *pin_config);
STD_Return_t gpio_pin_get_value(const pin_config_t *pin_config, logic_t *value);
STD_Return_t gpio_pin_write_value(const pin_config_t *pin_config);
STD_Return_t gpio_pin_toggle_value(const pin_config_t *pin_config);

STD_Return_t gpio_port_direction_initialize(port_ID_t port, direction_t direction);
STD_Return_t gpio_port_get_value(port_ID_t port, uint8 *value);
STD_Return_t gpio_port_write_value(port_ID_t port, uint8 value);
STD_Return_t gpio_port_toggle_value(port_ID_t port);
#endif	/* GPIO_H */

