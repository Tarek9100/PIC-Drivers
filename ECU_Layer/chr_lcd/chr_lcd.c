/* 
 * File:   chr_lcd.c
 * Author: Tarek Wael
 */
#include "chr_lcd.h"
static STD_Return_t lcd_send_4bits(chr_lcd_4bit_t *lcd, uint8 data);
static STD_Return_t lcd_send_enable_signal_4bits(chr_lcd_4bit_t *lcd);
static STD_Return_t lcd_send_enable_signal_8bits(chr_lcd_8bit_t *lcd);
static STD_Return_t lcd_8bit_set_cursor(chr_lcd_8bit_t *lcd,uint8 row,uint8 column);
static STD_Return_t lcd_4bit_set_cursor(chr_lcd_4bit_t *lcd,uint8 row,uint8 column);
STD_Return_t lcd_4bit_initialize(chr_lcd_4bit_t *lcd){
  STD_Return_t ret = STD_NOK;

    if (lcd){
        lcd->lcd_rs.direction = OUTPUT;lcd->lcd_rs.logic =LOW;
        lcd->lcd_en.direction = OUTPUT;lcd->lcd_en.logic =LOW;
        lcd->lcd_data[0].direction = OUTPUT;lcd->lcd_data[0].logic =LOW;
        lcd->lcd_data[1].direction = OUTPUT;lcd->lcd_data[1].logic =LOW;
        lcd->lcd_data[2].direction = OUTPUT;lcd->lcd_data[2].logic =LOW;
        lcd->lcd_data[3].direction = OUTPUT;lcd->lcd_data[3].logic =LOW;
        ret = gpio_pin_initialize(&(lcd->lcd_rs));
        ret = gpio_pin_initialize(&(lcd->lcd_en));
        ret = gpio_pin_initialize(&(lcd->lcd_data[0]));
        ret = gpio_pin_initialize(&(lcd->lcd_data[1]));
        ret = gpio_pin_initialize(&(lcd->lcd_data[2]));
        ret = gpio_pin_initialize(&(lcd->lcd_data[3]));
        __delay_ms(20);
        ret = lcd_4bit_send_command(lcd,LCD_8BIT_MODE_2_LINE);
        __delay_ms(4);
        ret = lcd_4bit_send_command(lcd,LCD_8BIT_MODE_2_LINE);
        __delay_us(150);
        ret = lcd_4bit_send_command(lcd,LCD_8BIT_MODE_2_LINE); 
        ret = lcd_4bit_send_command(lcd,LCD_CLEAR);
        ret = lcd_4bit_send_command(lcd,LCD_RETURN_HOME);
        ret = lcd_4bit_send_command(lcd,LCD_ENTRY_MODE_INC_SHIFT_OFF);
        ret = lcd_4bit_send_command(lcd,LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF);
        ret = lcd_4bit_send_command(lcd,LCD_4BIT_MODE_2_LINE); 
        ret = lcd_4bit_send_command(lcd,LCD_DDRAM_START); 
        
    }
    else{
        ret = STD_NULL_POINTER;
    }
    return ret;   
}   

STD_Return_t lcd_4bit_send_command(chr_lcd_4bit_t *lcd, uint8 command){
  STD_Return_t ret = STD_NOK;

    if (lcd){
        lcd->lcd_rs.logic = LOW;
        ret = gpio_pin_write_value(&(lcd->lcd_rs));
        ret = lcd_send_4bits(lcd, command >> 4);
        ret = lcd_send_enable_signal_4bits(lcd);
        ret = lcd_send_4bits(lcd, command);
        ret = lcd_send_enable_signal_4bits(lcd);        
    }
    else{
        ret = STD_NULL_POINTER;
    }
    return ret;   
}   

STD_Return_t lcd_4bit_send_char_data(chr_lcd_4bit_t *lcd, uint8 data){
  STD_Return_t ret = STD_NOK;

    if (lcd){
        lcd->lcd_rs.logic = HIGH;
        ret = gpio_pin_write_value(&(lcd->lcd_rs));
        ret = lcd_send_4bits(lcd, data >> 4);
        ret = lcd_send_enable_signal_4bits(lcd);
        ret = lcd_send_4bits(lcd, data);
        ret = lcd_send_enable_signal_4bits(lcd); 
    }
    else{
        ret = STD_NULL_POINTER;
    }
    return ret;   
}   

