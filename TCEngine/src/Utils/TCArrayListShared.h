#pragma once

#include "TCArrayList.h"

namespace Tce {

    template <typename T>
    class ArrayListShared : public ArrayList<std::shared_ptr<T>> {
    public:
    
    };

}