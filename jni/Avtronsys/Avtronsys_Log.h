/**************************************
 * 	�ļ���	��Avtronsys_Log.h
 *	����		����ӡ��־API
 *	����		��������
 *	����ʱ��	��2012/09/24
 *	����޸�	��������	 2012/09/24
 *	�޸�˵��	: �������ļ�
 *	����˵��	 ������
 ***************************************/
namespace Avtronsys
{
	class Log
	{
	public:
		static void error(const char* pMessage, ...);	//��ӡ������־
		static void warn(const char* pMessage, ...);	//��ӡ������־
		static void info(const char* pMessage, ...);	//��ӡ��ϸ��־
		static void debug(const char* pMessage, ...);	//��ӡ������Ϣ
	};
}
