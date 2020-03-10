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
		//��ʼʹ��PlaySound��  �˺���ֻ��Ҫ����һ��
		bool start();
		//ֹͣʹ��PlaySound��
		bool stop();
		//��ͣ���ڲ��ŵ�����
		bool puse();
		//�����������ڲ��ŵ�����
		void play();
		//����ָ����������Դ
		//����SoundHandler�е�������Դ
		void P_play(SoundHandler* pSoundHandler);
		//�������
		SoundHandler* registerSound(const char* path,bool isAsset);
	public:

	};
}
