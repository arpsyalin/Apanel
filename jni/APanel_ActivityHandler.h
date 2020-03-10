/**************************************
 * 	文件名	：Avtronsys_ActivityHandler.h
 *	作用		：Activity的基类的继承类
 *	作者		：刘亚林
 *	创建时间	：2012/09/25
 *	最后修改	：刘亚林	 2012/09/25
 *	修改说明	: 创建该文件
 *	遗留说明	 ：暂无
 ***************************************/
#ifndef _AVTRONSYS_ACTIVITYHANDLER_H
#define _AVTRONSYS_ACTIVITYHANDLER_H
#include "Avtronsys/Avtronsys_ActivityHandler.h"
#endif

#ifndef _AVTRONSYS_TYPEDEF_H
#define _AVTRONSYS_TYPEDEF_H
#include "Avtronsys/Avtronsys_TypeDef.h"
#endif

#ifndef _AVTRONSYS_CONTEXT_H
#define _AVTRONSYS_CONTEXT_H
#include "Avtronsys/Avtronsys_Context.h"
#endif

#ifndef _APANEL_DRAWING_H
#define _APANEL_DRAWING_H
#include "APanel_Drawing.h"
#endif

#ifndef _APANEL_EXIT_H
#define _APANEL_EXIT_H
#include "APanel_Exit.h"
#endif

#ifndef _SYSTEM_NATIVE_APP_GLUE_H
#define _SYSTEM_NATIVE_APP_GLUE_H
#include <android_native_app_glue.h>
#endif

namespace APanel
{
	//是否是旋转屏幕或者说第2次
	class APanelActivityHandler:public Avtronsys::ActivityHandler
	{
	public :
		APanelActivityHandler(Avtronsys::Context* pContext,APanel::Drawing* pDrawing,APanel::Exit* pExit,android_app* pApplication);
		virtual ~APanelActivityHandler();
	protected:
		//窗体的获得焦点并且可用
		Avtronsys::statedef onActivate();
		//暂停或显示窗口失去焦点或被摧毁。
		void onDesActivate();
		//没有事件调用发生的时候可发生
		Avtronsys::statedef onStep();

		//每一个事件都有一个生命周期下面是定义这些生命周期的函数
		void onStart();		//开始
		void onResume();	//重新开始
		void onPause();		//暂停
		void onStop();		//停止
		void onDestroy();	//摧毁

		void onSaveState(void** pData,size_t* pSize);	//保存状态
		void onConfigurationChanged();					//配置改变
		void onLowMemory();								//低内存的时候

		//活动窗体
		void onCreateWindow();	//窗体的创建
		void onDestroyWindow();	//窗体的摧毁
		void onGainFocus();		//添加/获得焦点
		void onLostFocus();		//移除/失去焦点
		void onResized();		//窗体改变大小

		void onRDraw();				//重绘
		void onRRECT();				//矩形内容改变
		static void* TestWeblinkThread(void*);
	private :
		///屏幕EGL
		Avtronsys::AvtronsysEGLDisplay* mAvtronsysEGLDisplay;
		android_app* mApplication;
		//消息处理
		Avtronsys::InputHandler* mInputHandler;
		//绘制
		APanel::Drawing* mDrawing;
		APanel::Exit* mExit;
	};
}
