#include <msp430g2553.h>
int val;
float vol;
int main(void)
{
WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer

ADC10CTL0 = ADC10SHT_2 + ADC10ON + ADC10IE; // choose speed get sample, turn on ADC, turn on interrupt ADC

ADC10CTL1 = INCH_1; // input A1// choose channel is A1 


ADC10AE0 |= BIT1; // P1.1 is input of ADC

P2DIR |= BIT1; 

P2OUT &= ~BIT1; 

while(1)
{
ADC10CTL0 |= ENC + ADC10SC; // Sampling and conversion start

__bis_SR_register(CPUOFF + GIE); //  interrupts enabled, GIE cho phep ngat, CPUOFF tat bo xu ly cpu de tiet kiem nang luong

val=ADC10MEM;



vol=(val*5)/1023;




if (ADC10MEM < 0x88) // ADC10MEM = A1 > 0.5V?
P1OUT &= ~BIT0; // Clear P1.0 LED off
else
P1OUT |= BIT0; // Set P1.0 LED on
}
}

// ADC10 interrupt service routine
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void)
{
__bic_SR_register_on_exit(CPUOFF); // Clear CPUOFF bit from 0(SR)
}



