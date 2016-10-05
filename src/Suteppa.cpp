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
	_initDiff = _initSpeed - _speed;
}
void Suteppa::beginSmooth(unsigned long step, unsigned long initSpeed)
{
	_smoothStep = step;
	_initSpeed = initSpeed;
	_initDiff = _initSpeed - _speed;
	_smooth = true;
}
void Suteppa::beginSmooth()
{
	_smoothStep = _defaultSmoothStep;
	_initDiff = _defaultInitSpeed - _speed;
	_smooth = true;
}
void Suteppa::setDefaultSmooth(unsigned long step, unsigned long initSpeed)
{
	_defaultSmoothStep = step;
	_defaultInitSpeed = initSpeed;
}

bool Suteppa::tick()
{
	if(_r_i >= _r_step) return false;
	unsigned long time = micros();
	if(time - _r_time < _r_interval) return true;
	_r_time = time;
	if(_r_smooth){
		_step += _r_direction;
		_rotator(_r_direction);
		float r = -1;
		if (_r_i <= _r_smoothStep) {
			r = (_r_i / (float)_r_smoothStep);
		}else if (_r_step - _r_i <= _r_smoothStep + 1) {
			r = ((_r_step - 1) - _r_i) / (float)_r_smoothStep;
		}
		float p;
		if(r < 0){
			p = _r_max;
		}else{
			p = sin(acos(1 - r)) * _r_max;
		}
		_r_interval = (1 - p) * _initDiff + _speed;
	}else{
		_step += _r_direction;
		_rotator(_r_direction);
		_r_interval = _speed;
	}
	_r_i ++;
	return true;
}

void Suteppa::rotate(int mode, long step, bool sync)
{
	if(mode == 0){
		_rotateRelative(step, sync);
	}else if(mode == 1){
		_rotateAbsolute(step, false, sync);
	}else if(mode == 2){
		_rotateAbsolute(step, true, sync);
	}
}

void Suteppa::rotate(int mode, long step)
{
	rotate(mode, step, true);
}

void Suteppa::_rotateRelative(long step, bool sync)
{
	_r_smoothStep = _smoothStep;
	_r_direction = 1;
	float interval = 1 / (float)_r_smoothStep;
	_r_smooth = _smooth;

	if(step < 0){
		_r_direction = -1;
		step *= -1;
	}
	_r_step = step;
	if(step < _r_smoothStep*2.1) _r_smoothStep = step/2.1;
	if(_r_smoothStep < 1) _r_smooth = false;
	if(_initSpeed < _speed) _r_smooth = false;
	_r_max = interval * _r_smoothStep;
	_r_interval = 0;
	_r_time = 0;
	_r_i = 0;
	if(sync){
		while(tick());
	}
}
void Suteppa::_rotateAbsolute(long step, bool skip, bool sync)
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
	_rotateRelative(step, sync);
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