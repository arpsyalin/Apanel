/**************************************
 * 	�ļ���	��Avtronsys_ActivityHandler.h
 *	����		��Activity�Ļ���ļ̳���
 *	����		��������
 *	����ʱ��	��2012/09/25
 *	����޸�	��������	 2012/09/25
 *	�޸�˵��	: �������ļ�
 *	����˵��	 ������
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
	//�Ƿ�����ת��Ļ����˵��2��
	class APanelActivityHandler:public Avtronsys::ActivityHandler
	{
	public :
		APanelActivityHandler(Avtronsys::Context* pContext,APanel::Drawing* pDrawing,APanel::Exit* pExit,android_app* pApplication);
		virtual ~APanelActivityHandler();
	protected:
		//����Ļ�ý��㲢�ҿ���
		Avtronsys::statedef onActivate();
		//��ͣ����ʾ����ʧȥ����򱻴ݻ١�
		void onDesActivate();
		//û���¼����÷�����ʱ��ɷ���
		Avtronsys::statedef onStep();

		//ÿһ���¼�����һ���������������Ƕ�����Щ�������ڵĺ���
		void onStart();		//��ʼ
		void onResume();	//���¿�ʼ
		void onPause();		//��ͣ
		void onStop();		//ֹͣ
		void onDestroy();	//�ݻ�

		void onSaveState(void** pData,size_t* pSize);	//����״̬
		void onConfigurationChanged();					//���øı�
		void onLowMemory();								//���ڴ��ʱ��

		//�����
		void onCreateWindow();	//����Ĵ���
		void onDestroyWindow();	//����Ĵݻ�
		void onGainFocus();		//���/��ý���
		void onLostFocus();		//�Ƴ�/ʧȥ����
		void onResized();		//����ı��С

		void onRDraw();				//�ػ�
		void onRRECT();				//�������ݸı�
		static void* TestWeblinkThread(void*);
	private :
		///��ĻEGL
		Avtronsys::AvtronsysEGLDisplay* mAvtronsysEGLDisplay;
		android_app* mApplication;
		//��Ϣ����
		Avtronsys::InputHandler* mInputHandler;
		//����
		APanel::Drawing* mDrawing;
		APanel::Exit* mExit;
	};
}
