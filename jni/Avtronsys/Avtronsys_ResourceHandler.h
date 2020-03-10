/**************************************
 * 	�ļ���	��Avtronsys_EGLDisplay.h
 *	����		��������Դ�ļ����ʵ�API
 *	����		��������
 *	����ʱ��	��2012/09/25
 *	����޸�	��������	 2012/09/25
 *	�޸�˵��	: ��Ӹ��ļ�������GLTextureID��
 *	����˵��	 ������
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

		const char* getPath();	//���·��

		statedef open();		//����Դ
		void close();			//�ر���Դ
		statedef read(void* pBuffer, size_t pCount);	//��ȡ����
        off_t getLength();		//��ó���
        ResourceDescriptor descript();	//ֻ���������洢��Assets�ļ�����Դ��ʱ��
	private:
		const char* mPath;	//�ļ�·��
		//�ļ����Զ����λ��ʱ���õ�
		std::ifstream mInputStream;
		char* mBuffer;
		//�ļ���Assets�ļ���
		AAssetManager* mAssetManager;
		AAsset* mAsset;
		bool misAsset;//�ļ��Ƿ���Assets�ļ���
	};
}
