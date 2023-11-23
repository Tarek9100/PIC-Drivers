/* 
 * File:   chr_lcd.h
 * Author: Tarek Wael
 */

#ifndef CHR_LCD_H
#define	CHR_LCD_H
#include "../../MCAL_Layer/GPIO/gpio.h"
#include "chr_lcd_cfg.h"

/* Section : Macro Declarations */
#define LCD_CLEAR                           0x01
#define LCD_RETURN_HOME                     0x02
#define LCD_ENTRY_MODE_DEC_SHIFT_OFF        0x04 
#define LCD_ENTRY_MODE_DEC_SHIFT_ON         0x05
#define LCD_ENTRY_MODE_INC_SHIFT_OFF        0x06 
#define LCD_ENTRY_MODE_INC_SHIFT_ON         0x07
#define LCD_CURSOR_MOVE_SHIFT_LEFT          0x10
#define LCD_CURSOR_MOVE_SHIFT_RIGHT         0x14
#define LCD_DISPAY_SHIFT_LEFT               0x18
#define LCD_DISPAY_SHIFT_RIGHT              0x1C
#define LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF    0x0C
#define LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_ON     0x0D
#define LCD_DISPLAY_ON_UNDERLINE_ON_CURSOR_OFF     0x0E
#define LCD_DISPLAY_ON_UNDERLINE_ON_CURSOR_ON      0x0F
#define LCD_DISPLAY_OFF_CURSOR_OFF          0x08
#define LCD_8BIT_MODE_2_LINE                0x38
#define LCD_4BIT_MODE_2_LINE                0x28

#define LCD_CGRAM_START                     0x40
#define LCD_DDRAM_START                     0x80    

#define ROW1        1
#define ROW2        2
#define ROW3        3
#define ROW4        4

/* Section : Macro Function Declarations */




/* Section : Data Type Declarations */
typedef struct{
  pin_config_t  lcd_rs;
  pin_config_t lcd_en;
  pin_config_t lcd_data[4];
}chr_lcd_4bit_t;

typedef struct{
  pin_config_t  lcd_rs;
  pin_config_t lcd_en;
  pin_config_t lcd_data[8];   
}chr_lcd_8bit_t;
/* Section : Function Declarations */

/* Section : Function Declarations */
STD_Return_t lcd_4bit_initialize(chr_lcd_4bit_t *lcd);
STD_Return_t lcd_4bit_send_command(chr_lcd_4bit_t *lcd, uint8 command);
STD_Return_t lcd_4bit_send_char_data(chr_lcd_4bit_t *lcd, uint8 data);
STD_Return_t lcd_4bit_send_char_data_pos(const chr_lcd_4bit_t *lcd, uint8 row, uint8 column, uint8 data);
STD_Return_t lcd_4bit_send_string(const chr_lcd_4bit_t *lcd, uint8 *str);
STD_Return_t lcd_4bit_send_string_pos(const chr_lcd_4bit_t *lcd, uint8 row, uint8 column, uint8 *str);
STD_Return_t lcd_4bit_send_custom_char(const chr_lcd_4bit_t *lcd, uint8 row, uint8 column,const uint8 chr[], uint8 mem_pos);

STD_Return_t lcd_8bit_initialize(chr_lcd_8bit_t *lcd);
STD_Return_t lcd_8bit_send_command(chr_lcd_8bit_t *lcd, uint8 command);
STD_Return_t lcd_8bit_send_char_data(chr_lcd_8bit_t *lcd, uint8 data);
STD_Return_t lcd_8bit_send_char_data_pos(const chr_lcd_8bit_t *lcd, uint8 row, uint8 column, uint8 data);
STD_Return_t lcd_8bit_send_string(const chr_lcd_8bit_t *lcd, uint8 *str);
STD_Return_t lcd_8bit_send_string_pos(const chr_lcd_8bit_t *lcd, uint8 row, uint8 column, uint8 *str);
STD_Return_t lcd_8bit_send_custom_char(const chr_lcd_8bit_t *lcd, uint8 row, uint8 column,const uint8 chr[], uint8 mem_pos);

STD_Return_t convert_byte_to_string(uint8 value, uint8 *str);
STD_Return_t convert_short_to_string(uint16 value, uint8 *str);
STD_Return_t convert_int_to_string(uint32 value, uint16 *str);
#endif	/* BUTTON_H */

