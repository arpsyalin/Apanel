/**************************************
 * 	文件名	：Avtronsys_EGLDisplay.h
 *	作用		：一系列的EGL工作API
 *	作者		：刘亚林
 *	创建时间	：2012/09/25
 *	最后修改	：刘亚林	 2012/09/25
 *	修改说明	: 添加了4个打印日志的实现
 *	遗留说明	 ：暂无
 ***************************************/
#ifndef _SYSTEM_EGL_H
#define _SYSTEM_EGL_H
#include <EGL/egl.h>
#endif

#ifndef _SYSTEM_NATIVE_APP_GLUE_H
#define _SYSTEM_NATIVE_APP_GLUE_H
#include <android_native_app_glue.h>
#endif

namespace Avtronsys
{
	class AvtronsysEGLDisplay
	{
	public :
		AvtronsysEGLDisplay(android_app* pApplication);
	public :
		int EGLInit();		//初始化
		void EGLDest();		//销毁
		int EGLUpdate();	//更新屏幕
		int32_t getWidth();	//获得屏宽
		int32_t getHeight();//获得屏高
	private:
		android_app* mApplication;

		EGLDisplay mDisplay;	//屏幕
		EGLContext mContext;	//对象
		EGLSurface mSurface;	//帧缓存
		int32_t mWidth;			//屏宽
		int32_t mHeight;		//屏高
	};
}
