/******************************************
**		文件：APanel_CSynchronousCtrls.h
**		作者：刘亚林
**		时间：12年10月24日
**		最后修改：无
*******************************************/
#ifndef _APANEL_TYPE_H
#define _APANEL_TYPE_H
#include "APanel_Type.h"
#endif

//#ifndef _APANEL_CDRAWCONTROL_H
//#define _APANEL_CDRAWCONTROL_H
#include "APanel_CDrawControl.h"
//#endif

namespace APanel
{
	/***************************************************************
	**
	**			CSynchronousCtrls同步元素族类
	**
	****************************************************************/
	class CSynchronousCtrls
	{
		//构造、析构函数
	public:
		CSynchronousCtrls();
		CSynchronousCtrls(const CSynchronousCtrls& objectSrc);
		~CSynchronousCtrls();

		//接口
	public:
		//添加一个元素到该组
		int				AppendCtrlToMutex(CDrawControl*  pAdd);

		//根据序号获得一个组内元素
		CDrawControl*	GetCtrlByIndex(UINT nIndex);

		//获得控件个数
		UINT			GetCtrlNum();

		//运算符重载
		void operator=(const CSynchronousCtrls& objectSrc);

		//操作
	protected:

		//属性：
	protected:
		vector<CDrawControl*> m_DrawCtrls;
	};

}
