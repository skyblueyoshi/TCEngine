#pragma once

#include <Type/SurfaceFormat.h>
#include "GraphicsResource.h"

namespace Tce {

    // 纹理
    class Texture : public GraphicsResource {
    public:
        // 表面类型
        enum EnumSurfaceType {
            TEXTURE,
            RENDER_TARGET,
            SWAP_CHAIN_RENDER_TARGET
        };

        // 构造函数
        // @param width 纹理宽度
        // @param height 纹理高度
        Texture(uint32_t handle, uint32_t width, uint32_t height);

        // 构造函数
        // @param width 纹理宽度
        // @param height 纹理高度
        // @param mipmap 是否使用MipMap
        // @param format 纹理表面格式
        Texture(uint32_t handle, uint32_t width, uint32_t height, bool mipmap, EnumSurfaceFormat format);

        // 构造函数
        // @param width 纹理宽度
        // @param height 纹理高度
        // @param mipmap 是否使用MipMap
        // @param format 纹理表面格式
        // @param type 纹理表面类型
        Texture(uint32_t handle, uint32_t width, uint32_t height, bool mipmap, EnumSurfaceFormat format,
                EnumSurfaceType type);

        // 获取表面格式
        // @return 表面格式
        inline EnumSurfaceFormat GetFormat() const {
            return m_eFormat;
        }

        // 获取层数
        // @return mipmap层数
        inline uint32_t GetLevelCount() const {
            return m_levelCount;
        }

        // 获取纹理宽度
        // @return 纹理宽度
        inline uint32_t GetWidth() const {
            return m_width;
        }

        // 获取纹理高度
        // @return 纹理高度
        inline uint32_t GetHeight() const {
            return m_height;
        }

        // 获取纹理横向单位
        // @return 纹理横向单位
        inline float GetTexelWidth() const {
            return m_texelWidth;
        }

        // 获取纹理纵向单位
        // @return 纹理纵向单位
        inline float GetTexelHeight() const {
            return m_texelHeight;
        }

    private:
        uint32_t m_width{};                             // 纹理宽度
        uint32_t m_height{};                            // 纹理高度
        float m_texelWidth{};                       // 纹理横向单位
        float m_texelHeight{};                      // 纹理纵向单位
        static uint32_t sSortKey;                       // 静态纹理排序键
        EnumSurfaceFormat m_eFormat{};              // 表面格式
        uint32_t m_levelCount{};                        // MipMap层数
        EnumSurfaceType m_type{};                   // 表面类型
    public:
        uint32_t __sortKey{sSortKey++};                 // 纹理排序键
    };

}

