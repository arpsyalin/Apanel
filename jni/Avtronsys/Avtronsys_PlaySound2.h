#ifndef _AVTRONSYS_SOUNDHANDLER_H
#define _AVTRONSYS_SOUNDHANDLER_H
#include "Avtronsys_SoundHandler.h"
#endif

#ifndef _AVTRONSYS_TYPEDEF_H
#define _AVTRONSYS_TYPEDEF_H
#include "Avtronsys_TypeDef.h"
#endif
#ifndef _SYSTEM_NATIVE_APP_GLUE_H
#define _SYSTEM_NATIVE_APP_GLUE_H
#include <android_native_app_glue.h>
#endif

#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>
#include <SLES/OpenSLES_AndroidConfiguration.h>

namespace Avtronsys
{
	class PlaySound
	{
	public:
		PlaySound(android_app* pApplication);
		~PlaySound();
	public:
		//开始使用PlaySound类  此函数只需要调用一次
		bool start();
		//停止使用PlaySound类
		bool stop();
		//暂停正在播放的声音
		bool puse();
		//继续播放正在播放的声音
		void play();
		//播放指定的声音资源
		//播放SoundHandler中的声音资源
		void P_play(SoundHandler* pSoundHandler);
		//添加声音
		SoundHandler* registerSound(const char* path,bool isAsset);
	public:

	};
}
