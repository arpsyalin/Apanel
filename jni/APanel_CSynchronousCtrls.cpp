/******************************************
**		�ļ���APanel_CSynchronousCtrls.cpp
**		���ߣ�������
**		ʱ�䣺12��10��24��
**		����޸ģ���
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


	//���һ��Ԫ�ص�����
	int CSynchronousCtrls ::AppendCtrlToMutex(CDrawControl*  pAdd)
	{
		if (pAdd == NULL)
		{
			return false;
		}
		//���������ͬһ��Ԫ��
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

	//������Ż��һ������Ԫ��
	CDrawControl* CSynchronousCtrls ::GetCtrlByIndex(UINT nIndex)
	{
		return m_DrawCtrls.at(nIndex);
	}

	//��ÿؼ�����
	UINT CSynchronousCtrls ::GetCtrlNum()
	{
		return m_DrawCtrls.size();
	}

	//���������
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
