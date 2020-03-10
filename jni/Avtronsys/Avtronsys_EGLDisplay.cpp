/**************************************
 * 	�ļ���	��Avtronsys_EGLDisplay.h
 *	����		��һϵ�е�EGL����API��ʵ��
 *	����		��������
 *	����ʱ��	��2012/09/25
 *	����޸�	��������	 2012/09/25
 *	�޸�˵��	: �����4����ӡ��־��ʵ��
 *	����˵��	 ������
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

	//EGL�ĳ�ʼ��
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
			//���Ĭ�ϵ�Display
			EGLDisplay display=eglGetDisplay(EGL_DEFAULT_DISPLAY);
			//��ʼ��display
			if(!eglInitialize(display,0,0))
			{
				goto ERROR;
			}
			//ѡ���һ����Ϊ���ǵı�׼����
			if(!eglChooseConfig(display,attribs,&config,1,&numConfigs))
			{
				goto ERROR;
			}
			//������õ�����
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
			//���display�Ŀ��
			eglQuerySurface(display,surface,EGL_WIDTH,&w);
			eglQuerySurface(display,surface,EGL_HEIGHT,&h);

			//��pDisplay�ĸ������ݸ�ֵ
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

	//EGL������
	void AvtronsysEGLDisplay:: EGLDest()
	{
		//��ʼ��ʽ������
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

	//������Ļ
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

