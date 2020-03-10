/******************************************
**		文件：CCtrlGroups.h
**		作者：刘亚林
**		时间：12年10月24日
**		最后修改：无
*******************************************/
#ifndef _APANEL_TYPE_H
#define _APANEL_TYPE_H
#include "APanel_Type.h"
#endif

#ifndef _APANEL_CCTRLGROUP_H
#define _APANEL_CCTRLGROUP_H
#include "APanel_CCtrlGroup.h"
#endif

namespace APanel
{
	class CCtrlGroups
		{
		public:
			CCtrlGroups();
			~CCtrlGroups();

			//接口
		public:
			//邦定控件到nGroupID组,nSynIndex同步元素族
			int	BindCtrlToGroup(UINT nGroupID, UINT nSynIndex, CDrawControl* pAdd);

			//获得组号为nGroupID的第nIndex个同步元素族
			CSynchronousCtrls&	GetCtrlFromGroup(UINT nGroupID, UINT nIndex);

			CCtrlGroup* GetCtrlGroup(UINT nGroupID);
			void initGroup(int maxGroupID,int maxMaskID);
			//获得某组同步元素族的个数
			//int								GetCtrlNumInGroup(UINT nGroupID);
			//属性
		protected:
			vector<CCtrlGroup*> m_groups;
			friend class XMLHelper;
		};

}
