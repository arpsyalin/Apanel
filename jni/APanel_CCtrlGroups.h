/******************************************
**		�ļ���CCtrlGroups.h
**		���ߣ�������
**		ʱ�䣺12��10��24��
**		����޸ģ���
*******************************************/
#ifndef _APANEL_TYPE_H
#define _APANEL_TYPE_H
#include "APanel_Type.h"
#endif

#ifndef _APANEL_CCTRLGROUP_H
#define _APANEL_CCTRLGROUP_H
#include "APanel_CCtrlGroup.h"
#endif

namespace APanel
{
	class CCtrlGroups
		{
		public:
			CCtrlGroups();
			~CCtrlGroups();

			//�ӿ�
		public:
			//��ؼ���nGroupID��,nSynIndexͬ��Ԫ����
			int	BindCtrlToGroup(UINT nGroupID, UINT nSynIndex, CDrawControl* pAdd);

			//������ΪnGroupID�ĵ�nIndex��ͬ��Ԫ����
			CSynchronousCtrls&	GetCtrlFromGroup(UINT nGroupID, UINT nIndex);

			CCtrlGroup* GetCtrlGroup(UINT nGroupID);
			void initGroup(int maxGroupID,int maxMaskID);
			//���ĳ��ͬ��Ԫ����ĸ���
			//int								GetCtrlNumInGroup(UINT nGroupID);
			//����
		protected:
			vector<CCtrlGroup*> m_groups;
			friend class XMLHelper;
		};

}
