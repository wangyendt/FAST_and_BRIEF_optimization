//
// Created by wang1 on 2022/8/16.
//

#ifndef HITOMI_LOGUTILS_H
#define HITOMI_LOGUTILS_H

#ifdef __ANDROID__ // Android平台
#include <android/log.h>
#else // 其它平台
#include <stdio.h>
#endif // __ANDROID__

#include <string.h>

#define DEBUG // 可以通过 CmakeLists.txt 等方式来定义在这个宏，实现动态打开和关闭LOG

// Windows 和 Linux 这两个宏是在 CMakeLists.txt 通过 ADD_DEFINITIONS 定义的
#ifdef Windows
#define __FILENAME__ (strrchr(__FILE__, '\\') + 1) // Windows下文件目录层级是'\\'
#else
#define __FILENAME__ (strrchr(__FILE__, '/') + 1) // Linux下文件目录层级是'/'，默认使用这种方式
#endif // Windows

#ifdef DEBUG // 如果打开了 DEBUG 开关

#ifdef __ANDROID__
#define TAG "wayne_proj"
#define LOGV(fmt, ...) __android_log_print(ANDROID_LOG_VERBOSE, TAG, "[%s][%s][%d]: " fmt, __FILENAME__, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define LOGD(fmt, ...) __android_log_print(ANDROID_LOG_DEBUG, TAG, "[%s][%s][%d]: " fmt, __FILENAME__, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define LOGI(fmt, ...) __android_log_print(ANDROID_LOG_INFO, TAG, "[%s][%s][%d]: " fmt, __FILENAME__, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define LOGW(fmt, ...) __android_log_print(ANDROID_LOG_WARN, TAG, "[%s][%s][%d]: " fmt, __FILENAME__, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define LOGE(fmt, ...) __android_log_print(ANDROID_LOG_ERROR, TAG, "[%s][%s][%d]: " fmt, __FILENAME__, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define LOGV2(tag, fmt, ...) __android_log_print(ANDROID_LOG_VERBOSE, tag, "[%s][%s][%d]: " fmt, __FILENAME__, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define LOGD2(tag, fmt, ...) __android_log_print(ANDROID_LOG_DEBUG, tag, "[%s][%s][%d]: " fmt, __FILENAME__, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define LOGI2(tag, fmt, ...) __android_log_print(ANDROID_LOG_INFO, tag, "[%s][%s][%d]: " fmt, __FILENAME__, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define LOGW2(tag, fmt, ...) __android_log_print(ANDROID_LOG_WARN, tag, "[%s][%s][%d]: " fmt, __FILENAME__, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define LOGE2(tag, fmt, ...) __android_log_print(ANDROID_LOG_ERROR, tag, "[%s][%s][%d]: " fmt, __FILENAME__, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#else
#define LOGV(fmt, ...) printf("[%s][%s][%d]: " fmt "\n", __FILENAME__, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define LOGD(fmt, ...) printf("[%s][%s][%d]: " fmt "\n", __FILENAME__, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define LOGI(fmt, ...) printf("[%s][%s][%d]: " fmt "\n", __FILENAME__, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define LOGW(fmt, ...) printf("[%s][%s][%d]: " fmt "\n", __FILENAME__, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define LOGE(fmt, ...) printf("[%s][%s][%d]: " fmt "\n", __FILENAME__, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#endif // __ANDROID__

#else // 如果没打开 DEBUG 开关，则只是一些空的语句
#define LOGV(fmt, ...)
#define LOGD(fmt, ...)
#define LOGI(fmt, ...)
#define LOGW(fmt, ...)
#define LOGE(fmt, ...)
#endif // DEBUG

#endif //HITOMI_LOGUTILS_H
