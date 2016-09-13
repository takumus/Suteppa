#include "Suteppa.h"
Suteppa::Suteppa()
{
}
void Suteppa::init(int allStep, int adStep, int begin, int max, void (*rotator)(int))
{
	_allStep = allStep;
	_begin = begin;
	_max = max;
	_adStep = adStep;
	_mbDiff = _begin-_max;
	_rotator = rotator;
}
void Suteppa::setMax(int max)
{
	_max = max;
	_mbDiff = _begin-_max;
}
void Suteppa::setBegin(int begin)
{
	_begin = begin;
	_mbDiff = _begin-_max;
}
void Suteppa::setSmooth(bool smooth)
{
	_smooth = smooth;
}
void Suteppa::rotateR(int step)
{
	rotateR(step, NULL);
}
void Suteppa::rotateR(int step, int (*update)(int))
{
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
			_step += direction;
			_rotator(direction);
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
			_delay(interval);
			if(update && update(_step)) break;
		}
	}else{
		for(int i = 0; i < step; i ++){
			_step += direction;
			_rotator(direction);
			_delay(_max);
			if(update && update(_step)) break;
		}
	}
}
void Suteppa::rotateA(int step, bool skip, int (*update)(int))
{
	if(skip){
		step = step%_allStep;
		_step = _step%_allStep;
		int diff = abs(step - _step);
		if(diff > _allStep / 2){
			if(_step < step){
				rotateR(-(_allStep - diff), update);
			}else{
				rotateR((_allStep - diff), update);
			}
		}else{
			rotateR(step - _step, update);
		}
	}else{
		rotateR(step - _step, update);
	}
}
void Suteppa::rotateA(int step, bool skip)
{
	rotateA(step, skip, NULL);
}
void Suteppa::rotateA(int step)
{
	rotateA(step, false, NULL);
}
void Suteppa::setHome()
{
	_step = 0;
}
float Suteppa::sigmoid(float x)
{
	return 1 / (1 + exp(-7 * x));
}
void Suteppa::_delay(int time)
{
	if(time < 10000){
		delayMicroseconds(time);
	}else{
		delay(time/1000);
	}
}