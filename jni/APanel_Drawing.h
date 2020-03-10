#ifndef _AVTRONSYS_EGLDISPLAY_H
#define _AVTRONSYS_EGLDISPLAY_H
#include "Avtronsys/Avtronsys_EGLDisplay.h"
#endif

#ifndef _APANEL_CDRAWCONTROL_H
#define _APANEL_CDRAWCONTROL_H
#include "APanel_CPanelManage.h"
#endif


#ifndef _APANEL_TYPE_H
#define _APANEL_TYPE_H
#include "APanel_Type.h"
#endif


namespace APanel
{
	class Drawing
	{
	public:
		Drawing(android_app* papp,CPanelManage* pCPanelManage,Avtronsys::AvtronsysEGLDisplay* pAvtronsysEGLDisplay);
	public:
		bool PanelManageInit(bool ismany);
		void XMLHelperStart();//xml解析开始
		void TouchSet(TouchType ptype,float x,float y); //鼠标按下属性修改
		void Init();
		void Resize(float pWidth,float pHeight);
		void Draw();
		void RDraw();
		void RDraw2();
		static void* LogoShow(void*);
		void mainshow();
	protected:
		CPanelManage* mCPanelManage;							//绘制的CPanelManage类(指定绘制的东西)
		Avtronsys::AvtronsysEGLDisplay* mAvtronsysEGLDisplay;	//绘制的EGL(指定绘制的地方)
		POINT mOldClickPoint;		//之前点击的Point
		android_app* mapp;
		friend class APanelActivityHandler;	//友元类
	};
}
