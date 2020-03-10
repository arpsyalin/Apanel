/******************************************
**		�ļ���APanel_CDrawDireButton.h
**		���ߣ�������
**		ʱ�䣺12��10��24��
**		����޸ģ���
*******************************************/
#ifndef _APANEL_TYPE_H
#define _APANEL_TYPE_H
#include "APanel_Type.h"
#endif

#ifndef _APANEL_CDRAWCHECKBUTTON_H
#define _APANEL_CDRAWCHECKBUTTON_H
#include "APanel_CDrawCheckButton.h"
#endif

#ifndef _SYSTEM_PTHREAD_H
#define _SYSTEM_PTHREAD_H
#include <pthread.h>
#endif

namespace APanel
{
	class CDrawDireButton : public CDrawButton
	{
		//���죬ϵ������
	public:
		CDrawDireButton();
		~CDrawDireButton();

		//�ӿ�
	public:
		virtual void			OnLButtonDown(bool istrue);
		//�������
		virtual void			OnLButtonUp(bool istrue);
		//���л�
//		virtual bool			Serialize(bool ismany);
		void TimerProc();
		void Rdraw();
		//�������ֵĵ���
		void soundplay();
		//�������ֵ��߳�
		static void *playsound(void* data);
		//����
	protected:
		UINT					m_nTimeDelay;
		friend class XMLHelper;
		friend class CPanelManage;
	private :
		POINT  downPT;	//���µ�pt
		static void *thread_fun(void* data);
	};
}
