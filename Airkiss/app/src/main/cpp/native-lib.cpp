#include <jni.h>
#include <string>
#include <stdlib.h>
#include "include/airkiss.h"
#include "include/logUtils.h"
#include <cstring>
#include <pthread.h>
#include <iostream>
#include  <fstream>
#include <ctime>
#include <unistd.h>
#include <vector>
#include "include/Box.h"
//当前监听的无线信道
uint8_t cur_channel = 1;
airkiss_context_t *akcontex;
/*
 * 平台相关定时器中断处理函数，100ms中断后切换信道
 */
char* nowTime;
const airkiss_config_t akconf = {
        (airkiss_memset_fn)&memset,
        (airkiss_memcpy_fn)&memcpy,
        (airkiss_memcmp_fn)&memcmp,
        0 };
 void* time_callback(void* args)
{
    //切换信道
  /*  if (cur_channel >= 13)
        cur_channel = 1;
    else
        cur_channel++;
    wifi_set_channel(cur_channel);
    airkiss_change_channel(akcontex);//清缓存*/
  while(1) {
      usleep(1000000);
      time_t now = time(0);
      nowTime = ctime(&now);
  }
}
 void scheduleThread() {
    pthread_t thread;
   int ret = pthread_create(&thread,NULL, time_callback, NULL);
 }


extern "C" JNIEXPORT jstring JNICALL
Java_com_elite_airkiss_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    /*std::string hello = airkiss_version();
    LOGD("airkiss version -> %s" ,hello.c_str());
    akcontex = (airkiss_context_t*)malloc(20*sizeof(char));
    memset(&akcontex,0,sizeof(char));
    int ret = airkiss_init(akcontex, &akconf);
    if (ret == 0) {
        LOGD("airkiss init success");
    } else {
        LOGE("airkiss init failed");
        return env->NewStringUTF("airkiss init failed");
    }*/
    scheduleThread();
    return env->NewStringUTF("Display now time!");
}
extern "C" JNIEXPORT jstring JNICALL
Java_com_elite_airkiss_MainActivity_getNowTimeFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    return env->NewStringUTF(nowTime);
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_elite_airkiss_MainActivity_getFileContentFromJNI(JNIEnv *env, jobject thiz, jstring path) {
    const char *str = env->GetStringUTFChars(path, 0);
    std::ifstream ifstream;
    ifstream.open(str, std::ios::in);
    std::string s;
    if (ifstream.good()) {
        LOGD("open file %s success ", str);
        while(getline(ifstream, s)) {
            LOGD("%s ",s.c_str());
        }
    } else {
        LOGE("open file %s failed ", str);
    }
    ifstream.close();
    return env->NewStringUTF(str);
}
extern "C"
JNIEXPORT jstring JNICALL
Java_com_elite_airkiss_MainActivity_writeFileContentFromJNI(JNIEnv *env, jobject thiz,
                                                            jstring path) {
    std::ofstream ofstream;
    const char *str = env->GetStringUTFChars(path, 0);
    ofstream.open(str);
    if (ofstream.good()) {
        LOGD("open file %s success ", str);
        ofstream << "hello word from C++" << std::endl;
        ofstream << "这是一个C++示例" << std::endl;
        ofstream.close();
    } else {
        LOGE("open file %s failed ", str);
    }
    return env->NewStringUTF(str);
}

/**
 * 遍历
 */
void foreachData() {
    using DynamicArray = std::vector<long>;
    DynamicArray dynamicArray = { 0L, 1L, 2L, 3L, 4L, 5L, 6L, 7L, 8L, 9L };
    for (DynamicArray::size_type index = 0; index < dynamicArray.size(); ++index) {
        LOGD("%ld", dynamicArray[index]);
    }
}

jdouble testCplusplusClass(double height, double length, double breadth) {
    Box box;
    Box *box1 = &box;
    box1->setHeight(height);
    box1->setLength(length);
    box1->setBreadth(breadth);
    double sum = box.sumBox();
    LOGD("Cplusplus test result -> %f", sum);
    Box box2(1.0,1.0,1.0);
    double sumBox2 = box2.sumBox();
    LOGD("sumBox2 -> %f", sumBox2);
    Box box3 = box2;
    return sum;
}

/**
 * 获取sd卡根目录
 * @param env
 * @return
 */
char getSdcardRootPath(JNIEnv *env){
    jclass envClz = env->FindClass("android/os/Environment");
    jmethodID getExternalStorageDirectory = env->GetStaticMethodID(envClz,
                                                                      "getExternalStorageDirectory",
                                                                      "()Ljava/io/File;");
    jobject jobject1 = env->CallStaticObjectMethod(envClz, getExternalStorageDirectory);
    jclass envFile = env->FindClass("java/io/File");
    jmethodID getAbsolutePath = env->GetMethodID(envFile,
                                                    "getAbsolutePath",
                                                    "()Ljava/lang/String;");
    jstring jstring1 = (jstring)env->CallObjectMethod(jobject1, getAbsolutePath);
    const char *path_utf = env->GetStringUTFChars(jstring1, NULL);
    LOGD("path_utf %s  ", path_utf);
    return *path_utf;
 }

extern "C"
JNIEXPORT jdouble JNICALL
Java_com_elite_airkiss_MainActivity_cPlusPlusClassFromJNI(JNIEnv *env, jobject thiz, jdouble a,jdouble b,jdouble c) {
    double height = a;
    double length = b;
    double breadth = c;
    return testCplusplusClass(height, length, breadth);
}