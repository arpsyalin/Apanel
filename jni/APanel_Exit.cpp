#include "APanel_Exit.h"
namespace APanel
{

	Exit::Exit(android_app * pApplication):mApplication(pApplication)
	{

	}

	Exit::~Exit()
	{

	}

	void Exit::ExitActivity()
	{
		//退出程序（为了应付Apanel项目）
		ANativeActivity_finish(mApplication->activity);
	}
}
