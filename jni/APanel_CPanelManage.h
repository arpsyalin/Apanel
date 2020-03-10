/******************************************
**		�ļ���APanel_CPanelManage.h
**		���ߣ�������
**		ʱ�䣺12��10��24��
**		����޸ģ���
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
		//���죬��������
	public:
		CPanelManage();
		~CPanelManage();

		//�ӿ�
	public:
		void setAndroid_app(android_app* papp);
		int showMain();
		void drawMain();
		void setMainGLID(GLuint ptid);
		//���л�
		bool				Serialize(bool ismany);
		//����Ŀ��IP
		void				SetHostAddress(const char* csAddress);

		//����wifi�ȵ�
		void				SetDestAP(const char* csDestAp);

		//���� / �� ȡϵͳ��ͨ�ŷ�ʽ
		void				SetCommType(UINT uCommType);
		UINT				GetCommType();

		//���ĳ��ҳ��
		CDrawPage*			GetPage(int iIndex);

		//��ӿؼ�Ԫ��
		bool				AppendCtrlItem(UINT nParentID,								//���ؼ�ID�����û��Ϊ0
										   APPEND_ITEM_STRUCT itemStr,					//�ؼ�����
										   DCS_STYLE style,								//�ؼ���ʽ
										   DC_CTRL_TYPE ctrlType			//�ؼ�����
										   );
		//Ϊҳ�����״̬
		//���ظ�״̬�����
		//����ֻȡpStateDC��(0, 0, width(nCtrlID), height(nCtrlID))����ͼ��
		//���ҳ��״̬����DC_MAX_STATE������-1
		//����ִ��ʧ�ܣ�����-1
		int					AppendCtrlState(UINT nCtrlID);
		//�¼���ϵ
		//nCtrlID:	���¼�Ϊ�ĸ��ؼ����¼�
		//eventData: �¼�Ҫ���������
		//			 PAGE_JUMP_EVENT, �ò���Ϊ��ת��ҳ���ID
		//			 JOINNUM_SEND_EVENT, �ò���ΪNULL,
		//			 DATA_SEND_EVENT, �ò���Ϊ�������ݵ���ַ
		//envetType: �¼�����
		//nDataLen: eventData �ĳ���
		//bUp:		�ؼ�����ʱ��Ӧ
		//bool				LinkEventToCtrl(UINT nCtrlID, LPVOID eventData,
		//								    DCS_EVENT enventType = PAGE_JUMP_EVENT, int nDataLen = 4, bool bUp = TRUE);

		bool LinkEventToCtrl(UINT nCtrlID, LPVOID eventData,
				DCS_EVENT enventType /* = PAGE_JUMP_EVENT */,
				int nDataLen /* = 4 */, DCS_EVENT_CASE eventDrv);

		//�󶨰�ť����
		//�����ɹ�����TRUE�����򷵻�FALSE��
		//����ʧ�ܿ��������� IDΪnButtonID������,Ҳ�����ǳ����˸������ɰ󶨰�ť��������
		//�������--�¶���
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
		//ϵͳ�к��� DC_MAX_GROUP������(Group)
		//ÿ������(Group)����DC_MAXCTRL_IN_G��ͬ��Ԫ����(Synch)
		//ÿ��ͬ��Ԫ����(Synch)�������ɸ��ؼ�(Ctrl)
		//����ͬ��ͬ��Ԫ����(synch)�е����пؼ�״̬��ͬ
		//��ͬһ������(Group)�в�ͬ��ͬ��Ԫ����(synch)��״̬���෴�ġ�
		//˵��:nGroupNumָ���󶨵���һ������
		//     nInnerIndexָ�����䵽����������һ��ͬ��Ԫ�����С�
		bool				BindButtonToGroup(UINT nButtonID, UINT nGroupNum, UINT nInnerIndex);
		//���õ�ǰҳ��  Ĭ���޶���
		void				SetCurrentPage(UINT nPageId,ANIMATION_MODEL animode = ANI_NULL);
		void				SetCurrentPage(CDrawPage* pPage,ANIMATION_MODEL animode = ANI_NULL);
		CDrawPage*			GetCurrentPage();
		//��ʼ����
		void				Work();
		//�¼���Ӧ
		/*ҳ����ת*/
		void				PageJump(UINT nID,ANIMATION_MODEL animode = ANI_NULL);
		/*����ĳ��Ԫ��*/
		void				HideItem(UINT nID);

		//����һ����갴ť�¼�
		void				PostButtonMessage(bool bDown, POINT pt);

		//���������¼�
		//nGroupID:��Ҫ�������ID
		//pEventStart:�¼�����ؼ�
		void				DoGroupEvent(UINT nGroupID, CDrawControl* pEventStart);

		void				DoGroupEvent2(UINT nGroupID, UINT nGroupMask);

		//�ж�ĳ���ؼ��Ƿ��ڵ�ǰ��Ļ��
		bool				IsCtrlInCurrentScreen(UINT nCtrlID);

		//��������
		bool				SetEventData(LPVOID pBuffer, UINT nLen);
		bool 				SendData(LAN_JOINNUM_FRAME var_sendFrame);
		//ֹͣ��������
		bool				EndSend();
		//����
		const char*			GetMachineIP();

		static	int AsyncPageSerial(LPVOID lpParameter);

		void setRDraw(Avtronsys::EventLoop* pelp);	//�ػ�
		void setRDraw2(Avtronsys::AvtronsysEGLDisplay* pegl);	//�ػ�
		void RDraw();
		void RDraw2();
		void playSound(int nub);
	protected:
		//����ĳ��CtrlID�Ŀؼ�
		CDrawControl*		FindCtrlByID(UINT nCtrlID);
		CDrawControl*		FindCtrlSubFun(CDrawPage* pPage, UINT nCtrlID);

		//���ҳ��
		int					AppendPage(CDrawPage* pAdd);

		//����ҳ��
		void				InsertPage(CDrawPage* pInsert, UINT iIndex);


		//����
	protected:
	
	public:
		Avtronsys::EventLoop* melp;
		Avtronsys::AvtronsysEGLDisplay* megl;
		CDrawControl* mLastDownControl; //����µİ�ť

		//����ֻ����ʵ����һ��
		bool								m_bConstructed;

		//��������ҳ�棨��ҳ�棩
		//ע�⣺��ҳ����ڵ�һ��Ԫ�ص�λ��
		vector<CDrawPage*>						m_Drawpages;

		//ϵͳ��ͨ��ģʽ��������һ��Ҳ�����Ƕ��֣����ֵı�ʾ�����磺DC_COMM_IP | DC_COMM_RF
		UINT									m_sysCommType;
		bool									m_bCommStart;

		//�Է��鰴ť������
		//ÿ��������ӵĿؼ���Ϊ32������sizeof(UINT)
		//���磺ĳ����ť���ڵ�3�飬Ϊ����ĵ�4��Ԫ�أ���
		//m_groupState[2]�ĵ�4λΪ1ʱ���ð�ť����״̬��Ϊ0������
		//ע�⣺ÿһ��״̬��32λֻ����һλΪ1������ʾ����Ŀؼ���ͬһʱ��
		//		ֻ������һ����ť���£�
		//static UINT								m_groupState[DC_MAX_GROUP];

		//��ǰҳ��
		CDrawPage*								m_currPage;
		ANIMATION_MODEL							m_Animation;

		//��ǰ���ڴ����¼���ҳ��
		CDrawPage*								m_activePage;

		//ҳ������
		int PageCount;

		//�������
		//�ڱ���ʱ����������ǲ���Ҫд���ļ��ģ�����ȡ��ʱ��Ҫ��ʱ����
		CCtrlGroups								m_groups;
		int maxGroupNum;

		//Ŀ���ַIP
		const char*									m_csHostIp;
		Avtronsys::DrawTexture m_hostlinkDT[3];
		Avtronsys::DrawTexture m_mainDT;
		Avtronsys::PlaySound * Allplaysound;
		Avtronsys::SoundHandler* mSoundHandler[2];

		//WIFI�ȵ�
		const char*									m_csWifiAp;
		android_app * mapp;
		friend class CDrawControl;
	};
}



