#include "Sprite.h"
#include "ExceptionHelper.h"
#include "TCMath.h"

namespace Tce {

    void
    Sprite::SpriteCache::Set(Texture *_pTexture, float _x, float _y, float _width, float _height,
                             float _texL, float _texT, float _texR, float _texB,
                             Color _color, float _depth) {
        this->pTexture = _pTexture;

        vertexs[TOP_LEFT].Set(_x, _y,
                              _depth, _color,
                              _texL, _texT);
        vertexs[TOP_RIGHT].Set(_x + _width, _y,
                               _depth, _color,
                               _texR, _texT);
        vertexs[BOTTOM_LEFT].Set(_x, _y + _height,
                                 _depth, _color,
                                 _texL, _texB);
        vertexs[BOTTOM_RIGHT].Set(_x + _width, _y + _height,
                                  _depth, _color,
                                  _texR, _texB);

    }

    void Sprite::SpriteCache::Set(Texture *_pTexture, const Vector2 &pos, const RectInt &sourceRect,
                                  Color color) {
        this->pTexture = _pTexture;

        float texW = 0, texH = 0, texL = 0, texT = 0, texR = 1, texB = 1;
        if (!sourceRect.Empty()) {
            texW = (float)sourceRect.width;
            texH = (float)sourceRect.height;
            texL = sourceRect.x * pTexture->GetTexelWidth();
            texT = sourceRect.y * pTexture->GetTexelHeight();
            texR = sourceRect.GetRight() * pTexture->GetTexelWidth();
            texB = sourceRect.GetBottom() * pTexture->GetTexelHeight();
        } else {
            texW = (float)pTexture->GetWidth();
            texH = (float)pTexture->GetHeight();
        }
        Set(pTexture,
            pos.x, pos.y,
            texW, texH,
            texL, texT,
            texR, texB,
            color, 0);
    }

    Sprite::Sprite(GraphicsDevice *pDevice) : GraphicsResource(pDevice) {

    }

    void
    Sprite::Draw(Texture *pTexture, const Vector2 &pos, const RectInt &sourceRect,
                 Color color) {
        CHECK_ARGUMENT_OR_ERROR(pTexture, pTexture != nullptr);
        _CheckRunning();

        auto &spriteCache = _CreateSpriteCache();
        spriteCache.Set(pTexture, pos, sourceRect, color);
        spriteCache.__sortKey =
                m_eSpriteSortMode == SpriteSortMode::TEXTURE ?
                (float) pTexture->__sortKey : 0;
    }

    void Sprite::_CheckRunning() {
        CHECK_RUNTIME_OR_ERROR(m_running, "Sprite draw call must between begin and end.");
    }

    Sprite::SpriteCache &Sprite::_CreateSpriteCache() {
        if (m_spriteCacheCount >= m_spriteCaches.size()) {
            m_spriteCaches.emplace_back(SpriteCache());
        }
        return m_spriteCaches[m_spriteCacheCount++];
    }

    void Sprite::Begin() {
        m_running = true;
    }

    void Sprite::End() {
        CHECK_RUNTIME_OR_ERROR(m_running, "Begin must called before calling End.");
        m_running = false;
        // TODO shader

        Flush();
    }

    void Sprite::Flush() {
        // TODO shader

        if (m_spriteCacheCount > 0) {
            switch (m_eSpriteSortMode) {
                case SpriteSortMode::TEXTURE:
                case SpriteSortMode::BACK_TO_FRONT:
                case SpriteSortMode::FRONT_TO_BACK:
                    TCMath::SortByKey<SpriteCache>(m_spriteCaches);
                    break;
                default:
                    break;
            }
        }
    }

}

