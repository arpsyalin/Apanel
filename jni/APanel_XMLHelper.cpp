#ifndef _APANEL_XMLHELPER_H
#define _APANEL_XMLHELPER_H
#include "APanel_XMLHelper.h"
#endif

#ifndef _AVTRONSYS_LOG_H
#define _AVTRONSYS_LOG_H
#include "Avtronsys/Avtronsys_Log.h"
#endif

namespace APanel
{
	const char* severIP;
	XMLHelper::XMLHelper(CPanelManage* pCPanelManage,const char *pxml_file_path,const char * prootpath)
	:mCPanelManage(pCPanelManage),mxml_file_path(pxml_file_path),mrootpath(prootpath)
	{
		maxGroupID=0;
		maxMaskID=0;
	}

	XMLHelper::~XMLHelper()
	{

	}

	bool XMLHelper:: XMLOpen()
	{
		bool bret = false;
		m_pdoc_read = NULL;
		m_proot = NULL;

		Avtronsys::Log::error("XML file\n:%s:::%s",mxml_file_path,mrootpath);
		if (mxml_file_path)
		{
			xmlKeepBlanksDefault(0);
			m_pdoc_read = xmlReadFile(mxml_file_path, "UTF-8",XML_PARSE_RECOVER);

			if (NULL == m_pdoc_read) {
				return false;
			}
			m_proot = xmlDocGetRootElement(m_pdoc_read);

			if (m_proot)
			{
				bret = true;
			}
		}
		return bret;
	}

	int XMLHelper:: XMLParse()
	{
		xmlNodePtr curNode;
		XMLOpen();	//打开XML
		curNode=m_proot;//确定根节点
		curNode = m_proot;
		//curNode = xmlDocGetRootElement(m_pdoc_read); //确定文档根元素
		if (NULL == curNode) //confirm the document is not empty.
		{
			Avtronsys::Log::error("Empty XML file\n");
			xmlFreeDoc(m_pdoc_read);
			return -1;
		}
		/*确认文档的根节点*/
		if (xmlStrcmp((m_proot)->name, BAD_CAST "Project"))
		{
			Avtronsys::Log::error("Document error!\n");
			xmlFreeDoc(m_pdoc_read);
			return -1;
		}
		curNode = curNode->xmlChildrenNode;
		xmlNodePtr propNodePtr = curNode;
		while (curNode != NULL) {
			//取出节点中的内容
			if ((!xmlStrcmp(curNode->name, (const xmlChar *) "CommType"))) {
				char * content;
				content = (char *) BAD_CAST (xmlNodeGetContent(curNode));
				mCPanelManage->m_sysCommType = atoi(content);
				free(content);
			}
			if ((!xmlStrcmp(curNode->name, (const xmlChar *) "HostIp"))) {
				const char* HostIpContent;// = new char[16];

				HostIpContent = (const char*) BAD_CAST (xmlNodeGetContent(curNode));
				mCPanelManage->m_csHostIp = HostIpContent;
				severIP = HostIpContent;
				//severIP = "192.168.1.243";
			}
			if ((!xmlStrcmp(curNode->name, (const xmlChar *) "WifiAP"))) {
				char * WifiApContent;
				WifiApContent = (char *) BAD_CAST (xmlNodeGetContent(curNode));
				mCPanelManage->m_csWifiAp=WifiApContent;
				xmlFree(WifiApContent);
			}
			if ((!xmlStrcmp(curNode->name, (const xmlChar *) "PageCount"))) {
				char * PageCountContent;
				PageCountContent = (char *) BAD_CAST (xmlNodeGetContent(curNode));
				mCPanelManage->PageCount = atoi(PageCountContent);
				free(PageCountContent);
			}
			//主页面
			if ((!xmlStrcmp(curNode->name, (const xmlChar *) "Page"))) {
				CDrawPage *Page_info =new CDrawPage;
				ParseXMLPage(curNode, Page_info);
				Page_info->m_ctrType = DC_CTRL_PAGE;
				Page_info->m_panelMan = mCPanelManage;
				mCPanelManage->m_Drawpages.push_back(Page_info);
			}
			curNode = curNode->next;
		}
		mCPanelManage->maxGroupNum = maxGroupID;
		mCPanelManage->m_groups.initGroup(maxGroupID,maxMaskID);
	}

