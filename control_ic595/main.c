#include "io430.h"
#define KHOA P2OUT
char giatri[]= {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0X88,0X83,0XC6,0XA1,0X86,0X8E}; 
char buff[4]={0,0,0,0};
int idx =0;
int  n=0;

//int buttonPushCounter = 0;   
int buttonState = 0;         
int lastButtonState = 0;    

int buttonState2 = 0;         
int lastButtonState2 = 0;   

#define BUTTON1 BIT3
#define BUTTON2 BIT4
#define BUTTON3 BIT5
#define BUTTON4 BIT6

unsigned char data;
#define DATA_PIN BIT0 // 14 ic
#define CLOCK_PIN BIT1// 11 ic
#define LATCH_PIN BIT2// 12 ic

void delayms(int ms){
  for (int i=0;i<ms;i++)
    __delay_cycles(1000); 
}
// output function for ic74hc595
void sendData(unsigned char data)
{
unsigned char i;
P1OUT &= ~LATCH_PIN;
for (i = 0; i < 8; i++)
{
P1OUT &= ~CLOCK_PIN;
if (data & 0x80)
P1OUT |= DATA_PIN;
else
P1OUT &= ~DATA_PIN;
P1OUT |= CLOCK_PIN;
data <<= 1;
}
P1OUT |= LATCH_PIN;
}

void scanled(){
char ch;
ch = buff[idx];
data = giatri[ch];

sendData(data); // chuyen so sang cho ic o day

KHOA = ~(1<<idx);

//idx=0 hang don vi bat
idx++;
if (idx>3) idx=0;
}

void count2buff(){
  //vd 1234= a,b,c,d
  buff[0]=n/1000;// lay so a
  buff[1]=(n%1000)/100;// so b
  buff[2]=((n%1000)%100)/10;// so c
  buff[3]=n%10;// so d
}

void main( void )
{
  WDTCTL = WDTPW + WDTHOLD;
  // set port for ic 595
  P1DIR |= (DATA_PIN + CLOCK_PIN + LATCH_PIN);
  P1OUT &= ~(DATA_PIN + CLOCK_PIN + LATCH_PIN);
  
  P1REN |= BUTTON1+BUTTON2+BUTTON3+BUTTON4;          
    P1OUT |= BUTTON1+BUTTON2+BUTTON3+BUTTON4;          
    
    
  P2DIR =0X0F; // port control 4 transistor
 
 
 
  while (1){
    /////////////////////////////////////// nut 1///////////////
    buttonState = (P1IN & BUTTON1);
     if (buttonState != lastButtonState) {
    if (buttonState == 0) {
     n++;
    }
  
  }
 
  lastButtonState = buttonState;
    
   /////////////////////////////////////// nut 2///////////////
  
  buttonState2 = (P1IN & BUTTON2);
     if (buttonState2 != lastButtonState2) {
    if (buttonState2 == 0) {
     n--;
    }
  
  }
   if (n <= 0) {
     n=0;
    }
  lastButtonState2 = buttonState2;
    /////////////////////////////////////// nut 3///////////////
      if((P1IN & BUTTON3) == 0)
        {
           n=0;    
        }
      n=1111; 

//n=1234; // number wil ouput
 count2buff(); // tach so n ra
  for(int i=0;i<4;i++){
  scanled();
  delayms(4);
 }
 
}
 }


