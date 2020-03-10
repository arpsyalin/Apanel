/******************************************
**		�ļ���APanel_CDrawPage.h
**		���ߣ�������
**		ʱ�䣺12��10��24��
**		����޸ģ���
*******************************************/
#ifndef _APANEL_TYPE_H
#define _APANEL_TYPE_H
#include "APanel_Type.h"
#endif

#ifndef _APANEL_CDRAWDIREBUTTON_H
#define _APANEL_CDRAWDIREBUTTON_H
#include "APanel_CDrawDireButton.h"
#endif

namespace APanel
{
	class CDrawPage : public APanel::CDrawControl
	{
		//���죬��������
	public:
		CDrawPage();
		~CDrawPage();

	public:
		typedef enum {
			ANI_NULL2 = 0,				//ANI_  Animation ��Ч��
			ANI_UPTODOWN2,				//�������·���
			ANI_DOWNTOUP2,				//�������Ϸ���
			ANI_LEFTTORIGHT2,			//�������ҷ���
			ANI_RIGHTTOLEFT2,			//�����������
			ANI_ALPHA_IN2,				//����
			ANI_ALPHA_OUT2
		}ANIMATION_MODEL2;

		//�ӿ�
	public:
		//���л�
		bool			Serialize(bool ismany);
		//����һ���ؼ���Ϊ��ҳ����ӿؼ�
		//�������ӵĿؼ��ڿؼ������е��±�
		//�ú�����Ԫ�ز��뵽�ռ���������
		int				AppendCtrl(CDrawControl* pAdd);

		//����һ���ؼ���ҳ����
		//nIndex����Ҫ�����λ�ã�ֵ�ķ�Χ��0-��GetChildCtrlCount���� - 1��
		void			InsertCtrl(CDrawControl* pInsert, UINT nIndex);

		//����ӿؼ��ĸ���
		UINT			GetChildCount();


		//����ҳ��
		bool			CreatePage(RECT rect,					//ҳ�������
								   DCS_STYLE dcStyle);			//ҳ�����ʽ��DCS_PARENT,DCS_CHILD

		//�� �� ����
		virtual bool	DrawSelf(ANIMATION_MODEL animode);
		virtual bool	DrawSelf();
		//������Ӧ
		virtual void	OnLButtonDown(POINT pt);
		virtual void	OnLButtonUp(POINT pt);

		//����ĳ������
		virtual void		InvalidateRect(RECT rect);

		//����/���ǰһ��ҳ��
		void				SetPrevPage(CDrawPage* pPage);
		CDrawPage*			GetPrevPage();

		virtual int			GetCtrlIndex(CDrawControl* pCtrl);

		//��ĳ���ӿؼ��Ƶ����ϲ�
		virtual bool		MoveCtrlToTopest(UINT nCtrlIndex);

		//����/��ȡ����Ч��--09/8/27
		ANIMATION_MODEL&	Animation();

		//����
	protected:
		//��ҳ������Ŀؼ�
		/* �����Ի�����Ǵ�����ĵ�һԪ�ؿ�ʼ���λ�������Ԫ�أ�
		   �ʣ�Ҫ���ֲ�Σ����ǣ���ϵ����Ҫ���²�Ԫ�ط������ϲ�Ԫ�ص�ǰ�棡*/

		//�����ô˷����޷���õ�Ԫ�ص������Լ�������ȷ�ĵ��ö�̬ʵ��������ĳ���������� //������10.26
		vector<CDrawControl*>	m_childCtrl;
		vector<int> m_drawindex;
		//��ǰ����Ӧ�¼��Ŀؼ�
		CDrawControl*			m_pActiveCtrl;

		//ǰ һҳ��
		CDrawPage*								m_prevPage;

		//����Ч������09/8/27
		ANIMATION_MODEL							m_aniMode;

		//vector<STATE>  m_stateImg;		//���Ա���ҳ���ͼƬ·���Լ�ID
		STATE bkimg;
		//��ҳ������
		int SubCount;
		friend class XMLHelper;
		friend class CPanelManage;
	};

}
