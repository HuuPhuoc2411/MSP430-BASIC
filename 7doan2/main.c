
#include "io430.h"
//#define LED P2OUT

#define KHOA P2OUT

#define DATA_PIN BIT0 // 14 ic
#define CLOCK_PIN BIT1// 11 ic
#define LATCH_PIN BIT2// 12 ic

char giatri[]= {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0X88,0X83,0XC6,0XA1,0X86,0X8E}; 
char buff[4]={0,0,0,0};
int idx =0;
int  n=0;
unsigned char data;

void delayms(int ms){
  for (int i=0;i<ms;i++)
    __delay_cycles(1000); 
}
void scanled(){
char ch;
ch = buff[idx];
LED=giatri[ch];
KHOA = ~(1<<idx);
//idx=0 hang don vi bat
idx++;
if (idx>3) idx=0;

}
void tach(){
  //vd 1234= a,b,c,d
  buff[0]=n/1000;// lay so a
  buff[1]=(n%1000)/100;// so b
  buff[2]=((n%1000)%100)/10;// so c
  buff[3]=n%10;// so d
}
void chop(){
 if(n<10){
        KHOA=0x0f; 
  }
  if(n>=10 && n<100){
   
         KHOA=0x07; 
  }
   if(n>=100 && n<1000){
   KHOA=0x03;
  }
   if(n>=1000 && n<10000){
 
      KHOA=0x01;
  }
}

void main( void )
{
  WDTCTL = WDTPW + WDTHOLD;
  P2DIR=0xff;
  P1DIR=0x0f;

  
 
  while (1){
  //n=17;
 
  tach();
  for(int i=0;i<150;i++){
  scanled();
  delayms(4);
 }
  n++;
  if(n>9999){
    n=0;
  }
  //KHOA=0x01;
// chop();
  //delayms(500);
 
}
 
 }
