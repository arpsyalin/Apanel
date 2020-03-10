/******************************************
**		文件：APanel_CDrawDireButton.h
**		作者：刘亚林
**		时间：12年10月24日
**		最后修改：无
*******************************************/
#ifndef _APANEL_TYPE_H
#define _APANEL_TYPE_H
#include "APanel_Type.h"
#endif

#ifndef _APANEL_CDRAWCHECKBUTTON_H
#define _APANEL_CDRAWCHECKBUTTON_H
#include "APanel_CDrawCheckButton.h"
#endif

#ifndef _SYSTEM_PTHREAD_H
#define _SYSTEM_PTHREAD_H
#include <pthread.h>
#endif

namespace APanel
{
	class CDrawDireButton : public CDrawButton
	{
		//构造，系构函数
	public:
		CDrawDireButton();
		~CDrawDireButton();

		//接口
	public:
		virtual void			OnLButtonDown(bool istrue);
		//左键弹起
		virtual void			OnLButtonUp(bool istrue);
		//序列化
//		virtual bool			Serialize(bool ismany);
		void TimerProc();
		void Rdraw();
		//播放音乐的调用
		void soundplay();
		//播放音乐的线程
		static void *playsound(void* data);
		//属性
	protected:
		UINT					m_nTimeDelay;
		friend class XMLHelper;
		friend class CPanelManage;
	private :
		POINT  downPT;	//按下的pt
		static void *thread_fun(void* data);
	};
}
