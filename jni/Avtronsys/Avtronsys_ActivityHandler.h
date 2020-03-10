/**************************************
 * 	文件名	：Avtronsys_ActivityHandler.h
 *	作用		：Activity的基类
 *	作者		：刘亚林
 *	创建时间	：2012/09/24
 *	最后修改	：刘亚林	 2012/09/25
 *	修改说明	: 创建该文件
 *	遗留说明	 ：暂无
 ***************************************/
#ifndef _AVTRONSYS_TYPEDEF_H
#define	_AVTRONSYS_TYPEDEF_H
#include "Avtronsys_TypeDef.h"
#endif

namespace Avtronsys
{

	class ActivityHandler
	{
	public:
		virtual ~ActivityHandler() {};	//析构函数
		virtual Avtronsys::statedef onActivate()=0;	//窗体的获得焦点并且可用
		virtual void onDesActivate()=0;	//暂停或显示窗口失去焦点或被摧毁。
		virtual Avtronsys::statedef onStep()=0;		//没有事件调用发生的时候可发生

		//每一个事件都有一个生命周期下面是定义这些生命周期的函数
		virtual void onStart(){};	//开始
		virtual void onResume(){};	//重新开始
		virtual void onPause(){};	//暂停
		virtual void onStop(){};	//停止
		virtual void onDestroy(){};	//摧毁

		virtual void onSaveState(void** pData,size_t* pSize){};	//保存状态
		virtual void onConfigurationChanged(){};					//配置改变
		virtual void onLowMemory(){};								//低内存的时候

		//活动窗体
		virtual void onCreateWindow(){};	//窗体的创建
		virtual void onDestroyWindow(){};	//窗体的摧毁
		virtual void onGainFocus(){};		//添加/获得焦点
		virtual void onLostFocus(){};		//移除/失去焦点
		virtual void onResized(){};			//window改变大小
		//内容改变
		virtual void onRDraw(){};				//重绘
		virtual void onRRECT(){};				//矩形内容改变

	};

}
