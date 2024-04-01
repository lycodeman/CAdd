#include <jni.h>
#include <string>
#include <android/log.h>
#define  LOG_TAG    "LY"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

static jint JNICALL cAdd(JNIEnv *env, jobject jobj, jint x, jint y){
    LOGI("cAdd x is :%d  y is :%d", x, y);
    return x + y;
}

static jstring JNICALL cSayHi(JNIEnv *env, jobject jobj, jint x, jint y){
    LOGI("cSayHi runs... will return a string in c");
    return env->NewStringUTF("hello from cSayHi");
}

/**
   第一个参数：javaAdd 是java中的方法名称
   第二个参数：(II)I  是java中方法的签名，可以通过javap -s -p 类名.class 查看
   第三个参数： (jstring *)cSayHi  （返回值类型）映射到native的方法名称

*/
static const JNINativeMethod gMethods[] = {
        {"javaAdd", "(II)I", (jint *)cAdd},
        {"javaSayHi","()Ljava/lang/String;",(jstring *)cSayHi}
};


static jclass myClass;
// 这里是java调用C的存在Native方法的类路径
static const char* const className="com/example/jni/dynamic/JniOnloadTest";
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved){
    LOGI("jni onload called");
    JNIEnv* env = NULL; //注册时在JNIEnv中实现的，所以必须首先获取它
    jint result = -1;
    if(vm->GetEnv((void **) &env, JNI_VERSION_1_4) != JNI_OK) { //从JavaVM获取JNIEnv，一般使用1.4的版本
        return -1;
    }
    // 获取映射的java类
    myClass = env->FindClass(className);
    if(myClass == NULL)
    {
        printf("cannot get class:%s\n", className);
        return -1;
    }
    // 通过RegisterNatives方法动态注册
    if(env->RegisterNatives(myClass, gMethods, sizeof(gMethods)/sizeof(gMethods[0])) < 0)
    {
        printf("register native method failed!\n");
        return -1;
    }
    LOGI("jni onload called end...");
    return JNI_VERSION_1_4; //这里很重要，必须返回版本，否则加载会失败。
}