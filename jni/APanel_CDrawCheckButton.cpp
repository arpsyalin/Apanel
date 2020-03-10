/******************************************
**		文件：APanel_CDrawCheckButton.cpp
**		作者：刘亚林
**		时间：12年10月24日
**		最后修改：无
*******************************************/
#ifndef _APANEL_CDRAWCHECKBUTTON_H
#define _APANEL_CDRAWCHECKBUTTON_H
#include "APanel_CDrawCheckButton.h"
#endif

#ifndef _APANEL_CPANELMANAGE_H
#define _APANEL_CPANELMANAGE_H
#include "APanel_CPanelManage.h"
#endif

#include "Avtronsys/Avtronsys_Log.h"

namespace APanel
	{
	CDrawCheckButton::CDrawCheckButton()
	{
		m_bChecked = false; //构造函数默认为非checked
	}

	CDrawCheckButton::~CDrawCheckButton()
	{

	}
	CDrawCheckButton::CDrawCheckButton(const CDrawButton& buttonSrc)
	{
		m_bChecked = false; //构造函数默认为非checked
		m_nCurrState = 0;
		m_nSateCount = buttonSrc.m_nSateCount;
		m_rgBindGroupId = buttonSrc.m_rgBindGroupId;
		m_ctrId = buttonSrc.m_ctrId;
		m_ctrShowType = buttonSrc.m_ctrShowType; //控件样式
		m_rgGroupMask = buttonSrc.m_rgGroupMask;
		m_pParentCtr = buttonSrc.m_pParentCtr;
		//拷贝事件
		for (int i = 0; i < buttonSrc.m_envents.size(); i++) {
			CEventLink pEventLink = buttonSrc.m_envents.at(i);
			this->m_envents.push_back(pEventLink);
		}
	}


	//序列化
	bool CDrawCheckButton::Serialize(bool ismany)
	{
		int num = 0;
		if(!ismany)
		{
			 num = GroupID.size();
			for(int i = 0; i < num; i ++)
			{
				m_rgBindGroupId.push_back(GroupID.at(i));
				m_rgGroupMask.push_back(MaskID.at(i));
			}

			num = m_rgBindGroupId.size();
			//处理分组
			for(int i = 0;i <num; i++)
			{
				int bindGroupId = m_rgBindGroupId.at(i);
				int groupMask  = m_rgGroupMask.at(i);
				bool bflag =  m_panelMan->m_groups.BindCtrlToGroup(bindGroupId, groupMask,(CDrawControl*)this);
				if (false == bflag)
				{
					return false;	//返回失败
				}
			}
		}
		num = m_StateArray.size();
		//循环加载各个状态的图片
		for(int i=0;i<num;i++)
		{
			glDeleteTextures(1, &m_StateArray[i].texID);
			Avtronsys::TexTureHandler lTexTureHandler(m_StateArray[i].imgPath.c_str());
			lTexTureHandler.load();
			m_StateArray[i].texID=lTexTureHandler.getTextureID();
		}
		//选择当前状态的图片加载到绘制
		ProjectDrawInit(m_StateArray[m_nCurrState].texID);
		return true;
	}
	void CDrawCheckButton::soundplay()
	{
		m_panelMan->playSound(0);
	}

	//按钮的事件处理
	void CDrawCheckButton::OnLButtonDown(bool istrue)
	{
		soundplay();

		int i;
		//如果pt在按钮的区域内
		UINT DataLen=0;
		int nID;

		for (i = 0; i < m_rgBindGroupId.size(); i++)
		{

			int bindGroupId = m_rgBindGroupId.at(i);
			int GroupMask = m_rgGroupMask.at(i);
			if (bindGroupId != -1)
			{
				m_panelMan->DoGroupEvent2(bindGroupId, GroupMask);
			}
		}

		//停止发送数据
		m_panelMan->EndSend();
		//轮训事件
		for (i = 0; i < m_envents.size(); i++)
		{

			if ((m_envents.at(i).GetEventCase() == LBUTTON_DOWN)
					|| (m_envents.at(i).GetEventCase() == PRESS_DOWN))
			{
				//判断事件类型
				switch (m_envents.at(i).GetEventType())
				{
				case PAGE_JUMP_EVENT:
				{
					nID = atoi((char*)(m_envents.at(i).GetEventData(DataLen)));
					m_panelMan->PageJump(nID, ANI_NULL);
					break;
				}
				case ITEM_HIDE_EVENT:
				{

					nID = atoi((char*)(m_envents.at(i).GetEventData(DataLen)));
					m_panelMan->HideItem(nID);
					break;
				}
				case JOINNUM_SEND_EVENT:
				{
					//发送RF_ID
					LAN_JOINNUM_FRAME var_SendFrame;
					var_SendFrame.bFrameHead = 0xAA;
					var_SendFrame.joinNum.bJoinNum[1] = (unsigned char)(atoi((char*)m_envents.at(i).GetEventData(DataLen))&NUM );
					var_SendFrame.joinNum.bJoinNum[0] = (unsigned char)((atoi((char*)m_envents.at(i).GetEventData(DataLen))>>8)&NUM );
					Avtronsys::Log::info("check1111 down 1:%d,2:%d",var_SendFrame.joinNum.bJoinNum[0],var_SendFrame.joinNum.bJoinNum[1]);
					var_SendFrame.bSingnalType = 1;
					var_SendFrame.bSingnalLen = 1;
					//按下事件
					var_SendFrame.bDownEvent = '1';
					m_panelMan->SendData(var_SendFrame);
					break;
				}

				case DATA_SEND_EVENT:
				{
					break;
				}
				default:
				{
					break;
				}
				}
			}
		}


		if (m_rgBindGroupId.size() <= 0)
		{
			SetChecked(!IsChecked());
		}
	}

	void CDrawCheckButton::OnLButtonUp(bool istrue)
	{
		UINT DataLen = 0;
		int nID;
		m_panelMan->EndSend();
		//如果pt在按钮的区域内
		//轮训事件
		for (int i = 0; i < m_envents.size(); i++)
		{
			if ((m_envents.at(i).GetEventCase() == LBUTTON_UP)|| (m_envents.at(i).GetEventCase() == PRESS_UP))
			{
				//判断事件类型
				switch (m_envents.at(i).GetEventType())
				{
				case PAGE_JUMP_EVENT:
					//nID = atoi((char*)(m_envents.at(i).GetEventData(DataLen)));
					//m_panelMan->PageJump(nID, ANI_NULL);
					break;
				case ITEM_HIDE_EVENT:
					//nID = atoi((char*)(m_envents.at(i).GetEventData(DataLen)));
					//Avtronsys::Log::debug("come DC_CTRL_CHECKBUTTON!!%d",atoi((char*)(m_envents.at(i).GetEventData(DataLen))));
					//m_panelMan->HideItem(nID);
					break;
				case JOINNUM_SEND_EVENT:
					//发送JionNum值
					LAN_JOINNUM_FRAME var_SendFrame;
					var_SendFrame.bFrameHead = 0xAA;
					var_SendFrame.joinNum.bJoinNum[1] = (unsigned char)(atoi((char*)m_envents.at(i).GetEventData(DataLen))&NUM );
					var_SendFrame.joinNum.bJoinNum[0] = (unsigned char)((atoi((char*)m_envents.at(i).GetEventData(DataLen))>>8)&NUM );
					Avtronsys::Log::info("id:%s",(char*)m_envents.at(i).GetEventData(DataLen));
					Avtronsys::Log::info("check up 2222 1:%d,2:%d",var_SendFrame.joinNum.bJoinNum[0],var_SendFrame.joinNum.bJoinNum[1]);
					var_SendFrame.bSingnalType = 1;
					var_SendFrame.bSingnalLen = 1;
					//弹起事件
					var_SendFrame.bDownEvent = '0';
					m_panelMan->SendData(var_SendFrame);
					break;

				case DATA_SEND_EVENT:
					break;

				default:
					break;
				}
			}
		}

	}

	//设置是否为check
	void CDrawCheckButton::SetChecked(bool bChecked)
	{
		int nID;
		UINT DataLen;

		//如果状态发生了变化, 当前页面，事件处理；非当前页面，不处理显示部分，但是数据需要修改
		if ((m_bChecked != bChecked)&& (m_panelMan->IsCtrlInCurrentScreen(this->m_ctrId)))
		{
			if (bChecked)
			{
				PlayStateTo(m_nSateCount - 1);
				//轮训事件
				for (int i = 0; i < m_envents.size(); i++)
				{
					if (m_envents.at(i).GetEventCase() == PRESS_DOWN)
					{
						//判断事件类型
						switch (m_envents.at(i).GetEventType())
						{
						case PAGE_JUMP_EVENT:
						{
							nID =  atoi((char*)(m_envents.at(i).GetEventData(DataLen)));
							m_panelMan->PageJump(nID, ANI_NULL);
						}
						break;

						case ITEM_HIDE_EVENT:
						{
							nID =  atoi((char*)(m_envents.at(i).GetEventData(DataLen)));
							m_panelMan->HideItem(nID);
						}
						break;

						case JOINNUM_SEND_EVENT:
						{
							//发送RF_ID
							LAN_JOINNUM_FRAME var_SendFrame;
							var_SendFrame.bFrameHead = 0xAA;
							var_SendFrame.joinNum.bJoinNum[1] = (unsigned char)(atoi((char*)m_envents.at(i).GetEventData(DataLen))&NUM );
							var_SendFrame.joinNum.bJoinNum[0] = (unsigned char)((atoi((char*)m_envents.at(i).GetEventData(DataLen))>>8)&NUM );
							Avtronsys::Log::info("id:%s",(char*)m_envents.at(i).GetEventData(DataLen));
							Avtronsys::Log::info("check down 3333 1:%d,2:%d",var_SendFrame.joinNum.bJoinNum[0],var_SendFrame.joinNum.bJoinNum[1]);
							var_SendFrame.bSingnalType = 1;
							var_SendFrame.bSingnalLen = 1;
							//按下事件
							var_SendFrame.bDownEvent = '1';
							m_panelMan->SendData(var_SendFrame);
							//m_JoinNum = m_envents.at(i).GetEventData(DataLen);
						}
						break;
						case DATA_SEND_EVENT:
						break;

						default:
						break;
						}
					}
				}
			}
			else
			{
				//不在当前屏
				PlayStateTo(0);
				for (int i = 0; i < m_envents.size(); i++)
				{
					if (m_envents.at(i).GetEventCase() != PRESS_UP)
						continue;
					//判断事件类型
					switch (m_envents.at(i).GetEventType())
					{
					case PAGE_JUMP_EVENT:
						nID =  atoi((char*)(m_envents.at(i).GetEventData(DataLen)));
						m_panelMan->PageJump(nID, ANI_NULL);
						break;

					case ITEM_HIDE_EVENT:
						nID =  atoi((char*)(m_envents.at(i).GetEventData(DataLen)));
						m_panelMan->HideItem(nID);
						break;

					case JOINNUM_SEND_EVENT:
					{
						//发送RF_ID
						LAN_JOINNUM_FRAME var_SendFrame;
						var_SendFrame.bFrameHead = 0xAA;
						var_SendFrame.joinNum.bJoinNum[1] = (unsigned char)(atoi((char*)m_envents.at(i).GetEventData(DataLen))&NUM );
						var_SendFrame.joinNum.bJoinNum[0] = (unsigned char)((atoi((char*)m_envents.at(i).GetEventData(DataLen))>>8)&NUM );
						Avtronsys::Log::info("id:%s",(char*)m_envents.at(i).GetEventData(DataLen));
						Avtronsys::Log::info("check  4444 up 1:%d,2:%d",var_SendFrame.joinNum.bJoinNum[0],var_SendFrame.joinNum.bJoinNum[1]);
						var_SendFrame.bSingnalType = 1;
						var_SendFrame.bSingnalLen = 1;
						//按下事件
						var_SendFrame.bDownEvent = '0';
						m_panelMan->SendData(var_SendFrame);
						 //m_JoinNum = m_envents.at(i).GetEventData(DataLen);
					}
						break;

					case DATA_SEND_EVENT:
						break;

					default:
						break;
					}
				}
			}
		}

		//如果状态发生了变化, 当前页面，事件处理；非当前页面，不处理显示部分，但是数据需要修改
		if ((m_bChecked != bChecked)
				&& (!m_panelMan->IsCtrlInCurrentScreen(this->m_ctrId)))
		{
			if (bChecked)
			{
				PlayStateTo(m_nSateCount - 1);
				//轮训事件
				for (int i = 0; i < m_envents.size(); i++)
				{
					if (m_envents.at(i).GetEventCase() != PRESS_DOWN)
						continue;
					//判断事件类型
					switch (m_envents.at(i).GetEventType())
					{
					case PAGE_JUMP_EVENT:
						nID = atoi((char*)(m_envents.at(i).GetEventData(DataLen)));
						m_panelMan->PageJump(nID, ANI_NULL);
						break;

					case ITEM_HIDE_EVENT:
						nID = atoi((char*)(m_envents.at(i).GetEventData(DataLen)));
						m_panelMan->HideItem(nID);
						break;

					case JOINNUM_SEND_EVENT:

						break;

					case DATA_SEND_EVENT:
						break;

					default:
						break;
					}
				}
			}
			else
			{
				PlayStateTo(0);
				for (int i = 0; i < m_envents.size(); i++)
				{

					if (m_envents.at(i).GetEventCase() != PRESS_UP)
						continue;
					//判断事件类型
					switch (m_envents.at(i).GetEventType())
					{
					case PAGE_JUMP_EVENT:
						nID = atoi((char*)(m_envents.at(i).GetEventData(DataLen)));
						m_panelMan->PageJump(nID, ANI_NULL);
						break;

					case ITEM_HIDE_EVENT:
						nID = atoi((char*)(m_envents.at(i).GetEventData(DataLen)));
						m_panelMan->HideItem(nID);
						break;

					case JOINNUM_SEND_EVENT:
						break;

					case DATA_SEND_EVENT:
						break;

					default:
						break;
					}
				}
			}
		}


		m_bChecked = bChecked;
		if (bChecked)
		{
			m_nCurrState = m_nSateCount - 1;
		}
		else
		{
			m_nCurrState = 0;
		}

	}

	//设置checkbutton的初始状态
	//编译时用，注意:需用在InitButtonState之后
	void CDrawCheckButton::SetInitialState(bool bChecked)
	{
		m_bChecked = bChecked;
		if (bChecked) {
			m_nCurrState = m_nSateCount - 1;
		}
		else
		{
			m_nCurrState = 0;
		}
	}

	//该按钮是否为check
	bool CDrawCheckButton::IsChecked()
	{
		return m_bChecked;
	}

	}
