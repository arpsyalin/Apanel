/******************************************
**		�ļ���APanel_CDrawControl.cpp
**		���ߣ�������
**		ʱ�䣺12��10��24��
**		����޸ģ���
*******************************************/
#ifndef _APANEL_CDRAWCONTROL_H
#define _APANEL_CDRAWCONTROL_H
#include "APanel_CDrawControl.h"
#endif

#include "Avtronsys/Avtronsys_Log.h"

namespace APanel
{
	CDrawControl::CDrawControl()
	{
	}

	CDrawControl::~CDrawControl()
	{

	}

	//���л�
	bool CDrawControl::Serialize(bool isfirst)
	{
		return true;
	}

	int CDrawControl::ProjectImageInit(bool isfirst)
	{
		return 0;
	}


	//���Ƴ�ʼ��
	void CDrawControl::ProjectDrawInit(GLuint pCurTextureid)
	{
		float left ,top,width,height,px,py,sizew,sizeh;
		left=0;
		top=0;

		width = m_rect.RWidth;
		height = m_rect.RHeight;

		if(m_pParentCtr==NULL)
		{
			px=m_rect.LTPoint.x;
			py=(pbDisplayH-(m_rect.LTPoint.y + height));
		}
		else
		{
			px=	m_pParentCtr->m_rect.LTPoint.x+m_rect.LTPoint.x;
			py =  pbDisplayH - (m_pParentCtr->m_rect.LTPoint.y + m_rect.LTPoint.y) - height;
		}

		sizew=width;
		sizeh=height;
		setLocation(px,py);
		setSize(sizew,sizeh);
		setTextureArray(left,top,width,height);
		setTexture(pCurTextureid);
	}

	//���û�������Ĵ�С
	void CDrawControl::setSize(float sizew,float sizeh)
	{
		mDrawTexture.setSize(sizew,sizeh);
	}

	//���û��������λ��
	void CDrawControl::setLocation(float px,float py)
	{
		mDrawTexture.setLocation(px,py);
	}
	//���������ƫ��ֵ
	void CDrawControl::setTextureDVT(float left,float top)
	{
		mDrawTexture.setTextureDVT(left,top);
	}

	//����������
	void CDrawControl::setTextureHAW(float width,float height)
	{
		mDrawTexture.setTextureHAW(width,height);
	}

	//���������ƫ��ֵ�Ϳ��
	void CDrawControl::setTextureArray(float left,float top,float width,float height)
	{
		mDrawTexture.setTextureArray(left,top,width,height);
	}

	//��������ID
	void CDrawControl::setTexture(GLuint pCurTextureid)
	{
		mDrawTexture.setTexture(pCurTextureid);
	}

	//�Ի溯��
	//Ҫ�����м̳��Ը�����࣬������д�ú���
	bool CDrawControl::DrawSelf()
	{
		return true;
	}
	bool CDrawControl::DrawSelf(ANIMATION_MODEL animode )
	{
		return true;
	}

	//���ÿؼ�����
	void CDrawControl::SetRect(RECT rect)
	{

	}
	//��ȡ�ؼ�����
	RECT CDrawControl::GetRect()
	{
		return m_rect;
	}

	//���ÿؼ�ID
	void CDrawControl::SetControlId(int nId)
	{
		m_ctrId = nId;
	}
	//��ȡ�ؼ�ID
	UINT CDrawControl::GetControlId()
	{
		return m_ctrId;
	}

	//�¼���Ӧ����
	//�������
	//pt �������Ըÿؼ���λ����Ϊ�ο�
	void CDrawControl::OnLButtonDown(POINT pt)
	{

	}
	//�������
	void CDrawControl::OnLButtonUp(POINT pt)
	{
	}

	//�¼���Ӧ����
	//�������
	//pt �������Ըÿؼ���λ����Ϊ�ο�
	void CDrawControl::OnLButtonDown(bool istrue)
	{

	}
	//�������
	void CDrawControl::OnLButtonUp(bool istrue)
	{
	}

