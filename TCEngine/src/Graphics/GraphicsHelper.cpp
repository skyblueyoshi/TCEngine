#include <src/Utils/Log.h>
#include "GraphicsHelper.h"
#include "GraphicsDevice.h"

namespace Tce {

    void GraphicsHelper::CheckError() {
        bool hasError = false;
#if defined(OPENGL)
        for (GLint error = glGetError(); error; error = glGetError()) {
            hasError = true;
            TCE_LOG_ERROR("glError (0x%x)\n", error);
        }
#endif
        if (hasError) {
            throw std::exception();
        }
    }
}