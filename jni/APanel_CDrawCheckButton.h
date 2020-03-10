/******************************************
**		�ļ���APanel_CDrawCheckButton.h
**		���ߣ�������
**		ʱ�䣺12��10��24��
**		����޸ģ���
*******************************************/
#ifndef _APANEL_TYPE_H
#define _APANEL_TYPE_H
#include "APanel_Type.h"
#endif

#ifndef _APANEL_CDRAWBUTTON_H
#define _APANEL_CDRAWBUTTON_H
#include "APanel_CDrawButton.h"
#endif

namespace APanel
{
	class CDrawCheckButton : public CDrawButton
	{
		//���죬����
	public:
		CDrawCheckButton();
		~CDrawCheckButton();
		//������๹��
		CDrawCheckButton(const CDrawButton& buttonSrc);

		//�ӿ�
	public:
		//���л�
		virtual bool Serialize(bool ismany);
		//�����Ƿ�Ϊcheck
		void				SetChecked(bool bChecked);

		//����checkbutton�ĳ�ʼ״̬
		//����ʱ�ã�ע��:������InitButtonState֮��
		void				SetInitialState(bool bChecked);

		//�ð�ť�Ƿ�Ϊcheck
		bool				IsChecked();

		//��ť���¼�����
		virtual void		OnLButtonDown(bool istrue);
		virtual void		OnLButtonUp(bool istrue);
		//�������ֵĵ���
		void soundplay();
		//�������ֵ��߳�
		static void *playsound(void* data);
		//����
	protected:

		//����
	protected:
		UINT GroupCount ;
		vector<UINT> GroupID;//����ID
		UINT MaskCount ;
		vector<UINT> MaskID;	//Mask ID
		string Bind;
		bool m_bChecked;					//�Ƿ�check
		friend class XMLHelper;
		friend class CPanelManage;
	};
}
