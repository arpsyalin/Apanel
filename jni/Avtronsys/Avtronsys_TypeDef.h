/**************************************
 * 	�ļ���	��Avtronsys_TypeDef.h
 *	����		������һЩȫ���õõ��ı���
 *	����		��������
 *	����ʱ��	��2012/09/24
 *	����޸�	��������	 2012/09/24
 *	�޸�˵��	: �������ļ�
 *	����˵��	 ������
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
	//return�Ľ��
	typedef int32_t statedef;
    const statedef state_Succse	= 0;	//�ɹ�
    const statedef state_Fail		= -1;	//ʧ��
    const statedef state_Exit		= -2;	//�ر�
}
