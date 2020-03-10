/******************************************
**		文件：APanel_CDrawCheckButton.cpp
**		作者：刘亚林
**		时间：12年10月24日
**		最后修改：无
*******************************************/
#ifndef _APANEL_CPANELMANAGE_H
#define _APANEL_CPANELMANAGE_H
#include "APanel_CPanelManage.h"
#endif
#include "Avtronsys/Avtronsys_Log.h"
#include <unistd.h>
namespace APanel
{

	////管理对象指针
	CPanelManage::CPanelManage()
	{
		//如果该对象构造两次，系统退出
		if (m_bConstructed)
		{
			return;
		}
		m_currPage = NULL;
		m_activePage = NULL;
		m_bConstructed = true;
		m_sysCommType = DC_COMM_WIFI;
		m_bCommStart = false;
		m_csHostIp = "";
		m_csWifiAp = "";
		m_Animation = ANI_NULL;
	}

	CPanelManage::~CPanelManage()
	{

	}

	//设置目标IP
	void CPanelManage::SetHostAddress(const char* csAddress)
	{
		this->m_csHostIp = csAddress;
	}

	//设置wifi热点
	void CPanelManage::SetDestAP(const char* csDestAp)
	{
		this->m_csWifiAp = csDestAp;
	}
	//进行序列化解析
	bool CPanelManage::Serialize(bool ismany)
	{
		//Avtronsys::Log::info("1111111111111111");
		Avtronsys::TexTureHandler lTexTureHandler1(m_Drawpages[0]->bkimg.imgPath.c_str());
		Avtronsys::Log::info("2222222222");
		lTexTureHandler1.load();	//程序这一处暂时有问题
		Avtronsys::Log::info("33333");

		for(int i=0;i<m_Drawpages.size();i++)
		{
			Avtronsys::Log::info("4444");
			m_Drawpages[i]->m_pParentCtr = NULL;	//主页面的parent为NULL
			m_Drawpages[i]->Serialize(ismany);
			if(i==0&&!ismany)
			{
				m_currPage=m_Drawpages[i];
			}
		}

		Avtronsys::Log::info("5555");
		int displayw,displayh;
		const char* imgstr[3]={"unsignal.png","signal.png","hostlink.png"};
		displayw = megl->getWidth();
		displayh = megl->getHeight();
		for(int i=0;i<3;i++)
		{

			Avtronsys::Log::info("6666");
			float px,py;
			int mh,mw;
			glDeleteTextures(1, &m_hostlinkDT[i].mTextureId);
			Avtronsys::TexTureHandler mTexTureHandler(mapp,imgstr[i],true);
			Avtronsys::Log::info("7777");
			mTexTureHandler.load();
			Avtronsys::Log::info("8888");
			m_hostlinkDT[i].setTexture(mTexTureHandler.getTextureID());
			mw = mTexTureHandler.getWidth();
			mh = mTexTureHandler.getHeight();
			m_hostlinkDT[i].setTextureArray(0,0,mw,mh);
			m_hostlinkDT[i].setSize(mw,mh);
			px = displayw - mw - 10;
			py = displayh - mh - 10;
			m_hostlinkDT[i].setLocation(px,py);
		}
		return true;
	}

	int CPanelManage::showMain()
	{
		int mh,mw;
		int tvid;
		Avtronsys::TexTureHandler mTexTureHandler(mapp,"main.png",true);
		mTexTureHandler.load();
		tvid=mTexTureHandler.getTextureID();
		m_mainDT.setTexture(tvid);
		mw = mTexTureHandler.getWidth();
		mh = mTexTureHandler.getHeight();
		m_mainDT.setTextureArray(0,0,mw,mh);
		m_mainDT.setSize(mw,mh);
		m_mainDT.setLocation(0,-150);
		Allplaysound=new Avtronsys::PlaySound(mapp) ;
		Allplaysound->start();
		Allplaysound->startSoundPlayer();

		const char* soundstr[2]= {"Button.wav","Page.wav"};
		for(int i=0;i<2;i++)
		{
			mSoundHandler[i] = new Avtronsys::SoundHandler(mapp,soundstr[i],true);
			mSoundHandler[i]->load();
		}
		return tvid;
	}


	//播放声音
	void CPanelManage::playSound(int nub)
	{
		Allplaysound->playSound(mSoundHandler[nub]);
	}

	void CPanelManage::drawMain()
	{
		m_mainDT.Drawself();
	}

	void  CPanelManage::setMainGLID(GLuint ptid)
	{
		m_mainDT.setTexture(ptid);
	}


	void CPanelManage::setAndroid_app(android_app* papp)
	{
		mapp = papp;
	}

