#include <Arduino.h>
#include "Suteppa.h"
Suteppa s;
const int IN1 = 9;
const int IN2 = 10;
const int IN3 = 11;
const int IN4 = 12;
int d_hs[9] = {
	B01000, 
	B01100,
	B00100,
	B00110,
	B00010,
	B00011,
	B00001,
	B01001,
	B00000
};
int i = 0;
void step(int d);
void setup()
{
	Serial.begin(9600);
	pinMode(IN1, OUTPUT);
	pinMode(IN2, OUTPUT);
	pinMode(IN3, OUTPUT);
	pinMode(IN4, OUTPUT);
	pinMode(2, INPUT_PULLUP);
	pinMode(3, INPUT_PULLUP);
	s.init(1024*4, 200, 6000, 850, true, step);
}
void loop()
{
	if(digitalRead(2) == 0){
		s.rotator(1024*3);
	}
	if(digitalRead(3) == 0){
		s.rotateA(0, true);
	}
}
void step(int d)
{
	i += d;
	if(i > 7) i = 0;
	if(i < 0) i = 7;
	if(d == 0)i = 8;
	byte b = d_hs[i];
	digitalWrite(IN1, bitRead(b, 0));
	digitalWrite(IN2, bitRead(b, 1));
	digitalWrite(IN3, bitRead(b, 2));
	digitalWrite(IN4, bitRead(b, 3));
}