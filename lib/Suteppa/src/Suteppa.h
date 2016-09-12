#ifndef SUTEPPA_H
#define SUTEPPA_H
#include <Arduino.h>

class Suteppa
{
	public:
		Suteppa(int step, int adStep, int begin, int max);
		void set(int step);
	private:
		int _step;
		int _begin;
		int _max;
		int _mbDiff;
		int _adStep;
		
		int _tmpAdStep;
		int _tmpMax;
		int _tmpInterval;
		int _tmpR;
};

#endif