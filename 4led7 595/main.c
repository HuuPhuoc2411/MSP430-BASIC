
#include <msp430g2553.h> 
#define DATA_PIN BIT0 // 14 ic
#define CLOCK_PIN BIT1// 11 ic
#define LATCH_PIN BIT2// 12 ic
#define LEDS2 P2OUT
  int val;
float vol;
float truocdo;
int val2;
int phannguyen;
  float thapphan;
char khoa[]= {0x07,0x0b,0x0d,0x0e,0xff}; // ma de dieu khien transistor
    int n=0; // so se hien thi tren led 7 doan
    int dem=0;
    int dem2=0;
    int m=0;
    int t=4; // thoi gian de set tan so quet cua led 7 doan
   

  unsigned char data;
//char giatri []={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0X77,0X7c,0X39,0X5e,0X79,0X71}; 
char giatri[]= {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0X88,0X83,0XC6,0XA1,0X86,0X8E}; 
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
  
void delayms(int ms){
  for (int i=0;i<ms;i++)
    __delay_cycles(1000); 
}

 int a,b,c,d; // cac thong so truyen vao ham led
    
    void led (int a, int b, int c, int d){
  for(int i=0;i<4;i++){ // bien i chay tu 0 den 3
  dem++; // bien dem cong len 1 moi lan lap
  if(dem>3){ // neu bien dem =4 thi se tro ve 0
    dem=0;
  }
 if(dem==0){ 
    
 
 
   data = giatri[d];
   sendData(data);

     LEDS2=khoa[dem];
         P2OUT |= BIT4;
    delayms(t); // delay 5ms
 
    
  } 
   if(dem==1){ 
    
  
    data = giatri[c];
    sendData(data);
 
     LEDS2=khoa[dem];
           P2OUT |= BIT4;
    delayms(t);// delay 5ms
 
  } 
  if(dem==2){

  
    data = giatri[b];
    sendData(data);
         
     LEDS2=khoa[dem]; 
      P2OUT &=~BIT4; 
    delayms(t);
    

  } 
    if(dem==3){  
 
    data = giatri[a];
    sendData(data);
            
    LEDS2=khoa[dem]; 
      P2OUT |= BIT4;    
    delayms(t);
    
 
   } 
    }
     }
    
    void chuyendoi(){
      a=n/1000%10;
      b=n/100%10;
      c=n/10%10;
      d=n/1%10;
    } 
    void dienap(float val){
 
    vol=(val*5)/1023;
    val2=(int)(vol*100);
   phannguyen = (int)vol;
   thapphan = vol - phannguyen;
  
   
    }
    


void main(void)
{
WDTCTL = WDTPW + WDTHOLD;
P1DIR |= (DATA_PIN + CLOCK_PIN + LATCH_PIN);
P1OUT &= ~(DATA_PIN + CLOCK_PIN + LATCH_PIN);
P2DIR |=0X1F; 

ADC10CTL0 = ADC10SHT_2 + ADC10ON + ADC10IE; // ADC10ON, interrupt enabled
ADC10CTL1 = INCH_5; // input A5
ADC10AE0 |= BIT5; // PA.5 ADC option select

while (1)
{

ADC10CTL0 |= ENC + ADC10SC; // Sampling and conversion start
__bis_SR_register(CPUOFF + GIE); // LPM0 with interrupts enabled

val=ADC10MEM;

dienap(val);

if((val2-truocdo)>=8 || (truocdo-val2)>=8  ){
truocdo=val2;
n=val2;
}

led(a,b,c,d);

chuyendoi();
}
}
// ADC10 interrupt service routine
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void)
{
__bic_SR_register_on_exit(CPUOFF); // Clear CPUOFF bit from 0(SR)
}


