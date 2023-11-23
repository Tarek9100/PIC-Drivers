/* 
 * File:   seven_segments.h
 * Author: Tarek Wael
 *
 */

#ifndef SEVEN_SEGMENTS_H
#define	SEVEN_SEGMENTS_H



/* Section : Includes */

#include "../../MCAL_Layer/GPIO/gpio.h"

/* Section : Macro Declarations */

#define SEGMENT_PIN0 0
#define SEGMENT_PIN1 1
#define SEGMENT_PIN2 2
#define SEGMENT_PIN3 3
#define SEGMENT_MAX_NUMBER  9
/* Section : Macro Function Declarations */




/* Section : Data Type Declarations */

typedef enum{
    SEGMENT_COMMON_ANODE,
    SEGMENT_COMMON_CATHODE
}segment_type_t;
typedef struct{
    pin_config_t segment_pins[4];
    segment_type_t segment_type;
}segment_t;

/* Section : Function Declarations */
STD_Return_t seven_segment_initialize(const segment_t *segment);
STD_Return_t seven_segment_write_number(segment_t *segment,const uint8 number);




#endif	/* SEVEN_SEGMENTS_H*/



