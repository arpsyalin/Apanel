/******************************************
**		文件：APanel_CDrawControl.h
**		作者：刘亚林
**		时间：12年10月24日
**		最后修改：无
*******************************************/
#ifndef _APANEL_TYPE_H
#define _APANEL_TYPE_H
#include "APanel_Type.h"
#endif



#ifndef _AVTRONSYS_DRAWTEXTURE_H
#define _AVTRONSYS_DRAWTEXTURE_H
#include "Avtronsys/Avtronsys_DrawTexture.h"
#endif

#ifndef _APANEL_CEVENTLINK_
#define _APANEL_CEVENTLINK_
#include "APanel_CEventLink.h"
#endif

namespace APanel
{
	class CPanelManage;
	class CDrawControl
	{
	public:
		CDrawControl();
		CDrawControl(DCS_STYLE	dcs_style);
		virtual ~CDrawControl();
	//接口
	public:
		//初始化项目所要用到的所有图片
		virtual int ProjectImageInit(bool isfirst);
		//项目初始化绘制
		virtual void ProjectDrawInit(GLuint pCurTextureid);
		//设置绘制纹理的大小
		virtual void setSize(float sizew,float sizeh);
		//设置绘制纹理的位置
		virtual void setLocation(float px,float py);
		//设置纹理的偏移
		virtual void setTextureDVT(float left,float top);
		//设置纹理的宽和高
		virtual void setTextureHAW(float width,float height);
		//设置偏移量和宽高
		virtual void setTextureArray(float left,float top,float width,float height);
		//设置纹理ID
		virtual void setTexture(GLuint pCurTextureid);

		//自绘函数
		//要求所有继承自该类的类，必须重写该函数
		virtual bool	DrawSelf();//{return true;};
		virtual bool	DrawSelf(ANIMATION_MODEL animode );//{return true;};
		//设置/获取控件区域
		void				SetRect(RECT rect);
		RECT				GetRect();

		//设置/获取控件ID
		void				SetControlId(int nId);
		UINT				GetControlId();
		//事件响应函数
		//左键按下
		//pt 的坐标以该控件的位置作为参考
		virtual void		OnLButtonDown(POINT pt);
		//左键弹起
		virtual void		OnLButtonUp(POINT pt);

		//pt 的坐标以该控件的位置作为参考
		virtual void		OnLButtonDown(bool istrue);
		//左键弹起
		virtual void		OnLButtonUp(bool istrue);

		//判断该控件在不在某个区域内
		bool				IsInRect(POINT	pt);
		bool				IsInRect(RECT	rect);
		//序列化
		virtual bool Serialize(bool ismany);

		//设置父控件
		void				SetParentCtr(CDrawControl* pParent);
		//使控件与组邦定
		//该函数不对某个组的状态量是否重复绑定，不做非法判定
		void				BindToGroup(int nGroupID, int indexInGroup);

		//设置控件类型
		void				SetControlType(DC_CTRL_TYPE dcstyle);
		UINT				GetControlType();

		//添加事件
		//void				AppendEventLink(DCS_EVENT eventType, LPVOID pData, UINT nDataLen, BOOL bUp);
		void				AppendEventLink(DCS_EVENT eventType, LPVOID pData, UINT nDataLen, DCS_EVENT_CASE eventDrv);

		//获得控件Index
		//没有该控件返回-1
		virtual int			GetCtrlIndex(CDrawControl* pCtrl);
		//获得组号及组内号
		//	int					GetGroupId()						{return m_bindGroupId;};
		//	int					GetInnerGrupIndex()					{return m_groupMask;};
		int					GetInnerGrupIndex(int i);
		//属性
	protected:
		//所在区域---相对于父控件而言
		RECT 				m_rect;
		//控件ID---对应于JoinNum
		UINT				m_ctrId;
		//控件样式
		DCS_STYLE			m_ctrShowType;
		//保存控件类型
		DC_CTRL_TYPE        m_ctrType;

		//事件数量数量
		int m_EventCount;
		
		//控件邦定的组号
		//如果没有邦定，m_bindGroupId = -1;
		//int				m_bindGroupId;
		vector<UINT>		m_rgBindGroupId;
		//控件组内掩码
		//2008.8.23 对其含义做了修改
		//修改后的含义为组内索引号--标示该控件属于该组中哪个同步组件族
		//int					m_groupMask;
		vector<UINT>		m_rgGroupMask;

		//父控件,默认为NULL
		CDrawControl*		m_pParentCtr;
		//声音
		int m_Music;
		CPanelManage * m_panelMan;
		//事件
		vector<CEventLink> m_envents;
		Avtronsys::DrawTexture mDrawTexture;	  	//绘制类

		friend class CPanelManage;
		friend class XMLHelper;
		friend class CDrawPage;
		friend class APanelActivityHandler;	//友元类

	};
}
