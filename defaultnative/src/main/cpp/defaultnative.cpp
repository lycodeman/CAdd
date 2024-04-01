#include <jni.h>
#include <stdio.h>
#include <android/log.h>
#include <pthread.h>
#include <string>
//#include "test.h"
#include <stdlib.h>
#include <dlfcn.h>
//动态链接库路径
#define LIB_CACULATE_PATH "/data/data/comm.example.cadd/cache/libcaculator.so"
#define LIB_CACULATE_PATH_OPEN "/data/data/comm.example.cadd/cache/test-dlopen.so"



extern "C"
JNIEXPORT void JNICALL
Java_com_example_defaultnative_DefaultNativeLib_addPerson(JNIEnv *env, jobject thiz, jstring id, jstring name, jstring email,
                                             jint image_id) {
    //由java String类对象 提取c字符串指针
    jboolean jbIsCopy = JNI_FALSE;
    const char *str1 = env->GetStringUTFChars(id, &jbIsCopy);
    const char *str2= env->GetStringUTFChars(name, &jbIsCopy);
    const char *str3= env->GetStringUTFChars(email, &jbIsCopy);
    __android_log_print(ANDROID_LOG_ERROR,"DefaultNativeLib","进入add方法");
    //获取到Person类
    jclass personClass = env->FindClass("com/example/defaultnative/Person");
    //实例化Person
    jobject person = env->NewObject(personClass, env->GetMethodID(personClass, "<init>",
                                                                  "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;I)V"),
                                    env->NewStringUTF(str1), env->NewStringUTF(str2), email, 0);
    //设置Person相关属性的值
    env->SetIntField(person, env->GetFieldID(personClass, "image", "I"), image_id);
//    env->SetObjectField(person, env->GetFieldID(personClass, "name", "Ljava/lang/String;"),  env->NewStringUTF(str2));
//    env->SetObjectField(person, env->GetFieldID(personClass, "email", "Ljava/lang/String;"),  env->NewStringUTF(str3));
    //获取到DefaultNativeLib类 -- 本地引用
    jobject DefaultNativeLib = thiz;
    //添加数据源
    env->CallVoidMethod(DefaultNativeLib, env->GetMethodID(env->GetObjectClass(DefaultNativeLib),
                                                       "addPer",
                                                       "(Lcom/example/defaultnative/Person;)V"), env->NewGlobalRef(person));
    //提示更新数据
    env->CallVoidMethod(DefaultNativeLib, env->GetMethodID(env->GetObjectClass(DefaultNativeLib),
                                                       "notifyDataChange",
                                                       "()V"));
    __android_log_print(ANDROID_LOG_ERROR,"DefaultNativeLib","结束add方法");
    //删除引用
//    env->DeleteLocalRef(DefaultNativeLib);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_defaultnative_DefaultNativeLib_removePerson(JNIEnv *env, jobject thiz, jstring id) {
    //获取到MainActivity类 -- 本地引用
    jobject defaultNativeLib = env->NewLocalRef(thiz);
    env->CallVoidMethod(defaultNativeLib, env->GetMethodID(env->GetObjectClass(defaultNativeLib),
                                                       "removePer",
                                                       "(Ljava/lang/String;)V"), id);
    //提示更新数据
    env->CallVoidMethod(defaultNativeLib, env->GetMethodID(env->GetObjectClass(defaultNativeLib),
                                                       "notifyDataChange",
                                                       "()V"));
    //删除引用
    env->DeleteLocalRef(defaultNativeLib);
}

