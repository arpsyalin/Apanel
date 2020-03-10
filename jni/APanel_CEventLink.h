/******************************************
**		文件：APanel_CEventLink.cpp
**		作者：刘亚林
**		时间：12年10月24日
**		最后修改：无
*******************************************/
#ifndef _APANEL_TYPE_H
#define _APANEL_TYPE_H
#include "APanel_Type.h"
#endif

namespace APanel
{
	class CEventLink
	{
	public:
		CEventLink();
		~CEventLink();
		CEventLink(const CEventLink& PEvent);
	public:
		virtual void Serialize();
		void SetEventLink(DCS_EVENT ptype, DCS_EVENT_CASE pdrvcase, LPVOID pdata, UINT plen);

		DCS_EVENT GetEventType();   	 //事件类型
		DCS_EVENT_CASE GetEventCase();   //事件驱动类型
		LPVOID GetEventData(UINT &pdatalen);
		bool IsUpEvent();
		DCS_EVENT_CASE	GetEventDrv();
	private:
		DCS_EVENT m_Type;
		DCS_EVENT_CASE m_Case;
		LPVOID m_Data;
		UINT m_DataLen;
	};

}
