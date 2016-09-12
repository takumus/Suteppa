#ifndef SUTEPPA_H
#define SUTEPPA_H
#include <Arduino.h>

class Suteppa
{
	public:
		Suteppa();
		void init(int allStep, int adStep, int begin, int max, bool smooth, void (*rotater)(int));
		void rotateR(int step);
		void rotateA(int step, bool skip);
		void setHome();
	private:
		bool _smooth;
		int _step;
		int _allStep;
		int _begin;
		int _max;
		int _mbDiff;
		int _adStep;
		float sigmoid(float x);
		void (*_rotater)(int);
};

#endif