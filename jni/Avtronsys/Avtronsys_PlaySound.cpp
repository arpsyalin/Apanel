#ifndef _AVTRONSYS_PLAYSOUND_H
#define _AVTRONSYS_PLAYSOUND_H
#include "Avtronsys_PlaySound.h"
#endif

#ifndef _AVTRONSYS_LOG_H
#define _AVTRONSYS_LOG_H
#include "Avtronsys_Log.h"
#endif

namespace Avtronsys
{
	PlaySound::PlaySound(android_app* pApplication) :
        mApplication(pApplication),
        mEngineObj(NULL), mEngine(NULL),
        mOutputMixObj(NULL),
        mMusicPlayerObj(NULL), mMusicPlayer(NULL), mMusicPlayerSeek(NULL)
    {
    }

    PlaySound::~PlaySound() {
    }

    statedef PlaySound::start() {
        SLresult lRes;
        const SLuint32      lEngineMixIIDCount = 1;
        const SLInterfaceID lEngineMixIIDs[]   = {SL_IID_ENGINE};
        const SLboolean     lEngineMixReqs[]   = {SL_BOOLEAN_TRUE};
        const SLuint32      lOutputMixIIDCount = 0;
        const SLInterfaceID lOutputMixIIDs[]   = {};
        const SLboolean     lOutputMixReqs[]   = {};

        lRes = slCreateEngine(&mEngineObj, 0, NULL,
            lEngineMixIIDCount, lEngineMixIIDs, lEngineMixReqs);
        if (lRes != SL_RESULT_SUCCESS) goto ERROR;
        lRes = (*mEngineObj)->Realize(mEngineObj,SL_BOOLEAN_FALSE);
        if (lRes != SL_RESULT_SUCCESS) goto ERROR;
        lRes = (*mEngineObj)->GetInterface(mEngineObj, SL_IID_ENGINE,
            &mEngine);
        if (lRes != SL_RESULT_SUCCESS) goto ERROR;

        lRes = (*mEngine)->CreateOutputMix(mEngine, &mOutputMixObj,
            lOutputMixIIDCount, lOutputMixIIDs, lOutputMixReqs);
        lRes = (*mOutputMixObj)->Realize(mOutputMixObj,
            SL_BOOLEAN_FALSE);

        return state_Succse;

    ERROR:
        Avtronsys::Log::error("Error while starting PlaySound");
        stop();
        return state_Fail;
    }

    void PlaySound::stop() {
        stopMusic();

        if (mOutputMixObj != NULL) {
            (*mOutputMixObj)->Destroy(mOutputMixObj);
            mOutputMixObj = NULL;
        }
        if (mEngineObj != NULL) {
            (*mEngineObj)->Destroy(mEngineObj);
            mEngineObj = NULL; mEngine = NULL;
        }
    }

    statedef PlaySound::startSoundPlayer()
    {
           Log::info("Starting sound player.");
           SLresult lRes;

           // Set-up sound audio source.
           SLDataLocator_AndroidSimpleBufferQueue lDataLocatorIn;
           lDataLocatorIn.locatorType =
               SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE;
           // At most one buffer in the queue.
           lDataLocatorIn.numBuffers = 1;

           SLDataFormat_PCM lDataFormat;
           lDataFormat.formatType = SL_DATAFORMAT_PCM;
           lDataFormat.numChannels = 1; // Mono sound.
           lDataFormat.samplesPerSec = SL_SAMPLINGRATE_44_1;
           lDataFormat.bitsPerSample = SL_PCMSAMPLEFORMAT_FIXED_16;
           lDataFormat.containerSize = SL_PCMSAMPLEFORMAT_FIXED_16;
           lDataFormat.channelMask = SL_SPEAKER_FRONT_CENTER;
           lDataFormat.endianness = SL_BYTEORDER_LITTLEENDIAN;

           SLDataSource lDataSource;
           lDataSource.pLocator = &lDataLocatorIn;
           lDataSource.pFormat = &lDataFormat;

           SLDataLocator_OutputMix lDataLocatorOut;
           lDataLocatorOut.locatorType = SL_DATALOCATOR_OUTPUTMIX;
           lDataLocatorOut.outputMix = mOutputMixObj;

           SLDataSink lDataSink;
           lDataSink.pLocator = &lDataLocatorOut;
           lDataSink.pFormat = NULL;

           // Creates the sounds player and retrieves its interfaces.
           const SLuint32 lSoundPlayerIIDCount = 2;
           const SLInterfaceID lSoundPlayerIIDs[] =
               { SL_IID_PLAY, SL_IID_BUFFERQUEUE };
           const SLboolean lSoundPlayerReqs[] =
               { SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE };

           lRes = (*mEngine)->CreateAudioPlayer(mEngine, &mPlayerObj,
               &lDataSource, &lDataSink, lSoundPlayerIIDCount,
               lSoundPlayerIIDs, lSoundPlayerReqs);
           if (lRes != SL_RESULT_SUCCESS) goto ERROR;
           lRes = (*mPlayerObj)->Realize(mPlayerObj, SL_BOOLEAN_FALSE);
           if (lRes != SL_RESULT_SUCCESS) goto ERROR;

           lRes = (*mPlayerObj)->GetInterface(mPlayerObj, SL_IID_PLAY,
               &mPlayer);
           if (lRes != SL_RESULT_SUCCESS) goto ERROR;
           lRes = (*mPlayerObj)->GetInterface(mPlayerObj,
               SL_IID_BUFFERQUEUE, &mPlayerQueue);
           if (lRes != SL_RESULT_SUCCESS) goto ERROR;

           // Starts the sound player. Nothing can be heard while the
           // sound queue remains empty.
           lRes = (*mPlayer)->SetPlayState(mPlayer,
               SL_PLAYSTATE_PLAYING);
           if (lRes != SL_RESULT_SUCCESS) goto ERROR;

           return state_Succse;

       ERROR:
           Log::error("Error while starting SoundPlayer");
           return state_Fail;
       }


