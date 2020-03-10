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
		//传一个自定义的纹理对象进来
		DrawTexture(TexTureHandler* pTexTureHandler);
		//传整个的绘制纹理需要的参数进来！
		DrawTexture(GLuint pTextureId,float pLeft,float pTop,
				float pWidth,float pHeight,float px,float py,float pSizeW,float pSizeH);
	public:
		///设置纹理数组
		void setTextureDVT(float pLeft,float pTop);//只设置偏移值
		void setTextureHAW(float pWidth,float pHeight);//只设置宽高
		void setTextureArray(float pLeft,float pTop,float pWidth,float pHeight);//设置宽高以及偏移值
		//设置绘制的位置
		void setLocation(float px,float py);
		//设置绘制的大小
		void setSize(float pSizeW,float pSizeH);//默认有多大图片就绘制多大这里提供一个设置
		//设置纹理贴图ID
		void setTexture(GLuint pTextureId);
		//绘制自身
		void Drawself();
	public:
		GLuint mTextureId;
		float mLeft,mTop,mWidth,mHeight;//左偏移值、上偏移值、图宽、图高
		float mx, my,mSizeW,mSizeH;		//绘制x、绘制的y、绘制的宽、绘制的高
	};
}
