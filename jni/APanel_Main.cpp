/**************************************
 * 	文件名	：Avtronsys_Main.cpp
 *	作用		：程序入口
 *	作者		：刘亚林
 *	创建时间	：2012/09/24
 *	最后修改	：刘亚林	 2012/09/24
 *	修改说明	: 创建该文件添加入口函数
 *	遗留说明	 ：暂无
 ***************************************/
#ifndef _AVTRONSYS_LOG_H
#define _AVTRONSYS_LOG_H
#include <Avtronsys/Avtronsys_Log.h>
#endif

#ifndef _AVTRONSYS_EVENTLOOP_H
#define _AVTRONSYS_EVENTLOOP_H
#include "Avtronsys/Avtronsys_EventLoop.h"
#endif


#ifndef _APANEL_INPUTHANDLER_H
#define _APANEL_INPUTHANDLER_H
#include "APanel_InputHandler.h"
#endif

#ifndef _APANEL_AVTIVITYHANDLER_H
#define _APANEL_AVTIVITYHANDLER_H
#include "APanel_ActivityHandler.h"
#endif

#ifndef _APANEL_XMLHELPER_H
#define _APANEL_XMLHELPER_H
#include "APanel_XMLHelper.h"
#endif

#ifndef _SYSTEM_NATIVE_APP_GLUE_H
#define _SYSTEM_NATIVE_APP_GLUE_H
#include <android_native_app_glue.h>
#endif

#include <android/log.h>
//程序入口函数
void android_main(android_app* pApplication)
{
	APanel::Exit lExit(pApplication);
	//声明CPanelManage对象并解析
	APanel::CPanelManage lcPanelManage;

	//事件处理以及程序的初始化
	//初始化egl
	Avtronsys::AvtronsysEGLDisplay lAvtronsysEGLDisplay(pApplication);
	//初始化绘制
	APanel::Drawing lDrawing(pApplication,&lcPanelManage,&lAvtronsysEGLDisplay);
	//初始化化操作响应
	APanel::APanelInputHandler lAPanelInputHandler(pApplication,&lDrawing,&lExit);
	Avtronsys::Context lContext={&lAPanelInputHandler,&lAvtronsysEGLDisplay};
	APanel:: APanelActivityHandler lAPanelActivityHandler(&lContext,&lDrawing,&lExit,pApplication);
	//初始化事件分发
	Avtronsys::EventLoop lEventLoop(pApplication);
	lcPanelManage.setRDraw(&lEventLoop);

	lEventLoop.LoopRun(&lAPanelActivityHandler,&lAPanelInputHandler);
}