	//设置系统的通信方式
	void CPanelManage::SetCommType(UINT uCommType)
	{
		this->m_sysCommType = uCommType;
	}

	//获取系统的通信方式
	UINT CPanelManage::GetCommType()
	{
		return this->m_sysCommType;
	}

	//获得某个页面
	CDrawPage* CPanelManage::GetPage(int iIndex)
	{
		if(iIndex >=m_Drawpages.size() || iIndex< 0)
					return NULL;
				return m_Drawpages.at(iIndex);
	}

	//添加控件元素
	bool CPanelManage::AppendCtrlItem(UINT nParentID,								//父控件ID，如果没有为0
										   APPEND_ITEM_STRUCT itemStr,					//控件属性
										   DCS_STYLE style,								//控件样式
										   DC_CTRL_TYPE ctrlType			//控件类型
										   )
	{
		//首先检查ctrlID是否重复
		//重复则返回FALSE
		if (FindCtrlByID(itemStr.nId) != NULL)
			return false;

		//根据ctrlType确定添加何种元素
		if (ctrlType == DC_CTRL_PAGE) //页面
		{
			if ((style & DCS_PARENT) != 0) //父页面
					{
				CDrawPage* pNewPage;
				//				pNewPage.CreatePage(CRect(itemStr.rect), style);
				pNewPage->SetControlId(itemStr.nId);
				AppendPage(pNewPage);
				return true;
		}
		else if ((style & DCS_CHILD) != 0) //子页面
		{
				CDrawPage* pNewPage;
				//pNewPage.CreatePage(CRect(itemStr.rect), style);
				pNewPage->SetControlId(itemStr.nId);

				CDrawPage* pParentPage = (CDrawPage*) FindCtrlByID(nParentID);
				if (pParentPage != NULL)
				{
					//设置其父控件
					pNewPage->SetParentCtr((CDrawControl*) pParentPage);
					pParentPage->AppendCtrl((CDrawControl*) pNewPage);
				}
				else
				{
					//父控件不存在
					pNewPage = NULL;
					return false;
				}
				return true;
			}
		}
		else if (ctrlType == DC_CTRL_BUTTON) //按钮
		{
			CDrawPage* pParentPage = (CDrawPage*) FindCtrlByID(nParentID);
			if (NULL == pParentPage)
				return false;
			CDrawButton* pNewButton;
			//pNewButton.SetRect(CRect(itemStr.rect));
			pNewButton->SetControlId(itemStr.nId);
			pNewButton->SetControlType(ctrlType);
			pNewButton->SetCurrentState(0, false);
			//设置父控件
			pNewButton->SetParentCtr((CDrawControl*) pParentPage);
			pParentPage->AppendCtrl((CDrawButton*) pNewButton);
			return true;
		}
		else if (ctrlType == DC_CTRL_CHECKBUTTON) //checked 按钮
		{
			CDrawPage* pParentPage = (CDrawPage*) FindCtrlByID(nParentID);

			if (pParentPage == NULL)
				return false;
			CDrawCheckButton* pNewButton;
			//pNewButton.SetRect(CRect(itemStr.rect));
			pNewButton->SetControlId(itemStr.nId);
			pNewButton->SetControlType(ctrlType);
			pNewButton->SetCurrentState(0, false);
			pNewButton->m_bChecked = false;
			//设置父控件
			pNewButton->SetParentCtr((CDrawControl*) pParentPage);
			pParentPage->AppendCtrl((CDrawButton*) pNewButton);
			return true;
		}
		else if (ctrlType == DC_CTRL_DIRECTIONBUTTON) //direction 按钮
		{

		}
		//以上 条件都 不 符 合
		return false;
	}

	//为页面添加状态
	//返回该状态的序号
	//函数只取pStateDC中(0, 0, width(nCtrlID), height(nCtrlID))部分图像
	//如果页面状态超过DC_MAX_STATE，返回-1
	//函数执行失败，返回-1
	int CPanelManage::AppendCtrlState(UINT nCtrlID)
	{
		CDrawControl*		pFinded;
		pFinded = FindCtrlByID(nCtrlID);
		//没有找到该控件
		if (NULL == pFinded)
		{
			return -1;
		}
		if(typeid(pFinded).name() != typeid(CDrawButton*).name())
		{
			return -1;
		}
		//int	nReturn = ((CDrawButton*)pFinded)->AppendButtonState(pState);
		return  0;
	}

