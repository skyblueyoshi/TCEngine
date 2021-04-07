#pragma once

#include <string>

namespace Tce {

    struct Matrix;

    // 2维向量{X, Y}
    struct Vector2 {
        float x{};
        float y{};

        // 零向量
        static const Vector2 kZero;
        // 全1向量
        static const Vector2 kOne;
        // X轴单位向量
        static const Vector2 kUnitX;
        // Y轴单位向量
        static const Vector2 kUnitY;

        Vector2() noexcept = default;

        Vector2(float _x, float _y) noexcept
                : x(_x), y(_y) {}

        Vector2(const Vector2 &value) noexcept
                : x(value.x), y(value.y) {}

        // 返回一个表示向量的字符串
        // @result 字符串
        std::string ToString() const;

        // 判断两个向量是否相同
        // @param value 另一个向量
        // @return 结果
        bool operator==(const Vector2 &value) const;

        // 判断两个向量是否不同
        // @param value 另一个向量
        // @return 结果
        bool operator!=(const Vector2 &value) const;

        // 向量相加
        // @param value 另一个向量
        // @return 结果
        Vector2 operator+(const Vector2 &value) const;

        // 向量相加
        // @param value 另一个向量
        Vector2 &operator+=(const Vector2 &value);

        // 向量相减
        // @param value 另一个向量
        // @return 结果
        Vector2 operator-(const Vector2 &value) const;

        // 向量相减
        // @param value 另一个向量
        Vector2 &operator-=(const Vector2 &value);

        // 向量取反
        Vector2 operator-();

        // 向量相乘
        // @param value 另一个向量
        // @return 结果
        Vector2 operator*(const Vector2 &value) const;

        // 向量相乘
        // @param value 另一个向量
        Vector2 &operator*=(const Vector2 &value);

        // 向量每个维度乘以一个数值
        // @param value 数值
        // @return 结果
        Vector2 operator*(float value) const;

        // 向量每个维度乘以一个数值
        // @param value 数值
        Vector2 &operator*=(float value);

        // 向量相除
        // @param value 另一个向量
        // @return 结果
        Vector2 operator/(const Vector2 &value) const;

        // 向量相除
        // @param value 另一个向量
        Vector2 &operator/=(const Vector2 &value);

        // 向量每个维度除以一个数值
        // @param value 数值
        // @return 结果
        Vector2 operator/(float value) const;

        // 向量每个维度除以一个数值
        // @param value 数值
        Vector2 &operator/=(float value);

        // 向量单位化
        void Normalize();

        // 向量单位化
        // @param value 原向量
        // @return 单位向量
        static Vector2 Normalize(const Vector2 &value);

        // 获取两个向量的最大值向量
        // @param value1 向量1
        // @param value2 向量2
        // @return 结果向量
        static Vector2 Max(const Vector2 &value1, const Vector2 &value2);

        // 获取两个向量的最小值向量
        // @param value1 向量1
        // @param value2 向量2
        // @return 结果向量
        static Vector2 Min(const Vector2 &value1, const Vector2 &value2);

        // 获取向量长度
        // @return 向量长度
        float GetLength() const;

        // 获取向量长度的平方
        // @return 向量长度的平方
        float GetLengthSquared() const;

        // 将每个维度向下取整
        void Floor();

        // 将向量每个维度向下取整
        // @param value 原向量
        // @return 结果向量
        static Vector2 Floor(const Vector2 &value);

        // 将每个维度向上取整
        void Ceil();

        // 将向量每个维度向上取整
        // @param value 原向量
        // @return 结果向量
        static Vector2 Ceil(const Vector2 &value);

        // 限制向量到给定范围
        // @param value 原向量
        // @param min 最小量
        // @param max 最大量
        // @return 结果向量
        void Clamp(const Vector2 &min, const Vector2 &max);

        // 限制向量到给定范围
        // @param value 原向量
        // @param min 最小量
        // @param max 最大量
        // @return 结果向量
        static Vector2 Clamp(const Vector2 &value, const Vector2 &min, const Vector2 &max);

