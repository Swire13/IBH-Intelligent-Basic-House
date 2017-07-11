#line 1 "D:/worx/__Matej_KOP_zdielane_20151228/IOPIC_16F887_EXTPWM_16F688/IOPIC_16F887.c"
#line 1 "c:/users/public/documents/mikroelektronika/mikroc pro for pic/include/built_in.h"
#line 4 "D:/worx/__Matej_KOP_zdielane_20151228/IOPIC_16F887_EXTPWM_16F688/IOPIC_16F887.c"
const constDHTRead=20;
const constRS232baud=19200;

const constPWMRes=0x20;

unsigned short value[32];
unsigned int cDHTRead, dta;
unsigned short rxbfr, txbfr, val, rid, Rain, DayLight;
bit DHTRead_bit, RST_bit;

unsigned short DHTCheck, DHTSum, PIRsensors, onebyte, ii, jj, rh1, rh2, tt1, tt2;

void DHT1_Read(char B, short ind){
 TRISA &= ~B;
 PORTA &= ~B;
 Delay_ms(20);
 PORTA |= B;
 Delay_us(30);
 TRISA |= B;
 DHTCheck = 0;
 Delay_us(40);
 if (!(PORTA&B)){
 Delay_us(80);
 if ((PORTA&B)) DHTCheck = 1;
 Delay_us(50);
 }
 if (DHTCheck == 1){
 for(ii=0;ii<8;ii++){
 while(!(PORTA&B));
 Delay_us(30);
 if(!(PORTA&B)) {
 onebyte&= ~(1<<(7-ii));
 } else {
 onebyte|= (1<<(7-ii));
 while((PORTA&B));
 }
 rh1=onebyte;
 }
 for(ii=0;ii<8;ii++){
 while(!(PORTA&B));
 Delay_us(30);
 if(!(PORTA&B)) {
 onebyte&= ~(1<<(7-ii));
 } else {
 onebyte|= (1<<(7-ii));
 while((PORTA&B));
 }
 rh2=onebyte;
 }
 for(ii=0;ii<8;ii++){
 while(!(PORTA&B));
 Delay_us(30);
 if(!(PORTA&B)) {
 onebyte&= ~(1<<(7-ii));
 } else {
 onebyte|= (1<<(7-ii));
 while((PORTA&B));
 }
 tt1=onebyte;
 }
 for(ii=0;ii<8;ii++){
 while(!(PORTA&B));
 Delay_us(30);
 if(!(PORTA&B)) {
 onebyte&= ~(1<<(7-ii));
 } else {
 onebyte|= (1<<(7-ii));
 while((PORTA&B));
 }
 tt2=onebyte;
 }
 for(ii = 0; ii < 8; ii++){
 while(!(PORTA&B));
 Delay_us(30);
 if(!(PORTA&B)) {
 onebyte&= ~(1<<(7-ii));
 } else {
 onebyte|= (1<<(7-ii));
 while((PORTA&B));
 }
 DHTSum = onebyte;
 }
 if(DHTSum == ((rh1+rh2+tt1+tt2) & 0Xff)) {
 value[ind+3]=rh1;
 value[ind+2]=rh2;
 value[ind+1]=tt1;
 value[ind+0]=tt2;
 } else {
 value[ind+3]=0xfd;
 value[ind+2]=0xfd;
 value[ind+1]=0xfd;
 value[ind+0]=0xfd;
 }
 } else {
 value[ind+3]=0xfe;
 value[ind+2]=0xfe;
 value[ind+1]=0xfe;
 value[ind+0]=0xfe;
 }
}

void DHT2_Read(char B, short ind){
 TRISE &= ~B;
 PORTE &= ~B;
 Delay_ms(20);
 PORTE |= B;
 Delay_us(30);
 TRISE |= B;
 DHTCheck = 0;
 Delay_us(40);
 if (!(PORTE&B)){
 Delay_us(80);
 if ((PORTE&B)) DHTCheck = 1;
 Delay_us(50);
 }
 if (DHTCheck == 1){
 for(ii=0;ii<8;ii++){
 while(!(PORTE&B));
 Delay_us(30);
 if(!(PORTE&B)) {
 onebyte&= ~(1<<(7-ii));
 } else {
 onebyte|= (1<<(7-ii));
 while((PORTE&B));
 }
 rh1=onebyte;
 }
 for(ii=0;ii<8;ii++){
 while(!(PORTE&B));
 Delay_us(30);
 if(!(PORTE&B)) {
 onebyte&= ~(1<<(7-ii));
 } else {
 onebyte|= (1<<(7-ii));
 while((PORTE&B));
 }
 rh2=onebyte;
 }
 for(ii=0;ii<8;ii++){
 while(!(PORTE&B));
 Delay_us(30);
 if(!(PORTE&B)) {
 onebyte&= ~(1<<(7-ii));
 } else {
 onebyte|= (1<<(7-ii));
 while((PORTE&B));
 }
 tt1=onebyte;
 }
 for(ii=0;ii<8;ii++){
 while(!(PORTE&B));
 Delay_us(30);
 if(!(PORTE&B)) {
 onebyte&= ~(1<<(7-ii));
 } else {
 onebyte|= (1<<(7-ii));
 while((PORTE&B));
 }
 tt2=onebyte;
 }
 for(ii = 0; ii < 8; ii++){
 while(!(PORTE&B));
 Delay_us(30);
 if(!(PORTE&B)) {
 onebyte&= ~(1<<(7-ii));
 } else {
 onebyte|= (1<<(7-ii));
 while((PORTE&B));
 }
 DHTSum = onebyte;
 }
 if(DHTSum == ((rh1+rh2+tt1+tt2) & 0Xff)) {
 value[ind+3]=rh1;
 value[ind+2]=rh2;
 value[ind+1]=tt1;
 value[ind+0]=tt2;
 } else {
 value[ind+3]=0xfd;
 value[ind+2]=0xfd;
 value[ind+1]=0xfd;
 value[ind+0]=0xfd;
 }
 } else {
 value[ind+3]=0xfe;
 value[ind+2]=0xfe;
 value[ind+1]=0xfe;
 value[ind+0]=0xfe;
 }
}

