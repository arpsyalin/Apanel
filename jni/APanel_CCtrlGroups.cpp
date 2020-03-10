/******************************************
**		文件：APanel_CCtrlGroups.cpp
**		作者：刘亚林
**		时间：12年10月24日
**		最后修改：无
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
		//初始化对象
		int num = maxGroupID+1;
		for(int i=0;i<num;i++)
		{
			CCtrlGroup *myGroup =new CCtrlGroup;
			myGroup->initMask(maxMaskID);
			m_groups.push_back(myGroup);
		}
	}

	//邦定控件到nGroupID组,nSynIndex同步元素族
	int CCtrlGroups::BindCtrlToGroup(UINT nGroupID, UINT nSynIndex, CDrawControl* pAdd)
	{
		if (nGroupID >= DC_MAX_GROUP)
		{
			return false;
		}

		bool bFlag = m_groups[nGroupID]->AppendCtrlToGroup(pAdd, nSynIndex);
		return bFlag;
	}

	//获得组号为nGroupID的第nIndex个同步元素族
	CSynchronousCtrls& CCtrlGroups::GetCtrlFromGroup(UINT nGroupID, UINT nIndex)
	{
		return m_groups[nGroupID]->GetByIndex(nIndex);
	}

	CCtrlGroup* CCtrlGroups::GetCtrlGroup(UINT nGroupID)
	{
		return (m_groups.at(nGroupID));
	}
}
