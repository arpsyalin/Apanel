/******************************************
**		�ļ���APanel_CDrawPage.cpp
**		���ߣ�������
**		ʱ�䣺12��10��24��
**		����޸ģ���
*******************************************/
#ifndef _APANEL_CDRAWPAGE_H
#define _APANEL_CDRAWPAGE_H
#include "APanel_CDrawPage.h"
#endif


#ifndef _APANEL_CPANELMANAGE_H
#define _APANEL_CPANELMANAGE_H
#include "APanel_CPanelManage.h"
#endif

#include "Avtronsys/Avtronsys_Log.h"
namespace APanel
{

	CDrawPage::CDrawPage()
	{
		this->m_ctrShowType = DCS_PARENT | DCS_SHOW;
		this->m_pActiveCtrl = NULL;
		this->m_prevPage = NULL;
	}

	CDrawPage::~CDrawPage()
	{
		vector<CDrawControl*>::iterator it;
		for(it = m_childCtrl.begin(); it!=m_childCtrl.end();)
		{
			it = m_childCtrl.erase(it);  //���ص���һ����һ��Ԫ�ص�λ��,ע�������ʧЧ����
		}
	}

	//�� �� ����
	bool CDrawPage::DrawSelf(ANIMATION_MODEL animode)
	{

	}

	bool CDrawPage::DrawSelf()
	{
		//����
		mDrawTexture.Drawself();

		for(int i=0;i<m_drawindex.size();i++)
		{

			if(m_childCtrl.at(m_drawindex.at(i))->m_ctrType==DC_CTRL_BUTTON)
			{
				CDrawButton* CDwBtn = dynamic_cast<CDrawButton*>(m_childCtrl.at(m_drawindex.at(i)));
				CDwBtn->DrawSelf();
			}
			else if(m_childCtrl.at(m_drawindex.at(i))->m_ctrType==DC_CTRL_PAGE)
			{
				//��ҳ��
				if(m_childCtrl.at(m_drawindex.at(i))->m_ctrShowType != DCS_CHILD)
				{
					CDrawPage* CDwPg = dynamic_cast<CDrawPage*>(m_childCtrl.at(m_drawindex.at(i)));
					CDwPg->DrawSelf();
				}
			}
			else if(m_childCtrl.at(m_drawindex.at(i))->m_ctrType==DC_CTRL_CHECKBUTTON)
			{
				//check��ť
				CDrawCheckButton* CDwCkBtn =  dynamic_cast<CDrawCheckButton*>(m_childCtrl.at(m_drawindex.at(i)));
				CDwCkBtn->DrawSelf();
			}
			else if(m_childCtrl.at(m_drawindex.at(i))->m_ctrType==DC_CTRL_DIRECTIONBUTTON)
			{
				//Direction��ť
				CDrawDireButton* CDwDrBtn = dynamic_cast<CDrawDireButton*>(m_childCtrl.at(m_drawindex.at(i)));
				CDwDrBtn->DrawSelf();
			}
		}
	}

	//���л�
	bool CDrawPage::Serialize(bool ismany)
	{
		Avtronsys::Log::info("aaaaaaaaaaa");
		int num =m_childCtrl.size();
		int drawindex= m_drawindex.size();
		if(drawindex==0&&num>0)
		{
			for(int i=0;i<num;i++)
			{
				m_drawindex.push_back(i);
			}
		}
		for(int i=0;i<num;i++)
		{
			m_childCtrl.at(i)->m_pParentCtr = this;
			if(m_childCtrl.at(i)->m_ctrType==DC_CTRL_BUTTON)
			{
				Avtronsys::Log::info("aaaaaaaaaaa4");
				CDrawButton* CDwBtn = dynamic_cast<CDrawButton*>(m_childCtrl.at(i));
				CDwBtn->Serialize(ismany);
			}
			else if(m_childCtrl.at(i)->m_ctrType==DC_CTRL_PAGE)
			{
				Avtronsys::Log::info("aaaaaaaaaaa3");
				//��ҳ��
				CDrawPage* CDwPg = dynamic_cast<CDrawPage*>(m_childCtrl.at(i));
				CDwPg->Serialize(ismany);
			}
			else if(m_childCtrl.at(i)->m_ctrType==DC_CTRL_CHECKBUTTON)
			{
				Avtronsys::Log::info("aaaaaaaaaaa2");
				//check��ť
				CDrawCheckButton* CDwCkBtn =  dynamic_cast<CDrawCheckButton*>(m_childCtrl.at(i));
				CDwCkBtn->Serialize(ismany);
			}
			else if(m_childCtrl.at(i)->m_ctrType==DC_CTRL_DIRECTIONBUTTON)
			{
				Avtronsys::Log::info("aaaaaaaaaaa1");
				//Direction��ť
				CDrawDireButton* CDwDrBtn = dynamic_cast<CDrawDireButton*>(m_childCtrl.at(i));
				CDwDrBtn->Serialize(ismany);
			}
		}
		//for(int i=0;i<m_stateImg.size();i++)
		//{
		//	glDeleteTextures(1, &m_stateImg[i].texID);
		//	Avtronsys::TexTureHandler mTexTureHandler(m_stateImg[i].imgPath.c_str());
		//	mTexTureHandler.load();
		//	m_stateImg[i].texID = mTexTureHandler.getTextureID();
		//}
		glDeleteTextures(1, &bkimg.texID);
		Avtronsys::TexTureHandler mTexTureHandler(bkimg.imgPath.c_str());
		mTexTureHandler.load();
		bkimg.texID = mTexTureHandler.getTextureID();
		//��ʼ����ǰҳ��ID
		//ProjectDrawInit(m_stateImg[0].texID);
		ProjectDrawInit(bkimg.texID);
	}

