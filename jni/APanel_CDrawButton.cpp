/******************************************
**		文件：APanel_CDrawButton.cpp
**		作者：刘亚林
**		时间：12年10月24日
**		最后修改：无
*******************************************/
#ifndef _APANEL_CDRAWBUTTON_H
#define _APANEL_CDRAWBUTTON_H
#include "APanel_CDrawButton.h"
#endif

#ifndef _APANEL_CPANELMANAGE_H
#define _APANEL_CPANELMANAGE_H
#include "APanel_CPanelManage.h"
#endif

#include <unistd.h>
#include "Avtronsys/Avtronsys_Log.h"

namespace APanel
{

	CDrawButton::CDrawButton()
	{

	}

	CDrawButton::~CDrawButton()
	{

	}
	//自绘函数
	bool CDrawButton::DrawSelf()
	{
		//绘制
		mDrawTexture.Drawself();
	}

	//序列化
	bool CDrawButton::Serialize(bool ismany)
	{
		//循环加载各个状态的图片
		for(int i=0;i<m_StateArray.size();i++)
		{
			Avtronsys::Log::info("aa,%d",ismany);
			Avtronsys::Log::info("a11a,%s",m_StateArray[i].imgPath.c_str());
			glDeleteTextures(1, &m_StateArray[i].texID);
			Avtronsys::Log::info("1111");
			Avtronsys::TexTureHandler lTexTureHandler(m_StateArray[i].imgPath.c_str());
			lTexTureHandler.load();
			Avtronsys::Log::info("333333");
			m_StateArray[i].texID=lTexTureHandler.getTextureID();
		}
		//选择当前状态的图片加载到绘制
		ProjectDrawInit(m_StateArray[m_nCurrState].texID);
		return true;
	}

	//初始化按钮状态
	//pState:表示状态的图片信息数组+
	//nCount:状态数量，要小于16
	//该函数从按钮的状态0开始初始化，并将未初始化的状态清空
	void CDrawButton::InitButtonState()
	{

	}

	//添加按钮的一个状态
	//调用成功返回 该状态的序号
	//否则返回-1
	int CDrawButton::AppendButtonState(STATE pSTATE)
	{
		if(m_nSateCount>DC_MAX_STATE)
			return -1;
		m_StateArray.push_back(pSTATE);
		m_nSateCount++;
		return  (m_nSateCount-1);
	}

	void CDrawButton::soundplay()
	{
		m_panelMan->playSound(0);
	}

