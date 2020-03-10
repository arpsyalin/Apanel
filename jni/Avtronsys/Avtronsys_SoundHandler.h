
#ifndef _AVTRONSYS_RESOURCEHANDLER_H
#define _AVTRONSYS_RESOURCEHANDLER_H
#include "Avtronsys_ResourceHandler.h"
#endif

#ifndef _AVTRONSYS_TYPEDEF_H
#define _AVTRONSYS_TYPEDEF_H
#include "Avtronsys_TypeDef.h"
#endif

class PlaySound;

namespace Avtronsys
{
    class SoundHandler
    {
    public:
    	SoundHandler(android_app* pApplication, const char* pPath,bool isAsset);
        const char* getPath();	//获得路径
        statedef load();		//加载资源
        statedef unload();		//卸载资源
	private:
	        friend class PlaySound;
    private:
        ResourceHandler mResource;	//资源处理类
        uint8_t* mBuffer;			//资源内容
        off_t mLength;				//资源长度
    };
}
