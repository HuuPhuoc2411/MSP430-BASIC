
#include <msp430g2553.h>
#define KHOA P2OUT
char giatri[]= {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0X88,0X83,0XC6,0XA1,0X86,0X8E,0x7F}; 
char buff[4]={0,0,0,0};
int idx =0;
int  n=0;

int val;
float vol;
float truocdo;
int val2;
#define BUTTON1 BIT4

int  n2=0;
int hientai2=0;
int truocdo2=1;


unsigned char data;
#define DATA_PIN BIT0 // 14 ic
#define CLOCK_PIN BIT1// 11 ic
#define LATCH_PIN BIT2// 12 ic

void delayms(int ms){
  for (int i=0;i<ms;i++)
    __delay_cycles(1000); 
}

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
sendData(data);
KHOA = ~(1<<idx);
//idx=0 hang don vi bat
idx++;
if (idx>3) idx=0;

if(n2==0){
if (idx==2) {
 P2OUT &=~BIT4; 
}
if (idx!=2) {
 P2OUT |=BIT4; 
}
}
}

 void dienap(float val){
 
    vol=(val*5)/1023;// chuyen sang dien ap
    val2=(int)(vol*100); // lay dien ap nhan 100
    }
void tach(){
  //vd 1234= a,b,c,d
  buff[0]=n/1000;// lay so a
  buff[1]=(n%1000)/100;// so b
  buff[2]=((n%1000)%100)/10;// so c
  buff[3]=n%10;// so d
}

void main( void )
{
  WDTCTL = WDTPW + WDTHOLD;
  P1DIR |= (DATA_PIN + CLOCK_PIN + LATCH_PIN);
  P1OUT &= ~(DATA_PIN + CLOCK_PIN + LATCH_PIN);
  
  P2DIR =0X1F; 
 // Set chan Analog 
ADC10CTL0 = ADC10SHT_2 + ADC10ON + ADC10IE; // ADC10ON, interrupt enabled
ADC10CTL1 = INCH_5; // input A5
ADC10AE0 |= BIT5; // PA.5 ADC option select
  
P1DIR |= ~ (BUTTON1);// set input
P1IE |= (BUTTON1);// cho phep ngat p3 
P1IES |= (BUTTON1); // =1 la chon xung canh xuong
P1IFG &=~ (BUTTON1); // =0 xoa co ngat
_BIS_SR(GIE); // cho phep ngat toan cuc



  while (1){

  ADC10CTL0 |= ENC + ADC10SC; // Sampling and conversion start
__bis_SR_register(CPUOFF + GIE); // LPM0 with interrupts enabled

val=ADC10MEM;// val la gia tri analog

if(n2==0){
dienap(val);// chuyen thanh dien ap

}
if(n2==1){
val2=val;
}
// tranh bi nhap nhay khi dien ap khong on dinh

if((val2-truocdo)>=3 || (truocdo-val2)>=3  ){
truocdo=val2;
n=val2; // n = gia tri dien ap
}

  tach(); // tach so n ra
  for(int i=0;i<4;i++){
  scanled();
  delayms(4);
 }
 
}
 
 }
// ADC10 interrupt service routine
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void)
{
__bic_SR_register_on_exit(CPUOFF); // Clear CPUOFF bit from 0(SR)
}
#pragma vector=PORT1_VECTOR
__interrupt void Port1(void){ 
  if ((P1IN & BUTTON1) == 0){
     if (hientai2 != truocdo2)
    {
     n2 ++;
    if(n2 > 1){
      n2 = 0; 
    }
      hientai2 = ~hientai2;
    }
      }
  P1IFG = 0x00; // Clear co ngat
}