void Interrupt() iv 0x000004 {

 if (TMR1IF_bit) {
 TMR1IF_bit = 0;
 TMR1H = 0x3C;
 TMR1L = 0xB0;
 cDHTRead--;
 if(cDHTRead == 0) {
 cDHTRead=constDHTRead;
 DHTRead_bit=1;
 }
 }

 if (RBIF_bit == 1){
 PIRsensors |= PORTB;
 RBIF_bit = 0;
 }

}

void InitTimer1() {
 T1CON = 0x31;
 TMR1IF_bit = 0;
 TMR1H = 0x3C;
 TMR1L = 0xB0;
 TMR1IE_bit = 1;
 INTCON = 0xC0;
}

void InitMain() {
 ANSEL = 0x00;
 ANSELH = 0x00;
 OSCCON = 0x7c;
 ADCON1 = 0x0F;

 TRISA = 0x3f;

 TRISB = 0xff;
 WPUB = 0x00;
 IOCB = 0xff;
 RBIE_bit = 1;

 TRISD = 0x00;

 TRISE = 0x03;

 TRISC0_bit=1;
 TRISC1_bit=1;
 TRISC3_bit=0;
 TRISC4_bit=1;
 TRISC5_bit=0;
 TRISC6_bit=1;

 SPI1_Init_Advanced(_SPI_MASTER_OSC_DIV4,_SPI_DATA_SAMPLE_MIDDLE,_SPI_CLK_IDLE_HIGH,_SPI_LOW_2_HIGH);
}

void main() {

 while (1) {
 InitMain();
 InitTimer1();
 UART1_Init(constRS232baud);
 Delay_ms(1000);
 cDHTRead=constDHTRead;
 DHTRead_bit = 0;
 PIRsensors = 0;
 RST_bit = 0;
 Rain = 0;
 DayLight = 0;

 UART1_Write_Text("IOPIC_v");
 UART1_Write_Text( "1.0" );

 while (RST_bit == 0) {

 if (DHTRead_bit == 1) {
 RBIE_bit=0;
 TMR1IE_bit=0;
 for(jj=0;jj<=5;jj++) {
 DHT1_Read(1<<jj,(jj<<2));
 }
 for(jj=6;jj<=7;jj++) {
 DHT2_Read(1<<(jj-6),jj<<2);
 }
 DHTRead_bit=0;
 RBIE_bit=1;
 TMR1IE_bit=1;
 }

 if (~RC1_bit) Rain=1;
 if (RC0_bit) DayLight=1;

 if(UART1_Data_Ready()==1) {
 rxbfr=UART1_Read();

 if (rxbfr=='d') {
 ii=0;
 while((ii<32)&&(1==1)) {
 if(UART1_Tx_Idle()==1) {
 txbfr = (value[ii]);
 UART1_Write(txbfr);
 ii++;
 }
 }
 }

 if (rxbfr=='p') {
 ii=0;
 while((ii<1)&&(1==1)) {
 if(UART1_Tx_Idle()==1) {
 UART1_Write(PIRsensors);
 ii++;
 PIRsensors = 0;
 }
 }
 }

 if (rxbfr=='r') {
 if(UART1_Tx_Idle()==1) {
 UART1_Write(Rain);
 Rain=0;
 }
 }

 if (rxbfr=='i') {
 if(UART1_Tx_Idle()==1) {
 UART1_Write(DayLight);
 DayLight=0;
 }
 }

 if (rxbfr=='H') {
 while (UART1_Data_Ready()==0);
 val=UART1_Read();
 PORTD = val;
 }

 if (rxbfr=='L') {
 while (UART1_Data_Ready()==0);
 rid=UART1_Read();
 while (UART1_Data_Ready()==0);
 val=UART1_Read();
 dta=(((val*(constPWMRes-1))/100)&0x1f)+((rid & 0x07)<<5);
 SPI1_Write(dta);
 }

 if (rxbfr=='@') {
 RST_bit=1;
 }

 if (rxbfr=='?') {
 ii=0;
 while((ii<1)&&(1==1)) {
 if(UART1_Tx_Idle()==1) {
 UART1_Write('!');
 ii++;
 }
 }
 }

 }
 }
 }
}
