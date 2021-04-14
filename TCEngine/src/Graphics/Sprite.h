#pragma once

#include "../Type/Rect.h"
#include <src/Type/Vector.h>
#include <src/Type/Color.h>
#include <src/Type/VertexFormat.h>
#include <vector>
#include "GraphicsResource.h"
#include "Texture.h"

namespace Tce {

    enum class SpriteSortMode {
        DEFERRED,       // 在End时绘制，忽略深度排序
        IMMEDIATE,      // 在Draw时立即绘制，忽略深度排序
        TEXTURE,        // 在End时绘制，将会按照Texture指针排序
        BACK_TO_FRONT,  // 在End时绘制，按照深度从后往前绘制
        FRONT_TO_BACK   // 在End时绘制，按照深度从前往后绘制
    };

    // 精灵渲染器类
    class Sprite : public GraphicsResource {

        const int MAX_VERTEX_BATCH_SIZE = 2048;      // 单次批量处理顶点个数

        // 精灵缓存信息
        struct SpriteCache {
            enum EnumVertexLocation {
                TOP_LEFT,
                TOP_RIGHT,
                BOTTOM_LEFT,
                BOTTOM_RIGHT,
                LOCATION_TOTAL
            };
            // 精灵贴图指针
            Texture *pTexture{nullptr};
            // 四个顶点信息
            VertexPositionColorTexture vertexs[LOCATION_TOTAL];

            SpriteCache() = default;

            // 设置信息
            void Set(Texture *_pTexture, const Vector2 &pos,
                     const RectInt &sourceRect, Color color);
            // 设置信息
            void Set(Texture *_pTexture, float _x, float _y, float _width, float _height,
                     float _texL, float _texT, float _texR, float _texB,
                     Color _color, float _depth);
        };

    public:
        Sprite(GraphicsDevice* pDevice);

        virtual ~Sprite() = default;

        void Begin();

        void End();

        void Flush();

        // 绘制一个精灵
        // @param pTexture 贴图指针
        // @param pos 渲染坐标
        // @param source 贴图剪裁区域
        // @param color 精灵颜色
        void Draw(Texture *pTexture, const Vector2 &pos,
                  const RectInt &sourceRect, Color color);

    private:

        // 检查绘制是否在生命周期内
        // 不在生命周期内则抛出异常
        void _CheckRunning();

        // 增加一个精灵缓存
        SpriteCache& _CreateSpriteCache();

    private:
        bool m_running{};                               // 正在一个精灵渲染的生命周期内
        SpriteSortMode m_eSpriteSortMode{};               // 当前排序模式
        std::vector<SpriteCache> m_spriteCaches;        // 精灵缓存列表
        size_t m_spriteCacheCount{};                    // 精灵缓存数量
    };

}