    statedef PlaySound::playMusic(const char* pPath,bool isAsset) {
        SLresult lRes;

        SLDataLocator_URI lDataLocatorIn1;
        SLDataLocator_AndroidFD lDataLocatorIn2;
        if(isAsset)
        {
        	ResourceHandler lResourceHandler(mApplication, pPath,isAsset);
            ResourceDescriptor lDescriptor = lResourceHandler.descript();
            if (lDescriptor.mDescriptor < 0)
            {
                return state_Fail;
            }


            lDataLocatorIn2.locatorType = SL_DATALOCATOR_ANDROIDFD;
            lDataLocatorIn2.fd          = lDescriptor.mDescriptor;
            lDataLocatorIn2.offset      = lDescriptor.mStart;
            lDataLocatorIn2.length      = lDescriptor.mLength;
        }
        else
        {
			std::string lPath = std::string("file://") + pPath;
			lDataLocatorIn1.locatorType = SL_DATALOCATOR_URI;
			lDataLocatorIn1.URI = (SLchar*) lPath.c_str();
        }

        SLDataFormat_MIME lDataFormat;
        lDataFormat.formatType    = SL_DATAFORMAT_MIME;
        lDataFormat.mimeType      = NULL;
        lDataFormat.containerType = SL_CONTAINERTYPE_UNSPECIFIED;

        SLDataSource lDataSource;
        if(isAsset)
        {
        	lDataSource.pLocator = &lDataLocatorIn2;
        }
        else
        {
        	lDataSource.pLocator = &lDataLocatorIn1;
        }
        lDataSource.pFormat  = &lDataFormat;

        SLDataLocator_OutputMix lDataLocatorOut;
        lDataLocatorOut.locatorType = SL_DATALOCATOR_OUTPUTMIX;
        lDataLocatorOut.outputMix   = mOutputMixObj;

        SLDataSink lDataSink;
        lDataSink.pLocator = &lDataLocatorOut;
        lDataSink.pFormat  = NULL;

        // Creates Music player and retrieves its interfaces.
        const SLuint32 lMuscPlayerIIDCount = 2;
        const SLInterfaceID lMusicPlayerIIDs[] =
            { SL_IID_PLAY, SL_IID_SEEK };
        const SLboolean lMusicPlayerReqs[] =
            { SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE };

        lRes = (*mEngine)->CreateAudioPlayer(mEngine,
            &mMusicPlayerObj, &lDataSource, &lDataSink,
            lMuscPlayerIIDCount, lMusicPlayerIIDs, lMusicPlayerReqs);
        if (lRes != SL_RESULT_SUCCESS) goto ERROR;
        lRes = (*mMusicPlayerObj)->Realize(mMusicPlayerObj,
            SL_BOOLEAN_FALSE);
        if (lRes != SL_RESULT_SUCCESS) goto ERROR;

        lRes = (*mMusicPlayerObj)->GetInterface(mMusicPlayerObj,
            SL_IID_PLAY, &mMusicPlayer);
        if (lRes != SL_RESULT_SUCCESS) goto ERROR;
        lRes = (*mMusicPlayerObj)->GetInterface(mMusicPlayerObj,
            SL_IID_SEEK, &mMusicPlayerSeek);
        if (lRes != SL_RESULT_SUCCESS) goto ERROR;

        // Enables looping and starts playing.

        //SL_BOOLEAN_FALSE SL_BOOLEAN_TRUE
        lRes = (*mMusicPlayerSeek)->SetLoop(mMusicPlayerSeek,
            SL_BOOLEAN_FALSE, 0, SL_TIME_UNKNOWN);
        if (lRes != SL_RESULT_SUCCESS) goto ERROR;
        lRes = (*mMusicPlayer)->SetPlayState(mMusicPlayer,
            SL_PLAYSTATE_PLAYING);
        if (lRes != SL_RESULT_SUCCESS) goto ERROR;

        return state_Succse;

    ERROR:
        return state_Fail;
    }

    void PlaySound::stopMusic() {
        if (mMusicPlayer != NULL) {
            SLuint32 lMusicPlayerState;
            (*mMusicPlayerObj)->GetState(mMusicPlayerObj,
                &lMusicPlayerState);
            if (lMusicPlayerState == SL_OBJECT_STATE_REALIZED) {
                (*mMusicPlayer)->SetPlayState(mMusicPlayer,
                    SL_PLAYSTATE_PAUSED);
                (*mMusicPlayerObj)->Destroy(mMusicPlayerObj);
                mMusicPlayerObj = NULL;
                mMusicPlayer = NULL; mMusicPlayerSeek = NULL;
            }
        }
    }

    void PlaySound::playSound(SoundHandler* pSound)
    {
           SLresult lRes;
           SLuint32 lPlayerState;
           (*mPlayerObj)->GetState(mPlayerObj, &lPlayerState);
           if (lPlayerState == SL_OBJECT_STATE_REALIZED) {
               int16_t* lBuffer = (int16_t*) pSound->mBuffer;
               off_t    lLength = pSound->mLength;
               // Removes any sound from the queue.
               lRes = (*mPlayerQueue)->Clear(mPlayerQueue);
               if (lRes != SL_RESULT_SUCCESS) goto ERROR;

               // Plays the new sound.
               lRes = (*mPlayerQueue)->Enqueue(mPlayerQueue, lBuffer,
                   lLength);
               if (lRes != SL_RESULT_SUCCESS) goto ERROR;
           }
           return;

       ERROR:
           Avtronsys::Log::error("Error trying to play sound");
       }

}
