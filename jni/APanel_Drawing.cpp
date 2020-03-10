
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
		float pbDisplayH=1024.00;//��ʼ����1024
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


		//����ͼƬ��ʼ����
		//xml�������ͼƬ���س�ʼ�� ��ֻ����һ�� .
		void Drawing::XMLHelperStart()
		{
			GLuint tvid;
			mCPanelManage->setRDraw2(mAvtronsysEGLDisplay);
			mCPanelManage->setAndroid_app(mapp);
			tvid=mCPanelManage->showMain();
			mainshow();
			Draw();
			//glDeleteTextures(1, &tvid);
			//����XML
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
			//�����ｫ��Ϣ���ݸ�CPanelManage����CPanelManage�ַ�
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
				//�ƶ���ʱ��
				//��ʱʲô������
				break;
			case mTouchOutside:
				//��ʱʲô������
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
		//���������Ȼ�����������ֻ���ڴ�����ʱ����Ҫ������
		//���������Ҫ������Ϊ�ĸı��С������ͱ�������ˣ�
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
