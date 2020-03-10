#ifndef _SYSTEM_INPUT_H
#define _SYSTEM_INPUT_H
#include <android/input.h>
#endif

#ifndef _SYSTEM_SENSOR_H
#define _SYSTEM_SENSOR_H
#include <android/sensor.h>
#endif

namespace Avtronsys
{
	class InputHandler
	{
		public:
			virtual ~InputHandler() {};
			virtual bool onTouchEvent(AInputEvent* pEvent) = 0;
			virtual bool onKeyboardEvent(AInputEvent* pEvent) = 0;
			virtual bool onTrackballEvent(AInputEvent* pEvent) = 0;
			virtual bool onAccelerometerEvent(ASensorEvent* pEvent) = 0;
	};
}