	void XMLHelper:: ParseXMLPage(xmlNodePtr Page, CDrawPage *pPage_info) {
		Page = Page->xmlChildrenNode;
		while (Page != NULL) {
			if ((!xmlStrcmp(Page->name, (const xmlChar *) "ID"))) //Page ID
			{	char * IDContent;
				IDContent = (char *) BAD_CAST (xmlNodeGetContent(Page));
				pPage_info->m_ctrId = atoi(IDContent);
				free(IDContent);
			}
			if ((!xmlStrcmp(Page->name, (const xmlChar *) "Rect"))) //Page Rect.
			{
				char * RectContent;
				RectContent = (char *) BAD_CAST (xmlNodeGetContent(Page));
				ParseXMLRect(RectContent,&pPage_info->m_rect);
				free(RectContent);
			}
			if ((!xmlStrcmp(Page->name, (const xmlChar *) "Style"))) //Page Style
			{
				char * StyleContent;
				StyleContent = (char *) BAD_CAST (xmlNodeGetContent(Page));
				pPage_info->m_ctrShowType = atoi(StyleContent);
				free(StyleContent);
			}
			if ((!xmlStrcmp(Page->name, (const xmlChar *) "EventCount"))) //Page EventCount
			{
				char * EventCountContent;
				EventCountContent = (char *) BAD_CAST (xmlNodeGetContent(Page));
				pPage_info->m_EventCount = atoi(EventCountContent);
				free(EventCountContent);
			}
			if ((!xmlStrcmp(Page->name, (const xmlChar *) "bkpng"))) //Page bkpng
			{
				char * bkpngContent;
				//STATE thisSTATE;
				bkpngContent = (char *) BAD_CAST (xmlNodeGetContent(Page));
				//thisSTATE.imgPath = mrootpath;
				//thisSTATE.imgPath += bkpngContent;
				//pPage_info->m_stateImg.push_back(thisSTATE);
				pPage_info->bkimg.imgPath = mrootpath;
				pPage_info->bkimg.imgPath += bkpngContent;
				free(bkpngContent);
			}
			if ((!xmlStrcmp(Page->name, (const xmlChar *) "Count"))) //Page Count
			{
				char * CountContent;
				CountContent = (char *) BAD_CAST (xmlNodeGetContent(Page));
				pPage_info->SubCount = atoi(CountContent);
				free(CountContent);
			}

			if ((!xmlStrcmp(Page->name, (const xmlChar *) "Button"))) //Page Button
			{
				CDrawButton* Button_info =new CDrawButton;
				ParseXMLButton(Page, Button_info);
				Button_info->m_ctrType = DC_CTRL_BUTTON;		// 设置控件类型
				Button_info->m_panelMan = mCPanelManage;
				//Avtronsys::Log::info("ip1=%s",mCPanelManage->m_csHostIp);
				//Avtronsys::Log::info("ip=%s",Button_info->m_panelMan->m_csHostIp);
				pPage_info->m_childCtrl.push_back(Button_info);
			}

			if ((!xmlStrcmp(Page->name, (const xmlChar *) "DireButton"))) //Page DireButton
			{
				CDrawDireButton* DireButton_info = new CDrawDireButton;
				ParseXMLDireButton(Page, DireButton_info);
				DireButton_info->m_ctrType = DC_CTRL_DIRECTIONBUTTON;	//设置控件类型
				DireButton_info->m_panelMan = mCPanelManage;
				//Avtronsys::Log::info("ip1=%s",mCPanelManage->m_csHostIp);
				//Avtronsys::Log::info("ip=%s",DireButton_info->m_panelMan->m_csHostIp);
				pPage_info->m_childCtrl.push_back(DireButton_info);
			}

			if ((!xmlStrcmp(Page->name, (const xmlChar *) "CheckButton"))) //Page CheckButton
			{
				CDrawCheckButton* CheckButton_info = new CDrawCheckButton;
				ParseXMLCheckButton(Page, CheckButton_info);
				CheckButton_info->m_ctrType = DC_CTRL_CHECKBUTTON;		//设置控件类型
				CheckButton_info->m_panelMan = mCPanelManage;
				//Avtronsys::Log::info("ip1=%s",mCPanelManage->m_csHostIp);
				//Avtronsys::Log::info("ip=%s",CheckButton_info->m_panelMan->m_csHostIp);
				pPage_info->m_childCtrl.push_back(CheckButton_info);
			}
			//子页面
			if ((!xmlStrcmp(Page->name, (const xmlChar *) "Page"))) //Page ----SubPage
			{
				CDrawPage* SubPage_info = new CDrawPage;					//注意这里是new出来
				ParseXMLPage(Page, SubPage_info);
				SubPage_info->m_ctrType = DC_CTRL_PAGE;						//设置控件类型
				SubPage_info->m_panelMan = mCPanelManage;
				//Avtronsys::Log::info("ip1=%s",mCPanelManage->m_csHostIp);
				//Avtronsys::Log::info("ip=%s",SubPage_info->m_panelMan->m_csHostIp);
				pPage_info->m_childCtrl.push_back(SubPage_info);
			}
			Page = Page->next;
		}
	}

