/**************************************
 * 	文件名	：Avtronsys_ActivityHandler.h
 *	作用		：Activity的基类的继承类实现
 *	作者		：刘亚林
 *	创建时间	：2012/09/25
 *	最后修改	：刘亚林	 2012/09/25
 *	修改说明	: 创建该文件
 *	遗留说明	 ：暂无
 ***************************************/
#ifndef _APANEL_AVTIVITYHANDLER_H
#define _APANEL_AVTIVITYHANDLER_H
#include "APanel_ActivityHandler.h"
#endif

#ifndef _AVTRONSYS_LOG_H
#define _AVTRONSYS_LOG_H
#include "Avtronsys/Avtronsys_Log.h"
#endif

#ifndef _SYSTEM_GL_H
#define _SYSTEM_GL_H
#include <GLES/gl.h>
#endif

#ifndef _SYSTEM_GLEXT_H
#define _SYSTEM_GLEXT_H
#include <GLES/glext.h>
#endif


#include "test.h"
#include "APanel_GetMac.h"
//#include "APanel_linuxping.h"
#include "APanel_AndroidPing.h"
#include <unistd.h>

extern pid_t pid;
extern int sockfd;
extern struct sockaddr_in dest_addr;
namespace APanel
{
	short impoWerstate;
	bool minitend;
	APanelActivityHandler::APanelActivityHandler(Avtronsys::Context *pContext,APanel::Drawing*pDrawing,APanel::Exit* pExit,android_app* pApplication)
	:mAvtronsysEGLDisplay(pContext->pAvtronsysEGLDisplay)
	,mInputHandler(pContext->pInputHandler)
	,mDrawing(pDrawing)
	,mExit(pExit)
	,mApplication(pApplication)
	{
		Avtronsys::Log::info("APanelHandler");
	}

	APanelActivityHandler::~APanelActivityHandler()
	{
		Avtronsys::Log::info("~APanelHandler");
	}

	//窗体的获得焦点并且可用
	Avtronsys::statedef APanelActivityHandler::onActivate()
	{
//		mAvtronsysEGLDisplay->EGLUpdate();
		Avtronsys::Log::info("onActivate");
		return Avtronsys::state_Succse;
	}


	//暂停或显示窗口失去焦点或被摧毁。
	void APanelActivityHandler::onDesActivate()
	{
		Avtronsys::Log::info("onDesActivate");
	}

	//没有事件调用发生的时候可发生
	Avtronsys::statedef APanelActivityHandler::onStep()
	{
//		Avtronsys::Log::info("onStep");
		return Avtronsys::state_Succse;
	}

	//开始
	void APanelActivityHandler::onStart()
	{
		Avtronsys::Log::info("onStart");
	}

	//重新开始
	void APanelActivityHandler:: onResume()
	{
		Avtronsys::Log::info("onResume");
	}

	//暂停
	void APanelActivityHandler:: onPause()
	{
		Avtronsys::Log::info("onResume");
	}

	//停止
	void APanelActivityHandler:: onStop()
	{
		Avtronsys::Log::info("onStop");
	}

	//摧毁
	void APanelActivityHandler:: onDestroy()
	{
		//mAvtronsysEGLDisplay->EGLDest();
		Avtronsys::Log::info("onDestroy");
	}

	//保存状态
	void APanelActivityHandler:: onSaveState(void** pData,size_t* pSize)
	{
		//mApplication->savedState = pData;
		//mApplication->savedStateSize = *pSize;
		Avtronsys::Log::info("onResume");
	}

	//配置改变
	void APanelActivityHandler:: onConfigurationChanged()
	{
		Avtronsys::Log::info("onConfigurationChanged");
	}

	//低内存的时候
	void APanelActivityHandler:: onLowMemory()
	{
		Avtronsys::Log::info("onLowMemory");
	}

	void* APanelActivityHandler::TestWeblinkThread(void* pDrawing)
	{
		APanel::Drawing* mDrawing =(APanel::Drawing*)pDrawing;
		LAN_JOINNUM_FRAME var_SendFrame;
		LAN_JOINNUM_FRAME tmp;
		//创建socket、绑定端口
		int sd = -1;
		socklen_t strsize;
		size_t vsfsize;
		int err;

		var_SendFrame.bFrameHead = 0xAB;
		var_SendFrame.joinNum.bJoinNum[1] = 2;
		var_SendFrame.joinNum.bJoinNum[0] = 3;
		var_SendFrame.bSingnalType = 0;
		var_SendFrame.bSingnalLen = 0;


		sockaddr_in addr_org;
		sd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); //  以UDP方式创建socket
		addr_org.sin_family = AF_INET;
		addr_org.sin_addr.s_addr = inet_addr(hostip);
		addr_org.sin_port = htons(2010);
		strsize=sizeof(struct sockaddr_in);
		vsfsize = sizeof(var_SendFrame);
		bind(sd, (struct sockaddr *) &(addr_org),strsize ); // 绑定IP和端口
		//发送数据
		sockaddr_in addr_dst;
		//弹起事件
		var_SendFrame.bDownEvent = '0';

