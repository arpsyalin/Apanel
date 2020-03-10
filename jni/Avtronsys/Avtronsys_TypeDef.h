/**************************************
 * 	文件名	：Avtronsys_TypeDef.h
 *	作用		：定义一些全局用得到的变量
 *	作者		：刘亚林
 *	创建时间	：2012/09/24
 *	最后修改	：刘亚林	 2012/09/24
 *	修改说明	: 创建该文件
 *	遗留说明	 ：暂无
 ***************************************/
#ifndef _SYSTEM_STDINT_H
#define _SYSTEM_STDINT_H
#include <stdint.h>
#endif

#ifndef _SYSTEM_CSTDLIB_H
#define _SYSTEM_CSTDLIB_H
#include <cstdlib>
#endif

namespace Avtronsys
{
	//return的结果
	typedef int32_t statedef;
    const statedef state_Succse	= 0;	//成功
    const statedef state_Fail		= -1;	//失败
    const statedef state_Exit		= -2;	//关闭
}