	void XMLHelper:: ParseXMLButton(xmlNodePtr Button, CDrawButton* pButton_info)
	{
		Button = Button->xmlChildrenNode;
		while (Button != NULL) {
			if ((!xmlStrcmp(Button->name, (const xmlChar *) "ID"))) //Button ID
			{
				char * IDContent;
				IDContent = (char *) BAD_CAST (xmlNodeGetContent(Button));
				pButton_info->m_ctrId = atoi(IDContent);
				free(IDContent);
			}
			if ((!xmlStrcmp(Button->name, (const xmlChar *) "Rect"))) //Button Rect.
			{
				char * RectContent;
				RectContent = (char *) BAD_CAST (xmlNodeGetContent(Button));
				ParseXMLRect(RectContent,&pButton_info->m_rect);
				free(RectContent);
			}
			if ((!xmlStrcmp(Button->name, (const xmlChar *) "Style"))) //Button Style
			{
				char * StyleContent;
				StyleContent = (char *) BAD_CAST (xmlNodeGetContent(Button));
				pButton_info->m_ctrShowType = atoi(StyleContent);
				free(StyleContent);
			}
			if ((!xmlStrcmp(Button->name, (const xmlChar *) "Animation"))) //Button Animation
			{
				char * AnimationContent;
				AnimationContent = (char *) BAD_CAST (xmlNodeGetContent(Button));
				pButton_info->m_aniMode =(ANIMATION_MODEL) atoi(AnimationContent);
				free(AnimationContent);
			}

			if ((!xmlStrcmp(Button->name, (const xmlChar *) "EventCount"))) //Button EventCount
			{
				char * EventCountContent;
				EventCountContent = (char *) BAD_CAST (xmlNodeGetContent(Button));
				pButton_info->m_EventCount = atoi(EventCountContent);
				free(EventCountContent);
			}

			if ((!xmlStrcmp(Button->name, (const xmlChar *) "Event"))) //Button Event
			{
				CEventLink Event_info;
				ParseXMLEvent(Button, &Event_info);
				pButton_info->m_envents.push_back(Event_info);
			}
			if ((!xmlStrcmp(Button->name, (const xmlChar *) "DelayTime"))) //Button DelayTime
			{
				char * DelayTimeContent;
				DelayTimeContent = (char *) BAD_CAST (xmlNodeGetContent(Button));
				pButton_info->m_ctrShowType = atoi(DelayTimeContent);

				free(DelayTimeContent);
			}
			if ((!xmlStrcmp(Button->name, (const xmlChar *) "StateCount"))) //Button StateCount
			{
				char * StateCountContent;
				StateCountContent = (char *) BAD_CAST (xmlNodeGetContent(Button));
				pButton_info->m_nSateCount = atoi(StateCountContent);
				free(StateCountContent);
			}
			if ((!xmlStrcmp(Button->name, (const xmlChar *) "CurrentState"))) //Button CurrentState
			{
				char * CurrentStateContent;
				CurrentStateContent = (char *) BAD_CAST (xmlNodeGetContent(Button));
				pButton_info->m_nCurrState = atoi(CurrentStateContent);
				free(CurrentStateContent);
			}
			if ((!xmlStrcmp(Button->name, (const xmlChar *) "Music"))) //Button Music
			{
				char * MusicContent;
				MusicContent = (char *) BAD_CAST (xmlNodeGetContent(Button));
				pButton_info->m_Music = atoi(MusicContent);
				free(MusicContent);
			}
			if (!(xmlStrcmp(Button->name, (const xmlChar *) "State"))) //Button State
			{
				STATE State_info;
				char * StateContent;
				StateContent = (char *) BAD_CAST (xmlNodeGetContent(Button));
				State_info.imgPath=mrootpath;
				State_info.imgPath+=StateContent;
				pButton_info->m_StateArray.push_back(State_info);
				free(StateContent);
			}

			Button = Button->next;
		}
	}

