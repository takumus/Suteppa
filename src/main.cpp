#include <Arduino.h>
#include "Suteppa.h"
Suteppa s(1024*4, 1024, 10000, 1000);
void setup()
{
	Serial.begin(9600);
	s.set(1024);
}
void loop()
{
	
}