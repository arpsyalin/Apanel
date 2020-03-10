/******************************************
**		文件：APanel_CDrawCheckButton.h
**		作者：刘亚林
**		时间：12年10月24日
**		最后修改：无
*******************************************/
#ifndef _APANEL_TYPE_H
#define _APANEL_TYPE_H
#include "APanel_Type.h"
#endif

#ifndef _APANEL_CDRAWBUTTON_H
#define _APANEL_CDRAWBUTTON_H
#include "APanel_CDrawButton.h"
#endif

namespace APanel
{
	class CDrawCheckButton : public CDrawButton
	{
		//构造，析构
	public:
		CDrawCheckButton();
		~CDrawCheckButton();
		//由其基类构造
		CDrawCheckButton(const CDrawButton& buttonSrc);

		//接口
	public:
		//序列化
		virtual bool Serialize(bool ismany);
		//设置是否为check
		void				SetChecked(bool bChecked);

		//设置checkbutton的初始状态
		//编译时用，注意:需用在InitButtonState之后
		void				SetInitialState(bool bChecked);

		//该按钮是否为check
		bool				IsChecked();

		//按钮的事件处理
		virtual void		OnLButtonDown(bool istrue);
		virtual void		OnLButtonUp(bool istrue);
		//播放音乐的调用
		void soundplay();
		//播放音乐的线程
		static void *playsound(void* data);
		//操作
	protected:

		//属性
	protected:
		UINT GroupCount ;
		vector<UINT> GroupID;//分组ID
		UINT MaskCount ;
		vector<UINT> MaskID;	//Mask ID
		string Bind;
		bool m_bChecked;					//是否被check
		friend class XMLHelper;
		friend class CPanelManage;
	};
}
