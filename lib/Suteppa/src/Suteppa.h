#ifndef SUTEPPA_H
#define SUTEPPA_H
#include <Arduino.h>

class Suteppa
{
	public:
		Suteppa();
		void init(int allStep, int adStep, int begin, int max, void (*rotator)(int));
		void setMax(int max);
		void setBegin(int begin);
		void setSmooth(bool smooth);

		void rotate(int step, int mode, int (*update)(int));
		void rotate(int step, int mode);
		void setHome();
	private:
		void _delay(int time);
		void _rotateAbsolute(int step, bool skip, int (*update)(int));
		void _rotateRelative(int step, int (*update)(int));
		bool _smooth = false;
		int _step;
		int _allStep;
		int _begin;
		int _max;
		int _mbDiff;
		int _adStep;
		float sigmoid(float x);
		void (*_rotator)(int);
};

#endif