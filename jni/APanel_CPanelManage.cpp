/******************************************
**		�ļ���APanel_CDrawCheckButton.cpp
**		���ߣ�������
**		ʱ�䣺12��10��24��
**		����޸ģ���
*******************************************/
#ifndef _APANEL_CPANELMANAGE_H
#define _APANEL_CPANELMANAGE_H
#include "APanel_CPanelManage.h"
#endif
#include "Avtronsys/Avtronsys_Log.h"
#include <unistd.h>
namespace APanel
{

	////�������ָ��
	CPanelManage::CPanelManage()
	{
		//����ö��������Σ�ϵͳ�˳�
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

	//����Ŀ��IP
	void CPanelManage::SetHostAddress(const char* csAddress)
	{
		this->m_csHostIp = csAddress;
	}

	//����wifi�ȵ�
	void CPanelManage::SetDestAP(const char* csDestAp)
	{
		this->m_csWifiAp = csDestAp;
	}
	//�������л�����
	bool CPanelManage::Serialize(bool ismany)
	{
		//Avtronsys::Log::info("1111111111111111");
		Avtronsys::TexTureHandler lTexTureHandler1(m_Drawpages[0]->bkimg.imgPath.c_str());
		Avtronsys::Log::info("2222222222");
		lTexTureHandler1.load();	//������һ����ʱ������
		Avtronsys::Log::info("33333");

		for(int i=0;i<m_Drawpages.size();i++)
		{
			Avtronsys::Log::info("4444");
			m_Drawpages[i]->m_pParentCtr = NULL;	//��ҳ���parentΪNULL
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


	//��������
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

	//����ϵͳ��ͨ�ŷ�ʽ
	void CPanelManage::SetCommType(UINT uCommType)
	{
		this->m_sysCommType = uCommType;
	}

	//��ȡϵͳ��ͨ�ŷ�ʽ
	UINT CPanelManage::GetCommType()
	{
		return this->m_sysCommType;
	}

	//���ĳ��ҳ��
	CDrawPage* CPanelManage::GetPage(int iIndex)
	{
		if(iIndex >=m_Drawpages.size() || iIndex< 0)
					return NULL;
				return m_Drawpages.at(iIndex);
	}

	//��ӿؼ�Ԫ��
	bool CPanelManage::AppendCtrlItem(UINT nParentID,								//���ؼ�ID�����û��Ϊ0
										   APPEND_ITEM_STRUCT itemStr,					//�ؼ�����
										   DCS_STYLE style,								//�ؼ���ʽ
										   DC_CTRL_TYPE ctrlType			//�ؼ�����
										   )
	{
		//���ȼ��ctrlID�Ƿ��ظ�
		//�ظ��򷵻�FALSE
		if (FindCtrlByID(itemStr.nId) != NULL)
			return false;

		//����ctrlTypeȷ����Ӻ���Ԫ��
		if (ctrlType == DC_CTRL_PAGE) //ҳ��
		{
			if ((style & DCS_PARENT) != 0) //��ҳ��
					{
				CDrawPage* pNewPage;
				//				pNewPage.CreatePage(CRect(itemStr.rect), style);
				pNewPage->SetControlId(itemStr.nId);
				AppendPage(pNewPage);
				return true;
		}
		else if ((style & DCS_CHILD) != 0) //��ҳ��
		{
				CDrawPage* pNewPage;
				//pNewPage.CreatePage(CRect(itemStr.rect), style);
				pNewPage->SetControlId(itemStr.nId);

				CDrawPage* pParentPage = (CDrawPage*) FindCtrlByID(nParentID);
				if (pParentPage != NULL)
				{
					//�����丸�ؼ�
					pNewPage->SetParentCtr((CDrawControl*) pParentPage);
					pParentPage->AppendCtrl((CDrawControl*) pNewPage);
				}
				else
				{
					//���ؼ�������
					pNewPage = NULL;
					return false;
				}
				return true;
			}
		}
		else if (ctrlType == DC_CTRL_BUTTON) //��ť
		{
			CDrawPage* pParentPage = (CDrawPage*) FindCtrlByID(nParentID);
			if (NULL == pParentPage)
				return false;
			CDrawButton* pNewButton;
			//pNewButton.SetRect(CRect(itemStr.rect));
			pNewButton->SetControlId(itemStr.nId);
			pNewButton->SetControlType(ctrlType);
			pNewButton->SetCurrentState(0, false);
			//���ø��ؼ�
			pNewButton->SetParentCtr((CDrawControl*) pParentPage);
			pParentPage->AppendCtrl((CDrawButton*) pNewButton);
			return true;
		}
		else if (ctrlType == DC_CTRL_CHECKBUTTON) //checked ��ť
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
			//���ø��ؼ�
			pNewButton->SetParentCtr((CDrawControl*) pParentPage);
			pParentPage->AppendCtrl((CDrawButton*) pNewButton);
			return true;
		}
		else if (ctrlType == DC_CTRL_DIRECTIONBUTTON) //direction ��ť
		{

		}
		//���� ������ �� �� ��
		return false;
	}

	//Ϊҳ�����״̬
	//���ظ�״̬�����
	//����ֻȡpStateDC��(0, 0, width(nCtrlID), height(nCtrlID))����ͼ��
	//���ҳ��״̬����DC_MAX_STATE������-1
	//����ִ��ʧ�ܣ�����-1
	int CPanelManage::AppendCtrlState(UINT nCtrlID)
	{
		CDrawControl*		pFinded;
		pFinded = FindCtrlByID(nCtrlID);
		//û���ҵ��ÿؼ�
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
		//û���ҵ���Ԫ��
		pFinded->AppendEventLink(enventType, (LPVOID)eventData, nDataLen, eventDrv);
		return true;

	}

	//�󶨰�ť����
	//�����ɹ�����TRUE�����򷵻�FALSE��
	//ϵͳ�к��� DC_MAX_GROUP������(Group)
	//ÿ������(Group)����DC_MAXCTRL_IN_G��ͬ��Ԫ����(Synch)
	//ÿ��ͬ��Ԫ����(Synch)�������ɸ��ؼ�(Ctrl)
	//����ͬ��ͬ��Ԫ����(synch)�е����пؼ�״̬��ͬ
	//��ͬһ������(Group)�в�ͬ��ͬ��Ԫ����(synch)��״̬���෴�ġ�
	//˵��:nGroupNumָ���󶨵���һ������
	//     nInnerIndexָ�����䵽����������һ��ͬ��Ԫ�����С�
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

	//���õ�ǰҳ��
	void CPanelManage::SetCurrentPage(UINT nPageId,ANIMATION_MODEL animode)
	{
		CDrawControl	*pFinded = FindCtrlByID(nPageId);
		//����ҵ���Ԫ�ز��Ϸ�
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

	//��õ�ǰҳ
	CDrawPage* CPanelManage::GetCurrentPage()
	{
		return m_currPage;
	}


	//��ʼ����
	void CPanelManage::Work()
	{
		m_currPage->DrawSelf();
		//�������������״̬
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

	//���������¼�
	//nGroupID:��Ҫ�������ID
	//pEventStart:�¼�����ؼ�
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

			//��ʱֻ����ť
			if (i != nGroupMask)//ͬһ���в�ͬͬ�����еİ�ť״̬�෴
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
			pButton->SetChecked(true);//ͬһ��ͬ��Ԫ��ͬ�����еİ�ť״̬��ͬ
		}
	}

	//�ж�ĳ���ؼ��Ƿ��ڵ�ǰ��Ļ��
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

	//��������
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
		if(impoWerstate!=0)	//�������״̬
		{
			//����socket���󶨶˿�
			//int sd = INVALID_SOCKET;
			Avtronsys::Log::info("dsadsadasdsad");
			int sd = -1;
			sockaddr_in addr_org;
			sd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); //  ��UDP��ʽ����socket
			addr_org.sin_family = AF_INET;
			addr_org.sin_addr.s_addr = inet_addr(hostip);
			//addr_org.sin_addr.s_addr = inet_addr("192.168.0.18");
			addr_org.sin_port = htons(2010);
			bind(sd, (struct sockaddr *) &(addr_org), sizeof(struct sockaddr_in)); // ��IP�Ͷ˿�
			//��������
			sockaddr_in addr_dst;
			addr_dst.sin_family = AF_INET;
			//addr_dst.sin_addr.s_addr = inet_addr("192.168.1.243");
			addr_dst.sin_addr.s_addr = inet_addr(this->m_csHostIp);
			addr_dst.sin_port = htons(2010);
			int erro = sendto(sd, (char*)&var_SendFrame, sizeof(var_SendFrame), 0, (struct sockaddr *)&(addr_dst), sizeof(sockaddr_in));  // ����DataBuff�е�����
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

	//ֹͣ��������
	bool CPanelManage::EndSend()
	{
		return true;
	}

	//���MachineIP
	const char* CPanelManage::GetMachineIP()
	{
		return m_csHostIp;
	}

	int CPanelManage::AsyncPageSerial(LPVOID lpParameter)
	{

	}

	//���ҳ��
	int CPanelManage::AppendPage(CDrawPage* pAdd)
	{
		if (NULL == pAdd)
		{
			return -1;
		}

		m_Drawpages.push_back(pAdd);
		return m_Drawpages.size() - 1;
	}
	
	//����ҳ��
	void CPanelManage::InsertPage(CDrawPage* pInsert, UINT iIndex)
	{
		if (NULL == pInsert || iIndex >m_Drawpages.size())
		{
			return ;
		}
		vector<CDrawPage*>::iterator it = m_Drawpages.begin();
		m_Drawpages.insert(it+iIndex,pInsert);
	}


	//����ĳ��CtrlID��ҳ��
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

			//�ݹ�
			pFonded = FindCtrlSubFun(m_Drawpages.at(i), nCtrlID);
			if (pFonded != NULL)
			{
				Result = pFonded;
				return Result;
			}
		}
	}

