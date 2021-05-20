
#include "TickRunner.h"

namespace Tce {

    uint64_t TickRunner::GetCurrentTickCount() {
        return TC_GetTickCount();
    }

    void TickRunner::DoSleep(unsigned long milliseconds) {
        TC_Sleep(milliseconds);
    }

}