/******************************************
**		文件：APanel_CPanelManage.h
**		作者：刘亚林
**		时间：12年10月24日
**		最后修改：无
*******************************************/
#ifndef _APANEL_TYPE_H
#define _APANEL_TYPE_H
#include "APanel_Type.h"
#endif

#ifndef _APANEL_CDRAWPAGE_H
#define _APANEL_CDRAWPAGE_H
#include "APanel_CDrawPage.h"
#endif

#ifndef _AVTRONSYS_EVENTLOOP_H
#define _AVTRONSYS_EVENTLOOP_H
#include "Avtronsys/Avtronsys_EventLoop.h"
#endif

#ifndef _AVTRONSYS_EGLDISPLAY_H
#define _AVTRONSYS_EGLDISPLAY_H
#include "Avtronsys/Avtronsys_EGLDisplay.h"
#endif

#ifndef _AVTRONSYS_DRAWTEXTURE_H
#define _AVTRONSYS_DRAWTEXTURE_H
#include "Avtronsys/Avtronsys_DrawTexture.h"
#endif

#ifndef _AVTRONSYS_PLAYSOUND_H
#define _AVTRONSYS_PLAYSOUND_H
#include "Avtronsys/Avtronsys_PlaySound.h"
#endif



namespace APanel
{
	class CPanelManage
	{
		//构造，析构函数
	public:
		CPanelManage();
		~CPanelManage();

		//接口
	public:
		void setAndroid_app(android_app* papp);
		int showMain();
		void drawMain();
		void setMainGLID(GLuint ptid);
		//序列化
		bool				Serialize(bool ismany);
		//设置目标IP
		void				SetHostAddress(const char* csAddress);

		//设置wifi热点
		void				SetDestAP(const char* csDestAp);

		//设置 / 获 取系统的通信方式
		void				SetCommType(UINT uCommType);
		UINT				GetCommType();

		//获得某个页面
		CDrawPage*			GetPage(int iIndex);

		//添加控件元素
		bool				AppendCtrlItem(UINT nParentID,								//父控件ID，如果没有为0
										   APPEND_ITEM_STRUCT itemStr,					//控件属性
										   DCS_STYLE style,								//控件样式
										   DC_CTRL_TYPE ctrlType			//控件类型
										   );
		//为页面添加状态
		//返回该状态的序号
		//函数只取pStateDC中(0, 0, width(nCtrlID), height(nCtrlID))部分图像
		//如果页面状态超过DC_MAX_STATE，返回-1
		//函数执行失败，返回-1
		int					AppendCtrlState(UINT nCtrlID);
		//事件联系
		//nCtrlID:	该事件为哪个控件的事件
		//eventData: 事件要处理的数据
		//			 PAGE_JUMP_EVENT, 该参数为跳转到页面的ID
		//			 JOINNUM_SEND_EVENT, 该参数为NULL,
		//			 DATA_SEND_EVENT, 该参数为发送数据的首址
		//envetType: 事件类型
		//nDataLen: eventData 的长度
		//bUp:		控件弹起时相应
		//bool				LinkEventToCtrl(UINT nCtrlID, LPVOID eventData,
		//								    DCS_EVENT enventType = PAGE_JUMP_EVENT, int nDataLen = 4, bool bUp = TRUE);

		bool LinkEventToCtrl(UINT nCtrlID, LPVOID eventData,
				DCS_EVENT enventType /* = PAGE_JUMP_EVENT */,
				int nDataLen /* = 4 */, DCS_EVENT_CASE eventDrv);