	//���һ���ؼ���Ϊ��ҳ����ӿؼ�
	//������ӵĿؼ��ڿؼ������е��±�
	//�ú�����Ԫ�ز��뵽�ռ���������
	int CDrawPage::AppendCtrl(CDrawControl* pAdd)
	{
		if(NULL == pAdd)
		{
			return -1;
		}
		m_childCtrl.push_back(pAdd);
		pAdd->SetParentCtr((CDrawPage*)this);
		return m_childCtrl.size()-1;
	}

	//����һ���ռ䵽ҳ����
	//nIndex����Ҫ�����λ�ã�ֵ�ķ�Χ��0-��GetChildCtrlCount���� - 1��
	void CDrawPage::InsertCtrl(CDrawControl* pInsert, UINT nIndex)
	{
		if(nIndex>(GetChildCount()-1 ) || nIndex <0)
			return ;
		m_childCtrl.insert(m_childCtrl.begin()+nIndex,pInsert);

	}

	//����ӿؼ��ĸ���
	UINT CDrawPage::GetChildCount()
	{
		return m_childCtrl.size();
	}

	//����ҳ��
	bool CreatePage(RECT rect,					//ҳ�������
					DCS_STYLE dcStyle)			//ҳ�����ʽ��DCS_PARENT,DCS_CHILD
	{
		return true;
	}



	//���ñ���
	//void			SetBkLzw(CLZWBits* pLzwBits);

	//������Ӧ
	void CDrawPage::OnLButtonDown(POINT pt)
	{
		int downi = -1;
		for (int i = m_childCtrl.size() - 1; i >= 0; i--)
		{
			//���ؼ��������Χ���ҿؼ��Ŀɼ���ʽ������ҳ��(��������Ϊֻ�е���Ϊ��ҳ���ʱ��Ų�����ʾ)
			if ((m_childCtrl.at(i)->IsInRect(pt)) && (m_childCtrl.at(i)->GetControlType() != DCS_CHILD))
			{
				m_panelMan->mLastDownControl = m_childCtrl.at(i);	//��¼��ǰ���µ�Ϊ���һ�ΰ��µĿؼ�
				m_pActiveCtrl = m_childCtrl.at(i);	//���õ�ǰ�����͡�
				downi = i;
				if(m_childCtrl.at(i)->m_ctrType == DC_CTRL_BUTTON)
				{
					//��ť
					CDrawButton* CDwBtn = dynamic_cast<CDrawButton*>(m_childCtrl.at(i));
					CDwBtn->OnLButtonDown(false);
				}
				else if(m_childCtrl.at(i)->m_ctrType==DC_CTRL_PAGE)
				{
					//ҳ��
					CDrawPage* CDwPg = dynamic_cast<CDrawPage*>(m_childCtrl.at(i));
					CDwPg->OnLButtonDown(pt);
				}
				else if(m_childCtrl.at(i)->m_ctrType==DC_CTRL_CHECKBUTTON)
				{
					//check��ť
					CDrawCheckButton* CDwCkBtn =  dynamic_cast<CDrawCheckButton*>(m_childCtrl.at(i));
					CDwCkBtn->OnLButtonDown(false);
				}
				else if(m_childCtrl.at(i)->m_ctrType==DC_CTRL_DIRECTIONBUTTON)
				{
					//Direction��ť
					CDrawDireButton* CDwDrBtn = dynamic_cast<CDrawDireButton*>(m_childCtrl.at(i));
					CDwDrBtn->OnLButtonDown(false);
				}
				break;
			}
		}

		if( downi != -1)
		{
			MoveCtrlToTopest(downi);
		}

	}

