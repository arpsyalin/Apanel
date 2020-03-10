
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
        const char* getPath();	//���·��
        statedef load();		//������Դ
        statedef unload();		//ж����Դ
	private:
	        friend class PlaySound;
    private:
        ResourceHandler mResource;	//��Դ������
        uint8_t* mBuffer;			//��Դ����
        off_t mLength;				//��Դ����
    };
}