		int sd1=-1;
		sd1 = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); //  以UDP方式创建socket
		bind(sd, (struct sockaddr *) &(addr_org),strsize ); // 绑定IP和端口
		//发送数据
		sockaddr_in addr_dst1;
		addr_dst1.sin_family = AF_INET;
		addr_dst1.sin_addr.s_addr = inet_addr(severIP);
		addr_dst1.sin_port = htons(2010);

		while(1)
		{
			Avtronsys::Log::info("11111111111113212,%d",minitend);
			if(minitend)
			{

				err=sendto(sd1, (char*)&var_SendFrame,vsfsize , 0, (struct sockaddr *)&(addr_dst1),strsize);  // 发送DataBuff中的数据
				Avtronsys::Log::info("11111111121312312312312:%d",vsfsize);
				sleep(1);
				//MSG_DONTWAIT
				err=recvfrom(sd,(char*)&tmp, vsfsize, MSG_DONTWAIT, (struct sockaddr *)&(addr_dst), &strsize);
				//如果正确接收返回接收到的字节数，失败返回0.
				if(err>0)
				{
					if(tmp.bFrameHead==0xA5)
					{
						impoWerstate = 2;
						mDrawing->RDraw();
					}
					else
					{
						impoWerstate = 1;
						mDrawing->RDraw();
					}
				}
				else
				{
					impoWerstate = 1;
					mDrawing->RDraw();
				}
				memset((char*)&tmp,0,sizeof(LAN_JOINNUM_FRAME));
				usleep(500000);
				//close(sd1);
			}
			usleep(500000);
		}
		shutdown(sd,8);
		shutdown(sd1,8);
		close(sd1);
		close(sd);
		return (void*)0;
	}
	static  bool ismany=false;
	//活动窗体
	//窗体的创建
	void APanelActivityHandler:: onCreateWindow()
	{
		//sleep(1);	///在这里暂停个1秒的时间先
		minitend =false;
		mAvtronsysEGLDisplay->EGLInit();
		mDrawing->Init();
		Avtronsys::Log::info("w:%d,h:%d",mAvtronsysEGLDisplay->getWidth(),mAvtronsysEGLDisplay->getHeight());
		if(!ismany)
		{
			mDrawing->Resize(mAvtronsysEGLDisplay->getWidth(),mAvtronsysEGLDisplay->getHeight());
			//目前程序是不会进入第2次的
			//如果是第2次initEGL就不用去解析了。
			mDrawing->XMLHelperStart();

			int result;
			result=compare();
			switch(result)
			{
			case 0:
			case 2:
				impoWerstate = 0;	//未授权
				break;
			case 1:
				impoWerstate = 1;	//已授权
				break;
			default:
				ANativeActivity_finish(mApplication->activity);
			}

			if(impoWerstate == 1)
			{
				pthread_t weblinkid;
				pthread_t id;
				int ret;
				ret=pthread_create(&id,NULL,TestWeblinkThread,mDrawing);
				if(ret!=0)
				{
					Avtronsys::Log::error("thread error!!!!!");
				}
				pthread_join(weblinkid,NULL);

			}
		}

	Avtronsys::Log::info("true1111::%d",ismainok);
	bool isInitTure = mDrawing->PanelManageInit(ismany);	//如果返回false可直接调用程序结束
	Avtronsys::Log::info("true2222::%d",ismainok);
	if(!ismainok)
	{
		while(1)
		{
			Avtronsys::Log::info("true1::%d",ismainok);
			if(ismainok)
			{
				Avtronsys::Log::info("true2::%d",ismainok);
				break;
			}
			sleep(1);
		}
	}
	ismany=true;
	minitend = true;
	}

	//窗体的摧毁
	void APanelActivityHandler:: onDestroyWindow()
	{
		//如果不退出
		//mExit->ExitActivity();
		//ANativeActivity_finish(mApplication->activity);
		mAvtronsysEGLDisplay->EGLDest();
		Avtronsys::Log::info("onDestroyWindow");
	}

	//添加/获得焦点
	void APanelActivityHandler:: onGainFocus()
	{
		mDrawing->Draw();
		Avtronsys::Log::info("onGainFocus");
	}

	//移除/失去焦点
	void APanelActivityHandler:: onLostFocus()
	{
		Avtronsys::Log::info("onLostFocus");
	}
	void APanelActivityHandler::onResized()
	{
		mDrawing->Resize(mAvtronsysEGLDisplay->getWidth(),mAvtronsysEGLDisplay->getHeight());
		Avtronsys::Log::info("onResized");
	}

	void APanelActivityHandler:: onRDraw()
	{
		Avtronsys::Log::info("onRDraw");
		mDrawing->Draw();
	};//重绘
	void APanelActivityHandler:: onRRECT()
	{

	};				//矩形内容改变
}