	bool CPanelManage::LinkEventToCtrl(UINT nCtrlID, LPVOID eventData,
									   DCS_EVENT enventType, int nDataLen,
									   DCS_EVENT_CASE eventDrv)
	{
		CDrawControl *pFinded = NULL;
		pFinded = FindCtrlByID(nCtrlID);
		//没有找到该元素
		pFinded->AppendEventLink(enventType, (LPVOID)eventData, nDataLen, eventDrv);
		return true;

	}

	//绑定按钮到组
	//如果邦定成功返回TRUE；否则返回FALSE；
	//系统中含有 DC_MAX_GROUP个分组(Group)
	//每个分组(Group)含有DC_MAXCTRL_IN_G个同步元素族(Synch)
	//每个同步元素族(Synch)中有若干个控件(Ctrl)
	//处于同个同步元素族(synch)中的所有控件状态相同
	//而同一个分组(Group)中不同的同步元素族(synch)的状态是相反的。
	//说明:nGroupNum指明绑定到哪一个分组
	//     nInnerIndex指明分配到这个分组的哪一个同步元素族中。
	bool CPanelManage::BindButtonToGroup(UINT nButtonID, UINT nGroupNum, UINT nInnerIndex)
	{

		CDrawControl* pFinded = FindCtrlByID(nButtonID);
		if (pFinded->m_ctrType == DC_CTRL_CHECKBUTTON)
		{
			m_groups.BindCtrlToGroup(nGroupNum, nInnerIndex, pFinded);
			pFinded->BindToGroup(nGroupNum, nInnerIndex);
		}
		else if (pFinded->m_ctrType == DC_CTRL_BUTTON)
		{
			int	iIndex;// = pFinded->m_pParentCtr->GetCtrlIndex(pFinded);
			if(pFinded->m_pParentCtr->m_ctrType != DC_CTRL_PAGE)
			{
				return false;
			}
			else
			{
				CDrawPage* CDwPg = dynamic_cast<CDrawPage*>(pFinded->m_pParentCtr);
				iIndex = CDwPg->GetCtrlIndex(pFinded);
			}

			if (iIndex == -1)
			{
				return false;
			}
			m_groups.BindCtrlToGroup(nGroupNum, nInnerIndex, pFinded);
			pFinded->BindToGroup(nGroupNum, nInnerIndex);
		}
		return true;
	}

	//设置当前页面
	void CPanelManage::SetCurrentPage(UINT nPageId,ANIMATION_MODEL animode)
	{
		CDrawControl	*pFinded = FindCtrlByID(nPageId);
		//如果找到的元素不合法
		if ((NULL == pFinded) || typeid(pFinded).name() !=typeid(CDrawPage*).name())
		{
			return;
		}
		m_currPage = (CDrawPage*)pFinded;
	}

	void CPanelManage::SetCurrentPage(CDrawPage* pPage,ANIMATION_MODEL animode)
	{
		if (NULL == pPage)
		{
			return;
		}
		m_currPage = pPage;
		if (m_currPage == NULL)
		{
			return;
		}
		m_currPage->DrawSelf();
	}

	//获得当前页
	CDrawPage* CPanelManage::GetCurrentPage()
	{
		return m_currPage;
	}


	//开始工作
	void CPanelManage::Work()
	{
		m_currPage->DrawSelf();
		//在这里绘制网络状态
		m_hostlinkDT[impoWerstate].Drawself();
	}

	void CPanelManage::setRDraw(Avtronsys::EventLoop* pelp)
	{
		melp=pelp;
	}

	void CPanelManage::setRDraw2(Avtronsys::AvtronsysEGLDisplay* pegl)
	{
		megl = pegl;
	}

	void CPanelManage::RDraw()
	{
		int cmd = APP_CMD_WINDOW_REDRAW_NEEDED;
		write(melp->mApplication->msgwrite, &cmd, sizeof(cmd)) != sizeof(cmd);
	}

	void CPanelManage::RDraw2()
	{
		megl->EGLUpdate();
	}

	//处理组内事件
	//nGroupID:需要处理的组ID
	//pEventStart:事件发起控件
	void CPanelManage::DoGroupEvent(UINT nGroupID, CDrawControl* pEventStart)
	{

	}

