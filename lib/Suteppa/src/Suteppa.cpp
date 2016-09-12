#include "Suteppa.h"
Suteppa::Suteppa(int step, int adStep, int begin, int max)
{
	_step = step;
	_begin = begin;
	_max = max;
	_adStep = adStep;
	_mbDiff = _begin-_max;
}
void Suteppa::set(int step)
{
	int adStep = _adStep;
	float max = 1;
	float interval = max / (float)adStep;
	if(step < adStep*2.1) {
		adStep = step/2.1;
	}
	max = interval * adStep;
	float r;
	for (int i = 0; i < step; i++) {
		r = -1;
		if (i <= adStep) {
			r = (i / (float)adStep);
		}else if (step - i <= adStep + 1) {
			r = ((step - 1) - i) / (float)adStep;
		}
		float p;
		if(r<0){
			p = max;
		}else{
			p = (cos(r * PI+PI)+1) / 2 * max;
		}
		Serial.println((1-p)*_mbDiff + _max);
	}
}