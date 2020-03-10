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

        statedef start();
        void stop();

        statedef playMusic(const char* pPath,bool isAsset);
        void stopMusic();
        void playSound(SoundHandler* pSound);
        statedef startSoundPlayer();
    private:
        android_app* mApplication;

        // OpenSL ES engine.
        SLObjectItf mEngineObj; SLEngineItf mEngine;
        // Audio output.
        SLObjectItf mOutputMixObj;

        // Background music player.
        SLObjectItf mMusicPlayerObj; SLPlayItf mMusicPlayer;
        SLSeekItf mMusicPlayerSeek;
        // Sound player.
	   SLObjectItf mPlayerObj; SLPlayItf mPlayer;
	   SLBufferQueueItf mPlayerQueue;

	};
}
