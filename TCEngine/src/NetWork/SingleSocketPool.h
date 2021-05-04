#pragma once

#include <vector>
#include <Utils/ByteStream.h>

namespace Tce {

    class SingleSocketPool {
    private:
        std::vector<int> mSocketIndexs;
        std::vector<ByteStream> mSocketStreams;
    public:
        static SingleSocketPool &GetInstance() {
            static SingleSocketPool _pool;
            return _pool;
        }
        int CreateSocket();
    };

}