	void CDrawPage::OnLButtonUp(POINT pt)
	{
		Avtronsys::Log::info("aasd");
		if(m_panelMan->mLastDownControl !=NULL && !m_panelMan->mLastDownControl->IsInRect(pt) && m_panelMan->IsCtrlInCurrentScreen(m_panelMan->mLastDownControl->m_ctrId))
		{
			if(m_panelMan->mLastDownControl->m_ctrType == DC_CTRL_BUTTON)
			{
				//��ť
				CDrawButton* CDwBtn = dynamic_cast<CDrawButton*>(m_panelMan->mLastDownControl);
				CDwBtn->OnLButtonUp(true);
				m_panelMan->mLastDownControl=NULL;
				return;
			}
			else if(m_panelMan->mLastDownControl->m_ctrType == DC_CTRL_CHECKBUTTON)
			{
				//��ť
				CDrawCheckButton* CDwBtn = dynamic_cast<CDrawCheckButton*>(m_panelMan->mLastDownControl);
				CDwBtn->OnLButtonUp(true);
				m_panelMan->mLastDownControl=NULL;
				return;
			}
		}

		int i = m_childCtrl.size()-1;
		for (; i >=0 ; i--)
		{
			//���ؼ��������Χ���ҿؼ��Ŀɼ���ʽ������ҳ��(��������Ϊֻ�е���Ϊ��ҳ���ʱ��Ų�����ʾ)
			if ((m_childCtrl.at(i)->IsInRect(pt)) && (m_childCtrl.at(i)->GetControlType() != DCS_CHILD))
			{
				if(m_childCtrl.at(i)->m_ctrType!=DC_CTRL_DIRECTIONBUTTON)
				{
					m_pActiveCtrl = m_childCtrl.at(i);	//���õ�ǰ�����͡�
				}
				if(m_childCtrl.at(i)->m_ctrType == DC_CTRL_BUTTON)
				{
					//��ť
					CDrawButton* CDwBtn = dynamic_cast<CDrawButton*>(m_childCtrl.at(i));
					CDwBtn->OnLButtonUp(false);
				}
				else if(m_childCtrl.at(i)->m_ctrType==DC_CTRL_PAGE)
				{
					//ҳ��
					CDrawPage* CDwPg = dynamic_cast<CDrawPage*>(m_childCtrl.at(i));
					CDwPg->OnLButtonUp(pt);
				}
				else if(m_childCtrl.at(i)->m_ctrType==DC_CTRL_CHECKBUTTON)
				{
					Avtronsys::Log::info("aasd1");
					//check��ť
					CDrawCheckButton* CDwCkBtn = dynamic_cast<CDrawCheckButton*>(m_childCtrl.at(i));
					CDwCkBtn->OnLButtonUp(false);
				}
				else if(m_childCtrl.at(i)->m_ctrType==DC_CTRL_DIRECTIONBUTTON)
				{
					//Direction��ť
					CDrawDireButton* CDwDrBtn = dynamic_cast<CDrawDireButton*>(m_childCtrl.at(i));
					CDwDrBtn->OnLButtonUp(false);
				}
				break;
			}
		}
	}

	//����ĳ������
	void CDrawPage::InvalidateRect(RECT rect)
	{

	}

	//����/���ǰһ��ҳ��
	void CDrawPage::SetPrevPage(CDrawPage* pPage)
	{
		m_prevPage = pPage;
	}
	CDrawPage* CDrawPage::GetPrevPage()
	{
		return m_prevPage;
	}

	int CDrawPage::GetCtrlIndex(CDrawControl* pCtrl)
	{
		if(NULL == pCtrl)
			return -1;
		for(int i = 0 ;i<m_childCtrl.size();++i)
		{
			if(pCtrl->m_ctrId == m_childCtrl.at(i)->m_ctrId)
			return i;
		}
	}

	//��ĳ���ӿؼ��Ƶ����ϲ�
	bool CDrawPage::MoveCtrlToTopest(UINT nCtrlIndex)
	{
		if(nCtrlIndex<0 || nCtrlIndex >=(int)GetChildCount())
		{
			return false;
		}
		int num = nCtrlIndex;
		vector<int>::iterator it;
		for(it = m_drawindex.begin(); it!=m_drawindex.end();)
		{
			if(*it == nCtrlIndex)
			{
				m_drawindex.erase(it);  //���ص���һ����һ��Ԫ�ص�λ��,ע�������ʧЧ����
				break;
			}
			else
			{
				it++;
			}
		}
		m_drawindex.push_back(nCtrlIndex);
		return true;

		/*
		if(nCtrlIndex<0 || nCtrlIndex >=(int)GetChildCount())
				return false;
		CDrawControl* pCtrl = m_childCtrl.at(nCtrlIndex);
		CDrawControl* pCtrl1 = new CDrawControl;
		memcpy(pCtrl1,pCtrl,sizeof(pCtrl));
		vector<CDrawControl*>::iterator it;
		for(it = m_childCtrl.begin(); it!=m_childCtrl.end();)
		{
			if(*it == pCtrl)
			{
				m_childCtrl.erase(it);  //���ص���һ����һ��Ԫ�ص�λ��,ע�������ʧЧ����
				break;
			}
			else
			{
				it++;
			}
		}
		m_childCtrl.push_back(pCtrl);
		return true;
		*/
	}

	//����/��ȡ����Ч��
	ANIMATION_MODEL& CDrawPage::Animation()
	{

	}
}
