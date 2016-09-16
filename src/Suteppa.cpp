#include "Suteppa.h"
Suteppa::Suteppa()
{
}
void Suteppa::init(unsigned long allStep, void (*rotator)(int))
{
	_allStep = allStep;
	_speed = 10000;
	_rotator = rotator;
}
void Suteppa::setSpeed(unsigned long speed)
{
	_speed = speed;
}
void Suteppa::beginSmooth(unsigned long step, unsigned long initSpeed)
{
	_smooth = true;
	_smoothStep = step;
	_initDiff = initSpeed-_speed;
}
void Suteppa::beginSmooth()
{
	_smooth = true;
}
void Suteppa::setDefaultSmooth(unsigned long step, unsigned long initSpeed)
{
	_smoothStep = step;
	_initDiff = initSpeed-_speed;
}


void Suteppa::rotate(int mode, long step, int (*update)(int))
{
	if(mode == 0){
		_rotateRelative(step, update);
	}else if(mode == 1){
		_rotateAbsolute(step, false, update);
	}else if(mode == 2){
		_rotateAbsolute(step, true, update);
	}
}

void Suteppa::rotate(int mode, long step)
{
	rotate(mode, step, NULL);
}

void Suteppa::_rotateRelative(long step, int (*update)(int))
{
	unsigned long smoothStep = _smoothStep;
	int direction = 1;
	float interval = 1 / (float)smoothStep;
	bool smooth = _smooth;
	float r = 0;

	if(step < 0){
		direction = -1;
		step *= -1;
	}
	unsigned long ustep = step;
	if(step < smoothStep*2.1) smoothStep = step/2.1;
	if(smoothStep < 1) smooth = false;
	float max = interval * smoothStep;
	if(update && update(_step)) return;
	if(smooth){
		for(unsigned int i = 0; i < ustep; i ++){
			_step += direction;
			_rotator(direction);
			r = -1;
			if (i <= smoothStep) {
				r = (i / (float)smoothStep);
			}else if (ustep - i <= smoothStep + 1) {
				r = ((ustep - 1) - i) / (float)smoothStep;
			}
			float p;
			if(r < 0){
				p = max;
			}else{
				p = sin(acos(1 - r)) * max;
			}
			_delay((1 - p) * _initDiff + _speed);
			if(update && update(_step)) break;
		}
	}else{
		for(unsigned int i = 0; i < ustep; i ++){
			_step += direction;
			_rotator(direction);
			_delay(_speed);
			if(update && update(_step)) break;
		}
	}
}
void Suteppa::_rotateAbsolute(long step, bool skip, int (*update)(int))
{
	if(skip){
		step = step%_allStep;
		_step = _step%_allStep;
		unsigned long diff = abs(step - _step);
		if(diff > _allStep / 2){
			if(_step < step){
				step = -(_allStep - diff);
			}else{
				step = (_allStep - diff);
			}
		}else{
			step = step - _step;
		}
	}else{
		step = step - _step;
	}
	_rotateRelative(step, update);
}
void Suteppa::setHome()
{
	_step = 0;
}
float Suteppa::sigmoid(float x)
{
	return 1 / (1 + exp(-7 * x));
}
void Suteppa::_delay(unsigned long time)
{
	if(time < 10000){
		delayMicroseconds(time);
	}else{
		delay(time/1000);
	}
}