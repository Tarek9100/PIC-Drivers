#include "SPI.h"

#if INTERNAL_INTERRUPT_MSSP_SPI_ENABLE== FEATURE_ENABLE
    static void (*SPI_InterruptHandler)(void) = NULL;
#endif

static void SPI_Interrupt_Init(const SPI_Config *SPI_obj);
static void SPI_Master_Mode_GPIO_PIN_Configurations(const SPI_Config *SPI_obj);
static void SPI_Slave_Mode_GPIO_PIN_Configurations(const SPI_Config *SPI_obj);
    
STD_Return_t SPI_Init(const SPI_Config *SPI_obj){
    STD_Return_t ret = STD_NOK;
    
    if(SPI_obj){
        /* Disable SPI Module */
        SPI_DISABLE_MODULE();
        /* MSSP SPI Mode Select */
        SSPCON1bits.SSPM = SPI_obj->spi_mode;
        /* GPIO PIN Configurations */
        if((SPI_obj->spi_mode == SPI_MASTER_FOSC_DIV4) || (SPI_obj->spi_mode == SPI_MASTER_FOSC_DIV16) ||
            (SPI_obj->spi_mode == SPI_MASTER_FOSC_DIV64) || (SPI_obj->spi_mode == SPI_MASTER_FOSC_TMR2)){
            SPI_Master_Mode_GPIO_PIN_Configurations(SPI_obj);
        }
        else if((SPI_obj->spi_mode == SPI_SLAVE_SS_ENABLE) || (SPI_obj->spi_mode == SPI_SLAVE_SS_DISABLE)){
            SPI_Slave_Mode_GPIO_PIN_Configurations(SPI_obj);
        }
        /* Clock Polarity Select */
        SSPCON1bits.CKP = SPI_obj->spi_config.ClockPolarity;
        /* SPI Sample Select */
        SSPSTATbits.SMP = SPI_obj->spi_config.SampleSelect;
        /* SPI Clock Select */
        SSPSTATbits.CKE = SPI_obj->spi_config.ClockSelect;
        /* MSSP SPI Interrupt Configurations*/
        SPI_Interrupt_Init(SPI_obj);
        /* Enable SPI Module */
        SPI_ENABLE_MODULE();
    }
    else{
        ret = STD_NULL_POINTER;

    }
    
    return ret;
}

STD_Return_t SPI_DeInit(const SPI_Config *SPI_obj){
    STD_Return_t ret = STD_NOK;
    
    if(SPI_obj){
        /* Disable SPI Module */
        SPI_DISABLE_MODULE();
/* Interrupt Configurations */        
#if INTERNAL_INTERRUPT_MSSP_SPI_ENABLE== FEATURE_ENABLE
        MSSP_SPI_InterruptDisable();
#endif
    }
    else{
        ret = STD_NULL_POINTER;
    }
    
    return ret;
}

STD_Return_t SPI_Send_Byte(const SPI_Config *SPI_obj, const uint8 _data){
    STD_Return_t ret = STD_NOK;
    
    if(SPI_obj){
        SSPBUF = _data;
        while(!(PIR1bits.SSPIF)); /* Waiting to transmit */
        PIR1bits.SSPIF = 0;
    }
    else{
        ret = STD_NULL_POINTER;
    }
    
    return ret;
}

STD_Return_t SPI_Read_Byte(const SPI_Config *SPI_obj, uint8 *_data){
    STD_Return_t ret = STD_NOK;
    
    if((NULL == SPI_obj) || (NULL == _data)){
        ret = STD_NULL_POINTER;
    }
    else{
        while(SSPSTATbits.BF == 0); /* Receive not complete, SSPBUF is empty */
        *_data = SSPBUF;
    }
    
    return ret;
}


void SPI_ISR(void){
#if MSSP_SPI_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    MSSP_SPI_InterruptFlagClear();
    if(SPI_InterruptHandler){
        SPI_InterruptHandler();
    }
#endif
}

static void SPI_Interrupt_Init(const SPI_Config *SPI_obj){
    #if INTERNAL_INTERRUPT_MSSP_SPI_ENABLE == FEATURE_ENABLE
        MSSP_SPI_InterruptEnable();
        MSSP_SPI_InterruptFlagClear();
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE == FEATURE_ENABLE
        if(INTERRUPT_LOW_PRIORITY == i2c_obj->I2C_Report_Write_Collision_Priority){
            MSSP_SPI_LowPrioritySet();
            INTERRUPT_GlobalInterruptLowEnable(); 
        }
        else{
            MSSP_SPI_HighPrioritySet();
            INTERRUPT_GlobalInterruptHighEnable(); 
        }
        #else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
        #endif
         SPI_InterruptHandler = SPI_obj->SPI_InterruptHandler;        
    #endif      
}

static void SPI_Master_Mode_GPIO_PIN_Configurations(const SPI_Config *SPI_obj){
    STD_Return_t ret = STD_NOK;
    pin_config_t SPI_SDO = {.port = PORTC_ID, .pin = PIN5, .direction = OUTPUT};
    pin_config_t SPI_SDI = {.port = PORTC_ID, .pin = PIN4, .direction = OUTPUT};
    pin_config_t SPI_CLK = {.port = PORTC_ID, .pin = PIN3, .direction = OUTPUT};
    
    ret = gpio_pin_initialize(&SPI_SDO); 
    ret = gpio_pin_initialize(&SPI_SDI);
    ret = gpio_pin_initialize(&SPI_CLK);
}

static void SPI_Slave_Mode_GPIO_PIN_Configurations(const SPI_Config *SPI_obj){
    STD_Return_t ret = STD_NOK;
    pin_config_t SPI_SDO = {.port = PORTC_ID, .pin = PIN5, .direction = OUTPUT};
    pin_config_t SPI_SDI = {.port = PORTC_ID, .pin = PIN4, .direction = INPUT};
    pin_config_t SPI_CLK = {.port = PORTC_ID, .pin = PIN3, .direction = INPUT};
    pin_config_t SPI_SS = {.port = PORTA_ID, .pin = PIN5, .direction = INPUT};
    
    ret = gpio_pin_initialize(&SPI_SDO); 
    ret = gpio_pin_initialize(&SPI_SDI);
    ret = gpio_pin_initialize(&SPI_CLK); 
    
    if(SPI_SLAVE_SS_ENABLE == SPI_obj->spi_mode){
        ret = gpio_pin_initialize(&SPI_SS);
    }
}
