#ifndef _AVTRONSYS_DRAWTEXTURE_H
#define _AVTRONSYS_DRAWTEXTURE_H
#include "Avtronsys_DrawTexture.h"
#endif
#include "Avtronsys_Log.h"

namespace Avtronsys
{
		DrawTexture::DrawTexture()
		:mTextureId(0)
		,mLeft(0),mTop(0)
		,mWidth(0),mHeight(0)
		,mx(0),my(0)
		,mSizeW(0),mSizeH(0)
		{

		}

		DrawTexture::DrawTexture(TexTureHandler* pTexTureHandler)
		:mWidth(pTexTureHandler->getWidth()),
		mHeight(pTexTureHandler->getHeight()),
		mTextureId(pTexTureHandler->getTextureID()),
		mx(0),my(0),mSizeW(0),mSizeH(0),
		mLeft(0),mTop(0)
		{
				mSizeW=mWidth;
				mSizeH=mHeight;
		}

		DrawTexture::DrawTexture(GLuint pTextureId,float pLeft,float pTop,float pWidth,float pHeight,float px,float py,float pSizeW,float pSizeH)
				:mTextureId(pTextureId)				//纹理ID
				,mLeft(pLeft),mTop(pTop)			//纹理偏移的值
				,mWidth(pWidth),mHeight(pHeight)	//纹理的大小
				,mx(px),my(py)						//贴图绘制位置
				,mSizeW(pSizeW),mSizeH(pSizeH)		//绘制的大小
		{

		}

		///设置纹理数组
		void DrawTexture::setTextureDVT(float pLeft,float pTop)
		{
			mLeft=pLeft;
			mTop=pTop;
		}
		//设置宽高
		void DrawTexture:: setTextureHAW(float pWidth,float pHeight)
		{
			mWidth=pWidth;
			mHeight=pHeight;
		}

		///设置纹理数组
		void DrawTexture::setTextureArray(float pLeft,float pTop,float pWidth,float pHeight)
		{
			mLeft=pLeft;
			mTop=pTop;
			mWidth=pWidth;
			mHeight=pHeight;
		}

		//设置绘制的位置
		void DrawTexture::setLocation(float px,float py)
		{
			mx=px;
			my=py;
		}

		//设置绘制的大小
		void DrawTexture::setSize(float pSizeW,float pSizeH)
		{
			mSizeW=pSizeW;
			mSizeH=pSizeH;
		}

		//设置纹理贴图ID
		void DrawTexture::setTexture(GLuint pTextureId)
		{
			mTextureId=pTextureId;
		}

		//绘制自身
		void DrawTexture::Drawself()
		{
			//Avtronsys::Log::info("mTextureId:%d,mLeft:%f,mTop:%f," \
			"mWidth:%f,mHeight:%f,mx:%f,my:%f,mSizeW:%f,mSizeH:%f",	\
			mTextureId,mLeft, mTop, mWidth,mHeight,mx, my, mSizeW,mSizeH);
			int cropRect[4] = { mLeft, mTop, mWidth, mHeight};
			glFrontFace(GL_CW);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glEnable(GL_TEXTURE_2D);
			glActiveTexture( GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D,mTextureId);
			glTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_CROP_RECT_OES, cropRect);
			glDrawTexfOES(mx,my, 0, mSizeW, mSizeH);
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
			glDisable(GL_TEXTURE_COORD_ARRAY);
		}

}
