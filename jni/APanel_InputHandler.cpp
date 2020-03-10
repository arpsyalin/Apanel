#ifndef _APANEL_INPUTHANDLER_H
#define _APANEL_INPUTHANDLER_H
#include "APanel_InputHandler.h"
#endif

#ifndef _AVTRONSYS_LOG_H
#define _AVTRONSYS_LOG_H
#include "Avtronsys/Avtronsys_Log.h"
#endif

#ifndef _APANEL_TYPE_H
#define _APANEL_TYPE_H
#include "APanel_Type.h"
#endif

namespace APanel
{

	APanelInputHandler::APanelInputHandler(android_app* pApplication,Drawing * pDrawing,APanel::Exit* pExit):
			mApplication(pApplication),mDrawing(pDrawing),mExit(pExit)
	{

	}

	bool APanelInputHandler::onTouchEvent(AInputEvent* pEvent)
	{
		Avtronsys::Log::info("MotionEvent!!!!");
		float fx,fy;
		fx=AMotionEvent_getX(pEvent,0);
		fy=AMotionEvent_getY(pEvent,0);
		int32_t EventType = AMotionEvent_getAction(pEvent);

		switch(EventType)
		{
			case AMOTION_EVENT_ACTION_DOWN:
				mDrawing->TouchSet(mTouchDown,fx,fy);
				Avtronsys::Log::info("AMOTION_EVENT_ACTION_DOWN!x:%f,y:%f.",fx,fy);
				break;
			case AMOTION_EVENT_ACTION_UP:
				mDrawing->TouchSet(mTouchUp,fx,fy);
				Avtronsys::Log::info("AMOTION_EVENT_ACTION_UP!x:%f,y:%f.",fx,fy);
				break;
			case AMOTION_EVENT_ACTION_MOVE:
				mDrawing->TouchSet(mTouchMove,fx,fy);
				Avtronsys::Log::info("AMOTION_EVENT_ACTION_MOVE!x:%f,y:%f.",fx,fy);
				break;
			case AMOTION_EVENT_ACTION_OUTSIDE:
				mDrawing->TouchSet(mTouchOutside,fx,fy);
				Avtronsys::Log::info("AMOTION_EVENT_ACTION_OUTSIDE!x:%f,y:%f.",fx,fy);
				break;
			default:
				Avtronsys::Log::info("AMOTION default!x:%f,y:%f.",fx,fy);
				break;
		}
		//mDrawing->Draw();
		return 1;
	}

