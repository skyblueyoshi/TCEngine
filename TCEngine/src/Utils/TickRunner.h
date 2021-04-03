#pragma once

#include <cstdint>

namespace Tce {
    class TickRunner {
    public:
        static uint64_t GetCurrentTickCount();
        static void DoSleep(unsigned long milliseconds);
    };
}