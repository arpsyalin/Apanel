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
		//�˳�����Ϊ��Ӧ��Apanel��Ŀ��
		ANativeActivity_finish(mApplication->activity);
	}
}
