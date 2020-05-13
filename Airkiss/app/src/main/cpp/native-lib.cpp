#include <jni.h>
#include <string>
#include <stdlib.h>
#include "include/airkiss.h"
#include "logUtils.h"
#include <cstring>
#include<android/log.h>
#include <pthread.h>
#include <iostream>
#include <ctime>
#include <unistd.h>
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
    //std::string hello = "Hello from C++";
    std::string hello = airkiss_version();
    // setp1 check version
    LOGD("airkiss version -> %s" ,hello.c_str());
    // step2 malloc

    akcontex = (airkiss_context_t*)malloc(20*sizeof(char));
    memset(&akcontex,0,sizeof(char));
    //step3 init
    int ret = airkiss_init(akcontex, &akconf);
    if (ret == 0) {
        LOGD("airkiss init success");
    } else {
        LOGE("airkiss init failed");
        return env->NewStringUTF("airkiss init failed");
    }
    scheduleThread();
    return env->NewStringUTF("Display now time!");
}
extern "C" JNIEXPORT jstring JNICALL
Java_com_elite_airkiss_MainActivity_getNowTimeFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    return env->NewStringUTF(nowTime);
}

