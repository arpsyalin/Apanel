/******************************************
**		�ļ���APanel_CDrawControl.h
**		���ߣ�������
**		ʱ�䣺12��10��24��
**		����޸ģ���
*******************************************/
#ifndef _APANEL_TYPE_H
#define _APANEL_TYPE_H
#include "APanel_Type.h"
#endif



#ifndef _AVTRONSYS_DRAWTEXTURE_H
#define _AVTRONSYS_DRAWTEXTURE_H
#include "Avtronsys/Avtronsys_DrawTexture.h"
#endif

#ifndef _APANEL_CEVENTLINK_
#define _APANEL_CEVENTLINK_
#include "APanel_CEventLink.h"
#endif

namespace APanel
{
	class CPanelManage;
	class CDrawControl
	{
	public:
		CDrawControl();
		CDrawControl(DCS_STYLE	dcs_style);
		virtual ~CDrawControl();
	//�ӿ�
	public:
		//��ʼ����Ŀ��Ҫ�õ�������ͼƬ
		virtual int ProjectImageInit(bool isfirst);
		//��Ŀ��ʼ������
		virtual void ProjectDrawInit(GLuint pCurTextureid);
		//���û�������Ĵ�С
		virtual void setSize(float sizew,float sizeh);
		//���û��������λ��
		virtual void setLocation(float px,float py);
		//���������ƫ��
		virtual void setTextureDVT(float left,float top);
		//��������Ŀ�͸�
		virtual void setTextureHAW(float width,float height);
		//����ƫ�����Ϳ��
		virtual void setTextureArray(float left,float top,float width,float height);
		//��������ID
		virtual void setTexture(GLuint pCurTextureid);

		//�Ի溯��
		//Ҫ�����м̳��Ը�����࣬������д�ú���
		virtual bool	DrawSelf();//{return true;};
		virtual bool	DrawSelf(ANIMATION_MODEL animode );//{return true;};
		//����/��ȡ�ؼ�����
		void				SetRect(RECT rect);
		RECT				GetRect();

		//����/��ȡ�ؼ�ID
		void				SetControlId(int nId);
		UINT				GetControlId();
		//�¼���Ӧ����
		//�������
		//pt �������Ըÿؼ���λ����Ϊ�ο�
		virtual void		OnLButtonDown(POINT pt);
		//�������
		virtual void		OnLButtonUp(POINT pt);

		//pt �������Ըÿؼ���λ����Ϊ�ο�
		virtual void		OnLButtonDown(bool istrue);
		//�������
		virtual void		OnLButtonUp(bool istrue);

		//�жϸÿؼ��ڲ���ĳ��������
		bool				IsInRect(POINT	pt);
		bool				IsInRect(RECT	rect);
		//���л�
		virtual bool Serialize(bool ismany);

		//���ø��ؼ�
		void				SetParentCtr(CDrawControl* pParent);
		//ʹ�ؼ�����
		//�ú�������ĳ�����״̬���Ƿ��ظ��󶨣������Ƿ��ж�
		void				BindToGroup(int nGroupID, int indexInGroup);

		//���ÿؼ�����
		void				SetControlType(DC_CTRL_TYPE dcstyle);
		UINT				GetControlType();

		//����¼�
		//void				AppendEventLink(DCS_EVENT eventType, LPVOID pData, UINT nDataLen, BOOL bUp);
		void				AppendEventLink(DCS_EVENT eventType, LPVOID pData, UINT nDataLen, DCS_EVENT_CASE eventDrv);

		//��ÿؼ�Index
		//û�иÿؼ�����-1
		virtual int			GetCtrlIndex(CDrawControl* pCtrl);
		//�����ż����ں�
		//	int					GetGroupId()						{return m_bindGroupId;};
		//	int					GetInnerGrupIndex()					{return m_groupMask;};
		int					GetInnerGrupIndex(int i);
		//����
	protected:
		//��������---����ڸ��ؼ�����
		RECT 				m_rect;
		//�ؼ�ID---��Ӧ��JoinNum
		UINT				m_ctrId;
		//�ؼ���ʽ
		DCS_STYLE			m_ctrShowType;
		//����ؼ�����
		DC_CTRL_TYPE        m_ctrType;

		//�¼���������
		int m_EventCount;
		
		//�ؼ�������
		//���û�а��m_bindGroupId = -1;
		//int				m_bindGroupId;
		vector<UINT>		m_rgBindGroupId;
		//�ؼ���������
		//2008.8.23 ���京�������޸�
		//�޸ĺ�ĺ���Ϊ����������--��ʾ�ÿؼ����ڸ������ĸ�ͬ�������
		//int					m_groupMask;
		vector<UINT>		m_rgGroupMask;

		//���ؼ�,Ĭ��ΪNULL
		CDrawControl*		m_pParentCtr;
		//����
		int m_Music;
		CPanelManage * m_panelMan;
		//�¼�
		vector<CEventLink> m_envents;
		Avtronsys::DrawTexture mDrawTexture;	  	//������

		friend class CPanelManage;
		friend class XMLHelper;
		friend class CDrawPage;
		friend class APanelActivityHandler;	//��Ԫ��

	};
}
