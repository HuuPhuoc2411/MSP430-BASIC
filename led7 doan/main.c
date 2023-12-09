
#include "msp430g2553.h"

void delayms(int ms){
  for (int i=0;i<ms;i++)
    __delay_cycles(1000); 
}
#define LEDS1 P1OUT // chan cua led 7 doan tu p1.0 den p1.7
#define LEDS2 P2OUT// chan cua transistor tu p2.0 den p2.3

// transistor dung la c1815 , tin hieu bat la 0, tin hieu tat la 1

char giatri[]= {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0X88,0X83,0XC6,0XA1,0X86,0X8E}; // ma led 7 doan
char khoa[]= {0x07,0x0b,0x0d,0x0e}; // ma de dieu khien transistor
    int n=0; // so se hien thi tren led 7 doan
    int dem=0;
    int dem2=0;
    int m=0;
    int t=5; // thoi gian de set tan so quet cua led 7 doan
     /// 4 led moi con chay 5ms vay la 4x5ms=20ms, f=1/T =1/5*10^-3=50Hz

    int a,b,c,d; // cac thong so truyen vao ham led
    
    void led (int a1, int a2, int a3, int a4){
  for(int i=0;i<4;i++){ // bien i chay tu 0 den 3
  dem++; // bien dem cong len 1 moi lan lap
  if(dem>3){ // neu bien dem =4 thi se tro ve 0
    dem=0;
  }
 if(dem==0){ // neu dem =0 thi
   LEDS2=khoa[dem];  // chan dieu khien led1 se sang
   LEDS1 =giatri[a4]; // led1 la led dau tien ben trai, gia tri hien thi se bang a4
    delayms(t); // delay 5ms
  } 
   if(dem==1){ 
   LEDS2=khoa[dem]; // chan dieu le2 sang
   LEDS1 =giatri[a3]; //gia tri hien thi se bang a3
    delayms(t);// delay 5ms
  } 
  if(dem==2){
   LEDS2=khoa[dem]; // tuong tu nhu tren
   LEDS1 =giatri[a2]; 
    delayms(t);
  } 
  
  // toi con led cuoi co them dem2 vao
  
  if(dem==3){   // // tuong tu nhu tren
    dem2++; // sao moi chu ky quet la 20ms, moi con led la 5ms, 4 con la 20ms. thi dem cong 1
    LEDS2=khoa[dem];  // chan dieu le4 sang, led4 la led cuoi ben phai
     LEDS1 =giatri[a1]; 
    delayms(t);
   if(dem2==5){ // khi dem2 len toi 5 nghia la thoi gian da troi qua 5x20ms=100ms  
   n++;// n tang them 1 . n la so se hien thi len led 7 doan
   }
     if(dem2>=10){ // khi dem2 lon hon 10 nghia la lon hon 200ms
       dem2=0; // thi dem2 ve 0
   }
      
//    if(n>15 && n<50){
//    n=15; // khi n lon hon 9999 thi ve 0 vi led7 doan co 4 so. max la 9999
//    }
      if(n>15){
    n=0; // khi n lon hon 9999 thi ve 0 vi led7 doan co 4 so. max la 9999
    }
   } 
    }
    
    
    }
    
  

    
void main( void )
{
 
WDTCTL = WDTPW + WDTHOLD;
P1DIR =0xFF; 
P2DIR |=BIT0+BIT1+BIT2+BIT3; 

while(1){
 n=99; 
led(a,b,c,d); //goi ra ham led ben tren
// dong code nay la de tach so n ra thanh cac so roi rac
// vd: n= 1298. thi a=1, b=2, c=9, d=8
// cac so a b c d se duoc truyen vao ham led
a=n/1000%10;
b=n/100%10;
c=n/10%10;
d=n/1%10;
}

 
}
