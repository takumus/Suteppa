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
	_tmpAdStep = _adStep;
	_tmpMax = 1;
	_tmpStep = step;
	float interval = _tmpMax / (float)_tmpAdStep;
	if(step < _tmpAdStep*2.1) {
		_tmpAdStep = step/2.1;
	}
	_tmpMax = interval * _tmpAdStep;
	_index = 0;
}
int Suteppa::step()
{
	if(_index >= _tmpStep) return 0;
	_tmpR = -1;
	if (_index <= _tmpAdStep) {
		_tmpR = (_index / (float)_tmpAdStep);
	}else if (_tmpStep - _index <= _tmpAdStep + 1) {
		_tmpR = ((_tmpStep - 1) - _index) / (float)_tmpAdStep;
	}
	float p;
	if(_tmpR<0){
		p = _tmpMax;
	}else{
		p = sin(acos(1-_tmpR)) * _tmpMax;
	}
	_index ++;
	if(_index >= _tmpStep) return 0;
	int interval = (1-p)*_mbDiff + _max;
	delayMicroseconds(interval);
	return 1;
}
float Suteppa::sigmoid(float x)
{
	return 1 / (1 + exp(-7 * x));
}