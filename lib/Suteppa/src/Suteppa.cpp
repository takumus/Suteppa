#include "Suteppa.h"
Suteppa::Suteppa()
{
}
void Suteppa::init(int allStep, int adStep, int begin, int max, bool smooth, void (*rotater)(int))
{
	_smooth = smooth;
	_allStep = allStep;
	_begin = begin;
	_max = max;
	_adStep = adStep;
	_mbDiff = _begin-_max;
	_rotater = rotater;
}
void Suteppa::rotateR(int step)
{
	_step += step;
	int adStep = _adStep;
	int max = 1;
	int direction = 1;
	float interval = max / (float)adStep;
	if(step < 0){
		direction = -1;
		step *= -1;
	}
	if(step < adStep*2.1) {
		adStep = step/2.1;
	}
	bool smooth = _smooth;
	if(adStep < 1) smooth = false;
	max = interval * adStep;
	float r = 0;
	if(smooth){
		for(int i = 0; i < step; i ++){
			_rotater(direction);
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
				p = sin(acos(1 - r)) * max;
			}
			int interval = (1 - p) * _mbDiff + _max;
			delayMicroseconds(interval);
		}
	}else{
		for(int i = 0; i < step; i ++){
			_rotater(direction);
			delayMicroseconds(_max);
		}
	}
}
void Suteppa::rotateA(int step, bool skip)
{
	if(skip){
		step = step%_allStep;
		_step = _step%_allStep;
		int diff = abs(step - _step);
		if(diff > _allStep / 2){
			if(_step < step){
				rotateR(-(_allStep - diff));
			}else{
				rotateR((_allStep - diff));
			}
		}else{
			rotateR(step - _step);
		}
	}else{
		rotateR(step - _step);
	}
	_step = step;
}
void Suteppa::setHome()
{
	_step = 0;
}
float Suteppa::sigmoid(float x)
{
	return 1 / (1 + exp(-7 * x));
}