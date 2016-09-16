#ifndef SUTEPPA_H
#define SUTEPPA_H
#include <Arduino.h>

class Suteppa
{
	public:
		Suteppa();
		void init(unsigned long allStep, void (*rotator)(int));
		void setSpeed(unsigned long speed);
		
		void setDefaultSmooth(unsigned long step, unsigned long initSpeed);

		void beginSmooth(unsigned long step, unsigned long initSpeed);
		void beginSmooth();

		void endSmooth(){_smooth = false;};

		long getStep(){return _step;};

		unsigned long getSpeed(){return _speed;};

		void rotate(int mode, long step, int (*update)(int));
		void rotate(int mode, long step);

		void setHome();

		static const int RELATIVE = 0;
		static const int ABSOLUTE = 1;
		static const int ABSOLUTE_SKIP = 2;
	private:
		void _delay(unsigned long time);
		
		void _rotateAbsolute(long step, bool skip, int (*update)(int));
		void _rotateRelative(long step, int (*update)(int));

		void (*_rotator)(int);

		bool _smooth = false;
		
		long _step;
		
		unsigned long _allStep;
		unsigned long _speed;
		unsigned long _initDiff;
		unsigned long _smoothStep;
		
		float sigmoid(float x);
};

#endif