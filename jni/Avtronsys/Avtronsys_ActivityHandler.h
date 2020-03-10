/**************************************
 * 	�ļ���	��Avtronsys_ActivityHandler.h
 *	����		��Activity�Ļ���
 *	����		��������
 *	����ʱ��	��2012/09/24
 *	����޸�	��������	 2012/09/25
 *	�޸�˵��	: �������ļ�
 *	����˵��	 ������
 ***************************************/
#ifndef _AVTRONSYS_TYPEDEF_H
#define	_AVTRONSYS_TYPEDEF_H
#include "Avtronsys_TypeDef.h"
#endif

namespace Avtronsys
{

	class ActivityHandler
	{
	public:
		virtual ~ActivityHandler() {};	//��������
		virtual Avtronsys::statedef onActivate()=0;	//����Ļ�ý��㲢�ҿ���
		virtual void onDesActivate()=0;	//��ͣ����ʾ����ʧȥ����򱻴ݻ١�
		virtual Avtronsys::statedef onStep()=0;		//û���¼����÷�����ʱ��ɷ���

		//ÿһ���¼�����һ���������������Ƕ�����Щ�������ڵĺ���
		virtual void onStart(){};	//��ʼ
		virtual void onResume(){};	//���¿�ʼ
		virtual void onPause(){};	//��ͣ
		virtual void onStop(){};	//ֹͣ
		virtual void onDestroy(){};	//�ݻ�

		virtual void onSaveState(void** pData,size_t* pSize){};	//����״̬
		virtual void onConfigurationChanged(){};					//���øı�
		virtual void onLowMemory(){};								//���ڴ��ʱ��

		//�����
		virtual void onCreateWindow(){};	//����Ĵ���
		virtual void onDestroyWindow(){};	//����Ĵݻ�
		virtual void onGainFocus(){};		//���/��ý���
		virtual void onLostFocus(){};		//�Ƴ�/ʧȥ����
		virtual void onResized(){};			//window�ı��С
		//���ݸı�
		virtual void onRDraw(){};				//�ػ�
		virtual void onRRECT(){};				//�������ݸı�

	};

}
