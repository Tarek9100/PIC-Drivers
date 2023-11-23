/* 
 * File:   I2C_cfg.h
 * Author: ENG TAREK
 *
 */

#ifndef I2C_CFG_H
#define	I2C_CFG_H

/* Section : Includes */
 

/* Section : Macro Declarations */
#define I2C_SLAVE_MODE_7BIT_ADDRESS                    0x06U
#define I2C_SLAVE_MODE_10BIT_ADDRESS                   0x07U  
#define I2C_SLAVE_MODE_7BIT_ADDRESS_SS_INT_ENABLE      0x0EU  
#define I2C_SLAVE_MODE_10BIT_ADDRESS_SS_INT_ENABLE     0x0FU 
#define I2C_MASTER_MODE_DEFINED_CLOCK                  0x08U  
#define I2C_MASTER_MODE_FIRMWARE_CONTROLLED            0x0BU 

#define I2C_CLOCK_100K              100000U
#define I2C_CLOCK_400K              400000U

/*Options: 1-I2C_SLAVE_MODE_7BIT_ADDRESS                 2-I2C_SLAVE_MODE_10BIT_ADDRESS     3-I2C_SLAVE_MODE_7BIT_ADDRESS_SS_INT_ENABLE
           4-I2C_SLAVE_MODE_10BIT_ADDRESS_SS_INT_ENABLE  5-I2C_MASTER_MODE_DEFINED_CLOCK    6-I2C_MASTER_MODE_FIRMWARE_CONTROLLED 
 */
#define I2C_MODE_CFG                I2C_MASTER_MODE_DEFINED_CLOCK

/*Options: 1-I2C_CLOCK_100K                 2-I2C_CLOCK_400K    
 */
#define I2C_CLOCK_FREQUENCY         I2C_CLOCK_100K           

/* Section : Macro Function Declarations */




/* Section : Data Type Declarations */


/* Section : Function Declarations */

#endif	/* I2C_CFG_H */

