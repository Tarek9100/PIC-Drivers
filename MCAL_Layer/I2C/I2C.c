
#include "I2C.h"
static void (*MSSP_I2C_InterruptHandler)(void) = NULL;
static void (*MSSP_I2C_Bus_Collision_InterruptHandler)(void) = NULL;
static void (*MSSP_I2C_Receive_Overflow_InterruptHandler)(void) = NULL;

static STD_Return_t I2C_Mode_GPIO_CFG(void);
static void I2C_Interrupt_Config(i2c_t *i2c_obj);

STD_Return_t I2C_Master_Init(const i2c_t *i2c_obj){
    STD_Return_t ret = STD_NOK;
    if(i2c_obj){ 
      I2C_MODULE_DISABLE();
      I2C_MODE_CONFIG(); 
      #if I2C_MODE_CFG == I2C_MASTER_MODE_DEFINED_CLOCK
      SSPADD = (uint8)(((_XTAL_FREQ / 4.0) / I2C_CLOCK_FREQUENCY) - 1); 
      #endif

      SSPCON2bits.GCEN = i2c_obj->i2c_config.i2c_general_call;  
      SSPSTATbits.SMP = i2c_obj->i2c_config.i2c_slew_rate;
      SSPSTATbits.CKE = i2c_obj->i2c_config.i2c_SMBus_control;
      
      I2C_Interrupt_Config(i2c_obj);
      ret = I2C_Mode_GPIO_CFG();
      I2C_MODULE_ENABLE();      
    }
    else{
     ret = STD_NULL_POINTER;   
    }
     return ret; 
}

STD_Return_t I2C_Slave_Init(const i2c_t *i2c_obj){
    STD_Return_t ret = STD_NOK;
    if(i2c_obj){ 
      I2C_MODULE_DISABLE();
      

      SSPCON2bits.GCEN = i2c_obj->i2c_config.i2c_general_call;  
      SSPCON1bits.WCOL = 0;
      SSPCON1bits.SSPOV = 0;
      SSPCON1bits.CKP = 1;
      SSPADD = i2c_obj->i2c_config.i2c_slave_address;
      I2C_MODE_CONFIG(); 
      I2C_Interrupt_Config(i2c_obj);
      ret = I2C_Mode_GPIO_CFG();
      I2C_MODULE_ENABLE();      
    }
    else{
     ret = STD_NULL_POINTER;   
    }
     return ret;     
}
STD_Return_t I2C_Deinit(const i2c_t *i2c_obj){
    STD_Return_t ret = STD_NOK;
    if(i2c_obj){
      I2C_MODULE_DISABLE();
#if INTERNAL_INTERRUPT_MSSP_I2C_ENABLE == FEATURE_ENABLE
      MSSP_I2C_InterruptDisable();
#endif

#if INTERNAL_INTERRUPT_MSSP_I2C_BUS_COLLISION_ENABLE == FEATURE_ENABLE
      MSSP_I2C_Bus_Collision_InterruptDisable();
#endif
    }
    else{
     ret = STD_NULL_POINTER;   
    }
     return ret; 
}
STD_Return_t I2C_Master_Send_Start(const i2c_t *i2c_obj){
    STD_Return_t ret = STD_NOK;
    if(i2c_obj){
        I2C_START_CONDITION_ENABLE();
        while(SSPCON2bits.SEN);
        PIR1bits.SSPIF = 0;
        if(SSPSTATbits.START == 1){
            ret = STD_OK;
        }
    }
    else{
     ret = STD_NULL_POINTER;   
    }
     return ret; 
}
STD_Return_t I2C_Master_Send_Repeated_Start(const i2c_t *i2c_obj){
    STD_Return_t ret = STD_NOK;
    if(i2c_obj){
        I2C_REPEATED_START_CONDITION_ENABLE();
        while(SSPCON2bits.RSEN);    
        PIR1bits.SSPIF = 0;        
        if(SSPSTATbits.START == 1){
            ret = STD_OK;
    }
    }
    else{
     ret = STD_NULL_POINTER;   
    }
     return ret; 
}
STD_Return_t I2C_Master_Send_Stop(const i2c_t *i2c_obj){
    STD_Return_t ret = STD_NOK;
    if(i2c_obj){
        I2C_STOP_CONDITION_ENABLE();
        while(SSPCON2bits.PEN);
        PIR1bits.SSPIF = 0;
        if(SSPSTATbits.STOP == 1){
            ret = STD_OK;
        }
    }
    else{
     ret = STD_NULL_POINTER;   
    }
     return ret; 
}
STD_Return_t I2C_Master_Write(const i2c_t *i2c_obj, uint8 i2c_data, uint8 *ack){
    STD_Return_t ret = STD_NOK;
    if(i2c_obj){
        SSPBUF = i2c_data;
        while(!PIR1bits.SSPIF);
        PIR1bits.SSPIF = 0;
        if(ack)
        *ack = !SSPCON2bits.ACKSTAT;
    }
    else{
     ret = STD_NULL_POINTER;   
    }
     return ret; 
}