	void XMLHelper::ParseXMLDireButton(xmlNodePtr Button, CDrawDireButton* DireButton_info) {

		Button = Button->xmlChildrenNode;
		while (Button != NULL)
		{
			if ((!xmlStrcmp(Button->name, (const xmlChar *) "ID"))) //Button ID
			{
				char * IDContent;
				IDContent = (char *) BAD_CAST (xmlNodeGetContent(Button));
				DireButton_info->m_ctrId = atoi(IDContent);
				free(IDContent);
			}
			if ((!xmlStrcmp(Button->name, (const xmlChar *) "Rect"))) //Button Rect.
			{
				char * RectContent;
				RectContent = (char *) BAD_CAST (xmlNodeGetContent(Button));
				ParseXMLRect(RectContent,&DireButton_info->m_rect);
				free(RectContent);
			}
			if ((!xmlStrcmp(Button->name, (const xmlChar *) "Style"))) //Button Style
			{
				char * StyleContent;
				StyleContent = (char *) BAD_CAST (xmlNodeGetContent(Button));
				DireButton_info->m_ctrShowType = atoi(StyleContent);
				free(StyleContent);
			}
			if ((!xmlStrcmp(Button->name, (const xmlChar *) "Animation"))) //Button Animation
			{
				char * AnimationContent;
				AnimationContent = (char *) BAD_CAST (xmlNodeGetContent(Button));
				DireButton_info->m_aniMode =(ANIMATION_MODEL) atoi(AnimationContent);
				free(AnimationContent);
			}

			if ((!xmlStrcmp(Button->name, (const xmlChar *) "EventCount"))) //Button EventCount
			{
				char * EventCountContent;
				EventCountContent = (char *) BAD_CAST (xmlNodeGetContent(Button));
				DireButton_info->m_EventCount = atoi(EventCountContent);
				free(EventCountContent);
			}

			if ((!xmlStrcmp(Button->name, (const xmlChar *) "Event"))) //Button Event
			{
				CEventLink Event_info;
				ParseXMLEvent(Button, &Event_info);
				DireButton_info->m_envents.push_back(Event_info);
			}
			if ((!xmlStrcmp(Button->name, (const xmlChar *) "DelayTime"))) //Button DelayTime
			{
				char * DelayTimeContent;
				DelayTimeContent = (char *) BAD_CAST (xmlNodeGetContent(Button));
				DireButton_info->m_nTimeDelay = atoi(DelayTimeContent);

				free(DelayTimeContent);
			}
			if ((!xmlStrcmp(Button->name, (const xmlChar *) "StateCount"))) //Button StateCount
			{
				char * StateCountContent;
				StateCountContent = (char *) BAD_CAST (xmlNodeGetContent(Button));
				DireButton_info->m_nSateCount = atoi(StateCountContent);
				free(StateCountContent);
			}
			if ((!xmlStrcmp(Button->name, (const xmlChar *) "CurrentState"))) //Button CurrentState
			{
				char * CurrentStateContent;
				CurrentStateContent = (char *) BAD_CAST (xmlNodeGetContent(Button));
				DireButton_info->m_nCurrState = atoi(CurrentStateContent);
				free(CurrentStateContent);
			}
			if ((!xmlStrcmp(Button->name, (const xmlChar *) "Music"))) //Button Music
			{
				char * MusicContent;
				MusicContent = (char *) BAD_CAST (xmlNodeGetContent(Button));
				DireButton_info->m_Music = atoi(MusicContent);
				free(MusicContent);
			}
			if (!(xmlStrcmp(Button->name, (const xmlChar *) "State"))) //Button State
			{
				STATE State_info;
				char * StateContent;
				StateContent = (char *) BAD_CAST (xmlNodeGetContent(Button));
				State_info.imgPath=mrootpath;
				State_info.imgPath+=StateContent;
				DireButton_info->m_StateArray.push_back(State_info);
				free(StateContent);
			}

			Button = Button->next;
		}
	}
	void XMLHelper::ParseXMLCheckButton(xmlNodePtr Button, CDrawCheckButton* pCheckButton_info)
	{
		Button = Button->xmlChildrenNode;
		while (Button != NULL) {
			if ((!xmlStrcmp(Button->name, (const xmlChar *) "ID"))) //Button ID
			{
				char * IDContent;
				IDContent = (char *) BAD_CAST (xmlNodeGetContent(Button));
				pCheckButton_info->m_ctrId = atoi(IDContent);
				free(IDContent);
			}
			if ((!xmlStrcmp(Button->name, (const xmlChar *) "Rect"))) //Button Rect.
			{
				char * RectContent;
				RectContent = (char *) BAD_CAST (xmlNodeGetContent(Button));
				ParseXMLRect(RectContent,&pCheckButton_info->m_rect);
				free(RectContent);
			}
			if ((!xmlStrcmp(Button->name, (const xmlChar *) "Style"))) //Button Style
			{
				char * StyleContent;
				StyleContent = (char *) BAD_CAST (xmlNodeGetContent(Button));
				pCheckButton_info->m_ctrShowType = atoi(StyleContent);
				free(StyleContent);
			}

			if ((!xmlStrcmp(Button->name, (const xmlChar *) "EventCount"))) //Button EventCount
			{
				char * EventCountContent;
				EventCountContent = (char *) BAD_CAST (xmlNodeGetContent(Button));
				pCheckButton_info->m_EventCount = atoi(EventCountContent);
				free(EventCountContent);
			}

			if ((!xmlStrcmp(Button->name, (const xmlChar *) "Event"))) //Button Event
			{
				CEventLink Event_info;
				ParseXMLEvent(Button, &Event_info);
				pCheckButton_info->m_envents.push_back(Event_info);

			}

			if ((!xmlStrcmp(Button->name, (const xmlChar *) "StateCount"))) //Button StateCount
			{
				char * StateCountContent;
				StateCountContent = (char *) BAD_CAST (xmlNodeGetContent(Button));
				pCheckButton_info->m_nSateCount = atoi(StateCountContent);
				free(StateCountContent);
			}
			if ((!xmlStrcmp(Button->name, (const xmlChar *) "CurrentState"))) //Button CurrentState
			{
				char * CurrentStateContent;
				CurrentStateContent = (char *) BAD_CAST (xmlNodeGetContent(Button));
				pCheckButton_info->m_nCurrState = atoi(CurrentStateContent);
				free(CurrentStateContent);
			}
			if ((!xmlStrcmp(Button->name, (const xmlChar *) "Music"))) //Button Music
			{
				char * MusicContent;
				MusicContent = (char *) BAD_CAST (xmlNodeGetContent(Button));
				pCheckButton_info->m_Music = atoi(MusicContent);
				free(MusicContent);
			}
			if (!(xmlStrcmp(Button->name, (const xmlChar *) "State"))) //Button State
			{
				STATE State_info;
				char * StateContent;
				StateContent = (char *) BAD_CAST (xmlNodeGetContent(Button));
				State_info.imgPath=mrootpath;
				State_info.imgPath+=StateContent;
				pCheckButton_info->m_StateArray.push_back(State_info);
				free(StateContent);
			}

			if ((!xmlStrcmp(Button->name, (const xmlChar *) "Check"))) //Button Check
			{
				char * CheckContent;
				CheckContent = (char *) BAD_CAST (xmlNodeGetContent(Button));
				if(atoi(CheckContent))
				{
					pCheckButton_info->m_bChecked=true;
				}
				else
				{
					pCheckButton_info->m_bChecked=false;
				}
				free(CheckContent);
			}
			if ((!xmlStrcmp(Button->name, (const xmlChar *) "GroupCount"))) //Button GroupCount
			{
				char * GroupCountContent;
				GroupCountContent = (char *) BAD_CAST (xmlNodeGetContent(Button));
				pCheckButton_info->GroupCount = atoi(GroupCountContent);
				free(GroupCountContent);
			}
			if ((!xmlStrcmp(Button->name, (const xmlChar *) "MaskCount"))) //Button MaskCount
			{
				char * MaskCountContent;
				MaskCountContent = (char *) BAD_CAST (xmlNodeGetContent(Button));
				pCheckButton_info->MaskCount = atoi(MaskCountContent);
				free(MaskCountContent);
			}
			if ((!xmlStrcmp(Button->name, (const xmlChar *) "Bind"))) //Button Bind
			{
				char * BindContent;
				BindContent = (char *) BAD_CAST (xmlNodeGetContent(Button));
				pCheckButton_info->Bind=(string)(BindContent);
				free(BindContent);
			}
			if ((!xmlStrcmp(Button->name, (const xmlChar *) "MaskID"))) //Button MaskID
			{
				char * MaskIDContent;
				MaskIDContent = (char *) BAD_CAST (xmlNodeGetContent(Button));
				ParseID(MaskIDContent,&pCheckButton_info->MaskID);
				for(int i=0;i<pCheckButton_info->MaskID.size();i++)
				{
					if(maxMaskID<=pCheckButton_info->MaskID.at(i))
					{
						maxMaskID=pCheckButton_info->MaskID.at(i);
					}
				}
				free(MaskIDContent);
			}

			if ((!xmlStrcmp(Button->name, (const xmlChar *) "GroupID"))) //Button GroupID
			{
				char * GroupIDContent;
				GroupIDContent = (char *) BAD_CAST (xmlNodeGetContent(Button));
				ParseID(GroupIDContent,&pCheckButton_info->GroupID);
				for(int i=0;i<pCheckButton_info->GroupID.size();i++)
				{
					if(maxGroupID<=pCheckButton_info->GroupID.at(i))
					{
						maxGroupID=pCheckButton_info->GroupID.at(i);
					}
				}

				free(GroupIDContent);
			}

			Button = Button->next;
		}
	}

