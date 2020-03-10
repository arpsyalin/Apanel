/**************************************
 * 	文件名	：Avtronsys_TexTureHandler.h
 *	作用		：基于纹理贴图的API声明
 *	作者		：刘亚林
 *	创建时间	：2012/09/25
 *	最后修改	：刘亚林	 2012/09/25
 *	修改说明	: 添加该文件
 *	遗留说明	 ：暂无
 ***************************************/
#ifndef _AVTRONSYS_RESOURCEHANDLER_H
#define _AVTRONSYS_RESOURCEHANDLER_H
#include "Avtronsys_ResourceHandler.h"
#endif

#ifndef _AVTRONSYS_TYPEDEF_H
#define _AVTRONSYS_TYPEDEF_H
#include "Avtronsys_TypeDef.h"
#endif

#ifndef _SYSTEM_NATIVE_APP_GLUE_H
#define _SYSTEM_NATIVE_APP_GLUE_H
#include <android_native_app_glue.h>
#endif

#ifndef _SYSTEM_GL_H
#define _SYSTEM_GL_H
#include <GLES/gl.h>
#endif

#ifndef _SYSTEM_PNG_H
#define _SYSTEM_PNG_H
#include <libpng/png.h>
#endif

namespace Avtronsys
{
	class TexTureHandler
	{
	public:
		TexTureHandler(const char* pPath);
		TexTureHandler(android_app* pApplication, const char* pPath,bool isAsset);

		const char* getPath();	//获得路径
		int32_t getHeight();	//获得高
		int32_t getWidth();		//获得宽

		statedef load();//加载纹理
		void unload();	//卸载纹理
		void apply();	//使用纹理
		GLuint getTextureID();	//获得纹理
	protected:
		//改变opengl贴图大小
		int32_t ChangeSize(int size);
		uint8_t* loadImage();//载入图片

	private:
		static void callback_read(png_structp pStruct,
			png_bytep pData, png_size_t pSize);
	private:
		ResourceHandler mResource;
		GLuint mTextureId;
		int32_t mWidth, mHeight;
		GLint mFormat;
	};

}