STD_Return_t I2C_Master_Send_Byte(const i2c_t *i2c_obj,uint8 i2c_address, uint8 i2c_data, uint8 *ack){
    STD_Return_t ret = STD_NOK;
    if(i2c_obj){
      I2C_Master_Send_Start(i2c_obj);
      I2C_Master_Write(i2c_obj,i2c_address,ack);
      I2C_Master_Write(i2c_obj,i2c_data,ack);
      I2C_Master_Send_Stop(i2c_obj);
    }
    else{
     ret = STD_NULL_POINTER;   
    }
     return ret; 
}

STD_Return_t I2C_Master_Send_String(const i2c_t *i2c_obj,uint8 i2c_address, uint8* i2c_data,uint32 strlen, uint8 *ack){
    STD_Return_t ret = STD_NOK;
    uint32 i = 0; 
    if(i2c_obj){
      for(i = 0;i<strlen;i++){ 
      ret = I2C_Master_Send_Start(i2c_obj);
      ret = I2C_Master_Write(i2c_obj,i2c_address,ack);
      ret = I2C_Master_Write(i2c_obj,i2c_data[i],ack);
      if(i == (strlen - 1))
      ret = I2C_Master_Send_Stop(i2c_obj);
      else
      ret = I2C_Master_Send_Repeated_Start(i2c_obj);
    }
    }
    else{
     ret = STD_NULL_POINTER;   
    }
     return ret; 
}
STD_Return_t I2C_Master_Read_Blocking(const i2c_t *i2c_obj, uint8 ack, uint8 *i2c_data){
    STD_Return_t ret = STD_NOK;
    if((NULL == i2c_obj)||(NULL == i2c_data)){
     ret = STD_NULL_POINTER;  
    }
    else{
        I2C_MASTER_RECEIVE_ENABLE();
        while(!SSPSTATbits.BF);
        *i2c_data = SSPBUF;
        if(I2C_MASTER_SEND_ACK == ack)
          SSPCON2bits.ACKDT =  I2C_MASTER_SEND_ACK; 
        else{
          SSPCON2bits.ACKDT =  I2C_MASTER_SEND_NACK;            
        }
        SSPCON2bits.ACKEN = 1;
    }
     return ret; 
}

void I2C_ISR(void){
#if INTERNAL_INTERRUPT_MSSP_I2C_ENABLE == FEATURE_ENABLE    
MSSP_I2C_InterruptFlagClear();   
if(MSSP_I2C_InterruptHandler)
    MSSP_I2C_InterruptHandler();
#endif
}
void I2C_BC_ISR(void){
#if INTERNAL_INTERRUPT_MSSP_I2C_BUS_COLLISION_ENABLE == FEATURE_ENABLE
MSSP_I2C_Bus_Collision_InterruptFlagClear(); 
if(MSSP_I2C_Bus_Collision_InterruptHandler)
    MSSP_I2C_Bus_Collision_InterruptHandler();
#endif
}


static STD_Return_t I2C_Mode_GPIO_CFG(void){
    STD_Return_t ret = STD_OK;
    TRISCbits.TRISC3 = 1;
    TRISCbits.TRISC4 = 1;    
    return ret;
}

static void I2C_Interrupt_Config(i2c_t *i2c_obj){
    #if INTERNAL_INTERRUPT_MSSP_I2C_ENABLE == FEATURE_ENABLE
        MSSP_I2C_InterruptEnable();
        MSSP_I2C_InterruptFlagClear();
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE == FEATURE_ENABLE
        if(INTERRUPT_LOW_PRIORITY == i2c_obj->I2C_DefaultInterruptPriority){
            MSSP_I2C_LowPrioritySet();
            INTERRUPT_GlobalInterruptLowEnable(); 
        }
        else{
            MSSP_I2C_HighPrioritySet();
            INTERRUPT_GlobalInterruptHighEnable(); 
        }
        #else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
        #endif
        MSSP_I2C_Receive_Overflow_InterruptHandler = i2c_obj->I2C_Report_Receive_Overflow; 
        MSSP_I2C_InterruptHandler = i2c_obj->I2C_DefaultInterruptHandler;        
    #endif   
    #if INTERNAL_INTERRUPT_MSSP_I2C_BUS_COLLISION_ENABLE == FEATURE_ENABLE
        MSSP_I2C_Bus_Collision_InterruptEnable();
        MSSP_I2C_Bus_Collision_InterruptFlagClear();
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE == FEATURE_ENABLE
        if(INTERRUPT_LOW_PRIORITY == i2c_obj->I2C_Report_Write_Collision_Priority){
            MSSP_I2C_Bus_Collision_LowPrioritySet();
            INTERRUPT_GlobalInterruptLowEnable(); 
        }
        else{
            MSSP_I2C_Bus_Collision_HighPrioritySet();
            INTERRUPT_GlobalInterruptHighEnable(); 
        }
        #else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
        #endif
         MSSP_I2C_Bus_Collision_InterruptHandler = i2c_obj->I2C_Report_Write_Collision;        
    #endif

    
}