	void CPanelManage::DoGroupEvent2(UINT nGroupID, UINT nGroupMask)
	{

		if (nGroupID >= DC_MAX_GROUP)
		{
			return;
		}


		CCtrlGroup* group = m_groups.GetCtrlGroup(nGroupID);

		int lenth =group->GetSynNum();
		for(int i=0; i<= lenth;i++)
		{

			//暂时只处理按钮
			if (i != nGroupMask)//同一组中不同同步族中的按钮状态相反
			{
				CSynchronousCtrls	synCtrls = m_groups.GetCtrlFromGroup(nGroupID, i);
				int synnum= (int)synCtrls.GetCtrlNum();

				for(int j  = 0; j < synnum; j++)
				{
					CDrawCheckButton* pButton = dynamic_cast<CDrawCheckButton*>(synCtrls.GetCtrlByIndex(j));
					pButton->SetChecked(false);
				}
			}
		}
		CSynchronousCtrls	synCtrls1 = m_groups.GetCtrlFromGroup(nGroupID, nGroupMask);
		int synnum=(int)synCtrls1.GetCtrlNum();
		for(int k = 0; k < synnum; k ++)
		{
			CDrawCheckButton* pButton =dynamic_cast<CDrawCheckButton*>(synCtrls1.GetCtrlByIndex(k));
			pButton->SetChecked(true);//同一组同个元素同步族中的按钮状态相同
		}
	}

	//判断某个控件是否在当前屏幕中
	bool CPanelManage::IsCtrlInCurrentScreen(UINT nCtrlID)
	{
		CDrawControl* pFind = NULL;
		pFind = FindCtrlSubFun(m_currPage, nCtrlID);

		if (NULL != pFind)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	//发送数据
	bool CPanelManage::SetEventData(LPVOID pBuffer, UINT nLen)
	{
		if (0 == pBuffer)
		{
				return false;
		}
		if (nLen <= 0)
		{
			return false;
		}
		return true;
	}


	bool CPanelManage::SendData(LAN_JOINNUM_FRAME var_SendFrame)
	{
		if(impoWerstate!=0)	//如果网络状态
		{
			//创建socket、绑定端口
			//int sd = INVALID_SOCKET;
			Avtronsys::Log::info("dsadsadasdsad");
			int sd = -1;
			sockaddr_in addr_org;
			sd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); //  以UDP方式创建socket
			addr_org.sin_family = AF_INET;
			addr_org.sin_addr.s_addr = inet_addr(hostip);
			//addr_org.sin_addr.s_addr = inet_addr("192.168.0.18");
			addr_org.sin_port = htons(2010);
			bind(sd, (struct sockaddr *) &(addr_org), sizeof(struct sockaddr_in)); // 绑定IP和端口
			//发送数据
			sockaddr_in addr_dst;
			addr_dst.sin_family = AF_INET;
			//addr_dst.sin_addr.s_addr = inet_addr("192.168.1.243");
			addr_dst.sin_addr.s_addr = inet_addr(this->m_csHostIp);
			addr_dst.sin_port = htons(2010);
			int erro = sendto(sd, (char*)&var_SendFrame, sizeof(var_SendFrame), 0, (struct sockaddr *)&(addr_dst), sizeof(sockaddr_in));  // 发送DataBuff中的数据
			if(erro>0)
			{
				Avtronsys::Log::info("success");
			}
			else
			{
				Avtronsys::Log::info("fail");
			}
			shutdown(sd,8);
			//closesocket(sd);
			close(sd);
			return true;
		}
		return false;
	}

	//停止发送数据
	bool CPanelManage::EndSend()
	{
		return true;
	}

	//获得MachineIP
	const char* CPanelManage::GetMachineIP()
	{
		return m_csHostIp;
	}

	int CPanelManage::AsyncPageSerial(LPVOID lpParameter)
	{

	}

	//添加页面
	int CPanelManage::AppendPage(CDrawPage* pAdd)
	{
		if (NULL == pAdd)
		{
			return -1;
		}

		m_Drawpages.push_back(pAdd);
		return m_Drawpages.size() - 1;
	}
	
	//插入页面
	void CPanelManage::InsertPage(CDrawPage* pInsert, UINT iIndex)
	{
		if (NULL == pInsert || iIndex >m_Drawpages.size())
		{
			return ;
		}
		vector<CDrawPage*>::iterator it = m_Drawpages.begin();
		m_Drawpages.insert(it+iIndex,pInsert);
	}


	//查找某个CtrlID的页面
	CDrawControl* CPanelManage::FindCtrlByID(UINT nCtrlID)
	{
		CDrawControl*  Result = NULL;
		for(int i = 0; i< m_Drawpages.size();i++)
		{
			CDrawControl* pFonded = NULL;

			if(m_Drawpages[i]->GetControlId() == nCtrlID)
			{
				Result =  m_Drawpages.at(i);
				return Result;
			}

			//递归
			pFonded = FindCtrlSubFun(m_Drawpages.at(i), nCtrlID);
			if (pFonded != NULL)
			{
				Result = pFonded;
				return Result;
			}
		}
	}

