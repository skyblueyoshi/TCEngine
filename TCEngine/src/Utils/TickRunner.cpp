
#include "TickRunner.h"
#include "Log.h"
#include <ctime>

#ifdef _WINDOWS
#include <windows.h>
#else
#include <unistd.h>
#include <assert.h>

#define Sleep(x) usleep((x)*1000L)
#endif

namespace Tce {

    // 每个平台的解决方案：
    // https://stackoverflow.com/a/56218976
    uint64_t TickRunner::GetCurrentTickCount() {
        //TODO 完善跨平台TICK处理
#if defined(_WINDOWS)
        return GetTickCount64();
#else
        struct timespec up{};
        int err = clock_gettime(CLOCK_BOOTTIME, &up);
        if (err != 0) {
            assert(false);
            //TODO 异常处理
        }
        uint64_t msec = (uint64_t)up.tv_sec * 1000L + (uint64_t)up.tv_nsec / 1000000L;
        //TCE_LOG_INFO("%ld  %ld -> %lld", up.tv_sec, up.tv_nsec, msec);
        return msec;
#endif
    }

    void TickRunner::DoSleep(unsigned long milliseconds) {
        Sleep(milliseconds);
    }

}