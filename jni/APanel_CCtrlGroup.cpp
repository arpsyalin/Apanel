/******************************************
**		�ļ���APanel_CCtrlGroup.cpp
**		���ߣ�������
**		ʱ�䣺12��10��24��
**		����޸ģ���
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
		//��ʼ������
		int num = maxMaskID;
		for(int i=0;i<=num;i++)
		{
			CSynchronousCtrls *lm_synCtrls =new CSynchronousCtrls;
			m_synCtrls.push_back(lm_synCtrls);
		}

	}

	//���һ���ؼ��������У����ظÿؼ������е�λ�ã����ʧ�ܷ���-1
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

	//��ø����nIndex��Ԫ��
	CSynchronousCtrls& CCtrlGroup::GetByIndex(UINT nIndex)
	{
		return *m_synCtrls[nIndex];
	}

	//���ظ�ֵ�����
	void CCtrlGroup::operator=(const CCtrlGroup& objectSrc)
	{
		for (int i = 0; i < DC_MAXCTRL_IN_G; i ++)
		{
			m_synCtrls[i] = objectSrc.m_synCtrls[i];
		}
		m_nCtrlNum = objectSrc.m_nCtrlNum;
	}

	//��ø�����ͬ��Ԫ����ĸ���
	UINT CCtrlGroup::GetSynNum()
	{
		return m_nCtrlNum;
	}
}