	bool APanelInputHandler::onKeyboardEvent(AInputEvent* pEvent)
	{
		Avtronsys::Log::info("KeyboardEvent!!!!,%d",AKeyEvent_getFlags(pEvent));

		switch(AKeyEvent_getFlags(pEvent))
		{
		case AKEY_EVENT_FLAG_WOKE_HERE:
			Avtronsys::Log::info("AKEY_EVENT_FLAG_WOKE_HERE!!!!");
			switch(AKeyEvent_getAction(pEvent))
			{
			case AKEY_EVENT_ACTION_DOWN:
				Avtronsys::Log::info("WOKE_HERE DOWN!!");
				break;
			case AKEY_EVENT_ACTION_UP:
				Avtronsys::Log::info("WOKE_HERE UP!!");
				break;
			case AKEY_EVENT_ACTION_MULTIPLE:
				Avtronsys::Log::info("WOKE_HERE MULTIPLE!!");
				break;
			}
			break;
		case AKEY_EVENT_FLAG_SOFT_KEYBOARD:
			Avtronsys::Log::info("SOFT_KEYBOARD!!!!");
			switch(AKeyEvent_getAction(pEvent))
			{
			case AKEY_EVENT_ACTION_DOWN:
				break;
			case AKEY_EVENT_ACTION_UP:
				break;
			case AKEY_EVENT_ACTION_MULTIPLE:
				break;
			}
			break;
		case AKEY_EVENT_FLAG_KEEP_TOUCH_MODE:
			Avtronsys::Log::info("TOUCH_MODE!!!!");
			switch(AKeyEvent_getAction(pEvent))
			{
			case AKEY_EVENT_ACTION_DOWN:
				break;
			case AKEY_EVENT_ACTION_UP:
				break;
			case AKEY_EVENT_ACTION_MULTIPLE:
				break;
			}
			break;
		case AKEY_EVENT_FLAG_FROM_SYSTEM:
			Avtronsys::Log::info("AKEY_EVENT_FLAG_FROM_SYSTEM!!!!");
			switch(AKeyEvent_getAction(pEvent))
			{
			case AKEY_EVENT_ACTION_DOWN:
				break;
			case AKEY_EVENT_ACTION_UP:
				break;
			case AKEY_EVENT_ACTION_MULTIPLE:
				break;
			}
			break;
		case AKEY_EVENT_FLAG_EDITOR_ACTION:
			Avtronsys::Log::info("AKEY_EVENT_FLAG_EDITOR_ACTION!!!!");
			switch(AKeyEvent_getAction(pEvent))
			{
			case AKEY_EVENT_ACTION_DOWN:
				break;
			case AKEY_EVENT_ACTION_UP:
				break;
			case AKEY_EVENT_ACTION_MULTIPLE:
				break;
			}
			break;
		case AKEY_EVENT_FLAG_CANCELED:
			Avtronsys::Log::info("CANCELED!!!!");
			switch(AKeyEvent_getAction(pEvent))
			{
			case AKEY_EVENT_ACTION_DOWN:
				break;
			case AKEY_EVENT_ACTION_UP:
				break;
			case AKEY_EVENT_ACTION_MULTIPLE:
				break;
			}
			break;
		case AKEY_EVENT_FLAG_VIRTUAL_HARD_KEY:
			Avtronsys::Log::info("VIRTUAL_HARD_KEY!!!!");
			switch(AKeyEvent_getAction(pEvent))
			{
			case AKEY_EVENT_ACTION_DOWN:
				break;
			case AKEY_EVENT_ACTION_UP:
				break;
			case AKEY_EVENT_ACTION_MULTIPLE:
				break;
			}
			break;
		case AKEY_EVENT_FLAG_LONG_PRESS:
			Avtronsys::Log::info("LONG_PRESS!!!!");
			switch(AKeyEvent_getAction(pEvent))
			{
			case AKEY_EVENT_ACTION_DOWN:
				break;
			case AKEY_EVENT_ACTION_UP:
				break;
			case AKEY_EVENT_ACTION_MULTIPLE:
				break;
			}
			break;
	    case AKEY_EVENT_FLAG_CANCELED_LONG_PRESS:
	    	Avtronsys::Log::info("CANCELED_LONG_PRESS!!!!");
	    	switch(AKeyEvent_getAction(pEvent))
			{
			case AKEY_EVENT_ACTION_DOWN:
				break;
			case AKEY_EVENT_ACTION_UP:
				break;
			case AKEY_EVENT_ACTION_MULTIPLE:
				break;
			}
			break;
	    case AKEY_EVENT_FLAG_TRACKING:
	    	Avtronsys::Log::info("FLAG_TRACKING!!!!");
	    	switch(AKeyEvent_getAction(pEvent))
			{
			case AKEY_EVENT_ACTION_DOWN:
				break;
			case AKEY_EVENT_ACTION_UP:
				break;
			case AKEY_EVENT_ACTION_MULTIPLE:
				break;
			}
	    	break;
	    	default:
	    		break;
		}
		return 1;
	}

	bool APanelInputHandler::onTrackballEvent(AInputEvent* pEvent)
	{
		Avtronsys::Log::info("TrackballEvent!!!!");
		return 1;
	}

	bool APanelInputHandler::onAccelerometerEvent(ASensorEvent* pEvent)
	{
		Avtronsys::Log::info("AccelerometerEvent!!!!");
		return 1;
	}
}
