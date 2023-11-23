/* 
 * File:   STD_Types.h
 * Author: ENG TAREK
 *
 */

#ifndef STD_TYPES_H
#define	STD_TYPES_H


/* Section : Includes */
#include "Compiler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* Section : Macro Declarations */
#define STD_HIGH        1
#define STD_LOW         0   
#define _XTAL_FREQ   8000000UL

/* Section : Macro Function Declarations */




/* Section : Data Type Declarations */
typedef unsigned char         uint8;
typedef unsigned short        uint16;
typedef unsigned long         uint32;
typedef signed char           sint8;
typedef signed short          sint16;
typedef signed long           sint32;
typedef float                 float32;
typedef double                float64;

typedef enum{
    STD_OK,
    STD_NOK,
    STD_NULL_POINTER        
}STD_Return_t;

/* Section : Function Declarations */

#endif	/* STD_TYPES_H */
