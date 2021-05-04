#include "SingleSocketPool.h"

namespace Tce {


    int SingleSocketPool::CreateSocket() {
        for (int mSocketIndex : mSocketIndexs) {
            if (mSocketIndex == -1) {
                //TODO
            }
        }

        return 0;
    }
}