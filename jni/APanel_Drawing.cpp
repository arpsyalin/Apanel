
#ifndef _APANEL_DRAWING_H
#define _APANEL_DRAWING_H
#include "APanel_Drawing.h"
#endif

#ifndef _SYSTEM_GL_H
#define _SYSTEM_GL_H
#include <GLES/gl.h>
#endif
#ifndef _SYSTEM_GLEXT_H
#define _SYSTEM_GLEXT_H
#include <GLES/glext.h>
#endif

#include "Avtronsys/Avtronsys_Log.h"

#ifndef _APANEL_XMLHELPER_H
#define _APANEL_XMLHELPER_H
#include "APanel_XMLHelper.h"
#endif

#include <unistd.h>
namespace APanel
{
		bool ismainok;
		float pbDisplayH=1024.00;//初始给他1024
		Drawing::Drawing(android_app* papp,CPanelManage * pCPanelManage,Avtronsys::AvtronsysEGLDisplay* pAvtronsysEGLDisplay)
		:mapp(papp),mCPanelManage(pCPanelManage),mAvtronsysEGLDisplay(pAvtronsysEGLDisplay)
		{

		}

		void* Drawing::LogoShow(void* pDrawing)
		{
			ismainok = false;
			Drawing* mDrawing = (Drawing*)pDrawing;
			mDrawing->RDraw();
			sleep(3);
			ismainok = true;
			return (void*)0;
		}

		void Drawing::mainshow()
		{
			pthread_t mainid;
			pthread_t showmain;
			int ret;
			ret=pthread_create(&mainid,NULL,LogoShow,this);
			if(ret!=0)
			{
				Avtronsys::Log::error("thread error!!!!!");
			}
			pthread_join(showmain,NULL);
		}
		void Drawing::RDraw()
		{
			mCPanelManage->RDraw();
		}

		void Drawing::RDraw2()
		{
			mCPanelManage->RDraw2();
		}


		//进行图片初始加载
		//xml解析外加图片加载初始化 请只运行一次 .
		void Drawing::XMLHelperStart()
		{
			GLuint tvid;
			mCPanelManage->setRDraw2(mAvtronsysEGLDisplay);
			mCPanelManage->setAndroid_app(mapp);
			tvid=mCPanelManage->showMain();
			mainshow();
			Draw();
			//glDeleteTextures(1, &tvid);
			//解析XML
			//APanel::XMLHelper::XMLHelper lXMLHelper(mCPanelManage
			//		,"/mnt/sdcard/iavn/ivp.avn","/mnt/sdcard/");
			APanel::XMLHelper::XMLHelper lXMLHelper(mCPanelManage
								,"/mnt/sdcard/android_avn/ivp.avn","/mnt/sdcard/");
			lXMLHelper.XMLParse();

		}

		bool Drawing::PanelManageInit(bool ismany)
		{
			return mCPanelManage->Serialize(ismany);
		}

		//
		void Drawing::TouchSet(TouchType ptype,float x,float y)
		{
			POINT ClickPoint;
			ClickPoint.x = x;
			ClickPoint.y = y;
			//Avtronsys::Log::info("click:%f,%f",x,y);
			//在这里将消息传递给CPanelManage在由CPanelManage分发
			switch(ptype)
			{
			case mTouchDown:
				mOldClickPoint = ClickPoint;
				mCPanelManage->PostButtonMessage(true,ClickPoint);
				goto thisDraw;
				break;
			case mTouchUp:
				mCPanelManage->PostButtonMessage(false,ClickPoint);
				goto thisDraw;
				break;
			case mTouchMove:
				//移动的时候
				//暂时什么都不做
				break;
			case mTouchOutside:
				//暂时什么都不做
				break;
			}
thisDraw:
		Draw();
		}

		void Drawing:: Init()
		{
			glEnable(GL_TEXTURE_2D);
			glShadeModel(GL_FLAT);
			//glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glEnable(GL_BLEND);

		}
		//这个函数虽然在这个程序中只会在创建的时候需要被调用
		//但是如果需要加上认为的改变大小那这个就必须调用了！
		void Drawing:: Resize(float pWidth,float pHeight)
		{
			pbDisplayH = pHeight;
			glViewport(0, 0,pWidth, pHeight);
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glOrthof(0.0,pWidth,0.0,pHeight,6,-10);
			glMatrixMode(GL_MODELVIEW);
		}

		void Drawing:: Draw()
		{
			glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
			if(ismainok)
			{
				//glClearColor(1.0,1.0,1.0,1.0);
				mCPanelManage->Work();
			}
			else
			{
				mCPanelManage->drawMain();
			}
			mAvtronsysEGLDisplay->EGLUpdate();
		}
}
