/******************************************
**		文件：APanel_CDrawDireButton.cpp
**		作者：刘亚林
**		时间：12年10月24日
**		最后修改：无
*******************************************/
#ifndef _APANEL_CDRAWDIREBUTTON_H
#define _APANEL_CDRAWDIREBUTTON_H
#include "APanel_CDrawDireButton.h"
#endif

#ifndef _APANEL_CPANELMANAGE_H
#define _APANEL_CPANELMANAGE_H
#include "APanel_CPanelManage.h"
#endif

#include <unistd.h>

#include "Avtronsys/Avtronsys_Log.h"
namespace APanel
{
CDrawDireButton::CDrawDireButton() {
		// TODO Auto-generated constructor stub
		//默认时间延迟40ms
		m_nTimeDelay = 40;
	}

	CDrawDireButton::~CDrawDireButton()
	{

	}

/*
	bool CDrawDireButton::Serialize(bool ismany)
	{
		//循环加载各个状态的图片
		for(int i=0;i<m_StateArray.size();i++)
		{
			Avtronsys::TexTureHandler lTexTureHandler(m_StateArray[i].imgPath.c_str());
			lTexTureHandler.load();
			m_StateArray[i].texID=lTexTureHandler.getTextureID();
		}
		//选择当前状态的图片加载到绘制
		ProjectDrawInit(m_StateArray[m_nCurrState].texID);
		return true;
	}
*/
	void CDrawDireButton::soundplay()
	{
		m_panelMan->playSound(0);
	}


	//让按钮过一段时间恢复
	void CDrawDireButton::OnLButtonDown(bool istrue)
	{
		//开个线程播放声音
		soundplay();

		PlayStateTo(m_nSateCount - 1);
		//处理事件
		//如果pt在按钮的区域内
		for (int i = 0; i < m_rgBindGroupId.size(); i++) {
			int bindGroupId = m_rgBindGroupId.at(i);
			int GroupMask = m_rgGroupMask.at(i);
			if (bindGroupId != -1) {
				m_panelMan->DoGroupEvent2(bindGroupId, GroupMask);
			}
		}
		int nID;
		UINT DataLen;
		//轮训事件
		for (int i = 0; i < m_envents.size(); i++)
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
				}
					break;
				case ITEM_HIDE_EVENT:
				{
					nID = atoi((char*)(m_envents.at(i).GetEventData(DataLen)));
					m_panelMan->HideItem(nID);
				}
					break;

				case JOINNUM_SEND_EVENT:
					//发送RF_ID
					//LAN_JOINNUM_FRAME var_SendFrame;
					//var_SendFrame.bFrameHead = 0xAA;
					//var_SendFrame.joinNum.bJoinNum[1] =
					//		(unsigned char) ((int) m_envents.at(i).GetEventData(
					//				DataLen) & NUM);
					//var_SendFrame.joinNum.bJoinNum[0] =
					//		(unsigned char) (((int) m_envents.at(i).GetEventData(
					//				DataLen) >> 8) & NUM);
					//var_SendFrame.bSingnalType = 1;
					//var_SendFrame.bSingnalLen = 1;
					//按下事件
					//var_SendFrame.bDownEvent = '1';
					//m_panelMan->SendData(var_SendFrame);


					//发送JionNum值
					LAN_JOINNUM_FRAME var_SendFrame;
					var_SendFrame.bFrameHead = 0xAA;
					var_SendFrame.joinNum.bJoinNum[1] = (unsigned char)
							(atoi((char*)m_envents.at(i).GetEventData(DataLen))&NUM );
					var_SendFrame.joinNum.bJoinNum[0] = (unsigned char)
							((atoi((char*)m_envents.at(i).GetEventData(DataLen))>>8)&NUM );
					var_SendFrame.bSingnalType = 1;
					var_SendFrame.bSingnalLen = 1;
					//弹起事件
					var_SendFrame.bDownEvent = '1';
					m_panelMan->SendData(var_SendFrame);
					break;

				case DATA_SEND_EVENT:
					break;

