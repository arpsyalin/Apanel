/**************************************
 * 	�ļ���	��Avtronsys_EventLoop.h
 *	����		���¼�ѭ���ȴ��Լ��ַ�����ʵ��
 *	����		��������
 *	����ʱ��	��2012/09/24
 *	����޸�	��������	 2012/09/24
 *	�޸�˵��	: �������ļ�
 *	����˵��	 ������
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
		//��ֵuserData
		mApplication->userData=this;
		//�󶨴����������¼�����
		mApplication->onInputEvent = input_callback;
		//�������
		mApplication->onAppCmd = cmd_dist;
	}

	void EventLoop::LoopRun(Avtronsys::ActivityHandler* pActivityHandler,
							Avtronsys::InputHandler* pInputHandler)
	{
        int32_t lEvent,lResult;
        android_poll_source* lsource;
        mActivityHandler = pActivityHandler;
        mInputHandler = pInputHandler;

    	//ȷ��glue�Ĵ�����Ч
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
	//�����¼�
	int32_t EventLoop::input_callback(android_app* pApplication, AInputEvent* pEvent)
	{
        EventLoop& lEventLoop = *(EventLoop*) pApplication->userData;
        return lEventLoop.input_handout(pEvent);
	}

	//�����¼���Ϣ�ַ�
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

	///ʵ��activity����
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

	//ʵ��activity�ݻ�
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
			case   APP_CMD_TERM_WINDOW://���մ���
				Avtronsys::Log::info("APP_CMD_TERM_WINDOW ");
				mActivityHandler->onDestroyWindow();
				DesActivity();
				break;
			case   APP_CMD_GAINED_FOCUS://�õ�����
				DesActivity();
				Avtronsys::Log::info("APP_CMD_GAINED_FOCUS ");
				mActivityHandler->onGainFocus();
				break;
			case   APP_CMD_LOST_FOCUS:	//ʧȥ����
				Avtronsys::Log::info("APP_CMD_LOST_FOCUS ");
				mActivityHandler->onLostFocus();
				DesActivity();
				break;
			case   APP_CMD_CONFIG_CHANGED://��ǰ�豸���øı�
				Avtronsys::Log::info("APP_CMD_CONFIG_CHANGED ");
				mActivityHandler->onConfigurationChanged();
				break;
			case   APP_CMD_LOW_MEMORY://�豸�ڴ治��
				Avtronsys::Log::info("APP_CMD_LOW_MEMORY ");
				mActivityHandler->onLowMemory();
				break;
			case   APP_CMD_START://��ʼ
				Avtronsys::Log::info("APP_CMD_START ");
				mActivityHandler->onStart();
				break;
			case   APP_CMD_RESUME://���¿�ʼ
				Avtronsys::Log::info("APP_CMD_RESUME ");
				mActivityHandler->onResume();
				break;
			case   APP_CMD_SAVE_STATE://����״̬
				Avtronsys::Log::info("APP_CMD_SAVE_STATE ");
				mActivityHandler->onSaveState(&mApplication->savedState,&mApplication->savedStateSize);
				break;
			case   APP_CMD_PAUSE://��ͣ
				Avtronsys::Log::info("APP_CMD_PAUSE ");
				mActivityHandler->onPause();
				break;
			case   APP_CMD_STOP://ֹͣ
				Avtronsys::Log::info("APP_CMD_STOP ");
				mActivityHandler->onStop();
				break;
			case   APP_CMD_DESTROY://����
				Avtronsys::Log::info("APP_CMD_DESTROY ");
				mActivityHandler->onDestroy();
				break;
			case APP_CMD_INPUT_CHANGED://���뷢���ı�
				Avtronsys::Log::info("APP_CMD_INPUT_CHANGED ");
				break;
			case  APP_CMD_INIT_WINDOW://������ʼ������
				Avtronsys::Log::info("APP_CMD_INIT_WINDOW ");
				mActivityHandler->onCreateWindow();
				break;
			case   APP_CMD_WINDOW_RESIZED://���������С���ػ�
				Avtronsys::Log::info("APP_CMD_WINDOW_RESIZED ");
				mActivityHandler->onResized();
				break;
			case   APP_CMD_WINDOW_REDRAW_NEEDED://��Ҫ�ػ�androidӦ��exec cmd()�Ա���˲̬ͼ���ϡ�
				Avtronsys::Log::info("APP_CMD_WINDOW_REDRAW_NEEDED ");
				mActivityHandler->onRDraw();
				break;
			case   APP_CMD_CONTENT_RECT_CHANGED://�������ݸı�
				Avtronsys::Log::info("APP_CMD_CONTENT_RECT_CHANGED ");
				mActivityHandler->onRRECT();
				break;
			default:
				Avtronsys::Log::info("DEFAULT!");
				break;
		}
	}
}
