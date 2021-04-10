#include "TextureManager.h"
#include <SDL_image.h>

namespace Tce {
    TextureManager::TextureManager(std::shared_ptr<GraphicsDevice> &pDevice)
            : GraphicsResourceManager(pDevice) {

    }

    uint32_t TextureManager::LoadTextureFromFile(const std::string &path) {
        SDL_Surface *p = IMG_Load("test.png");
        return 0;
    }
}