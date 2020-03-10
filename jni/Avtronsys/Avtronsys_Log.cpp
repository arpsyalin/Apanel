/**************************************
 * 	�ļ���	��Avtronsys_Log.cpp
 *	����		����ӡ��־API��ʵ��
 *	����		��������
 *	����ʱ��	��2012/09/24
 *	����޸�	��������	 2012/09/24
 *	�޸�˵��	: �����4����ӡ��־��ʵ��
 *	����˵��	 ������
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
//����ǿ������԰汾����ϴ˺�
//����Ƿ�������ȥ���˺�
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
