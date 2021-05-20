#pragma once

#include "SysConfig.h"

namespace Tce {

    class TCObject {
    public:
        virtual int GetHashCode() {
            return 0;
        }
    };

}