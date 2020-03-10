/**************************************
 * 	文件名	：Avtronsys_Context.h
 *	作用		：类结构体变量化
 *	作者		：刘亚林
 *	创建时间	：2012/09/24
 *	最后修改	：刘亚林	 2012/09/24
 *	修改说明	: 创建该文件
 *	遗留说明	 ：暂无
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

		Avtronsys::InputHandler* pInputHandler;			//事件处理类
		AvtronsysEGLDisplay	* pAvtronsysEGLDisplay;		//EGL
	};
}

