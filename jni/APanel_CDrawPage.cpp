/******************************************
**		文件：APanel_CDrawPage.cpp
**		作者：刘亚林
**		时间：12年10月24日
**		最后修改：无
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
			it = m_childCtrl.erase(it);  //返回的是一个下一个元素的位置,注意迭代器失效问题
		}
	}

	//自 绘 函数
	bool CDrawPage::DrawSelf(ANIMATION_MODEL animode)
	{

	}

	bool CDrawPage::DrawSelf()
	{
		//绘制
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
				//子页面
				if(m_childCtrl.at(m_drawindex.at(i))->m_ctrShowType != DCS_CHILD)
				{
					CDrawPage* CDwPg = dynamic_cast<CDrawPage*>(m_childCtrl.at(m_drawindex.at(i)));
					CDwPg->DrawSelf();
				}
			}
			else if(m_childCtrl.at(m_drawindex.at(i))->m_ctrType==DC_CTRL_CHECKBUTTON)
			{
				//check按钮
				CDrawCheckButton* CDwCkBtn =  dynamic_cast<CDrawCheckButton*>(m_childCtrl.at(m_drawindex.at(i)));
				CDwCkBtn->DrawSelf();
			}
			else if(m_childCtrl.at(m_drawindex.at(i))->m_ctrType==DC_CTRL_DIRECTIONBUTTON)
			{
				//Direction按钮
				CDrawDireButton* CDwDrBtn = dynamic_cast<CDrawDireButton*>(m_childCtrl.at(m_drawindex.at(i)));
				CDwDrBtn->DrawSelf();
			}
		}
	}

	//序列化
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
				//子页面
				CDrawPage* CDwPg = dynamic_cast<CDrawPage*>(m_childCtrl.at(i));
				CDwPg->Serialize(ismany);
			}
			else if(m_childCtrl.at(i)->m_ctrType==DC_CTRL_CHECKBUTTON)
			{
				Avtronsys::Log::info("aaaaaaaaaaa2");
				//check按钮
				CDrawCheckButton* CDwCkBtn =  dynamic_cast<CDrawCheckButton*>(m_childCtrl.at(i));
				CDwCkBtn->Serialize(ismany);
			}
			else if(m_childCtrl.at(i)->m_ctrType==DC_CTRL_DIRECTIONBUTTON)
			{
				Avtronsys::Log::info("aaaaaaaaaaa1");
				//Direction按钮
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
		//初始化当前页面ID
		//ProjectDrawInit(m_stateImg[0].texID);
		ProjectDrawInit(bkimg.texID);
	}

	//添加一个控件作为该页面的子控件
	//返回添加的控件在控件数组中的下标
	//该函数将元素插入到空间数组的最后
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

	//插入一个空间到页面中
	//nIndex：需要插入的位置，值的范围在0-（GetChildCtrlCount（） - 1）
	void CDrawPage::InsertCtrl(CDrawControl* pInsert, UINT nIndex)
	{
		if(nIndex>(GetChildCount()-1 ) || nIndex <0)
			return ;
		m_childCtrl.insert(m_childCtrl.begin()+nIndex,pInsert);

	}

	//获得子控件的个数
	UINT CDrawPage::GetChildCount()
	{
		return m_childCtrl.size();
	}

	//创建页面
	bool CreatePage(RECT rect,					//页面的区域
					DCS_STYLE dcStyle)			//页面的样式：DCS_PARENT,DCS_CHILD
	{
		return true;
	}



	//设置背景
	//void			SetBkLzw(CLZWBits* pLzwBits);

	//按键相应
	void CDrawPage::OnLButtonDown(POINT pt)
	{
		int downi = -1;
		for (int i = m_childCtrl.size() - 1; i >= 0; i--)
		{
			//当控件在这个范围内且控件的可见样式不是子页面(这里是因为只有当他为子页面的时候才不会显示)
			if ((m_childCtrl.at(i)->IsInRect(pt)) && (m_childCtrl.at(i)->GetControlType() != DCS_CHILD))
			{
				m_panelMan->mLastDownControl = m_childCtrl.at(i);	//记录当前按下的为最后一次按下的控件
				m_pActiveCtrl = m_childCtrl.at(i);	//设置当前的类型。
				downi = i;
				if(m_childCtrl.at(i)->m_ctrType == DC_CTRL_BUTTON)
				{
					//按钮
					CDrawButton* CDwBtn = dynamic_cast<CDrawButton*>(m_childCtrl.at(i));
					CDwBtn->OnLButtonDown(false);
				}
				else if(m_childCtrl.at(i)->m_ctrType==DC_CTRL_PAGE)
				{
					//页面
					CDrawPage* CDwPg = dynamic_cast<CDrawPage*>(m_childCtrl.at(i));
					CDwPg->OnLButtonDown(pt);
				}
				else if(m_childCtrl.at(i)->m_ctrType==DC_CTRL_CHECKBUTTON)
				{
					//check按钮
					CDrawCheckButton* CDwCkBtn =  dynamic_cast<CDrawCheckButton*>(m_childCtrl.at(i));
					CDwCkBtn->OnLButtonDown(false);
				}
				else if(m_childCtrl.at(i)->m_ctrType==DC_CTRL_DIRECTIONBUTTON)
				{
					//Direction按钮
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
				//按钮
				CDrawButton* CDwBtn = dynamic_cast<CDrawButton*>(m_panelMan->mLastDownControl);
				CDwBtn->OnLButtonUp(true);
				m_panelMan->mLastDownControl=NULL;
				return;
			}
			else if(m_panelMan->mLastDownControl->m_ctrType == DC_CTRL_CHECKBUTTON)
			{
				//按钮
				CDrawCheckButton* CDwBtn = dynamic_cast<CDrawCheckButton*>(m_panelMan->mLastDownControl);
				CDwBtn->OnLButtonUp(true);
				m_panelMan->mLastDownControl=NULL;
				return;
			}
		}

		int i = m_childCtrl.size()-1;
		for (; i >=0 ; i--)
		{
			//当控件在这个范围内且控件的可见样式不是子页面(这里是因为只有当他为子页面的时候才不会显示)
			if ((m_childCtrl.at(i)->IsInRect(pt)) && (m_childCtrl.at(i)->GetControlType() != DCS_CHILD))
			{
				if(m_childCtrl.at(i)->m_ctrType!=DC_CTRL_DIRECTIONBUTTON)
				{
					m_pActiveCtrl = m_childCtrl.at(i);	//设置当前的类型。
				}
				if(m_childCtrl.at(i)->m_ctrType == DC_CTRL_BUTTON)
				{
					//按钮
					CDrawButton* CDwBtn = dynamic_cast<CDrawButton*>(m_childCtrl.at(i));
					CDwBtn->OnLButtonUp(false);
				}
				else if(m_childCtrl.at(i)->m_ctrType==DC_CTRL_PAGE)
				{
					//页面
					CDrawPage* CDwPg = dynamic_cast<CDrawPage*>(m_childCtrl.at(i));
					CDwPg->OnLButtonUp(pt);
				}
				else if(m_childCtrl.at(i)->m_ctrType==DC_CTRL_CHECKBUTTON)
				{
					Avtronsys::Log::info("aasd1");
					//check按钮
					CDrawCheckButton* CDwCkBtn = dynamic_cast<CDrawCheckButton*>(m_childCtrl.at(i));
					CDwCkBtn->OnLButtonUp(false);
				}
				else if(m_childCtrl.at(i)->m_ctrType==DC_CTRL_DIRECTIONBUTTON)
				{
					//Direction按钮
					CDrawDireButton* CDwDrBtn = dynamic_cast<CDrawDireButton*>(m_childCtrl.at(i));
					CDwDrBtn->OnLButtonUp(false);
				}
				break;
			}
		}
	}

	//更新某个区域
	void CDrawPage::InvalidateRect(RECT rect)
	{

	}

	//设置/获得前一个页面
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

	//将某个子控件移到最上层
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
				m_drawindex.erase(it);  //返回的是一个下一个元素的位置,注意迭代器失效问题
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
				m_childCtrl.erase(it);  //返回的是一个下一个元素的位置,注意迭代器失效问题
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

	//设置/获取动画效果
	ANIMATION_MODEL& CDrawPage::Animation()
	{

	}
}
