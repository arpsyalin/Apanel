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
				:mTextureId(pTextureId)				//����ID
				,mLeft(pLeft),mTop(pTop)			//����ƫ�Ƶ�ֵ
				,mWidth(pWidth),mHeight(pHeight)	//����Ĵ�С
				,mx(px),my(py)						//��ͼ����λ��
				,mSizeW(pSizeW),mSizeH(pSizeH)		//���ƵĴ�С
		{

		}

		///������������
		void DrawTexture::setTextureDVT(float pLeft,float pTop)
		{
			mLeft=pLeft;
			mTop=pTop;
		}
		//���ÿ��
		void DrawTexture:: setTextureHAW(float pWidth,float pHeight)
		{
			mWidth=pWidth;
			mHeight=pHeight;
		}

		///������������
		void DrawTexture::setTextureArray(float pLeft,float pTop,float pWidth,float pHeight)
		{
			mLeft=pLeft;
			mTop=pTop;
			mWidth=pWidth;
			mHeight=pHeight;
		}

		//���û��Ƶ�λ��
		void DrawTexture::setLocation(float px,float py)
		{
			mx=px;
			my=py;
		}

		//���û��ƵĴ�С
		void DrawTexture::setSize(float pSizeW,float pSizeH)
		{
			mSizeW=pSizeW;
			mSizeH=pSizeH;
		}

		//����������ͼID
		void DrawTexture::setTexture(GLuint pTextureId)
		{
			mTextureId=pTextureId;
		}

		//��������
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
