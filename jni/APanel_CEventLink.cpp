/******************************************
**		文件：APanel_CEventLink.cpp
**		作者：刘亚林
**		时间：12年10月24日
**		最后修改：无
*******************************************/
#ifndef _APANEL_CEVENTLINK_H
#define _APANEL_CEVENTLINK_H
#include "APanel_CEventLink.h"
#endif

namespace APanel
{
	CEventLink::CEventLink():
		m_Data (0),
		m_DataLen(0),
		m_Type( NULL_EVENT),
		m_Case(NULL_DRV)
	{
	}

	CEventLink::~CEventLink()
	{
	}

	CEventLink::CEventLink(const CEventLink& PEvent)
	{
		m_Data = PEvent.m_Data;
		m_DataLen = PEvent.m_DataLen;
		m_Type = PEvent.m_Type;
		m_Case = PEvent.m_Case;
	}

	void CEventLink:: Serialize()
	{

	};

	void CEventLink::SetEventLink(DCS_EVENT ptype, DCS_EVENT_CASE pdrvcase, LPVOID pdata, UINT plen)
	{

		m_Data = pdata;
		m_DataLen = plen;
		m_Type = ptype;
		m_Case = pdrvcase;
	}

	DCS_EVENT CEventLink::GetEventType()
	{
		return m_Type;
	}

	DCS_EVENT_CASE CEventLink::GetEventCase()
	{
		return m_Case;
	}


	DCS_EVENT_CASE CEventLink::GetEventDrv()
	{

	}

	LPVOID CEventLink::GetEventData(UINT &datalen)
	{
		datalen=m_DataLen;
		return m_Data;
	}

	//是否为弹起事件
	bool CEventLink::IsUpEvent()
	{
		bool flag = false;
		if(m_Case == PRESS_UP )
			flag = true;
		return flag;
	}


}
