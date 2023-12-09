
#include "msp430g2553.h"
void delay(int ms){
  for(int i=0; i<ms;i++){
    __delay_cycles(1000);
  }

}
void main(void)
{
            WDTCTL = WDTPW | WDTHOLD;          
            
            P1DIR |=BIT0 + BIT1;
              
            P2DIR &=~ BIT3;// set input
            
            P2IE |= BIT3;// cho phep ngat p3 
            
            P2IES |= BIT3; // =1 la chon xung canh xuong
            
            P2IFG &=~ BIT3; // =0 xoa co ngat
            P1OUT=0x00;
            _BIS_SR(GIE); // cho phep ngat toan cuc
            P1OUT|=BIT0;  
            while(1)
            {
            P1OUT|=BIT1;
            delay(4000);
             P1OUT&=~BIT1;
             delay(4000);
            }
}

#pragma vector = PORT2_VECTOR
__interrupt void test(void)
{
 P1OUT^=BIT0;
 P2IFG &=~ BIT3;// =0 XOA CO NGAT
           
}
