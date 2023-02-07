//
// Created by wang1 on 2022/8/16.
//

#ifndef HITOMI_TIMEUTILS_H
#define HITOMI_TIMEUTILS_H

#define DEBUG

#ifdef DEBUG // 在 LogUtils.h 中定义了，也可以单独使用另一个宏开控制开关

#include "LogUtils.h"
#include "SaveFileUtils.h"
#include "MacroFuncOverloadUtils.h"
#include <ctime>
#include <chrono>

#define __TIC__(...) VFUNC(__TIC__, __VA_ARGS__)
#define __TOC__(...) VFUNC(__TOC__, __VA_ARGS__)


#ifdef TICTOC_SAVE_FILE
#define __TIC__1(tag) auto time_##tag##_start = std::chrono::high_resolution_clock::now()
#define __TOC__1(tag) auto time_##tag##_end = std::chrono::high_resolution_clock::now();\
        auto time_##tag##_span = std::chrono::duration_cast<std::chrono::duration<double>>(time_##tag##_end - time_##tag##_start);\
        SaveFileUtils::writeLinesStatic("slamdemo", std::to_string(std::chrono::time_point_cast<std::chrono::milliseconds>(time_##tag##_end).time_since_epoch().count()) + "," + #tag + std::string(",") + std::to_string((time_##tag##_span.count()) * 1000))
#define __TIC__2(tag, level) auto time_##tag##_start = std::chrono::high_resolution_clock::now()
#define __TOC__2(tag, level) auto time_##tag##_end = std::chrono::high_resolution_clock::now();\
        auto time_##tag##_span = std::chrono::duration_cast<std::chrono::duration<double>>(time_##tag##_end - time_##tag##_start);\
        SaveFileUtils::writeLinesStatic("slamdemo", std::to_string(std::chrono::time_point_cast<std::chrono::milliseconds>(time_##tag##_end).time_since_epoch().count()) + "," + #tag /*+ std::string("-") + std::to_string(level)*/ + std::string(",") + std::to_string((time_##tag##_span.count()) * 1000))
#define __TIC__4(tag, level, row, col) auto time_##tag##_start = std::chrono::high_resolution_clock::now()
#define __TOC__4(tag, level, row, col) auto time_##tag##_end = std::chrono::high_resolution_clock::now();\
        auto time_##tag##_span = std::chrono::duration_cast<std::chrono::duration<double>>(time_##tag##_end - time_##tag##_start);\
        SaveFileUtils::writeLinesStatic("slamdemo", std::to_string(std::chrono::time_point_cast<std::chrono::milliseconds>(time_##tag##_end).time_since_epoch().count()) + "," + #tag + std::string("-") + std::to_string(level) + std::string("-") + std::to_string(row) + std::string("-") + std::to_string(col) + std::string(",") + std::to_string((time_##tag##_span.count()) * 1000))
#else
#define __TIC__1(tag) auto time_##tag##_start = std::chrono::high_resolution_clock::now()
#define __TOC__1(tag) auto time_##tag##_end = std::chrono::high_resolution_clock::now();\
        auto time_##tag##_span = std::chrono::duration_cast<std::chrono::duration<double>>(time_##tag##_end - time_##tag##_start);\
        LOGD(#tag " time: %.3f ms", (time_##tag##_span.count()) * 1000)
#endif

#else
#define __TIC__(tag)
#define __TOC__(tag)
#endif // DEBUG

#endif //HITOMI_TIMEUTILS_H
