/******************************************
**		�ļ���APanel_CCtrlGroups.cpp
**		���ߣ�������
**		ʱ�䣺12��10��24��
**		����޸ģ���
*******************************************/
#ifndef _APANEL_CCTRLGROUPS_H
#define _APANEL_CCTRLGROUPS_H
#include "APanel_CCtrlGroups.h"
#endif
#include "Avtronsys/Avtronsys_Log.h"
namespace APanel
{

	CCtrlGroups::CCtrlGroups()
	{

	}

	CCtrlGroups::~CCtrlGroups()
	{

	}
	void CCtrlGroups::initGroup(int maxGroupID,int maxMaskID)
	{
		//��ʼ������
		int num = maxGroupID+1;
		for(int i=0;i<num;i++)
		{
			CCtrlGroup *myGroup =new CCtrlGroup;
			myGroup->initMask(maxMaskID);
			m_groups.push_back(myGroup);
		}
	}

	//��ؼ���nGroupID��,nSynIndexͬ��Ԫ����
	int CCtrlGroups::BindCtrlToGroup(UINT nGroupID, UINT nSynIndex, CDrawControl* pAdd)
	{
		if (nGroupID >= DC_MAX_GROUP)
		{
			return false;
		}

		bool bFlag = m_groups[nGroupID]->AppendCtrlToGroup(pAdd, nSynIndex);
		return bFlag;
	}

	//������ΪnGroupID�ĵ�nIndex��ͬ��Ԫ����
	CSynchronousCtrls& CCtrlGroups::GetCtrlFromGroup(UINT nGroupID, UINT nIndex)
	{
		return m_groups[nGroupID]->GetByIndex(nIndex);
	}

	CCtrlGroup* CCtrlGroups::GetCtrlGroup(UINT nGroupID)
	{
		return (m_groups.at(nGroupID));
	}
}
