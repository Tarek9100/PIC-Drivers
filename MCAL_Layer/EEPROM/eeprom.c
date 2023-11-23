/* 
 * File:   eeprom.c
 * Author: Tarek Wael
 *
 */
#include "eeprom.h"

/**
 * brief : function writes a byte to a specific address in the EEPROM
 * @param byteAddress : the address of the byte to write in 
 * @param byteData : the data needed to be written 
 * @return Status of the function 
 *        STD_OK : The function done successfully.
 *        STD_NOK : The function had an issue while performing this action.
 *        STD_NULL_POINTER : NULL parameter was passed to the function.
 */
STD_Return_t EEPROM_Write_Byte(uint16 byteAddress,uint8 byteData){
    STD_Return_t ret = STD_OK;
    uint8 global_interrupt_status = 0;
    global_interrupt_status = INTCONbits.GIE;
    EEADRH  = (uint8)((byteAddress >> 8) & 0x3);
    EEADR = (uint8)(byteAddress & 0xFF);
    EEDATA = byteData;
    ACCESS_EEPROM();
    EECON1bits.CFGS = 0;
    EECON1bits.WREN = 1;
    INTERRUPT_GlobalInterruptDisable();
    /*Unlocking mechanism : 0x55 -> 0xAA*/
    EECON2 = 0X55;
    EECON2 = 0XAA;
    EECON1bits.WR = 1;
    while(EECON1bits.WR);
    EECON1bits.WREN = 0;
    INTCONbits.GIE = global_interrupt_status;
  return ret;  
}

/**
 * brief : function reads a byte at a specific address in the EEPROM
 * @param byteAddress : the address of the byte needed to be read 
 * @param byteData : a pointer to uint8 that receives the data needed to be read
 * @return Status of the function 
 *        STD_OK : The function done successfully.
 *        STD_NOK : The function had an issue while performing this action.
 *        STD_NULL_POINTER : NULL parameter was passed to the function.
 */
STD_Return_t EEPROM_Read_Byte(uint16 byteAddress,uint8 *byteData){
    STD_Return_t ret = STD_NOK;
    if(byteData){
        ret = STD_OK;
        EEADRH  = (uint8)((byteAddress >> 8) & 0x3);
        EEADR = (uint8)(byteAddress & 0xFF); 
        ACCESS_EEPROM();
        EECON1bits.CFGS = 0;     
        EECON1bits.RD = 1;
        NOP();
        NOP();
        *byteData = EEDATA;
    }
  return ret; 
}