	//�жϸÿؼ��ڲ���ĳ��������
	bool CDrawControl::IsInRect(POINT pt)
	{
		if(this->m_pParentCtr!=NULL)
		{
			if((this->m_rect.LTPoint.x + this->m_pParentCtr->m_rect.LTPoint.x ) <= pt.x&&
			  ( this->m_rect.LTPoint.x + this->m_pParentCtr->m_rect.LTPoint.x + this->m_rect.RWidth)>pt.x&&
			  ( this->m_rect.LTPoint.y + this->m_pParentCtr->m_rect.LTPoint.y ) <= pt.y &&
			  ( this->m_rect.LTPoint.y + this->m_pParentCtr->m_rect.LTPoint.y + this->m_rect.RHeight)>pt.y
			)
			{
				//Avtronsys::Log::debug("1 IsInRect:false:%f,%f,%f,%f,%f,%f",	\
										((float)this->m_rect.LTPoint.x + (float)this->m_pParentCtr->m_rect.LTPoint.x),	\
										((float)this->m_rect.LTPoint.x + (float)this->m_pParentCtr->m_rect.LTPoint.x + (float)this->m_rect.RWidth), \
										((float)this->m_rect.LTPoint.y + (float)this->m_pParentCtr->m_rect.LTPoint.y),	\
										((float)this->m_rect.LTPoint.y + (float)this->m_pParentCtr->m_rect.LTPoint.y + (float)this->m_rect.RHeight),	\
									    pt.x,pt.y	\
										);

				//Avtronsys::Log::debug("11 IsInRect:false:%f,%f,%f,%f,%f,%f,%f,%f,%f,%f",	\
														(this->m_pParentCtr->m_rect.LTPoint.x),	\
														(this->m_pParentCtr->m_rect.LTPoint.y),	\
														(this->m_pParentCtr->m_rect.RWidth),	\
													    (this->m_pParentCtr->m_rect.RHeight),	\
													    (this->m_rect.RWidth),	\
													    (this->m_rect.RHeight),	\
														(this->m_rect.LTPoint.x),	\
														(this->m_rect.LTPoint.y),	\
													    pt.x,pt.y	\
														);
				return true;
			}
			else
			{
				//Avtronsys::Log::debug("2 IsInRect:false:%f,%f,%f,%f,%f,%f",	\
						((float)this->m_rect.LTPoint.x + (float)this->m_pParentCtr->m_rect.LTPoint.x),	\
						((float)this->m_rect.LTPoint.x + (float)this->m_pParentCtr->m_rect.LTPoint.x + (float)this->m_rect.RWidth),\
						((float)this->m_rect.LTPoint.y + (float)this->m_pParentCtr->m_rect.LTPoint.y),\
						((float)this->m_rect.LTPoint.y + (float)this->m_pParentCtr->m_rect.LTPoint.y + (float)this->m_rect.RHeight),	\
					    pt.x,pt.y \
						);
				//Avtronsys::Log::debug("22 IsInRect:false:%f,%f,%f,%f,%f,%f,%f,%f",\
										(this->m_pParentCtr->m_rect.LTPoint.x),\
										(this->m_pParentCtr->m_rect.LTPoint.y),\
										(m_pParentCtr->m_rect.RWidth),\
									    (m_pParentCtr->m_rect.RHeight),\
										(this->m_rect.LTPoint.x),\
										(this->m_rect.LTPoint.y),\
									    pt.x,pt.y\
										);
				return false;
			}
		}
		else
		{
			if(this->m_rect.LTPoint.x <= pt.x&&
			(this->m_rect.LTPoint.x + this->m_rect.RWidth)>pt.x &&
			this->m_rect.LTPoint.y <= pt.y &&
			(this->m_rect.LTPoint.y + m_rect.RHeight)>pt.y
			)
			{
				//Avtronsys::Log::debug("3 IsInRect:true:%f,%f,%f,%f,%f,%f",	\
						this->m_rect.LTPoint.x,	\
						(this->m_rect.LTPoint.x + this->m_rect.RWidth),	\
						this->m_rect.LTPoint.y,	\
						(this->m_rect.LTPoint.y + m_rect.RHeight),	\
						pt.x,pt.y	\
				);
				return true;
			}
			else
			{
				//Avtronsys::Log::debug("4 IsInRect:false:%f,%f,%f,%f,%f,%f",	\
						this->m_rect.LTPoint.x,	\
						(this->m_rect.LTPoint.x + this->m_rect.RWidth),	\
						this->m_rect.LTPoint.y,	\
						(this->m_rect.LTPoint.y + m_rect.RHeight),	\
						pt.x,pt.y	\
				);
				return false;
			}
		}
	}

	bool CDrawControl::IsInRect(RECT rect)
	{

	}


	//ʹ�ؼ�����
	//�ú�������ĳ�����״̬���Ƿ��ظ��󶨣������Ƿ��ж�
	void CDrawControl::BindToGroup(int nGroupID, int indexInGroup)
	{
		//��Ų��Ϸ�
		if ((nGroupID < 0) || (nGroupID >= DC_MAX_GROUP))
		{
			return;
		}
		//������Ų��Ϸ�
		if ((indexInGroup <0) || (indexInGroup >= DC_MAXCTRL_IN_G))
		{
			return;
		}
		m_rgBindGroupId.push_back(nGroupID);
		m_rgGroupMask.push_back((indexInGroup));
	}
	//���ø��ؼ�
	void CDrawControl::SetParentCtr(CDrawControl* pParent)
	{

	}


	//���ÿؼ�����
	void CDrawControl::SetControlType(DC_CTRL_TYPE dcstyle)
	{
		m_ctrShowType = dcstyle;
	}

	UINT CDrawControl::GetControlType()
	{
		return m_ctrShowType;
	}

	//����¼�
	void CDrawControl::AppendEventLink(DCS_EVENT eventType, LPVOID pData, UINT nDataLen, DCS_EVENT_CASE eventDrv)
	{

	}

	//��ÿؼ�Index
	//û�иÿؼ�����-1
	int CDrawControl::GetCtrlIndex(CDrawControl* pCtrl)
	{
		return -1;
	}
	
	//�����ż����ں�
	int CDrawControl::GetInnerGrupIndex(int i)
	{
		return m_rgGroupMask[i];
	}

}