STD_Return_t lcd_4bit_send_char_data_pos(const chr_lcd_4bit_t *lcd, uint8 row, uint8 column, uint8 data){
  STD_Return_t ret = STD_NOK;

    if (lcd){
        ret = lcd_4bit_set_cursor(lcd, row,column);
        ret = lcd_4bit_send_char_data(lcd, data);
    }
    else{
        ret = STD_NULL_POINTER;
    }
    return ret;    
}   

STD_Return_t lcd_4bit_send_string(const chr_lcd_4bit_t *lcd, uint8 *str){
  STD_Return_t ret = STD_NOK;

    if ((NULL == lcd) || (NULL == str)){
        ret = STD_NULL_POINTER;
    }
    else{

        while(*str){
            ret  = lcd_4bit_send_char_data(lcd,*str++);
        }
    }
    return ret;   
}   

STD_Return_t lcd_4bit_send_string_pos(const chr_lcd_4bit_t *lcd, uint8 row, uint8 column, uint8 *str){
  STD_Return_t ret = STD_NOK;

    if ((NULL == lcd) || (NULL == str)){
        ret = STD_NULL_POINTER;
    }
    else{
        ret = lcd_4bit_set_cursor(lcd, row,column);
        ret = lcd_4bit_send_string(lcd,str);
    }
    return ret;   
}   

STD_Return_t lcd_4bit_send_custom_char(const chr_lcd_4bit_t *lcd, uint8 row, uint8 column,const uint8 chr[], uint8 mem_pos){
  STD_Return_t ret = STD_NOK;
  uint8 i=0;
    if ((NULL == lcd) || (NULL == chr)){
        ret = STD_NULL_POINTER;
    }
    else{
        ret = lcd_4bit_send_command(lcd,(LCD_CGRAM_START+mem_pos*8));
        for(i=0;i<8;i++){
            lcd_4bit_send_char_data(lcd,chr[i]);
        }
        lcd_4bit_send_char_data_pos(lcd,row,column,mem_pos);
    }
    return ret;  
}   

STD_Return_t lcd_8bit_initialize(chr_lcd_8bit_t *lcd){
  STD_Return_t ret = STD_NOK;

    if (lcd){
        lcd->lcd_rs.direction = OUTPUT;lcd->lcd_rs.logic =LOW;
        lcd->lcd_en.direction = OUTPUT;lcd->lcd_en.logic =LOW;
        lcd->lcd_data[0].direction = OUTPUT;lcd->lcd_data[0].logic =LOW;
        lcd->lcd_data[1].direction = OUTPUT;lcd->lcd_data[1].logic =LOW;
        lcd->lcd_data[2].direction = OUTPUT;lcd->lcd_data[2].logic =LOW;
        lcd->lcd_data[3].direction = OUTPUT;lcd->lcd_data[3].logic =LOW;
        lcd->lcd_data[4].direction = OUTPUT;lcd->lcd_data[4].logic =LOW;
        lcd->lcd_data[5].direction = OUTPUT;lcd->lcd_data[5].logic =LOW;
        lcd->lcd_data[6].direction = OUTPUT;lcd->lcd_data[6].logic =LOW;
        lcd->lcd_data[7].direction = OUTPUT;lcd->lcd_data[7].logic =LOW;
        ret = gpio_pin_initialize(&(lcd->lcd_rs));
        ret = gpio_pin_initialize(&(lcd->lcd_en));
        ret = gpio_pin_initialize(&(lcd->lcd_data[0]));
        ret = gpio_pin_initialize(&(lcd->lcd_data[1]));
        ret = gpio_pin_initialize(&(lcd->lcd_data[2]));
        ret = gpio_pin_initialize(&(lcd->lcd_data[3]));
        ret = gpio_pin_initialize(&(lcd->lcd_data[4]));
        ret = gpio_pin_initialize(&(lcd->lcd_data[5]));
        ret = gpio_pin_initialize(&(lcd->lcd_data[6]));
        ret = gpio_pin_initialize(&(lcd->lcd_data[7]));
        __delay_ms(20);
        ret = lcd_8bit_send_command(lcd,LCD_8BIT_MODE_2_LINE);
        __delay_ms(5);
        ret = lcd_8bit_send_command(lcd,LCD_8BIT_MODE_2_LINE);
        __delay_us(150);
        ret = lcd_8bit_send_command(lcd,LCD_8BIT_MODE_2_LINE); 
        ret = lcd_8bit_send_command(lcd,LCD_CLEAR);
        ret = lcd_8bit_send_command(lcd,LCD_RETURN_HOME);
        ret = lcd_8bit_send_command(lcd,LCD_ENTRY_MODE_INC_SHIFT_OFF);
        ret = lcd_8bit_send_command(lcd,LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF);
        ret = lcd_8bit_send_command(lcd,LCD_8BIT_MODE_2_LINE); 
        ret = lcd_8bit_send_command(lcd,LCD_DDRAM_START); 
    }
    else{
        ret = STD_NULL_POINTER;
    }
    return ret;    
}   

