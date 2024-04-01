#include <jni.h>
#include <stdio.h>
#include <android/log.h>
#include <pthread.h>
#include <string>
//#include "test.h"
#include <stdlib.h>
#include <dlfcn.h>
#include "../../../../toolchains1/src/main/cpp/toolchains2.h"
#include "include/POSOfflineServiceApi.h"
#include "include/OfflineServiceApi.h"
//动态链接库路径
#define LIB_CACULATE_PATH "/data/data/comm.example.cadd/cache/libcaculator.so"
#define LIB_CACULATE_PATH_OPEN "/data/data/comm.example.cadd/cache/test-dlopen.so"
#define CADD_TOOLCHAINS1_H

extern "C"{
    extern jint add(jint a, jint b);
}
//函数指针
typedef int (*CAC_FUNC)(int, int);
extern "C"
JNIEXPORT jint JNICALL
Java_com_example_cadd_MainActivity_add(JNIEnv *env, jobject thiz, jint a, jint b) {
//    add(1,2);
    void *handle;
    char *error;
    CAC_FUNC cac_func = NULL;
    //打开动态链接库
    handle = dlopen(LIB_CACULATE_PATH_OPEN, RTLD_LAZY);
    void *  filehandle = dlopen("/data/data/com.ckl.SoCallSo/lib/libb.so", RTLD_LAZY );
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(EXIT_FAILURE);
    }
    //清除之前存在的错误
    dlerror();
    //获取一个函数
    *(void **) (&cac_func) = dlsym(handle, "add");
    if ((error = dlerror()) != NULL)  {
        fprintf(stderr, "%s\n", error);
        exit(EXIT_FAILURE);
    }
    printf("add: %d\n", (*cac_func)(a,b));
    dlclose(handle);
    return (*cac_func)(a,b);
}



//int test()
//{
//    void *handle;
//    char *error;
//    CAC_FUNC cac_func = NULL;
//    //打开动态链接库
//    handle = dlopen(LIB_CACULATE_PATH, RTLD_LAZY);
//    if (!handle) {
//        fprintf(stderr, "%s\n", dlerror());
//        exit(EXIT_FAILURE);
//    }
//    //清除之前存在的错误
//    dlerror();
//    //获取一个函数
//    *(void **) (&cac_func) = dlsym(handle, "add");
//    if ((error = dlerror()) != NULL)  {
//        fprintf(stderr, "%s\n", error);
//        exit(EXIT_FAILURE);
//    }
//    printf("add: %d\n", (*cac_func)(2,7));
//    cac_func = (CAC_FUNC)dlsym(handle, "sub");
//    printf("sub: %d\n", cac_func(9,2));
//    cac_func = (CAC_FUNC)dlsym(handle, "mul");
//    printf("mul: %d\n", cac_func(3,2));
//    cac_func = (CAC_FUNC)dlsym(handle, "div");
//    printf("div: %d\n", cac_func(8,2));
//    //关闭动态链接库
//    dlclose(handle);
//    exit(EXIT_SUCCESS);
//}
extern "C" {
    extern int getChains1();
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_cadd_MainActivity_stringFromJNI(JNIEnv *env, jobject thiz) {

//    POSOfflineServiceApi *posOfflineServiceApi = new POSOfflineServiceApi();
//    posOfflineServiceApi.run();
//    std::string hello = getData();
//    TestAAA *testAAA = new TestAAA();
//    testAAA.getAge()
//    getData();
//    __android_log_print(ANDROID_LOG_INFO, "JNI", "%s", hello.data());
    //测试so库链接调用
    int chains1 = getChains1();
    __android_log_print(ANDROID_LOG_INFO, "JNI", "%d", chains1);
    TestToolChains2 *pChains2 = new TestToolChains2();
    __android_log_print(ANDROID_LOG_INFO, "JNI", "===%d", pChains2->getChains2());
//    POSOfflineServiceApi *posOfflineServiceApi = new POSOfflineServiceApi();
//    __android_log_print(ANDROID_LOG_INFO, "JNI", "===%d", posOfflineServiceApi->run());
//    OfflineServiceApi *offlineServiceApi = new OfflineServiceApi();
//    __android_log_print(ANDROID_LOG_INFO, "JNI", "==wwww=%s", offlineServiceApi->run());
//    void* handle = dlopen("/data/data/com.example.cadd/cache/jni/libtoolchains1.so", RTLD_LAZY);
//    const char *dlopen_error = dlerror();
//    if (dlopen_error) {
//        // 输出错误信息
//        printf("dlopen error: %s\n", dlopen_error);
//    }
//    if (handle) {
//        typedef int (*example_func_t)();
//        example_func_t example_func = (example_func_t)dlsym(handle, "getChains1");
//        if (example_func) {
//            int result = example_func();
//            dlclose(handle);
//            __android_log_print(ANDROID_LOG_INFO, "JNI", "%d", result);
//        }
//        dlclose(handle);
//    }

    return env->NewStringUTF("hello");
}