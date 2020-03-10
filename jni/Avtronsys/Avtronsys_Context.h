/**************************************
 * 	�ļ���	��Avtronsys_Context.h
 *	����		����ṹ�������
 *	����		��������
 *	����ʱ��	��2012/09/24
 *	����޸�	��������	 2012/09/24
 *	�޸�˵��	: �������ļ�
 *	����˵��	 ������
 ***************************************/
#ifndef _AVTRONSYS_INPUTHANDLER_H
#define	_AVTRONSYS_INPUTHANDLER_H
#include "Avtronsys_InputHandler.h"
#endif

#ifndef _AVTRONSYS_EGLDISPLAY_H
#define	_AVTRONSYS_EGLDISPLAY_H
#include "Avtronsys_EGLDisplay.h"
#endif

#ifndef _AVTRONSYS_TYPEDEF_H
#define	_AVTRONSYS_TYPEDEF_H
#include "Avtronsys_TypeDef.h"
#endif

namespace Avtronsys
{
	class InputHandler;
	class AvtronsysEGLDisplay;
	struct Context
	{

		Avtronsys::InputHandler* pInputHandler;			//�¼�������
		AvtronsysEGLDisplay	* pAvtronsysEGLDisplay;		//EGL
	};
}

