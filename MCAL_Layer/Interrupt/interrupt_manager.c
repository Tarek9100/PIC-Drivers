/* 
 * File:   interrupt_manager.c
 * Author: Tarek Wael
 *
 */
#include "interrupt_manager.h"

static volatile uint8 RB4_Flag =1,RB5_Flag =1,RB6_Flag =1,RB7_Flag =1;
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == FEATURE_ENABLE
void __interrupt() InterruptManagerHigh(void){
    if((INTCONbits.INT0IE == INTERRUPT_ENABLE) && (INTCONbits.INT0IF == 1)){
       INT0_ISR(); 
      }

    }

void __interrupt(low_priority) InterruptManagerLow(void){
    if((INTCON3bits.INT2IE == INTERRUPT_ENABLE) && (INTCON3bits.INT2IF == 1)){
       INT2_ISR(); 
      }  
     if((INTCON3bits.INT1IE == INTERRUPT_ENABLE) && (INTCON3bits.INT1IF == 1)){
       INT1_ISR(); 
     }
}
#else
void __interrupt() InterruptManagerHigh(void){
    if((INTCONbits.INT0IE == INTERRUPT_ENABLE) && (INTCONbits.INT0IF == 1)){
 
       INT0_ISR(); 
      }
    if((INTCON3bits.INT1IE == INTERRUPT_ENABLE) && (INTCON3bits.INT1IF == 1)){
        INT1_ISR(); 
      } 
    if((INTCON3bits.INT2IE == INTERRUPT_ENABLE) && (INTCON3bits.INT2IF == 1)){
       INT2_ISR(); 
      } 
    if((PIE1bits.ADIE == INTERRUPT_ENABLE) && (PIR1bits.ADIF == 1)){
        ADC_ISR();
    }    
    if((INTCONbits.TMR0IE == INTERRUPT_ENABLE) && (INTCONbits.TMR0IF == 1)){
        TIMER0_ISR();
    }
    if((PIE1bits.TMR1IE == INTERRUPT_ENABLE) && (PIR1bits.TMR1IF == 1)){
        TIMER1_ISR();
    }
    if((PIE1bits.TMR2IE == INTERRUPT_ENABLE) && (PIR1bits.TMR2IF == 1)){
        TIMER2_ISR();
    }
    if((PIE2bits.TMR3IE == INTERRUPT_ENABLE) && (PIR2bits.TMR3IF == 1)){
        TIMER3_ISR();
    }
    if((PIE1bits.CCP1IE == INTERRUPT_ENABLE) && (PIR1bits.CCP1IF == 1)){
        CCP1_ISR();
    }
    if((PIE2bits.CCP2IE == INTERRUPT_ENABLE) && (PIR2bits.CCP2IF == 1)){
        CCP2_ISR();
    }
    if((PIE1bits.TXIE == INTERRUPT_ENABLE) && (PIR1bits.TXIF == 1)){
        USART_TX_ISR();
    }
    if((PIE1bits.RCIE == INTERRUPT_ENABLE) && (PIR1bits.RCIF == 1)){
        USART_RX_ISR();
    }
    if((PIE1bits.SSPIE == INTERRUPT_ENABLE) && (PIR1bits.SSPIF == 1)){
        I2C_ISR();
    }  
    if((PIE2bits.BCLIE == INTERRUPT_ENABLE) && (PIR2bits.BCLIF == 1)){
        I2C_BC_ISR();
    }      
    if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == 1) && (PORTBbits.RB4 == HIGH) && (RB4_Flag == 1)){
        RB4_Flag = 0;
        RB4_ISR(1);
    }
    if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == 1) && (PORTBbits.RB4 == LOW) && (RB4_Flag == 0)){
        RB4_Flag = 1;
        RB4_ISR(0);
    }
    if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == 1) && (PORTBbits.RB5 == HIGH) && (RB5_Flag == 1)){
        RB5_Flag =0;
        RB5_ISR(1);
    }
    if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == 1) && (PORTBbits.RB5 == LOW) && (RB5_Flag == 0)){
        RB5_Flag = 1;
        RB5_ISR(0);
    }    
    if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == 1) && (PORTBbits.RB6 == HIGH) && (RB6_Flag == 1)){
        RB6_Flag = 0;
        RB6_ISR(1);
    }
    if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == 1) && (PORTBbits.RB6 == LOW) && (RB6_Flag == 0)){
        RB6_Flag = 1;
        RB6_ISR(0);
    }
    if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == 1) && (PORTBbits.RB7 == HIGH) && (RB7_Flag == 1)){
        RB7_Flag = 0;
        RB7_ISR(1);
    }
    if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == 1) && (PORTBbits.RB7 == LOW) && (RB7_Flag == 0)){
        RB7_Flag = 1;
        RB7_ISR(0);
    }

    
}

#endif