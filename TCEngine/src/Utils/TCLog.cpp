#define _CRT_SECURE_NO_WARNINGS

#include "TCLog.h"

#ifdef _TC_ANDROID
#include <android/log.h>
#define LOG_TAG "TCEngine"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#endif

namespace Tce {

    static std::mutex s_logMutex;

#ifdef _TC_ANDROID
    static int _GetAndroidLevel(EnumLogLevel level) {
        switch (level) {
            case LOG_LEVEL_INFO:
                return ANDROID_LOG_INFO;
            case LOG_LEVEL_FATAL:
                return ANDROID_LOG_FATAL;
            case LOG_LEVEL_ERROR:
                return ANDROID_LOG_ERROR;
            case LOG_LEVEL_WARN:
                return ANDROID_LOG_WARN;
            case LOG_LEVEL_DEBUG:
                return ANDROID_LOG_DEBUG;
            default:
                break;
        }
        return ANDROID_LOG_INFO;
    }
#endif

    void Log::_Logging(EnumLogLevel level, bool showLabel, const char *label, bool showSysTime, const char *format, va_list list) {
        std::lock_guard<std::mutex> lockGuard(s_logMutex);
        String content;
        if (showLabel) {
            content = label;
            if (showSysTime) {
                time_t t = time(nullptr);
                auto _tm = *localtime(&t);
                int hh = _tm.tm_hour;
                int mm = _tm.tm_min;
                int ss = _tm.tm_sec;
                content += String::Format("[%02d:%02d:%02d]", hh,mm,ss);
            }
        }
        content += String::FormatFromList(format, list);
        // 打印
#if     !defined(__ANDROID__)
        std::printf("%s", content.Data());
#else
        __android_log_print(_GetAndroidLevel(level), LOG_TAG, "%s", content.Data());
#endif
    }

#define TCE_AUTO_LOG(level, label) {\
    va_list args;\
    va_start(args, format);\
    _Logging(level, true, label, true, format, args);\
    va_end(args);\
}

    void Log::Info(const char *format, ...) {
        TCE_AUTO_LOG(LOG_LEVEL_INFO, "Info");
    }

    void Log::Warn(const char *format, ...) {
        TCE_AUTO_LOG(LOG_LEVEL_WARN, "Warn");
    }

    void Log::Fatal(const char *format, ...) {
        TCE_AUTO_LOG(LOG_LEVEL_DEBUG, "Debug");
    }

    void Log::Error(const char *format, ...) {
        TCE_AUTO_LOG(LOG_LEVEL_ERROR, "Error");
    }

    void Log::Debug(const char *format, ...) {
        TCE_AUTO_LOG(LOG_LEVEL_DEBUG, "Debug");
    }

}