	//根据ID查找某个页面里面的某个控件
	CDrawControl* CPanelManage::FindCtrlSubFun(CDrawPage* pPage, UINT nCtrlID)
	{
		CDrawControl* pReturn = NULL;
		for (int i = 0; i < pPage->m_childCtrl.size(); i ++)
		{
			if (pPage->m_childCtrl.at(i)->GetControlId() == nCtrlID)
			{
				pReturn = pPage->m_childCtrl.at(i);
				return pReturn;
			}

			//若是子页面则找里面的控件
			if (pPage->m_childCtrl.at(i)->m_ctrType == DC_CTRL_PAGE)
			{
				CDrawPage* pChild = dynamic_cast<CDrawPage*>(pPage->m_childCtrl.at(i));
				CDrawControl* pFinded = FindCtrlSubFun(dynamic_cast<CDrawPage*>(pPage->m_childCtrl.at(i)), nCtrlID);
				if (pFinded != NULL)
				{
					// 隐藏的子页面的数据，不显示
					if ((pChild->GetControlType() & DCS_SHOW) != 0)
					{
						pReturn = pFinded;
					}
					return pReturn;
				}
			}
		}
		return pReturn;
	}

	//接受一个鼠标按钮事件
	void CPanelManage::PostButtonMessage(bool bDown, POINT pt)
	{
		//接受一个鼠标事件
		if (bDown)
		{
			m_activePage = m_currPage;	//设置当前正在触发的页面
			if(NULL != m_activePage)
			{
				m_activePage->OnLButtonDown(pt);
			}
		}
		else
		{ //弹起事件
			if (NULL == m_activePage)
			{
				return;
			}

			EndSend();
			m_activePage->OnLButtonUp(pt);
			m_activePage = NULL;
		}
	}

	//事件响应
	/*页面跳转*/
	void CPanelManage::PageJump(UINT nID,ANIMATION_MODEL animode)
	{
		if (nID != 0)
		{
			CDrawControl* pCtrl=FindCtrlByID(nID);
			CDrawPage* pFinded = dynamic_cast<CDrawPage*>(pCtrl);

			//如果跳转的页面为主页面
			if (pFinded->m_ctrShowType & DCS_PARENT)
			{
				playSound(1);
				pFinded->SetPrevPage(m_currPage);
				SetCurrentPage(pFinded, animode);
			}
			//如果跳转页面为子页面
			else if (pFinded->m_ctrShowType & DCS_CHILD)
			{

				pFinded->m_ctrShowType |= DCS_SHOW;

				UINT nCtrlIndex = pFinded->m_pParentCtr->GetCtrlIndex(pFinded);
				if(pFinded->m_pParentCtr->m_ctrType != DC_CTRL_PAGE)
				{

				}
				else
				{
					CDrawPage* CDwPg = dynamic_cast<CDrawPage*>(pFinded->m_pParentCtr);
					nCtrlIndex = CDwPg->GetCtrlIndex(pCtrl);

					((CDrawPage*) (pFinded->m_pParentCtr))->MoveCtrlToTopest(
						nCtrlIndex);

				//如果跳转的子页面并不是当前页面的子元素，不处理
				if (pFinded->m_pParentCtr != m_currPage)
					return;
				}
			}
		}
		else
		{

			CDrawPage* pCurrNew = m_currPage->GetPrevPage();
			//如果当前页面没有前一页面

			if (!pCurrNew)
				return;
			m_currPage->SetPrevPage(NULL);
			playSound(1);
			SetCurrentPage(pCurrNew);

		}
		m_currPage->DrawSelf();
	}





	/*隐藏某个元素*/
	void CPanelManage::HideItem(UINT nID)
	{
		if (nID <= 0)
			return;
		//查找该元素
		CDrawControl* pFinded = FindCtrlByID(nID);

		//ID 为 nID的元素不存在
		if (!pFinded)
			return;
		//如果隐藏的元素是主页面
		if(pFinded->m_ctrType == DC_CTRL_PAGE && pFinded->m_pParentCtr==NULL  &&(pFinded->m_ctrShowType== DCS_PARENT))
		{
			//跳转到前 页面
			if ((CDrawPage*)pFinded == m_currPage)
			{
				PageJump(0);
			}
		}
		//隐藏的是 一 般元素
		else
		{
			CDrawControl* pTemp = pFinded;
			pFinded->m_ctrShowType &= ~DCS_SHOW;

			while( pTemp->m_pParentCtr != NULL)
			{
				pTemp = pTemp->m_pParentCtr;
			}

			//判断该元素是否 为当前页面元素
			if ((CDrawPage*)pTemp != m_currPage)
			return;
		}
	}

}
