#ifndef _SYSTEM_GL_H
#define _SYSTEM_GL_H
#include <GLES/gl.h>
#endif

#ifndef _SYSTEM_GLEXT_H
#define _SYSTEM_GLEXT_H
#include <GLES/glext.h>
#endif

#ifndef _AVTRONSYS_TEXTUREHANDLER_H
#define _AVTRONSYS_TEXTUREHANDLER_H
#include "Avtronsys_TexTureHandler.h"
#endif

namespace Avtronsys
{
	class DrawTexture
	{
	public:
		DrawTexture();
		//��һ���Զ��������������
		DrawTexture(TexTureHandler* pTexTureHandler);
		//�������Ļ���������Ҫ�Ĳ���������
		DrawTexture(GLuint pTextureId,float pLeft,float pTop,
				float pWidth,float pHeight,float px,float py,float pSizeW,float pSizeH);
	public:
		///������������
		void setTextureDVT(float pLeft,float pTop);//ֻ����ƫ��ֵ
		void setTextureHAW(float pWidth,float pHeight);//ֻ���ÿ��
		void setTextureArray(float pLeft,float pTop,float pWidth,float pHeight);//���ÿ���Լ�ƫ��ֵ
		//���û��Ƶ�λ��
		void setLocation(float px,float py);
		//���û��ƵĴ�С
		void setSize(float pSizeW,float pSizeH);//Ĭ���ж��ͼƬ�ͻ��ƶ�������ṩһ������
		//����������ͼID
		void setTexture(GLuint pTextureId);
		//��������
		void Drawself();
	public:
		GLuint mTextureId;
		float mLeft,mTop,mWidth,mHeight;//��ƫ��ֵ����ƫ��ֵ��ͼ��ͼ��
		float mx, my,mSizeW,mSizeH;		//����x�����Ƶ�y�����ƵĿ����Ƶĸ�
	};
}
