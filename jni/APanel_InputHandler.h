#ifndef _AVTRONSYS_INPUTHANDLER_H
#define _AVTRONSYS_INPUTHANDLER_H
#include "Avtronsys/Avtronsys_InputHandler.h"
#endif

#ifndef _AVTRONSYS_CONTEXT_H
#define _AVTRONSYS_CONTEXT_H
#include "Avtronsys/Avtronsys_Context.h"
#endif

#ifndef _AVTRONSYS_TYPEDEF_H
#define _AVTRONSYS_TYPEDEF_H
#include "Avtronsys/Avtronsys_TypeDef.h"
#endif


#ifndef _APANEL_DRAWING_H
#define _APANEL_DRAWING_H
#include "APanel_Drawing.h"
#endif

#ifndef _SYSTEM_INPUT_H
#define _SYSTEM_INPUT_H
#include <android/input.h>
#endif

#ifndef _SYSTEM_SENSOR_H
#define _SYSTEM_SENSOR_H
#include <android/sensor.h>
#endif

#ifndef _SYSTEM_NATIVE_APP_GLUE_H
#define _SYSTEM_NATIVE_APP_GLUE_H
#include <android_native_app_glue.h>
#endif

#ifndef _APANEL_EXIT_H
#define _APANEL_EXIT_H
#include "APanel_Exit.h"
#endif

namespace APanel
{
	class APanelInputHandler:public Avtronsys::InputHandler
	{
	public :
		APanelInputHandler(android_app* pApplication,Drawing * pDrawing,APanel::Exit* pExit);
	public:
		bool onTouchEvent(AInputEvent* pEvent);
		bool onKeyboardEvent(AInputEvent* pEvent);
		bool onTrackballEvent(AInputEvent* pEvent);
		bool onAccelerometerEvent(ASensorEvent* pEvent);
	private :
		android_app* mApplication;
		Drawing* mDrawing;
		APanel::Exit* mExit;
	};
}