STD_Return_t lcd_8bit_send_command(chr_lcd_8bit_t *lcd, uint8 command){
  STD_Return_t ret = STD_NOK;
  uint8 i=0;
    if (lcd){
        lcd->lcd_rs.logic = LOW;
        ret = gpio_pin_write_value(&(lcd->lcd_rs));
        for(i=0;i<8;i++){
        lcd->lcd_data[i].logic= READ_BIT(command,i);
        ret = gpio_pin_write_value(&(lcd->lcd_data[i]));
        }
        ret = lcd_send_enable_signal_8bits(lcd);
    }
    else{
        ret = STD_NULL_POINTER;
    }
    return ret;     
}
STD_Return_t lcd_8bit_send_char_data(chr_lcd_8bit_t *lcd, uint8 data){
  STD_Return_t ret = STD_NOK;
    uint8 i=0;
    if (lcd){
        lcd->lcd_rs.logic = HIGH;
        ret = gpio_pin_write_value(&(lcd->lcd_rs));
        for(i=0;i<8;i++){
        lcd->lcd_data[i].logic= READ_BIT(data,i);
        ret = gpio_pin_write_value(&(lcd->lcd_data[i]));
        }
        ret = lcd_send_enable_signal_8bits(lcd);
    }
    else{
        ret = STD_NULL_POINTER;
    }
    return ret;     
}
STD_Return_t lcd_8bit_send_char_data_pos(const chr_lcd_8bit_t *lcd, uint8 row, uint8 column, uint8 data){
  STD_Return_t ret = STD_NOK;

    if (lcd){
        ret = lcd_8bit_set_cursor(lcd, row,column);
        ret = lcd_8bit_send_char_data(lcd, data);
    }
    else{
        ret = STD_NULL_POINTER;
    }
    return ret;     
}
STD_Return_t lcd_8bit_send_string(const chr_lcd_8bit_t *lcd, uint8 *str){
  STD_Return_t ret = STD_NOK;

    if ((NULL == lcd) || (NULL == str)){
        ret = STD_NULL_POINTER;
    }
    else{

        while(*str){
            ret  = lcd_8bit_send_char_data(lcd,*str++);
        }
    }
    return ret;   
}  
STD_Return_t lcd_8bit_send_string_pos(const chr_lcd_8bit_t *lcd, uint8 row, uint8 column, uint8 *str){
  STD_Return_t ret = STD_NOK;

    if ((NULL == lcd) || (NULL == str)){
        ret = STD_NULL_POINTER;
    }
    else{
        ret = lcd_8bit_set_cursor(lcd, row,column);
        ret = lcd_8bit_send_string(lcd,str);
    }
    return ret;   
}  
STD_Return_t lcd_8bit_send_custom_char(const chr_lcd_8bit_t *lcd, uint8 row, uint8 column,const uint8 chr[], uint8 mem_pos){
  STD_Return_t ret = STD_NOK;
  uint8 i=0;
    if ((NULL == lcd) || (NULL == chr)){
        ret = STD_NULL_POINTER;
    }
    else{
        ret = lcd_8bit_send_command(lcd,(LCD_CGRAM_START+mem_pos*8));
        for(i=0;i<8;i++){
            lcd_8bit_send_char_data(lcd,chr[i]);
        }
        lcd_8bit_send_char_data_pos(lcd,row,column,mem_pos);
    }
    return ret;   
}      


