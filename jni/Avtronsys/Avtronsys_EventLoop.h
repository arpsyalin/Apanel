/**************************************
 * 	文件名	：Avtronsys_EventLoop.h
 *	作用		：事件循环等待以及分发的类API
 *	作者		：刘亚林
 *	创建时间	：2012/09/24
 *	最后修改	：刘亚林	 2012/09/24
 *	修改说明	: 创建该文件
 *	遗留说明	 ：暂无
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
		//主循环用以循环等待事件消息
		void LoopRun(Avtronsys::ActivityHandler* pActivityHandler,InputHandler* pInputHandler);
	protected:
		//进行事件消息分发
		int32_t input_handout(AInputEvent* pEvent);
	private:
		//对于输入消息的回调(必须是静态的方法)
		static int32_t input_callback(android_app* pApplication, AInputEvent* pEvent);

		//对于命令的执行(必须是静态的方法)
		static void cmd_dist(android_app* pApplication, int32_t pcmd);
		void cmd_exec(int32_t pcmd);
	protected:
		void Activity();	//激活
		void DesActivity();	//摧毁
	private:
		//当应用是主动停下了保存状态
		bool mEnabled;
		//当事件处理程序想要退出
		bool mExit;
	private:
		ActivityHandler* mActivityHandler;		//Activity事件处理
		InputHandler* mInputHandler;			//消息事件处理
	public:
		android_app * mApplication;
	};
}
#endif
