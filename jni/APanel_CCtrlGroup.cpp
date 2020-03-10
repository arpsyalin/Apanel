/******************************************
**		文件：APanel_CCtrlGroup.cpp
**		作者：刘亚林
**		时间：12年10月24日
**		最后修改：无
*******************************************/

#ifndef _APANEL_CCTRLGROUP_H
#define _APANEL_CCTRLGROUP_H
#include "APanel_CCtrlGroup.h"
#endif

#include "Avtronsys/Avtronsys_Log.h"
namespace APanel
{
	CCtrlGroup::CCtrlGroup()
	{
		m_nCtrlNum = 0;
	}

	CCtrlGroup::CCtrlGroup(const CCtrlGroup& objectSrc)
	{
		for (int i = 0; i < DC_MAXCTRL_IN_G; i ++)
		{
			m_synCtrls[i] = objectSrc.m_synCtrls[i];

		}

	}
	CCtrlGroup::~CCtrlGroup()
	{

	}

	void CCtrlGroup::initMask(int maxMaskID)
	{
		//初始化对象
		int num = maxMaskID;
		for(int i=0;i<=num;i++)
		{
			CSynchronousCtrls *lm_synCtrls =new CSynchronousCtrls;
			m_synCtrls.push_back(lm_synCtrls);
		}

	}

	//添加一个控件到该组中，返回该控件在组中的位置，添加失败返回-1
	int CCtrlGroup::AppendCtrlToGroup(CDrawControl* pAdd, UINT	nInnerIndex)
	{
		if ((nInnerIndex >= DC_MAXCTRL_IN_G) || (pAdd == NULL))
		{
			return false;
		}
		if (m_nCtrlNum < nInnerIndex)
		{
			m_nCtrlNum = nInnerIndex;
		}

		bool bFlag = m_synCtrls[nInnerIndex]->AppendCtrlToMutex(pAdd);
		return bFlag;
	}

	//获得该组第nIndex个元素
	CSynchronousCtrls& CCtrlGroup::GetByIndex(UINT nIndex)
	{
		return *m_synCtrls[nIndex];
	}

	//重载赋值运算符
	void CCtrlGroup::operator=(const CCtrlGroup& objectSrc)
	{
		for (int i = 0; i < DC_MAXCTRL_IN_G; i ++)
		{
			m_synCtrls[i] = objectSrc.m_synCtrls[i];
		}
		m_nCtrlNum = objectSrc.m_nCtrlNum;
	}

	//获得改组中同步元素族的个数
	UINT CCtrlGroup::GetSynNum()
	{
		return m_nCtrlNum;
	}
}
