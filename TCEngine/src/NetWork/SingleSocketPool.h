#pragma once

#include "TCUtils.h"
#include "TCArrayList.h"
#include "TCByteStream.h"

namespace Tce {

    class SingleSocketPool {
    private:
        ArrayList<int> mSocketIndexs;
        ArrayList<ByteStream> mSocketStreams;
    public:
        static SingleSocketPool &GetInstance() {
            static SingleSocketPool _pool;
            return _pool;
        }
        int CreateSocket();
    };

}