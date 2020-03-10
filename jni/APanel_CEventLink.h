/******************************************
**		�ļ���APanel_CEventLink.cpp
**		���ߣ�������
**		ʱ�䣺12��10��24��
**		����޸ģ���
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

		DCS_EVENT GetEventType();   	 //�¼�����
		DCS_EVENT_CASE GetEventCase();   //�¼���������
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