		//绑定按钮到组
		//如果邦定成功返回TRUE；否则返回FALSE；
		//调用失败可能是由于 ID为nButtonID不存在,也可能是超过了该组最大可绑定按钮的数量等
		//分组概念--新定义
		//
		//________         ________        ___________________________
		//|Group1|-------->|Synch11|------>|Ctrl1 |Ctrl2 |Ctrl3| ...
		//--------         --------        ---------------------------
		//|Group2|---|     |Synch12|--|
		//--------   |     --------   |    ___________________________
		//|      |   |     |       |  |--->|Ctrl1 |Ctrl2 |Ctrl3|Ctrl4| ...
		//|  ... |   |     |  ...  |       ---------------------------
		//--------   |     --------
		//|Groupn|   |     |Synch1n|
		//--------   |     ________
		//           |     ________
		//           |---->|Synch21|
		//                 --------
		//                 |Synch22|
		//                 --------
		//                 |       |
		//                 |  ...  |
		//                 --------
		//                 |Synch2n|
		//                 ________
		//
		//系统中含有 DC_MAX_GROUP个分组(Group)
		//每个分组(Group)含有DC_MAXCTRL_IN_G个同步元素族(Synch)
		//每个同步元素族(Synch)中有若干个控件(Ctrl)
		//处于同个同步元素族(synch)中的所有控件状态相同
		//而同一个分组(Group)中不同的同步元素族(synch)的状态是相反的。
		//说明:nGroupNum指明绑定到哪一个分组
		//     nInnerIndex指明分配到这个分组的哪一个同步元素族中。
		bool				BindButtonToGroup(UINT nButtonID, UINT nGroupNum, UINT nInnerIndex);
		//设置当前页面  默认无动画
		void				SetCurrentPage(UINT nPageId,ANIMATION_MODEL animode = ANI_NULL);
		void				SetCurrentPage(CDrawPage* pPage,ANIMATION_MODEL animode = ANI_NULL);
		CDrawPage*			GetCurrentPage();
		//开始工作
		void				Work();
		//事件响应
		/*页面跳转*/
		void				PageJump(UINT nID,ANIMATION_MODEL animode = ANI_NULL);
		/*隐藏某个元素*/
		void				HideItem(UINT nID);

		//接受一个鼠标按钮事件
		void				PostButtonMessage(bool bDown, POINT pt);

		//处理组内事件
		//nGroupID:需要处理的组ID
		//pEventStart:事件发起控件
		void				DoGroupEvent(UINT nGroupID, CDrawControl* pEventStart);

		void				DoGroupEvent2(UINT nGroupID, UINT nGroupMask);

		//判断某个控件是否在当前屏幕中
		bool				IsCtrlInCurrentScreen(UINT nCtrlID);

		//发送数据
		bool				SetEventData(LPVOID pBuffer, UINT nLen);
		bool 				SendData(LAN_JOINNUM_FRAME var_sendFrame);
		//停止发送数据
		bool				EndSend();
		//操作
		const char*			GetMachineIP();

		static	int AsyncPageSerial(LPVOID lpParameter);

		void setRDraw(Avtronsys::EventLoop* pelp);	//重绘
		void setRDraw2(Avtronsys::AvtronsysEGLDisplay* pegl);	//重绘
		void RDraw();
		void RDraw2();
		void playSound(int nub);
	protected:
		//查找某个CtrlID的控件
		CDrawControl*		FindCtrlByID(UINT nCtrlID);
		CDrawControl*		FindCtrlSubFun(CDrawPage* pPage, UINT nCtrlID);

		//添加页面
		int					AppendPage(CDrawPage* pAdd);

		//插入页面
		void				InsertPage(CDrawPage* pInsert, UINT iIndex);


		//属性
	protected:
	
	public:
		Avtronsys::EventLoop* melp;
		Avtronsys::AvtronsysEGLDisplay* megl;
		CDrawControl* mLastDownControl; //最后按下的按钮

		//该类只允许实例化一次
		bool								m_bConstructed;

		//所包含的页面（父页面）
		//注意：主页面放在第一个元素的位置
		vector<CDrawPage*>						m_Drawpages;

		//系统的通信模式，可以是一种也可以是多种，多种的表示方法如：DC_COMM_IP | DC_COMM_RF
		UINT									m_sysCommType;
		bool									m_bCommStart;

		//对分组按钮的描述
		//每组允许添加的控件数为32个，即sizeof(UINT)
		//例如：某个按钮属于第3组，为该组的第4个元素，则：
		//m_groupState[2]的第4位为1时，该按钮按下状态，为0即弹起
		//注意：每一组状态的32位只允许一位为1，即表示该组的控件在同一时间
		//		只有允许一个按钮按下！
		//static UINT								m_groupState[DC_MAX_GROUP];

		//当前页面
		CDrawPage*								m_currPage;
		ANIMATION_MODEL							m_Animation;

		//当前正在处理事件的页面
		CDrawPage*								m_activePage;

		//页面数量
		int PageCount;

		//组管理器
		//在保存时，这个数据是不需要写入文件的，但读取的时候要临时构建
		CCtrlGroups								m_groups;
		int maxGroupNum;

		//目标地址IP
		const char*									m_csHostIp;
		Avtronsys::DrawTexture m_hostlinkDT[3];
		Avtronsys::DrawTexture m_mainDT;
		Avtronsys::PlaySound * Allplaysound;
		Avtronsys::SoundHandler* mSoundHandler[2];

		//WIFI热点
		const char*									m_csWifiAp;
		android_app * mapp;
		friend class CDrawControl;
	};
}



