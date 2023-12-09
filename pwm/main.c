#include <msp430.h>

#define PWM_PERIOD 1000 // Ð?nh nghia chu k? PWM
#define PWM_MAX_DUTY_CYCLE 0 // Ð?nh nghia giá tr? t?i da c?a d? r?ng xung

void pwm_init(unsigned int duty_cycle, unsigned int pwm_pin) {
  // C?u hình chân d?u ra PWM
  P1DIR |= pwm_pin;
  P1SEL |= pwm_pin;

  // C?u hình Timer_A d? t?o tín hi?u PWM
  TA0CCR0 = PWM_PERIOD - 1; // Ð?t giá tr? d?m t?i da c?a Timer_A
  TA0CCTL1 = OUTMOD_7; // Ð?t ch? d? d?u ra PWM
  TA0CCR1 = duty_cycle - 1; // Ð?t d? r?ng xung

  // B?t Timer_A
  TA0CTL = TASSEL_2 + MC_1 + TACLR; // SMCLK, ch? d? tang d?m, xóa b? d?m
}

void pwm_set_duty_cycle(unsigned int duty_cycle) {
  // Ð?t giá tr? d? r?ng xung m?i
  TA0CCR1 = duty_cycle - 1;
}

void main() {
  WDTCTL = WDTPW + WDTHOLD; // T?t Watchdog timer

  

  while (1) {
pwm_init(PWM_MAX_DUTY_CYCLE, BIT6); // Kh?i t?o PWM v?i d? r?ng xung t?i da và chân P1.6
  }
 
}
void analogWrite(uint8_t pin, int val)
{
 

 	
	else
	{

	    
	        if (port == NOT_A_PORT) return; // pin on timer?

			if(pin2timer < T0A0_SEL1)
			{
				pinMode_int(pin, OUTPUT | PORT_SELECTION0);
			}
			else if(pin2timer < T0A0_SEL01)
			{
				pinMode_int(pin, OUTPUT | PORT_SELECTION1);
				pin2timer -= (T0A0_SEL1 - T0A0);    // correct offset
			}
			else
			{
				pinMode_int(pin, OUTPUT | PORT_SELECTION0 | PORT_SELECTION1);
				pin2timer -= (T0A0_SEL01 - T0A0);    // correct offset
			}
			switch(pin2timer) {                     // which timer and CCR?
#if defined(__MSP430_HAS_TA3__) || defined(__MSP430_HAS_T0A2__) || defined(__MSP430_HAS_T0A3__) || defined(__MSP430_HAS_T0A5__) || defined(__MSP430_HAS_TA5__) 
 			//case: T0A0                            // CCR0 used as period register
			case T0A1:                              // TimerA0 / CCR1
                                TA0CCR0 = PWM_PERIOD;           // PWM Period
                                TA0CCTL1 = OUTMOD_7;            // reset/set
                                TA0CCR1 = PWM_DUTY(val);       // PWM duty cycle
                                TA0CTL = TASSEL_2 + MC_1 + analog_div;       // SMCLK, up mode
                                break;
#endif
#if defined(__MSP430_HAS_TA3__) || defined(__MSP430_HAS_T0A3__) || defined(__MSP430_HAS_T0A5__) || defined(__MSP430_HAS_TA5__) 
 			case T0A2:                              // TimerA0 / CCR2
                                TA0CCR0 = PWM_PERIOD;           // PWM Period
                                TA0CCTL2 = OUTMOD_7;            // reset/set
                                TA0CCR2 = PWM_DUTY(val);       // PWM duty cycle
                                TA0CTL = TASSEL_2 + MC_1+ analog_div;       // SMCLK, up mode
                                break;
#endif
#if defined(__MSP430_HAS_TA5__) || defined(__MSP430_HAS_T0A5__) 
 			case T0A3:                              // TimerA0 / CCR3
                                TA0CCR0 = PWM_PERIOD;           // PWM Period
                                TA0CCTL3 = OUTMOD_7;            // reset/set
                                TA0CCR3 = PWM_DUTY(val);       // PWM duty cycle
                                TA0CTL = TASSEL_2 + MC_1+ analog_div;       // SMCLK, up mode
                                break;
 			case T0A4:                              // TimerA0 / CCR4
                                TA0CCR0 = PWM_PERIOD;           // PWM Period
                                TA0CCTL4 = OUTMOD_7;            // reset/set
                                TA0CCR4 = PWM_DUTY(val);       // PWM duty cycle
                                TA0CTL = TASSEL_2 + MC_1+ analog_div;       // SMCLK, up mode
                                break;
#endif
#if defined(__MSP430_HAS_T1A3__) 
 			//case: T1A0                            // CCR0 used as period register
			case T1A1:                              // TimerA1 / CCR1
                                TA1CCR0 = PWM_PERIOD;           // PWM Period
                                TA1CCTL1 = OUTMOD_7;            // reset/set
                                TA1CCR1 = PWM_DUTY(val);       // PWM duty cycle
                                TA1CTL = TASSEL_2 + MC_1+ analog_div;       // SMCLK, up mode
                                break;
 			case T1A2:                              // TimerA1 / CCR2
                                TA1CCR0 = PWM_PERIOD;           // PWM Period
                                TA1CCTL2 = OUTMOD_7;            // reset/set
                                TA1CCR2 = PWM_DUTY(val);       // PWM duty cycle
                                TA1CTL = TASSEL_2 + MC_1+ analog_div;       // SMCLK, up mode
                                break;
#endif
#if defined(__MSP430_HAS_T2A3__)  
 			//case: T2A0                            // CCR0 used as period register
			case T2A1:                              // TimerA2 / CCR1
                                TA2CCR0 = PWM_PERIOD;           // PWM Period
                                TA2CCTL1 = OUTMOD_7;            // reset/set
                                TA2CCR1 = PWM_DUTY(val);       // PWM duty cycle
                                TA2CTL = TASSEL_2 + MC_1+ analog_div;       // SMCLK, up mode
                                break;
 			case T2A2:                              // TimerA2 / CCR2
                                TA2CCR0 = PWM_PERIOD;           // PWM Period
                                TA2CCTL2 = OUTMOD_7;            // reset/set
                                TA2CCR2 = PWM_DUTY(val);       // PWM duty cycle
                                TA2CTL = TASSEL_2 + MC_1+ analog_div;       // SMCLK, up mode
                                break;
#endif
#if defined(__MSP430_HAS_T0B3__) || defined(__MSP430_HAS_T0B7__) 
 			//case: T0B0                            // CCR0 used as period register
 			case T0B1:                              // TimerB0 / CCR1
                                TB0CCR0 = PWM_PERIOD;           // PWM Period
                                TB0CCTL1 = OUTMOD_7;            // reset/set
                                TB0CCR1 = PWM_DUTY(val);       // PWM duty cycle
                                TB0CTL = TBSSEL_2 + MC_1+ analog_div;       // SMCLK, up mode
                                break;
 			case T0B2:                              // TimerB0 / CCR1
                                TB0CCR0 = PWM_PERIOD;           // PWM Period
                                TB0CCTL2 = OUTMOD_7;            // reset/set
                                TB0CCR2 = PWM_DUTY(val);       // PWM duty cycle
                                TB0CTL = TBSSEL_2 + MC_1+ analog_div;       // SMCLK, up mode
                                break;
#endif
#if defined(__MSP430_HAS_T0B7__) 
 			case T0B3:                              // TimerB0 / CCR3
                                TB0CCR0 = PWM_PERIOD;           // PWM Period
                                TB0CCTL3 = OUTMOD_7;            // reset/set
                                TB0CCR3 = PWM_DUTY(val);       // PWM duty cycle
                                TB0CTL = TBSSEL_2 + MC_1+ analog_div;       // SMCLK, up mode
                                break;
 			case T0B4:                              // TimerB0 / CCR4
                                TB0CCR0 = PWM_PERIOD;           // PWM Period
                                TB0CCTL4 = OUTMOD_7;            // reset/set
                                TB0CCR4 = PWM_DUTY(val);       // PWM duty cycle
                                TB0CTL = TBSSEL_2 + MC_1+ analog_div;       // SMCLK, up mode
                                break;
 			case T0B5:                              // TimerB0 / CCR5
                                TB0CCR0 = PWM_PERIOD;           // PWM Period
                                TB0CCTL5 = OUTMOD_7;            // reset/set
                                TB0CCR5 = PWM_DUTY(val);       // PWM duty cycle
                                TB0CTL = TBSSEL_2 + MC_1+ analog_div;       // SMCLK, up mode
                                break;
 			case T0B6:                              // TimerB0 / CCR6
                                TB0CCR0 = PWM_PERIOD;           // PWM Period
                                TB0CCTL6 = OUTMOD_7;            // reset/set
                                TB0CCR6 = PWM_DUTY(val);       // PWM duty cycle
                                TB0CTL = TBSSEL_2 + MC_1+ analog_div;       // SMCLK, up mode
                                break;
#endif
#if defined(__MSP430_HAS_T1B3__) 
 			//case: T1B0                            // CCR0 used as period register
 			case T1B1:                              // TimerB0 / CCR1
                                TB1CCR0 = PWM_PERIOD;           // PWM Period
                                TB1CCTL1 = OUTMOD_7;            // reset/set
                                TB1CCR1 = PWM_DUTY(val);       // PWM duty cycle
                                TB1CTL = TBSSEL_2 + MC_1+ analog_div;       // SMCLK, up mode
                                break;
 			case T1B2:                              // TimerB0 / CCR1
                                TB1CCR0 = PWM_PERIOD;           // PWM Period
                                TB1CCTL2 = OUTMOD_7;            // reset/set
                                TB1CCR2 = PWM_DUTY(val);       // PWM duty cycle
                                TB1CTL = TBSSEL_2 + MC_1+ analog_div;       // SMCLK, up mode
                                break;
#endif
#if defined(__MSP430_HAS_T2B3__) 
 			//case: T1B0                            // CCR0 used as period register
 			case T2B1:                              // TimerB0 / CCR1
                                TB2CCR0 = PWM_PERIOD;           // PWM Period
                                TB2CCTL1 = OUTMOD_7;            // reset/set
                                TB2CCR1 = PWM_DUTY(val);       // PWM duty cycle
                                TB2CTL = TBSSEL_2 + MC_1+ analog_div;       // SMCLK, up mode
                                break;
 			case T2B2:                              // TimerB0 / CCR1
                                TB2CCR0 = PWM_PERIOD;           // PWM Period
                                TB2CCTL2 = OUTMOD_7;            // reset/set
                                TB2CCR2 = PWM_DUTY(val);       // PWM duty cycle
                                TB2CTL = TBSSEL_2 + MC_1+ analog_div;       // SMCLK, up mode
                                break;
#endif
 
                        
                }
        }
}