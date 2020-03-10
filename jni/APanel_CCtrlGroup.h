/******************************************
**		文件：CCtrlGroup.h
**		作者：刘亚林
**		时间：12年10月24日
**		最后修改：无
*******************************************/
#ifndef _APANEL_TYPE_H
#define _APANEL_TYPE_H
#include "APanel_Type.h"
#endif

#ifndef _APANEL_CSYNCHRONOUSCTRLS_H
#define _APANEL_CSYNCHRONOUSCTRLS_H
#include "APanel_CSynchronousCtrls.h"
#endif


namespace APanel
{
	class CCtrlGroup
	{
		//构造，析构函数
	public:
		CCtrlGroup();
		CCtrlGroup(const CCtrlGroup& objectSrc);
		~CCtrlGroup();

		//接口
	public:
		//添加一个控件到该组中，返回该控件在组中的位置，添加失败返回-1
		int					AppendCtrlToGroup(CDrawControl* pAdd, UINT	nInnerIndex);

		//获得该组第nIndex个元素
		CSynchronousCtrls&	GetByIndex(UINT nIndex);

		void initMask(int maxMaskID);
		//运算符重载
		void operator=(const CCtrlGroup& objectSrc);

		//获得该组中同步元素族的个数
		UINT				GetSynNum();
		//操作
	protected:

		//属性
	protected:
		vector<CSynchronousCtrls*>  m_synCtrls;
		int						   m_nCtrlNum;
		friend class CPanelManage;
	};
}
