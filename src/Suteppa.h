#ifndef SUTEPPA_H
#define SUTEPPA_H
#include <Arduino.h>

class Suteppa
{
	public:
		Suteppa();
		void init(int allStep, int adStep, void (*rotator)(int));
		void setMax(unsigned long max);
		void setBegin(unsigned long begin);
		void setSmooth(bool smooth);
		
		int getStep(){return _step;};
		unsigned long getMax(){return _max;};
		unsigned long getBegin(){return _begin;};

		void rotate(int mode, int step, int (*update)(int));
		void rotate(int mode, int step);
		void setHome();

		static const int RELATIVE = 0;
		static const int ABSOLUTE = 1;
		static const int ABSOLUTE_SKIP = 2;
	private:
		void _delay(int time);
		void _rotateAbsolute(int step, bool skip, int (*update)(int));
		void _rotateRelative(int step, int (*update)(int));
		//仮用アップデート
		bool _smooth = false;
		int _step;
		int _allStep;
		unsigned long _begin;
		unsigned long _max;
		unsigned long _mbDiff;
		int _adStep;
		float sigmoid(float x);
		void (*_rotator)(int);
};

#endif