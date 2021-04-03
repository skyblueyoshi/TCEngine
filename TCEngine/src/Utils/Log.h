#pragma once

#include <stdarg.h>

namespace Tce {

    enum EnumLogLevel {
        LOG_LEVEL_INFO,
        LOG_LEVEL_FATAL,
        LOG_LEVEL_ERROR,
        LOG_LEVEL_WARN,
        LOG_LEVEL_DEBUG
    };

    class Log {
    public:
        static void Info(const char * format, ...);
        static void Warn(const char * format, ...);
        static void Fatal(const char * format, ...);
        static void Error(const char * format, ...);
        static void Debug(const char * format, ...);
    private:
        // 执行一条日志信息
        // @param level         日志等级
        // @param showLabel     是否展示标签
        // @param label         若展示标签，表示标签字符串
        // @param showSysTime   是否展示系统时间
        // @param format        格式化文本
        // @param va_list       格式化文本对应可变参数
        static void _Logging(EnumLogLevel level, bool showLabel, const char *label, bool showSysTime, const char *format, va_list list);
    };

}

#define TCE_LOG_INFO(...) Tce::Log::Info(__VA_ARGS__)
#define TCE_LOG_WARN(...) Tce::Log::Warn(__VA_ARGS__)
#define TCE_LOG_FATAL(...) Tce::Log::Fatal(__VA_ARGS__)
#define TCE_LOG_ERROR(...) Tce::Log::Error(__VA_ARGS__)
#define TCE_LOG_DEBUG(...) Tce::Log::Debug(__VA_ARGS__)