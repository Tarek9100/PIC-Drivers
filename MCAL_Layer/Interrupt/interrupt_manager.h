/* 
 * File:   interrupt_manager.h
 * Author: ENG TAREK
 *
 */

#ifndef INTERRUPT_MANAGER_H
#define	INTERRUPT_MANAGER_H

/* Section : Includes */
#include "interrupt_cfg.h"

/* Section : Macro Declarations */

/* Section : Macro Function Declarations */

/* Section : Data Type Declarations */

/* Section : Function Declarations */

/* Section : Function Declarations */
void INT0_ISR(void);
void INT1_ISR(void);
void INT2_ISR(void);
void RB4_ISR(uint8 RB_Source);
void RB5_ISR(uint8 RB_Source);
void RB6_ISR(uint8 RB_Source);
void RB7_ISR(uint8 RB_Source);
void ADC_ISR(void);
void TIMER0_ISR(void);
void TIMER1_ISR(void);
void TIMER2_ISR(void);
void TIMER3_ISR(void);
void CCP1_ISR(void);
void CCP2_ISR(void);
void USART_TX_ISR(void);
void USART_RX_ISR(void);
void I2C_ISR(void);
void I2C_BC_ISR(void);
void SPI_ISR(void);
#endif	/* INTERRUPT_MANAGER_H */

