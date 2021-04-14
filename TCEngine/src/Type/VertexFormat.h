#pragma once

#include "Vector.h"
#include "Color.h"

namespace Tce {


    // 顶点格式：顶点坐标、顶点颜色
    struct VertexPositionColor {
        Vector3 position;
        Color color;

        VertexPositionColor(const Vector3 &_position, const Color &_color)
                : position(_position), color(_color) {}

        bool operator==(const VertexPositionColor &other) {
            return position == other.position &&
                   color == other.color;
        }

        bool operator!=(const VertexPositionColor &other) {
            return position != other.position ||
                   color != other.color;
        }
    };

    // 顶点格式：顶点坐标、顶点颜色、对应贴图UV坐标
    struct VertexPositionColorTexture {
        Vector3 position;
        Color color;
        Vector2 textureCoordinate;

        VertexPositionColorTexture() = default;
        VertexPositionColorTexture(const Vector3 &_position, Color _color,
                                   const Vector2 &_textureCoordinate)
                : position(_position), color(_color), textureCoordinate(_textureCoordinate) {}

        bool operator==(const VertexPositionColorTexture &other) {
            return position == other.position &&
                   color == other.color &&
                   textureCoordinate == other.textureCoordinate;
        }

        bool operator!=(const VertexPositionColorTexture &other) {
            return position != other.position ||
                   color != other.color ||
                   textureCoordinate != other.textureCoordinate;
        }

        // 写入数据
        void Set(float _x, float _y, float _z, Color _color, float _texX, float _texY) {
            position.x = _x;
            position.y = _y;
            position.z = _z;
            color = _color;
            textureCoordinate.x = _texX;
            textureCoordinate.y = _texY;
        }
    };

}