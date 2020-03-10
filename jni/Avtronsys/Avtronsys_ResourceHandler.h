/**************************************
 * 	文件名	：Avtronsys_EGLDisplay.h
 *	作用		：基于资源文件访问的API
 *	作者		：刘亚林
 *	创建时间	：2012/09/25
 *	最后修改	：刘亚林	 2012/09/25
 *	修改说明	: 添加该文件并创建GLTextureID类
 *	遗留说明	 ：暂无
 ***************************************/
#ifndef _SYSTEM_GL_H
#define _SYSTEM_GL_H
#include <GLES/gl.h>
#endif

#ifndef _SYSTEM_GLEXT_H
#define _SYSTEM_GLEXT_H
#include <GLES/glext.h>
#endif

#ifndef _SYSTEM_PNG_H
#define _SYSTEM_PNG_H
#include <libpng/png.h>
#endif

#ifndef _AVTRONSYS_TYPEDEF_H
#define _AVTRONSYS_TYPEDEF_H
#include "Avtronsys_TypeDef.h"
#endif

#ifndef _SYSTEM_NATIVE_APP_GLUE_H
#define _SYSTEM_NATIVE_APP_GLUE_H
#include <android_native_app_glue.h>
#endif

#ifndef _SYSTEM_FSTREAM_H
#define _SYSTEM_FSTREAM_H
#include <fstream>
#endif

namespace Avtronsys
{
	struct ResourceDescriptor {
		int32_t mDescriptor;
		off_t mStart;
		off_t mLength;
	};

	class ResourceHandler
	{
	public:
		ResourceHandler(const char* pPath,bool isAsset);
		ResourceHandler(android_app* pApplication, const char* pPath,bool isAsset);

		const char* getPath();	//获得路径

		statedef open();		//打开资源
		void close();			//关闭资源
		statedef read(void* pBuffer, size_t pCount);	//读取内容
        off_t getLength();		//获得长度
        ResourceDescriptor descript();	//只用在声音存储在Assets文件夹资源的时候
	private:
		const char* mPath;	//文件路径
		//文件在自定义的位置时候用到
		std::ifstream mInputStream;
		char* mBuffer;
		//文件在Assets文件夹
		AAssetManager* mAssetManager;
		AAsset* mAsset;
		bool misAsset;//文件是否在Assets文件夹
	};
}
