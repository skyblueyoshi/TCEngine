#pragma once

#include "GraphicsResourceManager.h"
#include "Texture.h"

namespace Tce {

    class TextureManager : public GraphicsResourceManager<Texture> {
    public:
        TextureManager(std::shared_ptr<GraphicsDevice> &pDevice);
        virtual ~TextureManager() = default;
        // 从文件中加载贴图
        // @param path 文件路径
        // @return 贴图ID
        uint32_t LoadTextureFromFile(const std::string & path);
    };

}