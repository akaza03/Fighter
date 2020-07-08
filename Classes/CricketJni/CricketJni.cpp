#include "CricketJni.h"
#include "cricket/inc/ck/ck.h"
#include "cricket/inc/ck/config.h"

extern "C" JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_AppActivity_initCricket(JNIEnv *env, jclass obj, jobject thiz)
{
#if CK_PLATFORM_ANDROID
	CkConfig config(env, thiz);
	CkInit(&config);
#endif
}