        // 获取向量之间的距离
        // @param value1 向量1
        // @param value2 向量2
        // @return 距离
        static float GetDistance(const Vector2 &value1, const Vector2 &value2);

        // 获取向量之间的距离平方
        // @param value1 向量1
        // @param value2 向量2
        // @return 距离平方
        static float GetDistanceSquared(const Vector2 &value1, const Vector2 &value2);

        // 将两个向量点乘，即每个维度乘积之和
        // @param value1 向量1
        // @param value2 向量2
        // @return 点乘结果
        static float Dot(const Vector2 &value1, const Vector2 &value2);

        // 向量转换
        static Vector2 Transform(const Vector2 &position, const Matrix &matrix);

        static void Transform(const Vector2 &position, const Matrix &matrix, Vector2 &result);

        // 零向量
        static const Vector2 ZERO;
        // 全1向量
        static const Vector2 ONE;
        // X轴单位向量
        static const Vector2 UNIT_X;
        // Y轴单位向量
        static const Vector2 UNIT_Y;
    };

    // 3维向量{X, Y, Z}
    struct Vector3 {
        float x{};
        float y{};
        float z{};

        // 零向量
        static const Vector3 kZero;
        // 全1向量
        static const Vector3 kOne;
        // X轴单位向量
        static const Vector3 kUnitX;
        // Y轴单位向量
        static const Vector3 kUnitY;
        // Z轴单位向量
        static const Vector3 kUnitZ;

        Vector3() noexcept = default;

        Vector3(float _x, float _y, float _z) noexcept
                : x(_x), y(_y), z(_z) {}

        Vector3(const Vector2 &value, float _z) noexcept
                : x(value.x), y(value.y), z(_z) {}

        // 构造函数
        // 各个维度填充相同值
        // @param value 每个维度填充值
        Vector3(float value) noexcept
                : x(value), y(value), z(value) {}

        // 返回一个表示向量的字符串
        // @result 字符串
        std::string ToString() const;

        // 判断两个向量是否相同
        // @param value 另一个向量
        // @return 结果
        bool operator==(const Vector3 &value) const;

        // 判断两个向量是否不同
        // @param value 另一个向量
        // @return 结果
        bool operator!=(const Vector3 &value) const;

        // 向量相加
        // @param value 另一个向量
        // @return 结果
        Vector3 operator+(const Vector3 &value) const;

        // 向量相加
        // @param value 另一个向量
        Vector3 &operator+=(const Vector3 &value);

        // 向量相减
        // @param value 另一个向量
        // @return 结果
        Vector3 operator-(const Vector3 &value) const;

        // 向量相减
        // @param value 另一个向量
        Vector3 &operator-=(const Vector3 &value);

        // 向量取反
        Vector3 operator-();

        // 向量相乘
        // @param value 另一个向量
        // @return 结果
        Vector3 operator*(const Vector3 &value) const;

        // 向量相乘
        // @param value 另一个向量
        Vector3 &operator*=(const Vector3 &value);

        // 向量每个维度乘以一个数值
        // @param value 数值
        // @return 结果
        Vector3 operator*(float value) const;

        // 向量每个维度乘以一个数值
        // @param value 数值
        Vector3 &operator*=(float value);

        // 向量相除
        // @param value 另一个向量
        // @return 结果
        Vector3 operator/(const Vector3 &value) const;

        // 向量相除
        // @param value 另一个向量
        Vector3 &operator/=(const Vector3 &value);

        // 向量每个维度除以一个数值
        // @param value 数值
        // @return 结果
        Vector3 operator/(float value) const;

        // 向量每个维度除以一个数值
        // @param value 数值
        Vector3 &operator/=(float value);

        // 向量单位化
        void Normalize();

        // 向量单位化
        // @param value 原向量
        // @return 单位向量
        static Vector3 Normalize(const Vector3 &value);

