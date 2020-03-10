/**************************************
 * 	文件名	：Avtronsys_Log.h
 *	作用		：打印日志API
 *	作者		：刘亚林
 *	创建时间	：2012/09/24
 *	最后修改	：刘亚林	 2012/09/24
 *	修改说明	: 创建该文件
 *	遗留说明	 ：暂无
 ***************************************/
namespace Avtronsys
{
	class Log
	{
	public:
		static void error(const char* pMessage, ...);	//打印错误日志
		static void warn(const char* pMessage, ...);	//打印警告日志
		static void info(const char* pMessage, ...);	//打印详细日志
		static void debug(const char* pMessage, ...);	//打印调试信息
	};
}
