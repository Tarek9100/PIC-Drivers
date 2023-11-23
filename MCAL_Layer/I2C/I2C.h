/* 
 * File:   I2C.h
 * Author: ENG TAREK
 *
 */

#ifndef I2C_H
#define	I2C_H

/* Section : Includes */
#include "../GPIO/gpio.h"
#include "../Interrupt/internal_interrupt.h" 
#include "I2C_cfg.h"

/* Section : Macro Declarations */
#define I2C_MASTER_MODE              1
#define I2C_SLAVE_MODE               0

#define I2C_LAST_BYTE_DATA           1   
#define I2C_LAST_BYTE_ADDRESS        0  

#define I2C_STOP_BIT_DETECTED        1
#define I2C_STOP_BIT_NOT_DETECTED    0

#define I2C_START_BIT_DETECTED       1
#define I2C_START_BIT_NOT_DETECTED   0

#define I2C_ENABLE                   1
#define I2C_DISABLE                  0

#define I2C_MASTER_SEND_ACK          0
#define I2C_MASTER_SEND_NACK         1
    
/* Section : Macro Function Declarations */
#define I2C_MODULE_ENABLE()                          (SSPCON1bits.SSPEN = 1)
#define I2C_MODULE_DISABLE()                         (SSPCON1bits.SSPEN = 0)

#define I2C_SLEW_RATE_DISABLE()                      (SSPSTATbits.SMP = 1)
#define I2C_SLEW_RATE_ENABLE()                       (SSPSTATbits.SMP = 0)

#define I2C_SMBus_DISABLE()                          (SSPSTATbits.CKE = 0)
#define I2C_SMBus_ENABLE()                           (SSPSTATbits.CKE = 1)

#define I2C_GENERAL_CALL_DISABLE()                   (SSPCON2bits.GCEN = 0)
#define I2C_GENERAL_CALL_ENABLE()                    (SSPCON2bits.GCEN = 1)

#define I2C_MASTER_RECEIVE_DISABLE()                 (SSPCON2bits.RCEN = 0)
#define I2C_MASTER_RECEIVE_ENABLE()                  (SSPCON2bits.RCEN = 1)

#define I2C_MODE_CONFIG()                            (SSPCON1bits.SSPM = I2C_MODE_CFG)

#define I2C_START_CONDITION_ENABLE()                 (SSPCON2bits.SEN = 1)
#define I2C_REPEATED_START_CONDITION_ENABLE()        (SSPCON2bits.RSEN = 1)
#define I2C_STOP_CONDITION_ENABLE()                  (SSPCON2bits.PEN = 1)

#define I2C_CLOCK_STRETCH_ENABLE()                   (SSPCON1bits.CKP = 0) 
#define I2C_CLOCK_STRETCH_DISABLE()                  (SSPCON1bits.CKP = 1)
/* Section : Data Type Declarations */
typedef struct{
uint8 i2c_slew_rate : 1;
uint8 i2c_SMBus_control : 1;
uint8 i2c_general_call : 1;
uint8 i2c_master_receive_mode : 1;
uint8 i2c_slave_address : 1; 
uint8 Reserved : 3;


}i2c_config_t;
typedef struct{
#if INTERNAL_INTERRUPT_MSSP_I2C_BUS_COLLISION_ENABLE == FEATURE_ENABLE
void (*I2C_Report_Write_Collision)(void);
uint8 I2C_Report_Write_Collision_Priority;
#endif

#if INTERNAL_INTERRUPT_MSSP_I2C_ENABLE == FEATURE_ENABLE
void (*I2C_DefaultInterruptHandler)(void);
uint8 I2C_DefaultInterruptPriority;
#endif
void (*I2C_Report_Receive_Overflow)(void);
i2c_config_t i2c_config;   
}i2c_t;

/* Section : Function Declarations */

STD_Return_t I2C_Master_Init(const i2c_t *i2c_obj);
STD_Return_t I2C_Slave_Init(const i2c_t *i2c_obj);
STD_Return_t I2C_Deinit(const i2c_t *i2c_obj);
STD_Return_t I2C_Master_Send_Start(const i2c_t *i2c_obj);
STD_Return_t I2C_Master_Send_Repeated_Start(const i2c_t *i2c_obj);
STD_Return_t I2C_Master_Send_Stop(const i2c_t *i2c_obj);
STD_Return_t I2C_Master_Write(const i2c_t *i2c_obj, uint8 i2c_data, uint8 *ack);
STD_Return_t I2C_Master_Send_Byte(const i2c_t *i2c_obj,uint8 i2c_address, uint8 i2c_data, uint8 *ack);
STD_Return_t I2C_Master_Send_String(const i2c_t *i2c_obj,uint8 i2c_address, uint8* i2c_data,uint32 strlen, uint8 *ack);
STD_Return_t I2C_Master_Read_Blocking(const i2c_t *i2c_obj, uint8 ack, uint8 *i2c_data);
#endif	/* I2C_H */

