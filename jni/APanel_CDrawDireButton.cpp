/******************************************
**		�ļ���APanel_CDrawDireButton.cpp
**		���ߣ�������
**		ʱ�䣺12��10��24��
**		����޸ģ���
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
		//Ĭ��ʱ���ӳ�40ms
		m_nTimeDelay = 40;
	}

	CDrawDireButton::~CDrawDireButton()
	{

	}

/*
	bool CDrawDireButton::Serialize(bool ismany)
	{
		//ѭ�����ظ���״̬��ͼƬ
		for(int i=0;i<m_StateArray.size();i++)
		{
			Avtronsys::TexTureHandler lTexTureHandler(m_StateArray[i].imgPath.c_str());
			lTexTureHandler.load();
			m_StateArray[i].texID=lTexTureHandler.getTextureID();
		}
		//ѡ��ǰ״̬��ͼƬ���ص�����
		ProjectDrawInit(m_StateArray[m_nCurrState].texID);
		return true;
	}
*/
	void CDrawDireButton::soundplay()
	{
		m_panelMan->playSound(0);
	}


	//�ð�ť��һ��ʱ��ָ�
	void CDrawDireButton::OnLButtonDown(bool istrue)
	{
		//�����̲߳�������
		soundplay();

		PlayStateTo(m_nSateCount - 1);
		//�����¼�
		//���pt�ڰ�ť��������
		for (int i = 0; i < m_rgBindGroupId.size(); i++) {
			int bindGroupId = m_rgBindGroupId.at(i);
			int GroupMask = m_rgGroupMask.at(i);
			if (bindGroupId != -1) {
				m_panelMan->DoGroupEvent2(bindGroupId, GroupMask);
			}
		}
		int nID;
		UINT DataLen;
		//��ѵ�¼�
		for (int i = 0; i < m_envents.size(); i++)
		{
			if ((m_envents.at(i).GetEventCase() == LBUTTON_DOWN)
					|| (m_envents.at(i).GetEventCase() == PRESS_DOWN))
			{
				//�ж��¼�����
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
					//����RF_ID
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
					//�����¼�
					//var_SendFrame.bDownEvent = '1';
					//m_panelMan->SendData(var_SendFrame);


					//����JionNumֵ
					LAN_JOINNUM_FRAME var_SendFrame;
					var_SendFrame.bFrameHead = 0xAA;
					var_SendFrame.joinNum.bJoinNum[1] = (unsigned char)
							(atoi((char*)m_envents.at(i).GetEventData(DataLen))&NUM );
					var_SendFrame.joinNum.bJoinNum[0] = (unsigned char)
							((atoi((char*)m_envents.at(i).GetEventData(DataLen))>>8)&NUM );
					var_SendFrame.bSingnalType = 1;
					var_SendFrame.bSingnalLen = 1;
					//�����¼�
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
				//�ж��¼�����
				switch (m_envents.at(i).GetEventType())
				{
				case PAGE_JUMP_EVENT:
					break;
				case ITEM_HIDE_EVENT:
					break;
				case JOINNUM_SEND_EVENT:
				{
					//����JionNumֵ
					LAN_JOINNUM_FRAME var_SendFrame;
					var_SendFrame.bFrameHead = 0xAA;
					var_SendFrame.joinNum.bJoinNum[1] = (unsigned char)(atoi((char*)m_envents.at(i).GetEventData(DataLen))&NUM );
					var_SendFrame.joinNum.bJoinNum[0] = (unsigned char)((atoi((char*)m_envents.at(i).GetEventData(DataLen))>>8)&NUM );
					Avtronsys::Log::info("id:%s",(char*)m_envents.at(i).GetEventData(DataLen));
					Avtronsys::Log::info("dir up 1:%d,2:%d",var_SendFrame.joinNum.bJoinNum[0],var_SendFrame.joinNum.bJoinNum[1]);
					var_SendFrame.bSingnalType = 1;
					var_SendFrame.bSingnalLen = 1;
					//�����¼�
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
		//��ѵ�¼�
		for (int i = 0; i < m_envents.size(); i++)
		{
			if (m_envents.at(i).GetEventCase() != PRESS_UP)
			{
				continue;
			}

			//�ж��¼�����
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
				//����RF_ID
				LAN_JOINNUM_FRAME var_SendFrame;
				var_SendFrame.bFrameHead = (unsigned char) 0xAA;
				var_SendFrame.joinNum.bJoinNum[1] = (unsigned char)(atoi((char*)m_envents.at(i).GetEventData(DataLen))&NUM );
				var_SendFrame.joinNum.bJoinNum[0] = (unsigned char)((atoi((char*)m_envents.at(i).GetEventData(DataLen))>>8)&NUM );
				Avtronsys::Log::info("id:%s",(char*)m_envents.at(i).GetEventData(DataLen));
				Avtronsys::Log::info("dir down 1:%d,2:%d",var_SendFrame.joinNum.bJoinNum[0],var_SendFrame.joinNum.bJoinNum[1]);var_SendFrame.bSingnalType = 1;
				var_SendFrame.bSingnalLen = 1;
				//�����¼�
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

