#ifndef _APANEL_CDRAWCONTROL_H
#define _APANEL_CDRAWCONTROL_H
#include "APanel_CPanelManage.h"
#endif

#ifndef _SYS_XML_H
#define _SYS_XML_H
#include "libxml2/include/libxml/parser.h"
#include "libxml2/include/libxml/tree.h"
#include "libxml2/include/libxml/xpath.h"
#include "libxml2/include/libxml/xpathInternals.h"
#include "libxml2/include/libxml/xmlmemory.h"
#include "libxml2/include/libxml/xpointer.h"
#endif

namespace APanel
{
	class XMLHelper
	{
	public :
		XMLHelper(CPanelManage* pCPanelManage,const char *pxml_file_path,const char *prootpath);
		~XMLHelper();
	public :
		int XMLParse();
	private :
		bool XMLOpen();
		void ParseXMLPage(xmlNodePtr Page,CDrawPage *Page_info);
		void ParseXMLButton(xmlNodePtr Button,CDrawButton* Button_info);
		void ParseXMLEvent(xmlNodePtr Button, CEventLink* Event_info);
		void ParseXMLDireButton(xmlNodePtr Button,CDrawDireButton* Button_info);
		void ParseXMLCheckButton(xmlNodePtr Button,CDrawCheckButton* Button_info);
		void ParseXMLRect(char * strRect, RECT *rect);
		void ParseID(char* strID,vector<UINT>* ID);
	private :
		CPanelManage * mCPanelManage;
		const char * mxml_file_path;
		const char * mrootpath;
		xmlDocPtr m_pdoc_read;
		xmlNodePtr m_proot;
		int maxGroupID;	//记录最大的groupID
		int maxMaskID;	//记录最大的maskid
	};
}