	void XMLHelper::ParseXMLEvent(xmlNodePtr Event, CEventLink* pEvent_info) {
		Event = Event->xmlChildrenNode;
		DCS_EVENT Type;
		DCS_EVENT_CASE Case;
		UINT DataLen;
		LPVOID Data=NULL;
		while (Event != NULL) {
			if ((!xmlStrcmp(Event->name, (const xmlChar *) "Type"))) //Event Type
			{
				char * TypeContent;
				TypeContent = (char *) BAD_CAST (xmlNodeGetContent(Event));
				Type = atoi(TypeContent);
				free(TypeContent);
			}
			if ((!xmlStrcmp(Event->name, (const xmlChar *) "Case"))) //Event Case
			{
				char * CaseContent;
				CaseContent = (char *) BAD_CAST (xmlNodeGetContent(Event));
				Case = atoi(CaseContent);
				free(CaseContent);
			}
			if ((!xmlStrcmp(Event->name, (const xmlChar *) "DataLen"))) //Event DataLen
			{
				char * DataLenContent;
				DataLenContent = (char *) BAD_CAST (xmlNodeGetContent(Event));
				DataLen = atoi(DataLenContent);
				free(DataLenContent);
			}
			if ((!xmlStrcmp(Event->name, (const xmlChar *) "Data"))) //Event Data
			{
				Data = (LPVOID) BAD_CAST (xmlNodeGetContent(Event));
			}
			Event = Event->next;
		}

		pEvent_info->SetEventLink(Type, Case, Data, DataLen);
	}