				default:
					break;
				}
				//pthread_t id;
				//int ret;
				//ret=pthread_create(&thread_id,NULL,thread_fun,this);
				//if(ret!=0)
				//{
				//		Avtronsys::Log::error("thread error!!!!!");
				//}
				//pthread_join(id,NULL);
			}
		}
		//*/
			pthread_t pid;
			pthread_t id;
			int ret;
			ret=pthread_create(&pid,NULL,thread_fun,this);
			if(ret!=0)
			{
					Avtronsys::Log::error("thread error!!!!!");
			}
			pthread_join(id,NULL);
	}

	void CDrawDireButton::OnLButtonUp(bool istrue)
	{
		UINT DataLen;
		for (int i = 0; i < m_envents.size(); i++)
		{

			if ((m_envents.at(i).GetEventCase() == LBUTTON_UP)
					|| (m_envents.at(i).GetEventCase() == PRESS_UP))
			{
				//判断事件类型
				switch (m_envents.at(i).GetEventType())
				{
				case PAGE_JUMP_EVENT:
					break;
				case ITEM_HIDE_EVENT:
					break;
				case JOINNUM_SEND_EVENT:
				{
					//发送JionNum值
					LAN_JOINNUM_FRAME var_SendFrame;
					var_SendFrame.bFrameHead = 0xAA;
					var_SendFrame.joinNum.bJoinNum[1] = (unsigned char)(atoi((char*)m_envents.at(i).GetEventData(DataLen))&NUM );
					var_SendFrame.joinNum.bJoinNum[0] = (unsigned char)((atoi((char*)m_envents.at(i).GetEventData(DataLen))>>8)&NUM );
					Avtronsys::Log::info("id:%s",(char*)m_envents.at(i).GetEventData(DataLen));
					Avtronsys::Log::info("dir up 1:%d,2:%d",var_SendFrame.joinNum.bJoinNum[0],var_SendFrame.joinNum.bJoinNum[1]);
					var_SendFrame.bSingnalType = 1;
					var_SendFrame.bSingnalLen = 1;
					//弹起事件
					var_SendFrame.bDownEvent = '0';
					m_panelMan->SendData(var_SendFrame);
//					ID = atoi((char*)(m_envents.at(i).GetEventData(DataLen)));
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

	void CDrawDireButton::Rdraw()
	{
		m_panelMan->Work();
		m_panelMan->RDraw();
	}

	void* CDrawDireButton::thread_fun(void* tdata)
	{
		CDrawDireButton* tempDBTN = NULL;
		tempDBTN = (CDrawDireButton*)tdata;
		usleep(tempDBTN->m_nTimeDelay*1000);
		tempDBTN->TimerProc();
		tempDBTN->Rdraw();
		return (void*)0;
	}

	void CDrawDireButton::TimerProc()
	{
		int nID;
		UINT DataLen;
		//轮训事件
		for (int i = 0; i < m_envents.size(); i++)
		{
			if (m_envents.at(i).GetEventCase() != PRESS_UP)
			{
				continue;
			}

			//判断事件类型
			switch (m_envents.at(i).GetEventType())
			{
			case PAGE_JUMP_EVENT:
			{
				nID = atoi((char*)(m_envents.at(i).GetEventData(DataLen)));
				m_panelMan->PageJump(nID, ANI_NULL);
				//bIsJump = true;
			}
				break;
			case ITEM_HIDE_EVENT:
			{
				nID = atoi((char*)(m_envents.at(i).GetEventData(DataLen)));
				m_panelMan->HideItem(nID);
			}
				break;
			case JOINNUM_SEND_EVENT:
			{
				//发送RF_ID
				LAN_JOINNUM_FRAME var_SendFrame;
				var_SendFrame.bFrameHead = (unsigned char) 0xAA;
				var_SendFrame.joinNum.bJoinNum[1] = (unsigned char)(atoi((char*)m_envents.at(i).GetEventData(DataLen))&NUM );
				var_SendFrame.joinNum.bJoinNum[0] = (unsigned char)((atoi((char*)m_envents.at(i).GetEventData(DataLen))>>8)&NUM );
				Avtronsys::Log::info("id:%s",(char*)m_envents.at(i).GetEventData(DataLen));
				Avtronsys::Log::info("dir down 1:%d,2:%d",var_SendFrame.joinNum.bJoinNum[0],var_SendFrame.joinNum.bJoinNum[1]);var_SendFrame.bSingnalType = 1;
				var_SendFrame.bSingnalLen = 1;
				//按下事件
				var_SendFrame.bDownEvent = '1';
				m_panelMan->SendData(var_SendFrame);
			}
				break;
			case DATA_SEND_EVENT:
				break;
			default:
				break;
			}
		}

		SetCurrentState(0, false);
	}
}

