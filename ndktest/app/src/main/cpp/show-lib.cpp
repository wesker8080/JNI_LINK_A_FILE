#include <jni.h>
#include <string>
#include "include/airkiss.h"
#include "include/Hello.h"

extern "C"
jstring
Java_com_example_liuhe_ndktest_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    //Hello h;
    //std::string hello = h.getSay();
    std::string hello = airkiss_version();
    return env->NewStringUTF(hello.c_str());
}
