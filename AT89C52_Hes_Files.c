#include <REGX52.H>

sbit pd = P1^0;
sbit medium_speed = P1^1;
sbit high_speed = P1^2;
sbit liver_dose = P1^3;

sbit heart_beat_sensor = P1^4;
sbit injecting_switch = P1^5;
sbit reversing_switch = P1^6;
sbit enable = P1^7;

sbit motor_positive=P2^0;
sbit motor_negative=P2^1;
sbit motor_enable=P2^2;

sbit lcd_rs = P2^5;
sbit lcd_rw = P2^6;
sbit lcd_en = P2^7;

sbit yellow_led = P3^3;
sbit blue_led = P3^4;
sbit buzzer = P3^5;
sbit red_led = P3^6;
sbit green_led = P3^7;

void delay();
void delayi();
void delay3();

void lcdcmd(unsigned char);
void lcddat(unsigned char);

void main(){
	unsigned int injection_value=0;
	yellow_led=0;blue_led=0;buzzer=0;red_led=0;green_led=0;
	while(1){
		if((heart_beat_sensor==0 && enable==0)&&(injecting_switch==0)&&(injection_value<150)&&(pd==0)){
					//inject signal;
			delay();
			motor_negative=0;
			motor_positive=1;
			delay();
			injection_value+=20;
			blue_led=1;green_led=1;red_led=0;buzzer=0;yellow_led=0;
			lcdcmd(0x38);delay();lcdcmd(0x01);delay();lcdcmd(0x10);delay();lcdcmd(0x0c);delay();lcdcmd(0x81);
			lcddat('2');delay();lcddat('0');delay();lcddat('M');delay();lcddat('g');delay();lcddat('/');delay();lcddat('m');delay();lcddat('i');delay();lcddat('n');delay();lcddat('.');delay();lcddat('.');delay();lcddat('.');delay();lcddat(' ');delay();lcddat(' ');delay();lcddat(' ');delay();lcddat(' ');delay();lcddat(' ');delay();lcddat(' ');delay();lcdcmd(0x01);
		}
			
		else if(injecting_switch==0 && medium_speed==0 && injection_value<300 && (heart_beat_sensor==0 && enable==0)){
				//inject signal;
			delayi();
			motor_negative=0;
			motor_positive=1;
			delayi();
			injection_value+=30;
			blue_led=1;green_led=1;red_led=0;buzzer=0;yellow_led=0;
			lcdcmd(0x38);delayi();lcdcmd(0x01);delayi();lcdcmd(0x10);delayi();lcdcmd(0x0c);delayi();lcdcmd(0x81);
			lcddat('3');delayi();lcddat('0');delayi();lcddat('M');delayi();lcddat('g');delayi();lcddat('/');delayi();lcddat('m');delayi();lcddat('i');delayi();lcddat('n');delayi();lcddat('.');delayi();lcddat('.');delayi();lcddat('.');delayi();lcddat(' ');lcdcmd(0x01);
		}
		else if(injecting_switch==0 && high_speed==0 && injection_value<300 && (heart_beat_sensor==0 && enable==0)){
				//inject signal;
			delay3();
			motor_negative=0;
			motor_positive=1;
			delay3();
			injection_value+=84;
			blue_led=1;green_led=1;red_led=0;buzzer=0;yellow_led=0;
			lcdcmd(0x38);delay3();lcdcmd(0x01);delay3();lcdcmd(0x10);delay3();lcdcmd(0x0c);delay3();lcdcmd(0x81);
			lcddat('8');delay3();lcddat('4');delay3();lcddat('M');delay3();lcddat('g');delay3();lcddat('/');delay3();lcddat('m');delay3();lcddat('i');delay3();lcddat('n');delay3();lcddat('.');delay3();lcddat('.');delay3();lcddat('.');delay3();lcddat(' ');lcdcmd(0x01);
		}
		else if(enable == 0 && reversing_switch==0){
			delay();
			motor_negative=1;
			motor_positive=0;
			delay();
			yellow_led=1;green_led=1;blue_led=0;red_led=0;buzzer=0;
			lcdcmd(0x38);delay();lcdcmd(0x01);delay();lcdcmd(0x10);delay();lcdcmd(0x0c);delay();lcdcmd(0x81);
			lcddat('R');delay();lcddat('E');delay();lcddat('V');delay();lcddat('E');delay();lcddat('R');delay();lcddat('S');delay();lcddat('I');delay();lcddat('N');delay();lcddat('G');delay();lcddat('.');delay();lcddat('.');delay();lcddat('.');lcddat('\n');lcddat('5');lcdcmd(0x01);				//reverse signal;
			
		}
		else if(injecting_switch==0 && liver_dose==0 && injection_value<38 && (heart_beat_sensor==0 && enable==0)){
				//inject signal;
			delay3();
			motor_negative=0;
			motor_positive=1;
			delay3();
			injection_value+=38;
			blue_led=1;green_led=1;red_led=0;buzzer=0;yellow_led=0;
			lcdcmd(0x38);delay3();lcdcmd(0x01);delay3();lcdcmd(0x10);delay3();lcdcmd(0x0c);delay3();lcdcmd(0x81);
			lcddat('3');delay3();lcddat('8');delay3();lcddat('M');delay3();lcddat('g');delay3();lcddat('.');delay3();lcddat('.');delay3();lcddat('.');delay3();lcddat(' ');delay3();lcddat(' ');delay3();lcddat(' ');delay3();lcddat(' ');delay3();lcddat(' ');lcdcmd(0x01);
		}
		else if(pd == 0&& injection_value>150){red_led=1;buzzer=1;green_led=0;blue_led=0;yellow_led=0;}
		else if((medium_speed == 0 || high_speed == 0)&& injection_value>300){red_led=1;buzzer=1;green_led=0;blue_led=0;yellow_led=0;}
		else if(pd == 0&& injection_value>150){red_led=1;buzzer=1;green_led=0;blue_led=0;yellow_led=0;}
		else if((liver_dose==0)&& injection_value>=38){red_led=1;buzzer=1;green_led=0;blue_led=0;yellow_led=0;}
		else{
			yellow_led=0;blue_led=0;buzzer=0;red_led=0;green_led=1;
		}
		motor_negative = ~motor_negative;
		motor_positive = ~motor_positive;
	}
}
void lcdcmd(unsigned char val){
	lcd_rs=0;P0=val;lcd_rw=0;lcd_en=1;delay();lcd_en=0;}
void lcddat(unsigned char val){
	lcd_rs=1;P0=val;lcd_rw=0;lcd_en=1;delay();lcd_en=0;}
void delay(){
	unsigned int i;
	for(i=0;i<12000;i++);}
void delayi(){
	unsigned int i;
	for(i=0;i<6000;i++);}
void delay3(){
	unsigned int i;
	for(i=0;i<3000;i++);}