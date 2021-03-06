//#include "TextureManager.h"
//#include "GraphicsDevice.h"
//
//namespace Tce {
//    TextureManager::TextureManager(GraphicsDevice* pDevice)
//            : GraphicsResourceManager(pDevice) {
//
//    }
//
//    uint32_t TextureManager::LoadTextureFromFile(const String &path) {
//        auto pTexture = m_pDevice->CreateTextureFromFile(path);
//        return GraphicsResourceManager::Load(pTexture);
//    }
//
//    void TextureManager::Unload(std::shared_ptr<Texture> &pTexture) {
//        if (pTexture) {
//            m_pDevice->DisposeTexture(pTexture->GetHandle());
//            GraphicsResourceManager::Unload(pTexture);
//        }
//    }
//}

#include "TextureManager.h"
#include "TCFile.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <GLES2/gl2.h>
#include <Utils/TCString.h>
#include "GraphicsDevice.h"

namespace Tce {
    TextureManager::TextureManager(GraphicsDevice* pDevice)
            : GraphicsResourceManager(pDevice) {

    }

    uint32_t TextureManager::LoadTextureFromFile(const String &path) {
        ArrayList<uint8_t> fileBits;
        if (!File::Open(path, fileBits)) {

        }
        int32_t imgWidth, imgHeight, imgChannelCount;
        stbi_set_flip_vertically_on_load(1);
        uint8_t *imageBits = stbi_load_from_memory(
                fileBits.Data(), fileBits.Count(),
                &imgWidth, &imgHeight, &imgChannelCount,
                STBI_rgb_alpha);
        // 创建纹理
        uint32_t handle = 0;
        glGenTextures(1, &handle);
        glBindTexture(GL_TEXTURE_2D, handle);
        // 传入纹理
        glTexImage2D(GL_TEXTURE_2D,
                     0, GL_RGBA,
                     imgWidth, imgHeight,
                     0, GL_RGBA,
                     GL_UNSIGNED_BYTE, imageBits);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

        stbi_image_free(imageBits);

        std::shared_ptr<Texture> pTexture = std::make_shared<Texture>(handle, imgWidth, imgHeight);
        return GraphicsResourceManager::Load(pTexture);
    }

    void TextureManager::Unload(std::shared_ptr<Texture> &pTexture) {
        if (pTexture) {
            m_pDevice->DisposeTexture(pTexture->GetHandle());
            GraphicsResourceManager::Unload(pTexture);
        }
    }
}