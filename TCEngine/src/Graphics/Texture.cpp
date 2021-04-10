#include <algorithm>
#include "Texture.h"
#include "ExceptionHelper.h"

namespace Tce {

    // 计算mipmap层数
    // @param 宽度
    // @param 高度
    // @return MipMap层数
    static uint _CalculateMipLevels(uint width, uint height) {
        uint levels = 1;
        uint size = std::max(width, height);
        while (size > 1) {
            size /= 2;
            levels++;
        }
        return levels;
    }

    Texture::Texture(uint width, uint height)
            : Texture(width, height, false, EnumSurfaceFormat::Color, EnumSurfaceType::TEXTURE) {}

    Texture::Texture(uint width, uint height, bool mipmap, EnumSurfaceFormat format)
            : Texture(width, height, mipmap, format, EnumSurfaceType::TEXTURE) {}

    Texture::Texture(uint width, uint height, bool mipmap, EnumSurfaceFormat format,
                     Texture::EnumSurfaceType type)
            : m_width(width), m_height(height),
              m_texelWidth(1.0f / width), m_texelHeight(1.0f / height),
              m_eFormat(format),
              m_levelCount(mipmap ? _CalculateMipLevels(width, height) : 1) {
        CHECK_ARGUMENT_OR_ERROR(width, width > 0);
        CHECK_ARGUMENT_OR_ERROR(height, height > 0);
    }
}

