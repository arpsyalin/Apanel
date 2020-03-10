#ifndef _SYSTEM_NATIVE_APP_GLUE_H
#define _SYSTEM_NATIVE_APP_GLUE_H
#include <android_native_app_glue.h>
#endif

namespace APanel
{
	class Exit
	{
	public:
		Exit(android_app * pApplication);
		~Exit();
	public:
		void ExitActivity();
	public:
		android_app * mApplication;
	};
}
