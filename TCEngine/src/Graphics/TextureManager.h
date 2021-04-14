#pragma once

#include "GraphicsResourceManager.h"
#include "Texture.h"

namespace Tce {

    class TextureManager : public GraphicsResourceManager<Texture> {
    public:
        TextureManager(GraphicsDevice* pDevice);
        virtual ~TextureManager() = default;
        // 从文件中加载贴图
        // @param path 文件路径
        // @return 贴图ID
        uint32_t LoadTextureFromFile(const std::string & path);

        // 卸载并清除指定贴图
        // @param pTexture 贴图指针
        void Unload(std::shared_ptr<Texture> & pTexture);
    };

}