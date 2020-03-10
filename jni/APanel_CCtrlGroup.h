/******************************************
**		�ļ���CCtrlGroup.h
**		���ߣ�������
**		ʱ�䣺12��10��24��
**		����޸ģ���
*******************************************/
#ifndef _APANEL_TYPE_H
#define _APANEL_TYPE_H
#include "APanel_Type.h"
#endif

#ifndef _APANEL_CSYNCHRONOUSCTRLS_H
#define _APANEL_CSYNCHRONOUSCTRLS_H
#include "APanel_CSynchronousCtrls.h"
#endif


namespace APanel
{
	class CCtrlGroup
	{
		//���죬��������
	public:
		CCtrlGroup();
		CCtrlGroup(const CCtrlGroup& objectSrc);
		~CCtrlGroup();

		//�ӿ�
	public:
		//���һ���ؼ��������У����ظÿؼ������е�λ�ã����ʧ�ܷ���-1
		int					AppendCtrlToGroup(CDrawControl* pAdd, UINT	nInnerIndex);

		//��ø����nIndex��Ԫ��
		CSynchronousCtrls&	GetByIndex(UINT nIndex);

		void initMask(int maxMaskID);
		//���������
		void operator=(const CCtrlGroup& objectSrc);

		//��ø�����ͬ��Ԫ����ĸ���
		UINT				GetSynNum();
		//����
	protected:

		//����
	protected:
		vector<CSynchronousCtrls*>  m_synCtrls;
		int						   m_nCtrlNum;
		friend class CPanelManage;
	};
}
