/**************************************
 * 	文件名	：Avtronsys_EventLoop.h
 *	作用		：事件循环等待以及分发的类实现
 *	作者		：刘亚林
 *	创建时间	：2012/09/24
 *	最后修改	：刘亚林	 2012/09/24
 *	修改说明	: 创建该文件
 *	遗留说明	 ：暂无
 ***************************************/
#ifndef _AVTRONSYS_EVENTLOOP_H
#define _AVTRONSYS_EVENTLOOP_H
#include "Avtronsys_EventLoop.h"
#endif

#ifndef _AVTRONSYS_LOG_H
#define _AVTRONSYS_LOG_H
#include "Avtronsys_Log.h"
#endif

#ifndef _SYSTEM_SENSOR_H
#define _SYSTEM_SENSOR_H
#include <android/sensor.h>
#endif
#include <unistd.h>

namespace Avtronsys
{
	EventLoop::EventLoop(android_app* pApplication)
		:mApplication(pApplication)
		,mInputHandler(NULL)
		,mActivityHandler(NULL)
	{
		//赋值userData
		mApplication->userData=this;
		//绑定处理按键处理事件函数
		mApplication->onInputEvent = input_callback;
		//绑定命令函数
		mApplication->onAppCmd = cmd_dist;
	}

	void EventLoop::LoopRun(Avtronsys::ActivityHandler* pActivityHandler,
							Avtronsys::InputHandler* pInputHandler)
	{
        int32_t lEvent,lResult;
        android_poll_source* lsource;
        mActivityHandler = pActivityHandler;
        mInputHandler = pInputHandler;

    	//确保glue的代码有效
    	app_dummy();
    	while(true)
    	{
    		while((lResult=ALooper_pollAll(-1,NULL,&lEvent,(void**)&lsource))>=0)
    		{
    			if(lsource!=NULL)
    			{
    				Avtronsys::Log::info("Event fund");
    				lsource->process(mApplication,lsource);
    			}
    			if(mApplication->destroyRequested)
    			{
    				 return;
    			}
    		}
    		if((mEnabled)&&(!mExit))
			{
				if((mActivityHandler->onStep())!=state_Succse)
				{
					mExit=true;
					ANativeActivity_finish(mApplication->activity);
				}
			}
    	}
	}
	//接受事件
	int32_t EventLoop::input_callback(android_app* pApplication, AInputEvent* pEvent)
	{
        EventLoop& lEventLoop = *(EventLoop*) pApplication->userData;
        return lEventLoop.input_handout(pEvent);
	}

	//进行事件消息分发
	int32_t EventLoop::input_handout(AInputEvent* pEvent)
	{
		int32_t lEventType = AInputEvent_getType(pEvent);
		 switch (lEventType) {
			case AINPUT_EVENT_TYPE_MOTION:
				switch (AInputEvent_getSource(pEvent)) {
				case AINPUT_SOURCE_TOUCHSCREEN:
					return mInputHandler->onTouchEvent(pEvent);
					break;
				case AINPUT_SOURCE_TRACKBALL:
					return mInputHandler->onTrackballEvent(pEvent);
					break;
				}
				break;
			case AINPUT_EVENT_TYPE_KEY:
				return mInputHandler->onKeyboardEvent(pEvent);
				break;
			default:
				break;
		 }
	}

	///实现activity激活
	void EventLoop::Activity()
	{
		if((!mEnabled)&&(mApplication->window!=NULL))
		{
			mEnabled =true;
			mExit=false;
			if(mActivityHandler->onActivate()!=state_Succse)
			{
				mExit=true;
				DesActivity();
				ANativeActivity_finish(mApplication->activity);
			}
		}
	}

	//实现activity摧毁
	void EventLoop::DesActivity()
	{
		if (mEnabled)
		{
			mActivityHandler->onDesActivate();
			mEnabled=false;
		}
	}

	void EventLoop::cmd_dist(android_app* pApplication,int32_t pcmd)
	{
		EventLoop& lEventLoop=*(EventLoop*)pApplication->userData;
		lEventLoop.cmd_exec(pcmd);
	}

	void EventLoop::cmd_exec(int32_t pcmd)
	{
		//int cmd;
		Avtronsys::Log::info("pCommand : %d",pcmd);
		switch(pcmd)
		{
			case   APP_CMD_TERM_WINDOW://回收窗体
				Avtronsys::Log::info("APP_CMD_TERM_WINDOW ");
				mActivityHandler->onDestroyWindow();
				DesActivity();
				break;
			case   APP_CMD_GAINED_FOCUS://得到焦点
				DesActivity();
				Avtronsys::Log::info("APP_CMD_GAINED_FOCUS ");
				mActivityHandler->onGainFocus();
				break;
			case   APP_CMD_LOST_FOCUS:	//失去焦点
				Avtronsys::Log::info("APP_CMD_LOST_FOCUS ");
				mActivityHandler->onLostFocus();
				DesActivity();
				break;
			case   APP_CMD_CONFIG_CHANGED://当前设备配置改变
				Avtronsys::Log::info("APP_CMD_CONFIG_CHANGED ");
				mActivityHandler->onConfigurationChanged();
				break;
			case   APP_CMD_LOW_MEMORY://设备内存不足
				Avtronsys::Log::info("APP_CMD_LOW_MEMORY ");
				mActivityHandler->onLowMemory();
				break;
			case   APP_CMD_START://开始
				Avtronsys::Log::info("APP_CMD_START ");
				mActivityHandler->onStart();
				break;
			case   APP_CMD_RESUME://重新开始
				Avtronsys::Log::info("APP_CMD_RESUME ");
				mActivityHandler->onResume();
				break;
			case   APP_CMD_SAVE_STATE://保存状态
				Avtronsys::Log::info("APP_CMD_SAVE_STATE ");
				mActivityHandler->onSaveState(&mApplication->savedState,&mApplication->savedStateSize);
				break;
			case   APP_CMD_PAUSE://暂停
				Avtronsys::Log::info("APP_CMD_PAUSE ");
				mActivityHandler->onPause();
				break;
			case   APP_CMD_STOP://停止
				Avtronsys::Log::info("APP_CMD_STOP ");
				mActivityHandler->onStop();
				break;
			case   APP_CMD_DESTROY://销毁
				Avtronsys::Log::info("APP_CMD_DESTROY ");
				mActivityHandler->onDestroy();
				break;
			case APP_CMD_INPUT_CHANGED://输入发生改变
				Avtronsys::Log::info("APP_CMD_INPUT_CHANGED ");
				break;
			case  APP_CMD_INIT_WINDOW://创建初始化窗体
				Avtronsys::Log::info("APP_CMD_INIT_WINDOW ");
				mActivityHandler->onCreateWindow();
				break;
			case   APP_CMD_WINDOW_RESIZED://窗体调整大小需重绘
				Avtronsys::Log::info("APP_CMD_WINDOW_RESIZED ");
				mActivityHandler->onResized();
				break;
			case   APP_CMD_WINDOW_REDRAW_NEEDED://需要重绘android应用exec cmd()以避免瞬态图故障。
				Avtronsys::Log::info("APP_CMD_WINDOW_REDRAW_NEEDED ");
				mActivityHandler->onRDraw();
				break;
			case   APP_CMD_CONTENT_RECT_CHANGED://矩形内容改变
				Avtronsys::Log::info("APP_CMD_CONTENT_RECT_CHANGED ");
				mActivityHandler->onRRECT();
				break;
			default:
				Avtronsys::Log::info("DEFAULT!");
				break;
		}
	}
}