        // 获取两个向量的最大值向量
        // @param value1 向量1
        // @param value2 向量2
        // @return 结果向量
        static Vector3 Max(const Vector3 &value1, const Vector3 &value2);

        // 获取两个向量的最小值向量
        // @param value1 向量1
        // @param value2 向量2
        // @return 结果向量
        static Vector3 Min(const Vector3 &value1, const Vector3 &value2);

        // 获取向量长度
        // @return 向量长度
        float GetLength() const;

        // 获取向量长度的平方
        // @return 向量长度的平方
        float GetLengthSquared() const;

        // 将每个维度向下取整
        void Floor();

        // 将向量每个维度向下取整
        // @param value 原向量
        // @return 结果向量
        static Vector3 Floor(const Vector3 &value);

        // 将每个维度向上取整
        void Ceil();

        // 将向量每个维度向上取整
        // @param value 原向量
        // @return 结果向量
        static Vector3 Ceil(const Vector3 &value);

        // 限制向量到给定范围
        // @param value 原向量
        // @param min 最小量
        // @param max 最大量
        // @return 结果向量
        void Clamp(const Vector3 &min, const Vector3 &max);

        // 限制向量到给定范围
        // @param value 原向量
        // @param min 最小量
        // @param max 最大量
        // @return 结果向量
        static Vector3 Clamp(const Vector3 &value, const Vector3 &min, const Vector3 &max);

        // 获取向量之间的距离
        // @param value1 向量1
        // @param value2 向量2
        // @return 距离
        static float GetDistance(const Vector3 &value1, const Vector3 &value2);

        // 获取向量之间的距离平方
        // @param value1 向量1
        // @param value2 向量2
        // @return 距离平方
        static float GetDistanceSquared(const Vector3 &value1, const Vector3 &value2);

        // 将两个向量点乘，即每个维度乘积之和
        // @param value1 向量1
        // @param value2 向量2
        // @return 点乘结果
        static float Dot(const Vector3 &value1, const Vector3 &value2);


        // 向量转换
        static Vector3 Transform(const Vector3 &position, const Matrix &matrix);

        static void Transform(const Vector3 &position, const Matrix &matrix, Vector3 &result);

    };

    // 4维向量{X, Y, Z, W}
    struct Vector4 {
        float x{};
        float y{};
        float z{};
        float w{};

        // 零向量
        static const Vector4 kZero;
        // 全1向量
        static const Vector4 kOne;
        // X轴单位向量
        static const Vector4 kUnitX;
        // Y轴单位向量
        static const Vector4 kUnitY;
        // Z轴单位向量
        static const Vector4 kUnitZ;
        // W轴单位向量
        static const Vector4 kUnitW;

        constexpr Vector4() noexcept = default;

        constexpr Vector4(float _x, float _y, float _z, float _w) noexcept
                : x(_x), y(_y), z(_z), w(_w) {}

        constexpr Vector4(const Vector3 &value, float _w) noexcept
                : x(value.x), y(value.y), z(value.z), w(_w) {}

        constexpr Vector4(const Vector2 &value, float _z, float _w) noexcept
                : x(value.x), y(value.y), z(_z), w(_w) {}

        // 构造函数
        // 各个维度填充相同值
        // @param value 每个维度填充值
        Vector4(float value) : x(value), y(value), z(value), w(value) {}

        // 返回一个表示向量的字符串
        // @result 字符串
        std::string ToString() const;

        // 判断两个向量是否相同
        // @param value 另一个向量
        // @return 结果
        bool operator==(const Vector4 &value) const;

        // 判断两个向量是否不同
        // @param value 另一个向量
        // @return 结果
        bool operator!=(const Vector4 &value) const;

        // 向量相加
        // @param value 另一个向量
        // @return 结果
        Vector4 operator+(const Vector4 &value) const;

        // 向量相加
        // @param value 另一个向量
        Vector4 &operator+=(const Vector4 &value);

