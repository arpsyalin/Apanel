/**************************************
 * 	文件名	：Avtronsys_TexTureHandler.cpp
 *	作用		：基于纹理贴图的API实现
 *	作者		：刘亚林
 *	创建时间	：2012/09/25
 *	最后修改	：刘亚林	 2012/09/26
 *	修改说明	: 添加函数实现
 *	遗留说明	 ：暂无
 ***************************************/
#ifndef _AVTRONSYS_TEXTUREHANDLER_H
#define _AVTRONSYS_TEXTUREHANDLER_H
#include "Avtronsys_TexTureHandler.h"
#endif

#ifndef _AVTRONSYS_LOG_H
#define _AVTRONSYS_LOG_H
#include "Avtronsys_Log.h"
#endif

namespace Avtronsys
{
	TexTureHandler::TexTureHandler(const char* pPath):
    mResource(pPath,false),
    mTextureId(0),
    mWidth(0), mHeight(0)
	{
	}


	TexTureHandler::TexTureHandler(android_app* pApplication,
        const char* pPath,bool isAsset) :
        mResource(pApplication, pPath,isAsset),
        mTextureId(0),
        mWidth(0), mHeight(0)
    {}

	//获得图片的路径
    const char* TexTureHandler::getPath()
    {
        return mResource.getPath();
    }

    //获得图片的高
    int32_t TexTureHandler::getHeight()
    {

    	//Log::info("mHeight:%d",mHeight);
        return mHeight;
    }

    //获得图片的宽
    int32_t TexTureHandler::getWidth()
    {
    	//Log::info("getWidth:%d",mWidth);
        return mWidth;
    }

    //加载图片
    uint8_t* TexTureHandler::loadImage()
    {

        png_byte lHeader[8];
        png_structp lPngPtr = NULL;
		png_infop lInfoPtr = NULL;
        png_byte* lImageBuffer = NULL;
		png_bytep* lRowPtrs = NULL;
        png_int_32 lRowSize;
		bool lTransparency;

        if (mResource.open() != state_Succse)
        {
        	Log::error("OPENFILE ERROR");
        	goto ERROR;
        }

        if (mResource.read(lHeader, sizeof(lHeader)) != state_Succse)
         {
        	Log::error("READFILE ERROR");
        	goto ERROR;
         }
        if (png_sig_cmp(lHeader, 0, 8) != 0) goto ERROR;

        lPngPtr = png_create_read_struct(PNG_LIBPNG_VER_STRING,
            NULL, NULL, NULL);
        if (!lPngPtr)
        {
        	Log::error("lPngPtr");
        	goto ERROR;
        }
        lInfoPtr = png_create_info_struct(lPngPtr);
        if (!lInfoPtr)
        {
        	goto ERROR;
        }

        png_set_read_fn(lPngPtr, &mResource, callback_read);
        if (setjmp(png_jmpbuf(lPngPtr)))
        {
        	Log::error("png_set_read_fn ERROR");
        	goto ERROR;
        }

        png_set_sig_bytes(lPngPtr, 8);
        png_read_info(lPngPtr, lInfoPtr);

        png_int_32 lDepth, lColorType;
        png_uint_32 lWidth, lHeight;
        png_get_IHDR(lPngPtr, lInfoPtr, &lWidth, &lHeight,
            &lDepth, &lColorType, NULL, NULL, NULL);
        mWidth = lWidth;
        mHeight = lHeight;

        //创建一个完整的alpha通道
        lTransparency = false;
        if (png_get_valid(lPngPtr, lInfoPtr, PNG_INFO_tRNS))
        {
            png_set_tRNS_to_alpha(lPngPtr);
            lTransparency = true;
            Log::error("png_set_tRNS_to_alpha");
            goto ERROR;
        }

        if (lDepth < 8)
        {
            png_set_packing (lPngPtr);

        } else if (lDepth == 16)
        {
            png_set_strip_16(lPngPtr);
        }

        //根据图片的类型不同进行不同处理
        switch (lColorType)
        {
        case PNG_COLOR_TYPE_PALETTE:
            png_set_palette_to_rgb(lPngPtr);
            mFormat = lTransparency ? GL_RGBA : GL_RGB;
            break;
        case PNG_COLOR_TYPE_RGB:
            mFormat = lTransparency ? GL_RGBA : GL_RGB;
            break;
        case PNG_COLOR_TYPE_RGBA:
            mFormat = GL_RGBA;
            break;
        case PNG_COLOR_TYPE_GRAY:
            png_set_expand_gray_1_2_4_to_8(lPngPtr);
            mFormat = lTransparency ? GL_LUMINANCE_ALPHA:GL_LUMINANCE;
            break;
        case PNG_COLOR_TYPE_GA:
            png_set_expand_gray_1_2_4_to_8(lPngPtr);
            mFormat = GL_LUMINANCE_ALPHA;
            break;
        }

        png_read_update_info(lPngPtr, lInfoPtr);

        //获取像素行
        lRowSize = png_get_rowbytes(lPngPtr, lInfoPtr);
        if (lRowSize <= 0)
        {
           	Log::error("lRowSize");
        	goto ERROR;
        }

        lImageBuffer = new png_byte[lRowSize * lHeight];
        if (!lImageBuffer)
        {
        	Log::error("lImageBuffer");
        	goto ERROR;
        }

        //将图片像素重新排列成opengl能用的left-top的
        lRowPtrs = new png_bytep[lHeight];
        if (!lRowPtrs)
        {
        	goto ERROR;
        }
        for (int32_t i = 0; i < lHeight; ++i)
        {
            lRowPtrs[lHeight - (i + 1)] = lImageBuffer + i * lRowSize;
        }
        //读图片内容
        png_read_image(lPngPtr, lRowPtrs);

        //释放内存
        mResource.close();
        png_destroy_read_struct(&lPngPtr, &lInfoPtr, NULL);
        delete[] lRowPtrs;
        return lImageBuffer;

    ERROR:
        Log::error("Error while reading PNG file");
        mResource.close();
        delete[] lRowPtrs; delete[] lImageBuffer;
        if (lPngPtr != NULL)
        {
            png_infop* lInfoPtrP = lInfoPtr != NULL ? &lInfoPtr: NULL;
            png_destroy_read_struct(&lPngPtr, lInfoPtrP, NULL);
        }
        return NULL;
    }
    //回调数据
    void TexTureHandler::callback_read(png_structp pStruct,
        png_bytep pData, png_size_t pSize)
    {
        ResourceHandler* lResource = ((ResourceHandler*) png_get_io_ptr(pStruct));
        if (lResource->read(pData, pSize) != state_Succse)
        {
            lResource->close();
        }
    }