	/*后面还有几组函数在方案验证可行后再继续*/
	//事件响应函数
	//左键按下
	//pt 的坐标以该控件的位置作为参考
	void CDrawButton::OnLButtonDown(bool istrue)
	{
		soundplay();

		UINT DataLen = 0;

		if(m_nSateCount>2)
		{
			for(int n=0;n<m_nSateCount;n++)
			{
				PlayStateTo(n);
				m_panelMan->Work();
				m_panelMan->RDraw2();
			}
		}
		//更新状态
		PlayStateTo(m_nSateCount - 1);

		//停止发送数据
		m_panelMan->EndSend();


		//轮询事件
		for(int i = 0; i < m_envents.size(); i++)
		{
			if((m_envents.at(i).GetEventCase()!= LBUTTON_DOWN) && (m_envents.at(i).GetEventCase() != PRESS_DOWN))
			{
				continue;
			}


			//判断事件类型
			switch(m_envents.at(i).GetEventType())
			{
			case PAGE_JUMP_EVENT:
			{
				int JumpID = atoi((char*)(m_envents.at(i).GetEventData(DataLen)));
				m_panelMan->PageJump(JumpID,ANI_NULL);
			break;
			}
			case ITEM_HIDE_EVENT:{
				int HideID = atoi((char*)(m_envents.at(i).GetEventData(DataLen)));
				m_panelMan->HideItem(HideID);
				break;}
			case JOINNUM_SEND_EVENT:
			{
				//发送JionNum值
				LAN_JOINNUM_FRAME var_SendFrame;
				var_SendFrame.bFrameHead = 0xAA;
				var_SendFrame.joinNum.bJoinNum[1] = (unsigned char)(atoi((char*)m_envents.at(i).GetEventData(DataLen))&NUM );
				var_SendFrame.joinNum.bJoinNum[0] = (unsigned char)((atoi((char*)m_envents.at(i).GetEventData(DataLen))>>8)&NUM );
				var_SendFrame.bSingnalType = 1;
				var_SendFrame.bSingnalLen = 1;
				//按下事件
				var_SendFrame.bDownEvent = '1';
				//发送数据
				m_panelMan->SendData(var_SendFrame);
				break;}
			case DATA_SEND_EVENT:
			break;
			default:
				break;
			}
		}
	}
	//左键弹起
	void CDrawButton::OnLButtonUp(bool istrue)
	{
		UINT DataLen = 0;
		//轮询事件
		if(m_nSateCount>2)
		{
			for(int n=m_nSateCount-1;n>=0;n--)
			{
				PlayStateTo(n);
				m_panelMan->Work();
				m_panelMan->RDraw2();
			}
		}

		//更新状态
		PlayStateTo(0);
		if(!istrue)
		{
			m_panelMan->EndSend();

			//轮询事件
			for(int i = 0; i < m_envents.size(); i++)
			{
				if((m_envents.at(i).GetEventCase() != LBUTTON_UP) && (m_envents.at(i).GetEventCase() != PRESS_UP))
				{
					continue;
				}

				//判断事件类型
				switch(m_envents.at(i).GetEventType())
				{
				case PAGE_JUMP_EVENT:
				{

					int JumpID =atoi((char*)(m_envents.at(i).GetEventData(DataLen)));
					m_panelMan->PageJump(JumpID,ANI_NULL);
				}break;
				case ITEM_HIDE_EVENT:
				{
					int HideID =atoi((char*)(m_envents.at(i).GetEventData(DataLen)));
					m_panelMan->HideItem(HideID);
				}
				break;
				case JOINNUM_SEND_EVENT:
				{
					//发送JionNum值
					LAN_JOINNUM_FRAME var_SendFrame;
					var_SendFrame.bFrameHead = 0xAA;
					var_SendFrame.joinNum.bJoinNum[1] = (unsigned char)(atoi((char*)m_envents.at(i).GetEventData(DataLen))&NUM );
					var_SendFrame.joinNum.bJoinNum[0] = (unsigned char)((atoi((char*)m_envents.at(i).GetEventData(DataLen))>>8)&NUM );
					Avtronsys::Log::info("btn up 1:%d,2:%d",var_SendFrame.joinNum.bJoinNum[0],var_SendFrame.joinNum.bJoinNum[1]);
					var_SendFrame.bSingnalType = 1;
					var_SendFrame.bSingnalLen = 1;
					//弹起事件
					var_SendFrame.bDownEvent = '0';
					m_panelMan->SendData(var_SendFrame);
				}
				break;
				case DATA_SEND_EVENT:
				{

				}
				break;

				}

			}
		}
	}


	//设置按钮状态   bRepaint = TRUE
	//				 将按钮自绘显示到pDC上。
	//				 bRepaint = FALSE
	//				 仅改变按钮状态但不自绘
	void CDrawButton::SetCurrentState(UINT nState, bool bRepaint)
	{
		//if(bRepaint)
		//{
			//m_nCurrState  = nState;
			//setTexture(m_StateArray[m_nCurrState].texID);
			//DrawSelf();
		//}
		//else
		//{
			m_nCurrState = nState;
			setTexture(m_StateArray[m_nCurrState].texID);
		//}
	}

	//从当前状态过渡到目标状态
	void CDrawButton::PlayStateTo(UINT nDestState)
	{
		if(nDestState==m_nCurrState || nDestState > m_nSateCount)
				return ;
			SetCurrentState(nDestState,true); //将目标状态设置为当前状态并重绘
	}
	
	void CDrawButton::SetAnimation(ANIMATION_MODEL mode)
	{
		m_aniMode = mode;
	}
	ANIMATION_MODEL CDrawButton::GetAnimation(void)
	{
		return m_aniMode;
	}
}
