#line 1 "F:/Worx/dokumenty/__Matej_KOP/IOPIC_16F887_EXTPWM_16F688/EXTPWM_16F88.c"
#line 1 "c:/users/public/documents/mikroelektronika/mikroc pro for pic/include/built_in.h"
#line 3 "F:/Worx/dokumenty/__Matej_KOP/IOPIC_16F887_EXTPWM_16F688/EXTPWM_16F88.c"
const constI2CSlAddr = 0x69;
const constPWMRes = 32;

unsigned short pwm[8]={0,4,9,14,19,24,29,31};
unsigned short rxbfr, txbfr, tmpbfr, rid, val, pwmcnt;
bit PWM_bit;

unsigned short ii, jj, onebit;
unsigned long retval;

void Interrupt() iv 0x000004 {

 if (SSPIF_bit) {
 val = SSPBUF;
 pwm[(val>>5)&0x07] = val&0x1f;
 SSPIF_bit = 0;
 }

 if (TMR2IF_bit){
 TMR2IF_bit = 0;
 PWM_bit=1;
#line 52 "F:/Worx/dokumenty/__Matej_KOP/IOPIC_16F887_EXTPWM_16F688/EXTPWM_16F88.c"
 }
}

void InitTimer2() {
 T2CON = 0x24;
 PR2 = 249;
 TMR2IE_bit = 1;
 INTCON = 0xC0;
}

void InitSPI() {
 TRISB1_bit=1;
 TRISB2_bit=0;
 TRISB4_bit=1;
 SPI1_Init_Advanced(_SPI_SLAVE_SS_DIS,_SPI_DATA_SAMPLE_MIDDLE,_SPI_CLK_IDLE_HIGH,_SPI_LOW_2_HIGH);
 SSPIF_bit = 0;
 SSPIE_bit = 1;
}

void InitMain() {
 OSCCON = 0x7c;
 ANSEL = 0x00;
 ADCON1 = 0x00;
 TRISA = 0x00;
 TRISB = 0x00;
}

void main() {
 InitMain();
 InitTimer2();
 InitSPI();


 while (1) {
 if(PWM_bit) {
 if (pwm[0]<=pwmcnt) {
 RA0_bit=0;
 } else {
 RA0_bit=1;
 }
 if (pwm[1]<=pwmcnt) {
 RA1_bit=0;
 } else {
 RA1_bit=1;
 }
 if (pwm[2]<=pwmcnt) {
 RA2_bit=0;
 } else {
 RA2_bit=1;
 }
 if (pwm[3]<=pwmcnt) {
 RA3_bit=0;
 } else {
 RA3_bit=1;
 }
 if (pwm[4]<=pwmcnt) {
 RA4_bit=0;
 } else {
 RA4_bit=1;
 }
 if (pwm[5]<=pwmcnt) {
 RB0_bit=0;
 } else {
 RB0_bit=1;
 }
 if (pwm[6]<=pwmcnt) {
 RB3_bit=0;
 } else {
 RB3_bit=1;
 }
 if (pwm[7]<=pwmcnt) {
 RB5_bit=0;
 } else {
 RB5_bit=1;
 }
 pwmcnt++;
 if (pwmcnt > constPWMRes){
 pwmcnt=0;
 }
 PWM_bit = 0;
 }
 }
}