	//����ID����ĳ��ҳ�������ĳ���ؼ�
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

			//������ҳ����������Ŀؼ�
			if (pPage->m_childCtrl.at(i)->m_ctrType == DC_CTRL_PAGE)
			{
				CDrawPage* pChild = dynamic_cast<CDrawPage*>(pPage->m_childCtrl.at(i));
				CDrawControl* pFinded = FindCtrlSubFun(dynamic_cast<CDrawPage*>(pPage->m_childCtrl.at(i)), nCtrlID);
				if (pFinded != NULL)
				{
					// ���ص���ҳ������ݣ�����ʾ
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

	//����һ����갴ť�¼�
	void CPanelManage::PostButtonMessage(bool bDown, POINT pt)
	{
		//����һ������¼�
		if (bDown)
		{
			m_activePage = m_currPage;	//���õ�ǰ���ڴ�����ҳ��
			if(NULL != m_activePage)
			{
				m_activePage->OnLButtonDown(pt);
			}
		}
		else
		{ //�����¼�
			if (NULL == m_activePage)
			{
				return;
			}

			EndSend();
			m_activePage->OnLButtonUp(pt);
			m_activePage = NULL;
		}
	}

	//�¼���Ӧ
	/*ҳ����ת*/
	void CPanelManage::PageJump(UINT nID,ANIMATION_MODEL animode)
	{
		if (nID != 0)
		{
			CDrawControl* pCtrl=FindCtrlByID(nID);
			CDrawPage* pFinded = dynamic_cast<CDrawPage*>(pCtrl);

			//�����ת��ҳ��Ϊ��ҳ��
			if (pFinded->m_ctrShowType & DCS_PARENT)
			{
				playSound(1);
				pFinded->SetPrevPage(m_currPage);
				SetCurrentPage(pFinded, animode);
			}
			//�����תҳ��Ϊ��ҳ��
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

				//�����ת����ҳ�沢���ǵ�ǰҳ�����Ԫ�أ�������
				if (pFinded->m_pParentCtr != m_currPage)
					return;
				}
			}
		}
		else
		{

			CDrawPage* pCurrNew = m_currPage->GetPrevPage();
			//�����ǰҳ��û��ǰһҳ��

			if (!pCurrNew)
				return;
			m_currPage->SetPrevPage(NULL);
			playSound(1);
			SetCurrentPage(pCurrNew);

		}
		m_currPage->DrawSelf();
	}





	/*����ĳ��Ԫ��*/
	void CPanelManage::HideItem(UINT nID)
	{
		if (nID <= 0)
			return;
		//���Ҹ�Ԫ��
		CDrawControl* pFinded = FindCtrlByID(nID);

		//ID Ϊ nID��Ԫ�ز�����
		if (!pFinded)
			return;
		//������ص�Ԫ������ҳ��
		if(pFinded->m_ctrType == DC_CTRL_PAGE && pFinded->m_pParentCtr==NULL  &&(pFinded->m_ctrShowType== DCS_PARENT))
		{
			//��ת��ǰ ҳ��
			if ((CDrawPage*)pFinded == m_currPage)
			{
				PageJump(0);
			}
		}
		//���ص��� һ ��Ԫ��
		else
		{
			CDrawControl* pTemp = pFinded;
			pFinded->m_ctrShowType &= ~DCS_SHOW;

			while( pTemp->m_pParentCtr != NULL)
			{
				pTemp = pTemp->m_pParentCtr;
			}

			//�жϸ�Ԫ���Ƿ� Ϊ��ǰҳ��Ԫ��
			if ((CDrawPage*)pTemp != m_currPage)
			return;
		}
	}

}
