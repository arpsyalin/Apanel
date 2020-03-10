/**************************************
 * 	�ļ���	��Avtronsys_EGLDisplay.h
 *	����		��һϵ�е�EGL����API
 *	����		��������
 *	����ʱ��	��2012/09/25
 *	����޸�	��������	 2012/09/25
 *	�޸�˵��	: �����4����ӡ��־��ʵ��
 *	����˵��	 ������
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
		int EGLInit();		//��ʼ��
		void EGLDest();		//����
		int EGLUpdate();	//������Ļ
		int32_t getWidth();	//�������
		int32_t getHeight();//�������
	private:
		android_app* mApplication;

		EGLDisplay mDisplay;	//��Ļ
		EGLContext mContext;	//����
		EGLSurface mSurface;	//֡����
		int32_t mWidth;			//����
		int32_t mHeight;		//����
	};
}
