/******************************************
**		文件：APanel_CSynchronousCtrls.cpp
**		作者：刘亚林
**		时间：12年10月24日
**		最后修改：无
*******************************************/
#ifndef _APANEL_CSYNCHRONOUSCTRLS_H
#define _APANEL_CSYNCHRONOUSCTRLS_H
#include "APanel_CSynchronousCtrls.h"
#endif
#include "Avtronsys/Avtronsys_Log.h"

namespace APanel
{
	CSynchronousCtrls ::CSynchronousCtrls()
	{

	}

	CSynchronousCtrls ::~CSynchronousCtrls()
	{
	}

	CSynchronousCtrls::CSynchronousCtrls(const CSynchronousCtrls& objectSrc)
	{
		for (int i = 0; i < objectSrc.m_DrawCtrls.size(); i ++)
		{
			m_DrawCtrls.push_back(objectSrc.m_DrawCtrls.at(i));
		}
	}


	//添加一个元素到该组
	int CSynchronousCtrls ::AppendCtrlToMutex(CDrawControl*  pAdd)
	{
		if (pAdd == NULL)
		{
			return false;
		}
		//不允许插入同一个元素
		for (int i = 0; i < m_DrawCtrls.size(); i++)
		{
			if ( m_DrawCtrls.at(i)==pAdd)
			{
				return false;
			}
		}

		m_DrawCtrls.push_back(pAdd);
		return true;
	}

	//根据序号获得一个组内元素
	CDrawControl* CSynchronousCtrls ::GetCtrlByIndex(UINT nIndex)
	{
		return m_DrawCtrls.at(nIndex);
	}

	//获得控件个数
	UINT CSynchronousCtrls ::GetCtrlNum()
	{
		return m_DrawCtrls.size();
	}

	//运算符重载
	void CSynchronousCtrls ::operator=(const CSynchronousCtrls& objectSrc)
	{
		m_DrawCtrls.clear();
		int	nTemp = objectSrc.m_DrawCtrls.size();
		for (int i = 0; i < nTemp; i ++)
		{
			m_DrawCtrls.push_back(objectSrc.m_DrawCtrls.at(i));
		}
	}
}
