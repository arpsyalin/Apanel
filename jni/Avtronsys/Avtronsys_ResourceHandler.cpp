/*******************************************
 * 	文件名		：Avtronsys_EGLDisplay.h
 *	作用		：基于资源文件访问API的实现
 *	作者		：刘亚林
 *	创建时间	：2012/09/25
 *	最后修改	：刘亚林	 2012/09/25
 *	修改说明	：增加GLTextureID类的实现
 *	遗留说明	：暂无
 *******************************************/
#ifndef _AVTRONSYS_RESOURCEHANDLER_H
#define _AVTRONSYS_RESOURCEHANDLER_H
#include "Avtronsys_ResourceHandler.h"
#endif

#ifndef _AVTRONSYS_LOG_H
#define _AVTRONSYS_LOG_H
#include "Avtronsys_Log.h"
#endif

#ifndef _SYSTEM_STAT_H
#define _SYSTEM_STAT_H
#include <sys/stat.h>
#endif

namespace Avtronsys
{
	ResourceHandler::ResourceHandler(const char* pPath,bool isAsset):
	mPath(pPath), mInputStream(), mBuffer(NULL),
	misAsset(isAsset)
	{
	}

	ResourceHandler::ResourceHandler(android_app* pApplication, const char* pPath,bool isAsset):
        mPath(pPath), mInputStream(), mBuffer(NULL),
        misAsset(isAsset),mAssetManager(pApplication->activity->assetManager),
        mAsset(NULL)
    {

    }
	//打开文件
    statedef ResourceHandler::open() {
    	if(misAsset)
    	{
    		mAsset = AAssetManager_open(mAssetManager, mPath,
    		                                    AASSET_MODE_UNKNOWN);
			return (mAsset != NULL) ? state_Succse : state_Fail;
    	}
    	else
    	{
			mInputStream.open(mPath, std::ios::in | std::ios::binary);
			return mInputStream ? state_Succse : state_Fail;
    	}
    }

    //关闭文件
    void ResourceHandler::close() {
    	if(misAsset)
    	{
    		if (mAsset != NULL)
    		{
				AAsset_close(mAsset);
				mAsset = NULL;
			}
    	}
    	else
    	{
			mInputStream.close();
			delete[] mBuffer; mBuffer = NULL;

    	}
    }
    //读取数据
    statedef ResourceHandler::read(void* pBuffer, size_t pCount) {
    	if(misAsset)
    	{
    		int32_t lReadCount = AAsset_read(mAsset, pBuffer, pCount);
			return (lReadCount == pCount) ? state_Succse : state_Fail;
    	}
    	else
    	{
			mInputStream.read((char*)pBuffer, pCount);
			return (!mInputStream.fail()) ? state_Succse : state_Fail;
    	}
    }
    //获得路径
    const char* ResourceHandler::getPath() {
        return mPath;
    }

    //获得文件长度
    off_t ResourceHandler::getLength()
    {
    	if(misAsset)
    	{
    		 return AAsset_getLength(mAsset);
    	}
    	else
    	{
			struct stat filestatus;
			if (stat(mPath, &filestatus) >= 0)
			{
				return filestatus.st_size;
			}
			else
			{
				return -1;
			}
    	}
	}

    ResourceDescriptor ResourceHandler::descript() {
	   ResourceDescriptor lDescriptor = { -1, 0, 0 };
	   AAsset* lAsset = AAssetManager_open(mAssetManager, mPath,
										   AASSET_MODE_UNKNOWN);
	   if (lAsset != NULL) {
		   lDescriptor.mDescriptor = AAsset_openFileDescriptor(
			   lAsset, &lDescriptor.mStart, &lDescriptor.mLength);
		   AAsset_close(lAsset);
	   }
	   return lDescriptor;
   }

}