        // 向量相减
        // @param value 另一个向量
        // @return 结果
        Vector4 operator-(const Vector4 &value) const;

        // 向量相减
        // @param value 另一个向量
        Vector4 &operator-=(const Vector4 &value);

        // 向量取反
        Vector4 operator-();

        // 向量相乘
        // @param value 另一个向量
        // @return 结果
        Vector4 operator*(const Vector4 &value) const;

        // 向量相乘
        // @param value 另一个向量
        Vector4 &operator*=(const Vector4 &value);

        // 向量每个维度乘以一个数值
        // @param value 数值
        // @return 结果
        Vector4 operator*(float value) const;

        // 向量每个维度乘以一个数值
        // @param value 数值
        Vector4 &operator*=(float value);

        // 向量相除
        // @param value 另一个向量
        // @return 结果
        Vector4 operator/(const Vector4 &value) const;

        // 向量相除
        // @param value 另一个向量
        Vector4 &operator/=(const Vector4 &value);

        // 向量每个维度除以一个数值
        // @param value 数值
        // @return 结果
        Vector4 operator/(float value) const;

        // 向量每个维度除以一个数值
        // @param value 数值
        Vector4 &operator/=(float value);

        // 向量单位化
        void Normalize();

        // 向量单位化
        // @param value 原向量
        // @return 单位向量
        static Vector4 Normalize(const Vector4 &value);

        // 获取两个向量的最大值向量
        // @param value1 向量1
        // @param value2 向量2
        // @return 结果向量
        static Vector4 Max(const Vector4 &value1, const Vector4 &value2);

        // 获取两个向量的最小值向量
        // @param value1 向量1
        // @param value2 向量2
        // @return 结果向量
        static Vector4 Min(const Vector4 &value1, const Vector4 &value2);

        // 获取向量长度
        // @return 向量长度
        float GetLength() const;

        // 获取向量长度的平方
        // @return 向量长度的平方
        float GetLengthSquared() const;

        // 将每个维度向下取整
        void Floor();

        // 将向量每个维度向下取整
        // @param value 原向量
        // @return 结果向量
        static Vector4 Floor(const Vector4 &value);

        // 将每个维度向上取整
        void Ceil();

        // 将向量每个维度向上取整
        // @param value 原向量
        // @return 结果向量
        static Vector4 Ceil(const Vector4 &value);

        // 限制向量到给定范围
        // @param value 原向量
        // @param min 最小量
        // @param max 最大量
        // @return 结果向量
        void Clamp(const Vector4 &min, const Vector4 &max);

        // 限制向量到给定范围
        // @param value 原向量
        // @param min 最小量
        // @param max 最大量
        // @return 结果向量
        static Vector4 Clamp(const Vector4 &value, const Vector4 &min, const Vector4 &max);

        // 获取向量之间的距离
        // @param value1 向量1
        // @param value2 向量2
        // @return 距离
        static float GetDistance(const Vector4 &value1, const Vector4 &value2);

        // 获取向量之间的距离平方
        // @param value1 向量1
        // @param value2 向量2
        // @return 距离平方
        static float GetDistanceSquared(const Vector4 &value1, const Vector4 &value2);

        // 将两个向量点乘，即每个维度乘积之和
        // @param value1 向量1
        // @param value2 向量2
        // @return 点乘结果
        static float Dot(const Vector4 &value1, const Vector4 &value2);

        // 向量转换
        static Vector4 Transform(const Vector4 &value, const Matrix &matrix);

        static Vector4 Transform(const Vector3 &value, const Matrix &matrix);

        static Vector4 Transform(const Vector2 &value, const Matrix &matrix);

        static void Transform(const Vector4 &value, const Matrix &matrix, Vector4 &result);

        static void Transform(const Vector3 &value, const Matrix &matrix, Vector4 &result);

        static void Transform(const Vector2 &value, const Matrix &matrix, Vector4 &result);
    };
}