	///解析id到内
	void XMLHelper::ParseID(char* strID,vector<UINT>* ID)
	{

		int i;
		int dotcount=0;
		int lastdot=0;
		int firstdot = 0;
		ID->push_back(0);
		for(i=0;*(strID+i)!='\0';i++)
		{

			if(*(strID+i)==',')
			{
				char temp[10];
				int k;
				if(dotcount==0)
				{
					strncpy(temp,strID+lastdot,i-lastdot);
					temp[i-lastdot]='\0';
				}
				else
				{
					strncpy(temp,strID+lastdot+1,i-lastdot-1);
					temp[i-lastdot-1]='\0';
				}

				printf("%s \n",temp);
				k=atoi(temp);

				lastdot = i;
				if(dotcount == 0)
				{
					ID->at(0) = k;
					firstdot = i;
				}
				else
				{
					ID->push_back(k);
				}
				dotcount++;
			}
		}

		if(dotcount==0)
		{
			firstdot = i;
			char temp[10];
			int k;
			strncpy(temp,strID,firstdot);
			temp[firstdot] ='\0';
			k=atoi(temp);
			ID->at(0) = k;
		}
		else
		{
			char temp[10];
			int k;
			strncpy(temp,strID+lastdot+1,i-lastdot-1);
			temp[i-lastdot-1]='\0';
			k=atoi(temp);
			ID->push_back(k);
		}

	}

