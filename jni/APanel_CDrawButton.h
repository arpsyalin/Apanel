/******************************************
**		文件：APanel_CDrawButton.h
**		作者：刘亚林
**		时间：12年10月24日
**		最后修改：无
*******************************************/
#ifndef _APANEL_TYPE_H
#define _APANEL_TYPE_H
#include "APanel_Type.h"
#endif

#ifndef _APANEL_CCTRLGROUPS_H
#define _APANEL_CCTRLGROUPS_H
#include "APanel_CCtrlGroups.h"
#endif


namespace APanel
{
	//CDrawButton:按钮类

	class CDrawButton : public CDrawControl
	{

		//构造，析构函数
	public:
		CDrawButton();
		virtual ~CDrawButton();

		//接口
	public:
		//序列化
		virtual bool Serialize(bool ismany);

		//初始化按钮状态
		//pState:表示状态的图片信息数组+
		//nCount:状态数量，要小于16
		//该函数从按钮的状态0开始初始化，并将未初始化的状态清空
		void				InitButtonState();

		//添加按钮的一个状态
		//调用成功返回 该状态的序号
		//否则返回-1
		int					AppendButtonState(STATE pSTATE);

		/*后面还有几组函数在方案验证可行后再继续*/
		//事件响应函数
		//左键按下
		//pt 的坐标以该控件的位置作为参考
		virtual void		OnLButtonDown(bool istrue);
		//左键弹起
		virtual void		OnLButtonUp(bool istrue);
		//自绘函数
		virtual bool		DrawSelf();
		//设置按钮状态   bRepaint = TRUE
		//				 将按钮自绘显示到pDC上。
		//				 bRepaint = FALSE
		//				 仅改变按钮状态但不自绘
		void				SetCurrentState(UINT nState, bool bRepaint = true);

		//从当前状态过渡到目标状态
		void				PlayStateTo(UINT nDestState);

		void				SetAnimation(ANIMATION_MODEL mode);
		ANIMATION_MODEL		GetAnimation(void);
		//播放音乐的调用
		void soundplay();
		//播放音乐的线程
		static void *playsound(void* data);
		//属性
	protected:
		//按钮默认含有16个状态
		//当前状态
		UINT				m_nCurrState;
		ANIMATION_MODEL		m_aniMode;
		//该按钮实际包含的状态数
		UINT				m_nSateCount;
		vector<STATE>		m_StateArray;

		friend class XMLHelper;
		friend class CDrawCheckButton;
	};
}
