#include <jni.h>
#include <string>
#include <jni.h>
#include <android/log.h>
#include "POSOfflineServiceApiI.h"


extern "C"
JNIEXPORT jint JNICALL
Java_com_example_dllnative_DllNativeLib_add(JNIEnv *env, jobject thiz, jint a, jint b) {
    return a + b;
}

void myFunction() {
    __android_log_print(ANDROID_LOG_DEBUG, "JNI", "Hello from myFunction!");
}
//void myFunction(){}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_dllnative_DllNativeLib_printHelloWorld(JNIEnv *env, jobject thiz) {
    myFunction();
    POSOfflineServiceApiI().run();
    __android_log_print(ANDROID_LOG_DEBUG, "JNI", "成功打印");
}