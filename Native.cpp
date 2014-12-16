#include <jni.h>

extern "C"
{
	jstring Java_com_example_nativesample_MainActivity_getString(JNIEnv* jni,jobject object)
	{
		return jni->NewStringUTF("Hello world!");
	}
}