STD_Return_t convert_byte_to_string(uint8 value, uint8 *str){
  STD_Return_t ret = STD_NOK;

    if (str){
        memset(str,'\0', 4);
        sprintf((char*)str,"%i",value);
    }
    else{
        ret = STD_NULL_POINTER;
    }    
}
STD_Return_t convert_short_to_string(uint16 value, uint8 *str){
  STD_Return_t ret = STD_NOK;

    if (str){
        memset(str,'\0', 6);
        sprintf((char*)str,"%i",value);
    }
    else{
        ret = STD_NULL_POINTER;
    }     
   return ret; 
}
STD_Return_t convert_int_to_string(uint32 value, uint16 *str){
  STD_Return_t ret = STD_NOK;

    if (str){
        memset(str,'\0', 11);
        sprintf((char*)str,"%i",value);
    }
    else{
        ret = STD_NULL_POINTER;
    }
  return ret;
}

static STD_Return_t lcd_send_4bits(chr_lcd_4bit_t *lcd, uint8 data){
      STD_Return_t ret = STD_NOK;

    if (lcd){
        lcd->lcd_data[0].logic= READ_BIT(data,0);
        lcd->lcd_data[1].logic= READ_BIT(data,1);
        lcd->lcd_data[2].logic= READ_BIT(data,2);
        lcd->lcd_data[3].logic= READ_BIT(data,3);
        ret = gpio_pin_write_value(&(lcd->lcd_data[0]));
        ret = gpio_pin_write_value(&(lcd->lcd_data[1]));
        ret = gpio_pin_write_value(&(lcd->lcd_data[2]));
        ret = gpio_pin_write_value(&(lcd->lcd_data[3]));
    }
    else{
        ret = STD_NULL_POINTER;
    }
    return ret;  
}

static STD_Return_t lcd_send_enable_signal_4bits(chr_lcd_4bit_t *lcd){
      STD_Return_t ret = STD_NOK;

    if (lcd){
        lcd->lcd_en.logic =HIGH;
        gpio_pin_write_value(&(lcd->lcd_en));
        __delay_us(5);
        lcd->lcd_en.logic =LOW;
        gpio_pin_write_value(&(lcd->lcd_en));        
    }
    else{
        ret = STD_NULL_POINTER;
    }
  return ret;    
}
static STD_Return_t lcd_send_enable_signal_8bits(chr_lcd_8bit_t *lcd){
      STD_Return_t ret = STD_NOK;

    if (lcd){
        lcd->lcd_en.logic =HIGH;
        gpio_pin_write_value(&(lcd->lcd_en));
        __delay_us(5);
        lcd->lcd_en.logic =LOW;
        gpio_pin_write_value(&(lcd->lcd_en));        
    }
    else{
        ret = STD_NULL_POINTER;
    }
  return ret;    
}
static STD_Return_t lcd_8bit_set_cursor(chr_lcd_8bit_t *lcd,uint8 row,uint8 column){
    STD_Return_t ret = STD_NOK;
        if (lcd){
            column--;
            switch (row){
                case ROW1: ret = lcd_8bit_send_command(lcd,(0x80 + column));break;
                case ROW2: ret = lcd_8bit_send_command(lcd,(0xC0 + column));break;
                case ROW3: ret = lcd_8bit_send_command(lcd,(0x94 + column));break;
                case ROW4: ret = lcd_8bit_send_command(lcd,(0xD4 + column));break;
            }
    }
    else{
        ret = STD_NULL_POINTER;
    }
  return ret;  
}
static STD_Return_t lcd_4bit_set_cursor(chr_lcd_4bit_t *lcd,uint8 row,uint8 column){
    STD_Return_t ret = STD_NOK;
        if (lcd){
            column--;
            switch (row){
                case ROW1: ret = lcd_4bit_send_command(lcd,(0x80 + column));break;
                case ROW2: ret = lcd_4bit_send_command(lcd,(0xC0 + column));break;
                case ROW3: ret = lcd_4bit_send_command(lcd,(0x94 + column));break;
                case ROW4: ret = lcd_4bit_send_command(lcd,(0xD4 + column));break;
            }
    }
    else{
        ret = STD_NULL_POINTER;
    }
  return ret;  
}