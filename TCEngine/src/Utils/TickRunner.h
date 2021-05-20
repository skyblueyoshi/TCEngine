#pragma once

#include "SysConfig.h"

namespace Tce {
    class TickRunner {
    public:
        static uint64_t GetCurrentTickCount();
        static void DoSleep(unsigned long milliseconds);
    };
}