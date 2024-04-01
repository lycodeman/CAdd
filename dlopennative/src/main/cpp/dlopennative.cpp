#include <jni.h>
#include <string>
#include <stdlib.h>
#include <dlfcn.h>
//动态链接库路径
#define LIB_CACULATE_PATH "/data/data/comm.example.cadd/cache/caculate.so"
#define LIB_CACULATE_PATH_OPEN "/data/data/comm.example.cadd/cache/test-dlopen.so"
//函数指针
typedef int (*CAC_FUNC)(int, int);

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_dlopennative_DLOpenNativeLib_add(JNIEnv *env, jobject thiz, jint a, jint b) {
    void *handle;
    char *error;
    CAC_FUNC cac_func = NULL;
    //打开动态链接库
    handle = dlopen(LIB_CACULATE_PATH, RTLD_LAZY);
    void *  filehandle = dlopen("/data/data/com.ckl.SoCallSo/lib/libb.so", RTLD_LAZY );
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        return env->NewStringUTF("dlopen error");
//        exit(EXIT_FAILURE);
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
    return reinterpret_cast<jstring>((*cac_func)(a, b));
}