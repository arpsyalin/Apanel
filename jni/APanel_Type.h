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

	//�ؼ�����
	typedef enum
	{
			DC_CTRL_BUTTON,						//��ť
			DC_CTRL_PAGE,						//ҳ��
			DC_CTRL_CHECKBUTTON,				//check��ť
			DC_CTRL_DIRECTIONBUTTON				//Direction��ť
	}DC_CTRL_TYPE;



	//�Զ���һ��UINT
	typedef unsigned int UINT;
	typedef void* LPVOID;
	//�ؼ���ʽ
	#define DCS_STYLE			UINT
	#define DCS_PARENT				0x01		//���ؼ�
	#define DCS_CHILD				0x02		//�ӿؼ�
	#define DCS_SHOW				0x04		//�ɼ�
	///�����и�5��6 5Ϊҳ���������ʽΪ��ҳ�� 6Ϊ��ҳ���ʱ��

	#define DCS_HIDE				0x00//(~0x04)		//���ɼ�


	//���ķ���
	#define DC_MAX_GROUP			128
	#define DC_MAXCTRL_IN_G			64
	#define DC_INDEX_IN_G(i)		0x00000001 << (i)

	//�¼�����
	#define DCS_EVENT			UINT
	#define NULL_EVENT				0x00		//���¼�
	#define PAGE_JUMP_EVENT			0x01		//ҳ����ת

	#define ITEM_HIDE_EVENT			0x02		//����ĳ��Ԫ��
	#define JOINNUM_SEND_EVENT		0x04		// �� ��JoinNum
	#define DATA_SEND_EVENT			0x08		// �� ������

	//�¼���Ӧʱ��
	#define DCS_EVENT_CASE			UINT
	#define LBUTTON_DOWN			0x01		//����������
	#define LBUTTON_UP				0x02		//����������
	#define PRESS_DOWN				0x04		//�ؼ�������
	#define PRESS_UP				0x08		//�ؼ�����
	#define NULL_DRV				0x00		// û���ź�����
	#define TIMER_OVER				0x09		// Duration ��ť��ʱ
	#define ANIMATION				0x10		// ��Ч�¼�


	//ϵͳ��ͨ��ģʽ
	#define DC_COMM_NULL			0x00000000	//��ͨ��ģ��
	#define DC_COMM_LAN				0x00000001	//����ͨ��ģʽ
	#define DC_COMM_COM				0x00000002	//����ͨ��ģʽ
	#define DC_COMM_RF				0x00000004	//RFͨ��ģʽ
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
		ANI_NULL = 0,				//ANI_  Animation ��Ч��
		ANI_UPTODOWN,				//�������·���
		ANI_DOWNTOUP,				//�������Ϸ���
		ANI_LEFTTORIGHT,			//�������ҷ���
		ANI_RIGHTTOLEFT,			//�����������
		ANI_ALPHA_IN,				//����
		ANI_ALPHA_OUT,
		ANI_PlayRain,
		ANI_PlayClosedoor,
		ANI_PlayPlus
	}ANIMATION_MODEL;


	//LAN�ڷ���JOINNUM��֡�ṹ
	#pragma pack(push, 1)   //����һ�ֽڶ���
	typedef struct lan_joinnum_struct
	{
		unsigned char 	bFrameHead;				//֡ͷ������Ϊ0xAA
		union 									//��Ҫ���͵�joinnum��ֵ
		{
			typedef unsigned short	wJoninNum;
			unsigned char 			bJoinNum[2];
		}joinNum;
		unsigned char 	bSingnalType;			//�ź����ͣ��ڸð汾�к�Ϊ1������ʾΪ��������
												//�ö���Ϊ�˱�����ɰ汾�ļ�����
		unsigned char 	bSingnalLen;			//�źų��ȣ�������Ϊ1��ģ����Ϊ2 --�ð汾��Ϊ1

		unsigned char 	bReserve[5];			//�����ֶ�

		unsigned char 	bDownEvent;				//���·���'1',������'0'

	}LAN_JOINNUM_FRAME;
	#pragma pack(pop)

	#define NUM 0xFF
	#define MAX_DATA_BUF_LEN 10240
	#define BUFFERSIZE 12
	#define ITOC_OFFSET 48  //int->char ���͵�ƫ���� ,��'2' = 2+48.

	//ƽ������
	struct POINT
	{
		float x;
		float y;
	};

	//���ڱ���ͼƬ·���Լ�����ID
	struct STATE
	{
		string imgPath;//״̬��Ӧ��ͼƬ·��
		GLuint texID;//״̬ͼƬ���ɵ�����(texture)��ID
	};

	struct RECT
	{
		POINT LTPoint;			//����
		float RWidth;			//��
		float RHeight;			//��
	};
	//���ӿؼ�
	typedef struct append_item_struct
	{
		UINT		nId;						//�ؼ�ID
		RECT		rect;						//�ؼ���������ڸ�����
		UINT		nJoinNum;					//JoinNum,û�и�0
		UINT		nInitState;					//��ʼ״̬����Page�ȿؼ���Ч
		bool		bChecked;					//�Ƿ�Ϊchecked������check ��ť��Ч
		UINT		nTimeDelay;					//����Diretion��ť��Ч

	public:
		append_item_struct()
		{
			nId = 0;
			rect.LTPoint.x=rect.LTPoint.y=rect.RWidth=rect.RHeight=0;
			nJoinNum = 0;
			nInitState = 0;
			bChecked = false;
			nTimeDelay = 40;			//Ĭ���ӳ�40ms
		}
	}APPEND_ITEM_STRUCT;
	//����״̬��
	#define DC_MAX_STATE			16
	extern float pbDisplayH;	//�����඼�����������Ļ�ĸ�APanel_CPanelManage.cpp����һ������Ϊȫ�ֱ���
	extern short impoWerstate;	//0.δ����ͨ 1.δ��ͨ 2.�ѡ���ͨ.3.�ѡ�ͨ  1δ��Ȩ 2������Ȩ 3������Ȩδ����
	extern char* hostip;
	extern const char* severIP;
	extern bool minitend;
	extern bool ismainok;
}