	void  XMLHelper::ParseXMLRect(char * strRect, RECT *rect) {
		string str(strRect);
		int pt[] = { 0, 0, 0, 0 };
		int dotCount = 0, dotPos = 0;
		char temp;
		string::iterator it;
		for (it = str.begin(); it != str.end(); it++)
		{

			if (*it == '{' || *it == '}')
			{
				str.erase(it);
				it--;
			}
		}
		for (int i = 0; i < str.length(); ++i)
		{
			temp = str.at(i);
			if (temp == ',')
			{
				if (dotCount == 0)
				{
					string strSub = str.substr(dotPos, i);
					dotPos =i+ 1;
					pt[dotCount] = atoi(strSub.c_str());
					dotCount += 1;
					continue;
				}
				if (dotCount == 1)
				{
					string strSub = str.substr(dotPos, i);
					dotPos =i + 1;
					pt[dotCount] = atoi(strSub.c_str());
					dotCount += 1;
					continue;
				}
				if (dotCount == 2)
				{
					string strSub = str.substr(dotPos, i);
					dotPos = i + 1;
					pt[dotCount] = atoi(strSub.c_str());
					dotCount += 1;
					string strSub1 = str.substr(dotPos,str.length());
					pt[dotCount] = atoi(strSub1.c_str());
					break;
				}
			}
		}

		rect->LTPoint.x = (float)pt[0];
		rect->LTPoint.y = (float)pt[1];
		rect->RWidth	= (float)pt[2];
		rect->RHeight	= (float)pt[3];
	}
}
