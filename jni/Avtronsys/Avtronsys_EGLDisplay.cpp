/**************************************
 * 	文件名	：Avtronsys_EGLDisplay.h
 *	作用		：一系列的EGL工作API的实现
 *	作者		：刘亚林
 *	创建时间	：2012/09/25
 *	最后修改	：刘亚林	 2012/09/25
 *	修改说明	: 添加了4个打印日志的实现
 *	遗留说明	 ：暂无
 ***************************************/
#ifndef _AVTRONSYS_EGLDISPLAY_H
#define _AVTRONSYS_EGLDISPLAY_H
#include "Avtronsys_EGLDisplay.h"
#endif

#ifndef _AVTRONSYS_TYPEDEF_H
#define _AVTRONSYS_TYPEDEF_H
#include "Avtronsys_TypeDef.h"
#endif

#ifndef _AVTRONSYS_LOG_H
#define _AVTRONSYS_LOG_H
#include "Avtronsys_Log.h"
#endif

namespace Avtronsys
{
	AvtronsysEGLDisplay::AvtronsysEGLDisplay(android_app* pApplication):
			mApplication(pApplication),
			mDisplay(EGL_NO_DISPLAY),
			mContext(EGL_NO_CONTEXT),
			mSurface(EGL_NO_SURFACE),
			mWidth(0),
			mHeight(0)
	{

	}

	int32_t AvtronsysEGLDisplay:: getWidth()
	{
		return mWidth;
	}

	int32_t AvtronsysEGLDisplay:: getHeight()
	{
		return mHeight;
	}

	//EGL的初始化
	int AvtronsysEGLDisplay::EGLInit()
	{
		const EGLint attribs[]=
			{
				EGL_SURFACE_TYPE,EGL_WINDOW_BIT,
				EGL_BLUE_SIZE,8,
				EGL_GREEN_SIZE,8,
				EGL_RED_SIZE,8,
				EGL_NONE
			};
			EGLint w,h,dummy,format;

			EGLint numConfigs;
			EGLConfig config;
			EGLSurface surface;
			EGLContext context;
			//获得默认的Display
			EGLDisplay display=eglGetDisplay(EGL_DEFAULT_DISPLAY);
			//初始化display
			if(!eglInitialize(display,0,0))
			{
				goto ERROR;
			}
			//选择第一个作为我们的标准配置
			if(!eglChooseConfig(display,attribs,&config,1,&numConfigs))
			{
				goto ERROR;
			}
			//获得配置的属性
			if(!eglGetConfigAttrib(display,config,EGL_NATIVE_VISUAL_ID,&format))
			{
				goto ERROR;
			}
			//
			ANativeWindow_setBuffersGeometry(mApplication->window,0,0,format);

			surface = eglCreateWindowSurface(display,config,mApplication->window,NULL);
			context = eglCreateContext(display,config,NULL,NULL);
			if(eglMakeCurrent(display,surface,surface,context)==EGL_FALSE)
			{
				goto ERROR;
			}
			//获得display的宽高
			eglQuerySurface(display,surface,EGL_WIDTH,&w);
			eglQuerySurface(display,surface,EGL_HEIGHT,&h);

			//给pDisplay的各项内容赋值
			mDisplay = display;
			mContext = context;
			mSurface = surface;
			mWidth = w;
			mHeight = h;
			return state_Succse;
		ERROR:
			Avtronsys::Log::error("EGLInit error!");
			EGLDest();
			return state_Fail;
	}

	//EGL的销毁
	void AvtronsysEGLDisplay:: EGLDest()
	{
		//初始化式的销毁
		if(mDisplay!=EGL_NO_DISPLAY)
		{
			eglMakeCurrent(mDisplay,EGL_NO_SURFACE,EGL_NO_SURFACE,EGL_NO_CONTEXT);
			if(mContext!=EGL_NO_CONTEXT)
			{
				eglDestroyContext(mDisplay,mContext);
			}
			if(mSurface!=EGL_NO_SURFACE)
			{
				eglDestroySurface(mDisplay,mSurface);
			}
			 eglTerminate(mDisplay);
		}
		mDisplay = EGL_NO_DISPLAY;
		mContext = EGL_NO_CONTEXT;
		mSurface = EGL_NO_SURFACE;
	}

	//更新屏幕
	int AvtronsysEGLDisplay::EGLUpdate()
	{
		if(eglSwapBuffers(mDisplay,mSurface)!=EGL_TRUE)
		{
			Avtronsys::Log::error("EGLUpdate error!");
			return state_Fail;
		}
		return state_Succse;
	}
}

