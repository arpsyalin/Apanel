/**************************************
 * 	�ļ���	��Avtronsys_TexTureHandler.h
 *	����		������������ͼ��API����
 *	����		��������
 *	����ʱ��	��2012/09/25
 *	����޸�	��������	 2012/09/25
 *	�޸�˵��	: ��Ӹ��ļ�
 *	����˵��	 ������
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

		const char* getPath();	//���·��
		int32_t getHeight();	//��ø�
		int32_t getWidth();		//��ÿ�

		statedef load();//��������
		void unload();	//ж������
		void apply();	//ʹ������
		GLuint getTextureID();	//�������
	protected:
		//�ı�opengl��ͼ��С
		int32_t ChangeSize(int size);
		uint8_t* loadImage();//����ͼƬ

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



