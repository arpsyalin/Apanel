#ifndef _SYSTEM_STDINT_H
#define _SYSTEM_STDINT_H
#include <stdint.h>
#endif

#ifndef _SYSTEM_CSTDLIB_H
#define _SYSTEM_CSTDLIB_H
#include <cstdlib>
#endif

#ifndef _SYS_VECTOR_H
#define _SYS_VECTOR_H
#include <vector>
#endif

#ifndef _SYS_SELECT_H
#define _SYS_SELECT_H
#include <sys/select.h>
#endif

#ifndef _SYS_SOCKET_H
#include <sys/socket.h>
#endif

#ifndef _ARPA_INET_H
#define _ARPA_INET_H
#include <arpa/inet.h>
#endif

#ifndef _SYS_TYPEINFO_H
#define _SYS_TYPEINFO_H
#include <typeinfo>
#endif

#ifndef _SYS_IOSTREAM_H
#define _SYS_IOSTREAM_H
#include <IOSTREAM>
#endif

#ifndef _SYSTEM_GL_H
#define _SYSTEM_GL_H
#include <GLES/gl.h>
#endif

#ifndef _SYSTEM_GLEXT_H
#define _SYSTEM_GLEXT_H
#include <GLES/glext.h>
#endif
using namespace std;

namespace APanel
{
	typedef int TouchType;
	const TouchType mTouchDown = 0x01;
	const TouchType mTouchUp = 0x02;
	const TouchType mTouchMove = 0x03;
	const TouchType mTouchOutside = 0x04;

	//控件类型
	typedef enum
	{
			DC_CTRL_BUTTON,						//按钮
			DC_CTRL_PAGE,						//页面
			DC_CTRL_CHECKBUTTON,				//check按钮
			DC_CTRL_DIRECTIONBUTTON				//Direction按钮
	}DC_CTRL_TYPE;



	//自定义一个UINT
	typedef unsigned int UINT;
	typedef void* LPVOID;
	//控件样式
	#define DCS_STYLE			UINT
	#define DCS_PARENT				0x01		//主控件
	#define DCS_CHILD				0x02		//子控件
	#define DCS_SHOW				0x04		//可见
	///这里有个5和6 5为页面的类型样式为主页面 6为子页面的时候

	#define DCS_HIDE				0x00//(~0x04)		//不可见


	//最大的分组
	#define DC_MAX_GROUP			128
	#define DC_MAXCTRL_IN_G			64
	#define DC_INDEX_IN_G(i)		0x00000001 << (i)

	//事件类型
	#define DCS_EVENT			UINT
	#define NULL_EVENT				0x00		//无事件
	#define PAGE_JUMP_EVENT			0x01		//页面跳转

	#define ITEM_HIDE_EVENT			0x02		//隐藏某个元素
	#define JOINNUM_SEND_EVENT		0x04		// 发 送JoinNum
	#define DATA_SEND_EVENT			0x08		// 发 送数据

	//事件响应时机
	#define DCS_EVENT_CASE			UINT
	#define LBUTTON_DOWN			0x01		//鼠标左键按下
	#define LBUTTON_UP				0x02		//鼠标左键弹起
	#define PRESS_DOWN				0x04		//控件被按下
	#define PRESS_UP				0x08		//控件弹起
	#define NULL_DRV				0x00		// 没有信号驱动
	#define TIMER_OVER				0x09		// Duration 按钮定时
	#define ANIMATION				0x10		// 特效事件


	//系统的通信模式
	#define DC_COMM_NULL			0x00000000	//无通信模块
	#define DC_COMM_LAN				0x00000001	//网络通信模式
	#define DC_COMM_COM				0x00000002	//串口通信模式
	#define DC_COMM_RF				0x00000004	//RF通信模式
	#define DC_COMM_WIFI			0x00000008	// WIFI

	#define		LAN_CONNECT		0x0
	#define		RF_CONNECT		0x1
	#define		WIFI_NOSIGNAL	0x2
	#define		WIFI_SCAN		0x3
	#define		LAN_DISCONNETCT	0x4

	#define		PING_RESET_LEVEL 15
	#define		WIFI_RESET_LEVEL 15

	#define IOCTL_WIFIMODULE_SETON	  0x80002008
	#define IOCTL_WIFIMODULE_SETOFF	  0x8000200C

	typedef enum {
		ANI_NULL = 0,				//ANI_  Animation 无效果
		ANI_UPTODOWN,				//从上向下飞入
		ANI_DOWNTOUP,				//从下向上飞入
		ANI_LEFTTORIGHT,			//从左向右飞入
		ANI_RIGHTTOLEFT,			//从右向左飞入
		ANI_ALPHA_IN,				//渐进
		ANI_ALPHA_OUT,
		ANI_PlayRain,
		ANI_PlayClosedoor,
		ANI_PlayPlus
	}ANIMATION_MODEL;


	//LAN口发送JOINNUM的帧结构
	#pragma pack(push, 1)   //按照一字节对齐
	typedef struct lan_joinnum_struct
	{
		unsigned char 	bFrameHead;				//帧头，定死为0xAA
		union 									//需要发送的joinnum的值
		{
			typedef unsigned short	wJoninNum;
			unsigned char 			bJoinNum[2];
		}joinNum;
		unsigned char 	bSingnalType;			//信号类型，在该版本中恒为1，即表示为数字量。
												//该段是为了保持与旧版本的兼容性
		unsigned char 	bSingnalLen;			//信号长度：数字量为1，模拟量为2 --该版本恒为1

		unsigned char 	bReserve[5];			//保留字段

		unsigned char 	bDownEvent;				//按下发送'1',弹起发送'0'

	}LAN_JOINNUM_FRAME;
	#pragma pack(pop)

	#define NUM 0xFF
	#define MAX_DATA_BUF_LEN 10240
	#define BUFFERSIZE 12
	#define ITOC_OFFSET 48  //int->char 类型的偏移量 ,例'2' = 2+48.

	//平面坐标
	struct POINT
	{
		float x;
		float y;
	};

	//用于保存图片路径以及纹理ID
	struct STATE
	{
		string imgPath;//状态对应的图片路径
		GLuint texID;//状态图片生成的纹理(texture)的ID
	};

	struct RECT
	{
		POINT LTPoint;			//左上
		float RWidth;			//宽
		float RHeight;			//高
	};
	//增加控件
	typedef struct append_item_struct
	{
		UINT		nId;						//控件ID
		RECT		rect;						//控件区域，相对于父而言
		UINT		nJoinNum;					//JoinNum,没有赋0
		UINT		nInitState;					//初始状态：对Page等控件无效
		bool		bChecked;					//是否为checked：仅对check 按钮有效
		UINT		nTimeDelay;					//仅对Diretion按钮有效

	public:
		append_item_struct()
		{
			nId = 0;
			rect.LTPoint.x=rect.LTPoint.y=rect.RWidth=rect.RHeight=0;
			nJoinNum = 0;
			nInitState = 0;
			bChecked = false;
			nTimeDelay = 40;			//默认延迟40ms
		}
	}APPEND_ITEM_STRUCT;
	//最大的状态数
	#define DC_MAX_STATE			16
	extern float pbDisplayH;	//所有类都含有这个是屏幕的高APanel_CPanelManage.cpp中做一个声明为全局变量
	extern short impoWerstate;	//0.未、不通 1.未、通 2.已、不通.3.已、通  1未授权 2是已授权 3是已授权未联网
	extern char* hostip;
	extern const char* severIP;
	extern bool minitend;
	extern bool ismainok;
}
