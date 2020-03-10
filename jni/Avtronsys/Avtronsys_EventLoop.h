/**************************************
 * 	�ļ���	��Avtronsys_EventLoop.h
 *	����		���¼�ѭ���ȴ��Լ��ַ�����API
 *	����		��������
 *	����ʱ��	��2012/09/24
 *	����޸�	��������	 2012/09/24
 *	�޸�˵��	: �������ļ�
 *	����˵��	 ������
 ***************************************/
#ifndef _AVTRONSYS_ACTIVITYHANDLER_H
#define _AVTRONSYS_ACTIVITYHANDLER_H
#include "Avtronsys_ActivityHandler.h"
#endif

#ifndef _AVTRONSYS_INPUTHANDLER_H
#define _AVTRONSYS_INPUTHANDLER_H
#include "Avtronsys_InputHandler.h"
#endif


#ifndef _SYSTEM_NATIVE_APP_GLUE_H
#define _SYSTEM_NATIVE_APP_GLUE_H
#include <android_native_app_glue.h>
#endif

#ifndef _AVTRONSYS_EVENTLOOP_H_
#define	_AVTRONSYS_EVENTLOOP_H_
namespace Avtronsys
{
	class EventLoop
	{
	public:
		EventLoop(android_app* pApplication);
		//��ѭ������ѭ���ȴ��¼���Ϣ
		void LoopRun(Avtronsys::ActivityHandler* pActivityHandler,InputHandler* pInputHandler);
	protected:
		//�����¼���Ϣ�ַ�
		int32_t input_handout(AInputEvent* pEvent);
	private:
		//����������Ϣ�Ļص�(�����Ǿ�̬�ķ���)
		static int32_t input_callback(android_app* pApplication, AInputEvent* pEvent);

		//���������ִ��(�����Ǿ�̬�ķ���)
		static void cmd_dist(android_app* pApplication, int32_t pcmd);
		void cmd_exec(int32_t pcmd);
	protected:
		void Activity();	//����
		void DesActivity();	//�ݻ�
	private:
		//��Ӧ��������ͣ���˱���״̬
		bool mEnabled;
		//���¼����������Ҫ�˳�
		bool mExit;
	private:
		ActivityHandler* mActivityHandler;		//Activity�¼�����
		InputHandler* mInputHandler;			//��Ϣ�¼�����
	public:
		android_app * mApplication;
	};
}
#endif
