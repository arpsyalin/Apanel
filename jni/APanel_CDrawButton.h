/******************************************
**		�ļ���APanel_CDrawButton.h
**		���ߣ�������
**		ʱ�䣺12��10��24��
**		����޸ģ���
*******************************************/
#ifndef _APANEL_TYPE_H
#define _APANEL_TYPE_H
#include "APanel_Type.h"
#endif

#ifndef _APANEL_CCTRLGROUPS_H
#define _APANEL_CCTRLGROUPS_H
#include "APanel_CCtrlGroups.h"
#endif


namespace APanel
{
	//CDrawButton:��ť��

	class CDrawButton : public CDrawControl
	{

		//���죬��������
	public:
		CDrawButton();
		virtual ~CDrawButton();

		//�ӿ�
	public:
		//���л�
		virtual bool Serialize(bool ismany);

		//��ʼ����ť״̬
		//pState:��ʾ״̬��ͼƬ��Ϣ����+
		//nCount:״̬������ҪС��16
		//�ú����Ӱ�ť��״̬0��ʼ��ʼ��������δ��ʼ����״̬���
		void				InitButtonState();

		//��Ӱ�ť��һ��״̬
		//���óɹ����� ��״̬�����
		//���򷵻�-1
		int					AppendButtonState(STATE pSTATE);

		/*���滹�м��麯���ڷ�����֤���к��ټ���*/
		//�¼���Ӧ����
		//�������
		//pt �������Ըÿؼ���λ����Ϊ�ο�
		virtual void		OnLButtonDown(bool istrue);
		//�������
		virtual void		OnLButtonUp(bool istrue);
		//�Ի溯��
		virtual bool		DrawSelf();
		//���ð�ť״̬   bRepaint = TRUE
		//				 ����ť�Ի���ʾ��pDC�ϡ�
		//				 bRepaint = FALSE
		//				 ���ı䰴ť״̬�����Ի�
		void				SetCurrentState(UINT nState, bool bRepaint = true);

		//�ӵ�ǰ״̬���ɵ�Ŀ��״̬
		void				PlayStateTo(UINT nDestState);

		void				SetAnimation(ANIMATION_MODEL mode);
		ANIMATION_MODEL		GetAnimation(void);
		//�������ֵĵ���
		void soundplay();
		//�������ֵ��߳�
		static void *playsound(void* data);
		//����
	protected:
		//��ťĬ�Ϻ���16��״̬
		//��ǰ״̬
		UINT				m_nCurrState;
		ANIMATION_MODEL		m_aniMode;
		//�ð�ťʵ�ʰ�����״̬��
		UINT				m_nSateCount;
		vector<STATE>		m_StateArray;

		friend class XMLHelper;
		friend class CDrawCheckButton;
	};
}