    //加载纹理
    statedef TexTureHandler::load()
    {
        uint8_t* lImageBuffer = loadImage();
        if (lImageBuffer == NULL)
        {
            return state_Fail;
        }

        // Creates a new OpenGL texture.
        GLenum lErrorResult;
        glGenTextures(1, &mTextureId);
        glBindTexture(GL_TEXTURE_2D, mTextureId);
        // Set-up texture properties.
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
            GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
            GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
            GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
            GL_CLAMP_TO_EDGE);

        //改变贴图大小
		int maxW,maxH;
		maxW=ChangeSize(mWidth);
		maxH=ChangeSize(mHeight);

		//加载数据到openGL
		glTexImage2D(GL_TEXTURE_2D, 0, mFormat, maxW, maxH, 0,mFormat, GL_UNSIGNED_BYTE, NULL);
		glTexSubImage2D (GL_TEXTURE_2D, 0, 0, 0, mWidth ,mHeight  ,mFormat,GL_UNSIGNED_BYTE, lImageBuffer);

        delete[] lImageBuffer;
        if (glGetError() != GL_NO_ERROR)
        {
            Log::error("Error loading texture into OpenGL.");
            unload();
            return state_Fail;
        }
        return state_Succse;
    }

    //改变大小将不是2的n次方的数字改变成2的N次
	int TexTureHandler::ChangeSize(int size)
	{
		int returnSize=1;
		while(true)
		{
			//进行移位
			returnSize<<=1;
			if(returnSize>=size)
			{
				break;
			}
		}
		return returnSize;
	}

	//卸载纹理
    void TexTureHandler::unload() {
        if (mTextureId != 0)
        {
            glDeleteTextures(1, &mTextureId);
            mTextureId = 0;
        }
        mWidth = 0; mHeight = 0; mFormat = 0;
    }

    //获得纹理ID
    GLuint TexTureHandler:: getTextureID()
    {
    	return mTextureId;
    };

    //使用纹理
    void TexTureHandler::apply()
    {
        glActiveTexture( GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, mTextureId);
    }
}
