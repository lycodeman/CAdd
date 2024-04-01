#include <jni.h>
#include <string>
//#include <wer.h>

//
//extern "C"
//JNIEXPORT jstring JNICALL
//Java_com_dmall_JnaI_test1(JNIEnv *env, jobject thiz, jstring data) {
//    printf("test1: %s\n", reinterpret_cast<const char *>(data));
//    return env->NewStringUTF(strcat("hello from jna: " ,reinterpret_cast<const char *>(data)));
//}
int add(int a, int b);
extern "C"
JNIEXPORT jint JNICALL
Java_com_example_jnanative_JNANativeLib_add(JNIEnv *env, jobject thiz, jint a, jint b) {
    printf("add: %d\n", a + b);
    printf("开始调用hello.so库中的add方法，返回: %d\n", add(a, b));
    return a + b;
}

//int add(int a, int b) {
//    printf("add: %d\n", a + b);
//    return a + b;
//}

//char * test1(char * data) {
//    printf("test1: %s\n", data);
//    return strcat("hello from jna: " ,data);
//}