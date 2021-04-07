#pragma once

#include <cstring>
#include "Vector.h"

namespace Tce {

    struct Vector4;

    // 4x4矩阵
    struct Matrix {
    public:
        union {
            struct {
                float _11, _12, _13, _14;
                float _21, _22, _23, _24;
                float _31, _32, _33, _34;
                float _41, _42, _43, _44;
            };
            float m[4][4];
        };

        Matrix() = default;

        // 构造一个矩阵
        Matrix(float m11, float m12, float m13, float m14,
               float m21, float m22, float m23, float m24,
               float m31, float m32, float m33, float m34,
               float m41, float m42, float m43, float m44) noexcept;

        // 构造一个矩阵
        // @param row1 矩阵第一行向量
        // @param row2 矩阵第二行向量
        // @param row3 矩阵第三行向量
        // @param row4 矩阵第四行向量
        Matrix(const Vector4 &row1, const Vector4 &row2, const Vector4 &row3,
               const Vector4 &row4);

        // 比较两个矩阵是否相同
        // @matrix 另一个矩阵
        // @return 是否相同
        bool operator==(const Matrix & matrix);

        // 比较两个矩阵是否不同
        // @matrix 另一个矩阵
        // @return 是否不同
        bool operator!=(const Matrix & matrix);

        // 矩阵相加
        // @matrix 另一个矩阵
        // @return 结果矩阵
        Matrix operator+(const Matrix & matrix);

        // 矩阵相加
        // @matrix 另一个矩阵
        Matrix& operator+=(const Matrix & matrix);

        // 矩阵相减
        // @matrix 另一个矩阵
        // @return 结果矩阵
        Matrix operator-(const Matrix & matrix);

        // 矩阵相减
        // @matrix 另一个矩阵
        Matrix& operator-=(const Matrix & matrix);

        // 矩阵取反
        // @return 结果矩阵
        Matrix operator-();

        // 矩阵相乘
        // @matrix 另一个矩阵
        // @return 结果矩阵
        Matrix operator*(const Matrix & matrix);

        // 矩阵每个元素乘以一个数值
        // @scaleFactor 数值
        // @return 结果矩阵
        Matrix operator*(float scaleFactor);

        // 矩阵相除
        // @matrix 另一个矩阵
        // @return 结果矩阵
        Matrix operator/(const Matrix & matrix);

        // 矩阵每个元素除以一个数值
        // @divider 数值
        // @return 结果矩阵
        Matrix operator/(float divider);

        // 返回一个表示矩阵的字符串
        // @return 字符串
        std::string ToString();

        // 转置矩阵，即行列交换
        // @return 结果矩阵
        Matrix Transpose();

        // 返回包含指定矩阵中值的线性插值矩阵
        // @param matrix 指定矩阵
        // @param amount 插值
        // @return 结果矩阵
        Matrix Lerp(Matrix matrix, float amount);

        // 矩阵逆变换
        // @return 结果矩阵
        Matrix Invert();

        // 求矩阵行列式
        // @return 行列式结果
        float Determinant();

        // 获取存储坐标
        // 返回向量{M41, M42, M43}
        Vector3 GetTranslation();

        // 写入存储坐标{M41, M42, M43}
        void SetTranslation(const Vector3 & vector3);

        // 获取左向量{-M11, -M12, -M13}
        Vector3 GetLeft();

        // 写入左向量{-M11, -M12, -M13}
        void SetLeft(const Vector3 & vector3);

        // 获取右向量{M11, M12, M13}
        Vector3 GetRight();

        // 写入右向量{M11, M12, M13}
        void SetRight(const Vector3 & vector3);

        // 获取上向量{M21, M22, M23}
        Vector3 GetUp();

        // 写入上向量{M21, M22, M23}
        void SetUp(const Vector3 & vector3);

        // 获取下向量{-M21, -M22, -M23}
        Vector3 GetDown();

        // 写入下向量{-M21, -M22, -M23}
        void SetDown(const Vector3 & vector3);

        // 获取前向量{-M31, -M32, -M33}
        Vector3 GetForward();

        // 写入前向量{-M31, -M32, -M33}
        void SetForward(const Vector3 & vector3);

        // 获取后向量{M31, M32, M33}
        Vector3 GetBackward();

        // 写入后向量{M31, M32, M33}
        void SetBackward(const Vector3 & vector3);

        //单位矩阵
        static const Matrix identity;
    };

}