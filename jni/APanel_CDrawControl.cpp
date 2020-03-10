/******************************************
**		文件：APanel_CDrawControl.cpp
**		作者：刘亚林
**		时间：12年10月24日
**		最后修改：无
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

	//序列化
	bool CDrawControl::Serialize(bool isfirst)
	{
		return true;
	}

	int CDrawControl::ProjectImageInit(bool isfirst)
	{
		return 0;
	}


	//绘制初始化
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

	//设置绘制纹理的大小
	void CDrawControl::setSize(float sizew,float sizeh)
	{
		mDrawTexture.setSize(sizew,sizeh);
	}

	//设置绘制纹理的位置
	void CDrawControl::setLocation(float px,float py)
	{
		mDrawTexture.setLocation(px,py);
	}
	//设置纹理的偏移值
	void CDrawControl::setTextureDVT(float left,float top)
	{
		mDrawTexture.setTextureDVT(left,top);
	}

	//设置纹理宽高
	void CDrawControl::setTextureHAW(float width,float height)
	{
		mDrawTexture.setTextureHAW(width,height);
	}

	//设置纹理的偏移值和宽高
	void CDrawControl::setTextureArray(float left,float top,float width,float height)
	{
		mDrawTexture.setTextureArray(left,top,width,height);
	}

	//设置纹理ID
	void CDrawControl::setTexture(GLuint pCurTextureid)
	{
		mDrawTexture.setTexture(pCurTextureid);
	}

	//自绘函数
	//要求所有继承自该类的类，必须重写该函数
	bool CDrawControl::DrawSelf()
	{
		return true;
	}
	bool CDrawControl::DrawSelf(ANIMATION_MODEL animode )
	{
		return true;
	}

	//设置控件区域
	void CDrawControl::SetRect(RECT rect)
	{

	}
	//获取控件区域
	RECT CDrawControl::GetRect()
	{
		return m_rect;
	}

	//设置控件ID
	void CDrawControl::SetControlId(int nId)
	{
		m_ctrId = nId;
	}
	//获取控件ID
	UINT CDrawControl::GetControlId()
	{
		return m_ctrId;
	}

	//事件响应函数
	//左键按下
	//pt 的坐标以该控件的位置作为参考
	void CDrawControl::OnLButtonDown(POINT pt)
	{

	}
	//左键弹起
	void CDrawControl::OnLButtonUp(POINT pt)
	{
	}

	//事件响应函数
	//左键按下
	//pt 的坐标以该控件的位置作为参考
	void CDrawControl::OnLButtonDown(bool istrue)
	{

	}
	//左键弹起
	void CDrawControl::OnLButtonUp(bool istrue)
	{
	}

	//判断该控件在不在某个区域内
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


	//使控件与组邦定
	//该函数不对某个组的状态量是否重复绑定，不做非法判定
	void CDrawControl::BindToGroup(int nGroupID, int indexInGroup)
	{
		//组号不合法
		if ((nGroupID < 0) || (nGroupID >= DC_MAX_GROUP))
		{
			return;
		}
		//组内序号不合法
		if ((indexInGroup <0) || (indexInGroup >= DC_MAXCTRL_IN_G))
		{
			return;
		}
		m_rgBindGroupId.push_back(nGroupID);
		m_rgGroupMask.push_back((indexInGroup));
	}
	//设置父控件
	void CDrawControl::SetParentCtr(CDrawControl* pParent)
	{

	}


	//设置控件类型
	void CDrawControl::SetControlType(DC_CTRL_TYPE dcstyle)
	{
		m_ctrShowType = dcstyle;
	}

	UINT CDrawControl::GetControlType()
	{
		return m_ctrShowType;
	}

	//添加事件
	void CDrawControl::AppendEventLink(DCS_EVENT eventType, LPVOID pData, UINT nDataLen, DCS_EVENT_CASE eventDrv)
	{

	}

	//获得控件Index
	//没有该控件返回-1
	int CDrawControl::GetCtrlIndex(CDrawControl* pCtrl)
	{
		return -1;
	}
	
	//获得组号及组内号
	int CDrawControl::GetInnerGrupIndex(int i)
	{
		return m_rgGroupMask[i];
	}

}
