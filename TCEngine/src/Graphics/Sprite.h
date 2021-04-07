#pragma once

#include "GraphicsResource.h"

namespace Tce {

    class Sprite : public GraphicsResource {
    public:
        Sprite(std::shared_ptr<GraphicsDevice> & pDevice);
        virtual ~Sprite() = default;
        void Begin();
        void End();
        void Flush();
    };

}