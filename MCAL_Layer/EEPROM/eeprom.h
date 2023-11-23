/* 
 * File:   eeprom.h
 * Author: Tarek Wael
 *
 */

#ifndef EEPROM_H
#define	EEPROM_H
/* Section : Includes */
#include "../std_types.h"
#include <pic18f4620.h>
#include "../Interrupt/internal_interrupt.h"
/* Section : Macro Declarations */



/* Section : Macro Function Declarations */
#define ACCESS_EEPROM()           (EECON1bits.EEPGD=0)
#define ACCESS_FLASH()            (EECON1bits.EEPGD=1)


/* Section : Data Type Declarations */


/* Section : Function Declarations */
STD_Return_t EEPROM_Write_Byte(uint16 byteAddress,uint8 byteData);
STD_Return_t EEPROM_Read_Byte(uint16 byteAddress,uint8 *byteData);
#endif	/* EEPROM_H */

