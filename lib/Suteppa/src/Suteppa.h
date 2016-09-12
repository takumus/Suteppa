#ifndef SUTEPPA_H
#define SUTEPPA_H
#include <Arduino.h>

class Suteppa
{
	public:
		Suteppa();
		void init(int allStep, int adStep, int begin, int max, void (*rotater)(int));
		void rotateR(int step, bool smooth);
		void rotateA();
	private:
		int _allStep;
		int _begin;
		int _max;
		int _mbDiff;
		int _adStep;
		float sigmoid(float x);
		void (*_rotater)(int);
};

#endif