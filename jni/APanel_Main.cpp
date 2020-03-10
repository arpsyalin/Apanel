/**************************************
 * 	�ļ���	��Avtronsys_Main.cpp
 *	����		���������
 *	����		��������
 *	����ʱ��	��2012/09/24
 *	����޸�	��������	 2012/09/24
 *	�޸�˵��	: �������ļ������ں���
 *	����˵��	 ������
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
//������ں���
void android_main(android_app* pApplication)
{
	APanel::Exit lExit(pApplication);
	//����CPanelManage���󲢽���
	APanel::CPanelManage lcPanelManage;

	//�¼������Լ�����ĳ�ʼ��
	//��ʼ��egl
	Avtronsys::AvtronsysEGLDisplay lAvtronsysEGLDisplay(pApplication);
	//��ʼ������
	APanel::Drawing lDrawing(pApplication,&lcPanelManage,&lAvtronsysEGLDisplay);
	//��ʼ����������Ӧ
	APanel::APanelInputHandler lAPanelInputHandler(pApplication,&lDrawing,&lExit);
	Avtronsys::Context lContext={&lAPanelInputHandler,&lAvtronsysEGLDisplay};
	APanel:: APanelActivityHandler lAPanelActivityHandler(&lContext,&lDrawing,&lExit,pApplication);
	//��ʼ���¼��ַ�
	Avtronsys::EventLoop lEventLoop(pApplication);
	lcPanelManage.setRDraw(&lEventLoop);

	lEventLoop.LoopRun(&lAPanelActivityHandler,&lAPanelInputHandler);
}
