#ifndef _AVTRONSYS_SOUNDHANDLER_H
#define _AVTRONSYS_SOUNDHANDLER_H
#include "Avtronsys_SoundHandler.h"
#endif

#ifndef _AVTRONSYS_LOG_H
#define _AVTRONSYS_LOG_H
#include "Avtronsys_Log.h"
#endif

namespace Avtronsys
{
	SoundHandler::SoundHandler(android_app* pApplication, const char* pPath,bool isAsset) :
		mResource(pApplication, pPath,isAsset),
		mBuffer(NULL), mLength(0) {
	}

	const char* SoundHandler::getPath() {
		return mResource.getPath();
	}

	statedef SoundHandler::load() {
		statedef lRes;

		// Opens sound file.
		if (mResource.open() != state_Succse) {
			return state_Fail;
		}

		// Reads sound file.
		mLength = mResource.getLength();
		mBuffer = new uint8_t[mLength];
		lRes = mResource.read(mBuffer, mLength);
		mResource.close();

		if (lRes != state_Succse) {
			Log::error("Error while reading PCM sound.");
			return state_Fail;
		} else {
			return state_Succse;
		}
	}

	statedef SoundHandler::unload() {
		delete[] mBuffer;
		mBuffer = NULL; mLength = 0;

		return state_Succse;
	}
}
