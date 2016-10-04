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
		long getStepAbsolute(){return _step%_allStep;};

		unsigned long getSpeed(){return _speed;};

		void rotate(int mode, long step, bool sync);
		void rotate(int mode, long step);

		void setHome();
		bool tick();

		static const int RELATIVE = 0;
		static const int ABSOLUTE = 1;
		static const int ABSOLUTE_SKIP = 2;
	private:
		void _delay(unsigned long time);
		
		void _rotateAbsolute(long step, bool skip, bool sync);
		void _rotateRelative(long step, bool sync);

		void (*_rotator)(int);

		bool _smooth = false;
		
		long _step;
		
		unsigned long _allStep;
		unsigned long _speed;
		unsigned long _initDiff;
		unsigned long _smoothStep;
		unsigned long _initSpeed;

		unsigned long _defaultSmoothStep;
		unsigned long _defaultInitSpeed;

		int _r_direction;
		unsigned long _r_step;
		unsigned long _r_smoothStep;
		bool _r_smooth;
		float _r_max;
		unsigned int _r_i;
		unsigned long _r_time;
		unsigned long _r_interval;
		
		float sigmoid(float x);
};

#endif