static jclass personClass;
static jclass perGlobalClazz;
static bool isLoadClass = false;
static pthread_mutex_t mutex;
extern "C"
JNIEXPORT jobject * JNICALL
Java_com_example_defaultnative_DefaultNativeLib_createPerson(JNIEnv *env, jobject thiz) {
//    if (!isLoadClass){
//        pthread_mutex_init(&mutex, NULL);
//    }
//    pthread_mutex_lock(&mutex);
    //获取到DefaultNativeLib类 -- 本地引用
    jobject defaultNativeLib = env->NewLocalRef(thiz);
    //获取到dataList结合对象
    jclass defaultNativeLibClass = (jclass) env->NewGlobalRef(env->GetObjectClass(defaultNativeLib));
    jobject dataList = env->GetObjectField(defaultNativeLib,
                                           env->GetFieldID(defaultNativeLibClass,
                                                           "dataList",
                                                           "Ljava/util/List;"));
    //获取dataList的长度
    jclass listClass = (jclass) env->NewGlobalRef(env->GetObjectClass(dataList));
    jint dataSize = env->CallIntMethod(dataList, env->GetMethodID(listClass,
                                                                  "size",
                                                                  "()I"));
    //获取imageList结合对象
    jobject imageList = env->GetObjectField(defaultNativeLib,
                                            env->GetFieldID(defaultNativeLibClass,
                                                            "imageList",
                                                            "Ljava/util/List;"));
    //获取imageList的长度
    jint imageSize = env->CallIntMethod(imageList,
                                        env->GetMethodID(listClass,
                                                         "size",
                                                         "()I"));

    //这里有问题没有获取到具体的值
//    jobject imageId = (env->CallObjectMethod(imageObject, env->GetMethodID(
//            env->GetObjectClass(imageObject),
//            "toString",
//            "()Ljava/lang/String;")));
    //获取name输入框
    jstring name = (jstring)env->CallObjectMethod(defaultNativeLib, env->GetMethodID(env->GetObjectClass(defaultNativeLib),
                                                                              "getName",
                                                                              "()Ljava/lang/String;"));
    //获取到email
    jstring email = (jstring)env->CallObjectMethod(defaultNativeLib, env->GetMethodID(env->GetObjectClass(defaultNativeLib),
                                                                                       "getEmail",
                                                                                       "()Ljava/lang/String;"));

//    if (!isLoadClass){
//        //获取到Person类
    personClass = env->FindClass("com/example/defaultnative/Person");
    perGlobalClazz = (jclass) env->NewGlobalRef(personClass);
//        isLoadClass = true;
//    }

//    jobject imageValue = (*env).CallObjectMethod(imageObject, env->GetMethodID(
//            env->GetObjectClass(imageObject),
//            "toString",
//            "()Ljava/lang/String;"));
//    __android_log_print(ANDROID_LOG_ERROR,"DefaultNativeLib","imageValue:%s", imageValue);
    jobject person = env->NewObject(perGlobalClazz, env->GetMethodID(perGlobalClazz, "<init>",
                                                                     "()V"));
    //设置Person相关属性的值
    env->SetIntField(person, env->GetFieldID(perGlobalClazz, "image", "I"), dataSize % imageSize);
    env->SetObjectField(person, env->GetFieldID(perGlobalClazz, "name", "Ljava/lang/String;"), name);
    env->SetObjectField(person, env->GetFieldID(perGlobalClazz, "email", "Ljava/lang/String;"), email);
    env->SetObjectField(person, env->GetFieldID(perGlobalClazz, "id", "Ljava/lang/String;"),reinterpret_cast<jobject>(dataSize));
    return reinterpret_cast<jobject *>(person);
//    env->CallVoidMethod(mainActivity, env->GetMethodID(mainActivityClass,
//                                                   "addPer2",
//                                                       "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;I)V"),id , name, email, dataSize%imageSize);
    //dataList添加数据源
//    env->CallBooleanMethod(dataList, env->GetMethodID(listClass,
//                                                      "add",
//                                                      "(Ljava/lang/Object;)Z"), person);
    //提示更新数据
//    env->CallVoidMethod(mainActivity, env->GetMethodID(mainActivityClass,
//                                                       "notifyDataChange",
//                                                       "()V"));
    //删除引用
//    env->ReleaseStringUTFChars(id, env->GetStringUTFChars(id, 0));
//    env->DeleteLocalRef(id);
//    env->DeleteLocalRef(dataList);
//    env->DeleteLocalRef(imageList);
//    env->DeleteLocalRef(imageObject);
//    env->DeleteLocalRef(binding);
//    env->DeleteLocalRef(etEmail);
//    env->DeleteLocalRef(etName);
//    env->DeleteLocalRef(nameEt);
//    env->DeleteLocalRef(name);
//    env->DeleteLocalRef(emailEt);
//    env->DeleteLocalRef(email);
//    env->DeleteLocalRef(personClass);
//    env->DeleteLocalRef(person);
//    env->DeleteLocalRef(mainActivity);
//    env->DeleteGlobalRef(perGlobalClazz);
//    env->DeleteGlobalRef(listClass);
//    env->DeleteGlobalRef(stringClass);
//    env->DeleteGlobalRef(editableClass);
//    env->DeleteGlobalRef(mainActivityClass);
//    env->DeleteGlobalRef(bindingClass);
//    pthread_mutex_unlock(&mutex);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_defaultnative_DefaultNativeLib_removePerson2(JNIEnv *env, jobject thiz, jobject person) {
    //获取到DefaultNativeLib类 -- 本地引用
    jobject defaultNativeLib = env->NewLocalRef(thiz);
    //获取到dataList结合对象
    jobject dataList = env->GetObjectField(defaultNativeLib,
                                           env->GetFieldID(env->GetObjectClass(defaultNativeLib),
                                                           "dataList",
                                                           "Ljava/util/List;"));
    //dataList删除数据源
    env->CallBooleanMethod(dataList, env->GetMethodID(env->GetObjectClass(dataList),
                                                      "remove",
                                                      "(Ljava/lang/Object;)Z"), person);
    //提示更新数据
    env->CallVoidMethod(defaultNativeLib, env->GetMethodID(env->GetObjectClass(defaultNativeLib),
                                                       "notifyDataChange",
                                                       "()V"));
    //删除引用
    env->DeleteLocalRef(defaultNativeLib);
}