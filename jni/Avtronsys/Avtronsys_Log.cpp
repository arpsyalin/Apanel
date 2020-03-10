/**************************************
 * 	文件名	：Avtronsys_Log.cpp
 *	作用		：打印日志API的实现
 *	作者		：刘亚林
 *	创建时间	：2012/09/24
 *	最后修改	：刘亚林	 2012/09/24
 *	修改说明	: 添加了4个打印日志的实现
 *	遗留说明	 ：暂无
 ***************************************/
#ifndef _AVTRONSYS_LOG_H
#define _AVTRONSYS_LOG_H
#include "Avtronsys_Log.h"
#endif

#ifndef _SYSTEM_STDARG_H
#define _SYSTEM_STDARG_H
#include <stdarg.h>
#endif

#ifndef _SYSTEM_LOG_H
#define _SYSTEM_LOG_H
#include <android/log.h>
#endif
//如果是开发调试版本请加上此宏
//如果是发布版请去掉此宏
//#define _DEBUG_

namespace Avtronsys
{
	void Log::info(const char* pMessage, ...) {
#ifdef _DEBUG_
        va_list lVarArgs;
        va_start(lVarArgs, pMessage);
        __android_log_vprint(ANDROID_LOG_INFO, "Avtronsys", pMessage,
            lVarArgs);
        __android_log_print(ANDROID_LOG_INFO, "Avtronsys", "\n");
        va_end(lVarArgs);
#endif
	}

    void Log::error(const char* pMessage, ...) {
#ifdef _DEBUG_
        va_list lVarArgs;
        va_start(lVarArgs, pMessage);
        __android_log_vprint(ANDROID_LOG_ERROR, "Avtronsys", pMessage,
            lVarArgs);
        __android_log_print(ANDROID_LOG_ERROR, "Avtronsys", "\n");
        va_end(lVarArgs);
#endif
    }

    void Log::warn(const char* pMessage, ...) {
#ifdef _DEBUG_
        va_list lVarArgs;
        va_start(lVarArgs, pMessage);
        __android_log_vprint(ANDROID_LOG_WARN, "Avtronsys", pMessage,
            lVarArgs);
        __android_log_print(ANDROID_LOG_WARN, "Avtronsys", "\n");
        va_end(lVarArgs);
#endif
    }

    void Log::debug(const char* pMessage, ...) {
#ifdef _DEBUG_
        va_list lVarArgs;
        va_start(lVarArgs, pMessage);
        __android_log_vprint(ANDROID_LOG_DEBUG, "Avtronsys", pMessage,
            lVarArgs);
        __android_log_print(ANDROID_LOG_DEBUG, "Avtronsys", "\n");
        va_end(lVarArgs);
#endif
    }
}
