#include <algorithm>
#include "Texture.h"
#include "ExceptionHelper.h"

namespace Tce {

    uint32_t Texture::sSortKey = 0;

    // 计算mipmap层数
    // @param 宽度
    // @param 高度
    // @return MipMap层数
    static uint32_t _CalculateMipLevels(uint32_t width, uint32_t height) {
        uint32_t levels = 1;
        uint32_t size = TCMath::Max(width, height);
        while (size > 1) {
            size /= 2;
            levels++;
        }
        return levels;
    }

    Texture::Texture(uint32_t handle, uint32_t width, uint32_t height)
            : Texture(handle, width, height, false, EnumSurfaceFormat::Color, EnumSurfaceType::TEXTURE) {}

    Texture::Texture(uint32_t handle, uint32_t width, uint32_t height, bool mipmap, EnumSurfaceFormat format)
            : Texture(handle, width, height, mipmap, format, EnumSurfaceType::TEXTURE) {}

    Texture::Texture(uint32_t handle, uint32_t width, uint32_t height, bool mipmap, EnumSurfaceFormat format,
                     Texture::EnumSurfaceType type)
            : GraphicsResource(handle), m_width(width), m_height(height),
              m_texelWidth(1.0f / width), m_texelHeight(1.0f / height),
              m_eFormat(format),
              m_levelCount(mipmap ? _CalculateMipLevels(width, height) : 1),
              m_type(type) {
        CHECK_ARGUMENT_OR_ERROR(width, width > 0);
        CHECK_ARGUMENT_OR_ERROR(height, height > 0);
    }
}

