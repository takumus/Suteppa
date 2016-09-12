#ifndef SUTEPPA_H
#define SUTEPPA_H
#include <Arduino.h>

class Suteppa
{
	public:
		Suteppa(int step, int adStep, int begin, int max);
		void set(int step);
		int step();
	private:
		int _step;
		int _begin;
		int _max;
		int _mbDiff;
		int _adStep;

		int _index;
		int _tmpAdStep;
		int _tmpStep;
		float _tmpMax;
		float _tmpR;
		float sigmoid(float x);
};

#endif