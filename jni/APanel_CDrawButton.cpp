/******************************************
**		�ļ���APanel_CDrawButton.cpp
**		���ߣ�������
**		ʱ�䣺12��10��24��
**		����޸ģ���
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
	//�Ի溯��
	bool CDrawButton::DrawSelf()
	{
		//����
		mDrawTexture.Drawself();
	}

	//���л�
	bool CDrawButton::Serialize(bool ismany)
	{
		//ѭ�����ظ���״̬��ͼƬ
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
		//ѡ��ǰ״̬��ͼƬ���ص�����
		ProjectDrawInit(m_StateArray[m_nCurrState].texID);
		return true;
	}

	//��ʼ����ť״̬
	//pState:��ʾ״̬��ͼƬ��Ϣ����+
	//nCount:״̬������ҪС��16
	//�ú����Ӱ�ť��״̬0��ʼ��ʼ��������δ��ʼ����״̬���
	void CDrawButton::InitButtonState()
	{

	}

	//��Ӱ�ť��һ��״̬
	//���óɹ����� ��״̬�����
	//���򷵻�-1
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

	/*���滹�м��麯���ڷ�����֤���к��ټ���*/
	//�¼���Ӧ����
	//�������
	//pt �������Ըÿؼ���λ����Ϊ�ο�
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
		//����״̬
		PlayStateTo(m_nSateCount - 1);

		//ֹͣ��������
		m_panelMan->EndSend();


		//��ѯ�¼�
		for(int i = 0; i < m_envents.size(); i++)
		{
			if((m_envents.at(i).GetEventCase()!= LBUTTON_DOWN) && (m_envents.at(i).GetEventCase() != PRESS_DOWN))
			{
				continue;
			}


			//�ж��¼�����
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
				//����JionNumֵ
				LAN_JOINNUM_FRAME var_SendFrame;
				var_SendFrame.bFrameHead = 0xAA;
				var_SendFrame.joinNum.bJoinNum[1] = (unsigned char)(atoi((char*)m_envents.at(i).GetEventData(DataLen))&NUM );
				var_SendFrame.joinNum.bJoinNum[0] = (unsigned char)((atoi((char*)m_envents.at(i).GetEventData(DataLen))>>8)&NUM );
				var_SendFrame.bSingnalType = 1;
				var_SendFrame.bSingnalLen = 1;
				//�����¼�
				var_SendFrame.bDownEvent = '1';
				//��������
				m_panelMan->SendData(var_SendFrame);
				break;}
			case DATA_SEND_EVENT:
			break;
			default:
				break;
			}
		}
	}
	//�������
	void CDrawButton::OnLButtonUp(bool istrue)
	{
		UINT DataLen = 0;
		//��ѯ�¼�
		if(m_nSateCount>2)
		{
			for(int n=m_nSateCount-1;n>=0;n--)
			{
				PlayStateTo(n);
				m_panelMan->Work();
				m_panelMan->RDraw2();
			}
		}

		//����״̬
		PlayStateTo(0);
		if(!istrue)
		{
			m_panelMan->EndSend();

			//��ѯ�¼�
			for(int i = 0; i < m_envents.size(); i++)
			{
				if((m_envents.at(i).GetEventCase() != LBUTTON_UP) && (m_envents.at(i).GetEventCase() != PRESS_UP))
				{
					continue;
				}

				//�ж��¼�����
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
					//����JionNumֵ
					LAN_JOINNUM_FRAME var_SendFrame;
					var_SendFrame.bFrameHead = 0xAA;
					var_SendFrame.joinNum.bJoinNum[1] = (unsigned char)(atoi((char*)m_envents.at(i).GetEventData(DataLen))&NUM );
					var_SendFrame.joinNum.bJoinNum[0] = (unsigned char)((atoi((char*)m_envents.at(i).GetEventData(DataLen))>>8)&NUM );
					Avtronsys::Log::info("btn up 1:%d,2:%d",var_SendFrame.joinNum.bJoinNum[0],var_SendFrame.joinNum.bJoinNum[1]);
					var_SendFrame.bSingnalType = 1;
					var_SendFrame.bSingnalLen = 1;
					//�����¼�
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


	//���ð�ť״̬   bRepaint = TRUE
	//				 ����ť�Ի���ʾ��pDC�ϡ�
	//				 bRepaint = FALSE
	//				 ���ı䰴ť״̬�����Ի�
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

	//�ӵ�ǰ״̬���ɵ�Ŀ��״̬
	void CDrawButton::PlayStateTo(UINT nDestState)
	{
		if(nDestState==m_nCurrState || nDestState > m_nSateCount)
				return ;
			SetCurrentState(nDestState,true); //��Ŀ��״̬����Ϊ��ǰ״̬���ػ�
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
