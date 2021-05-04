#pragma once

#include <string>

namespace Tce {

    struct Matrix;

    // 2维向量{X, Y}
    template <typename Type>
    struct Vector2T {
        Type x{};
        Type y{};

        // 零向量
        static Vector2T GetZero();

        // 全1向量
        static Vector2T GetOne();

        // X轴单位向量
        static Vector2T GetUnitX();

        // Y轴单位向量
        static Vector2T GetUnitY();

        Vector2T() noexcept = default;

        Vector2T(Type _x, Type _y) noexcept;

        Vector2T(const Vector2T &value) noexcept = default;

        // 判断两个向量是否相同
        // @param value 另一个向量
        // @return 结果
        bool operator==(const Vector2T &value) const;

        // 判断两个向量是否不同
        // @param value 另一个向量
        // @return 结果
        bool operator!=(const Vector2T &value) const;

        // 向量相加
        // @param value 另一个向量
        // @return 结果
        Vector2T operator+(const Vector2T &value) const;

        // 向量相加
        // @param value 另一个向量
        Vector2T &operator+=(const Vector2T &value);

        // 向量相减
        // @param value 另一个向量
        // @return 结果
        Vector2T operator-(const Vector2T &value) const;

        // 向量相减
        // @param value 另一个向量
        Vector2T &operator-=(const Vector2T &value);

        // 向量取反
        Vector2T operator-();

        // 向量相乘
        // @param value 另一个向量
        // @return 结果
        Vector2T operator*(const Vector2T &value) const;

        // 向量相乘
        // @param value 另一个向量
        Vector2T &operator*=(const Vector2T &value);

        // 向量每个维度乘以一个数值
        // @param value 数值
        // @return 结果
        Vector2T operator*(Type value) const;

        // 向量每个维度乘以一个数值
        // @param value 数值
        Vector2T &operator*=(Type value);

        // 向量相除
        // @param value 另一个向量
        // @return 结果
        Vector2T operator/(const Vector2T &value) const;

        // 向量相除
        // @param value 另一个向量
        Vector2T &operator/=(const Vector2T &value);

        // 向量每个维度除以一个数值
        // @param value 数值
        // @return 结果
        Vector2T operator/(Type value) const;

        // 向量每个维度除以一个数值
        // @param value 数值
        Vector2T &operator/=(Type value);

        // 向量单位化
        void Normalize();

        // 向量单位化
        // @param value 原向量
        // @return 单位向量
        static Vector2T Normalize(const Vector2T &value);

        // 获取两个向量的最大值向量
        // @param value1 向量1
        // @param value2 向量2
        // @return 结果向量
        static Vector2T Max(const Vector2T &value1, const Vector2T &value2);

        // 获取两个向量的最小值向量
        // @param value1 向量1
        // @param value2 向量2
        // @return 结果向量
        static Vector2T Min(const Vector2T &value1, const Vector2T &value2);

        // 获取向量长度
        // @return 向量长度
        Type GetLength() const;

        // 获取向量长度的平方
        // @return 向量长度的平方
        Type GetLengthSquared() const;

        // 将每个维度向下取整
        void Floor();

        // 将向量每个维度向下取整
        // @param value 原向量
        // @return 结果向量
        static Vector2T Floor(const Vector2T &value);

        // 将每个维度向上取整
        void Ceil();

        // 将向量每个维度向上取整
        // @param value 原向量
        // @return 结果向量
        static Vector2T Ceil(const Vector2T &value);

        // 限制向量到给定范围
        // @param value 原向量
        // @param min 最小量
        // @param max 最大量
        // @return 结果向量
        void Clamp(const Vector2T &min, const Vector2T &max);

        // 限制向量到给定范围
        // @param value 原向量
        // @param min 最小量
        // @param max 最大量
        // @return 结果向量
        static Vector2T Clamp(const Vector2T &value, const Vector2T &min, const Vector2T &max);

        // 获取向量之间的距离
        // @param value1 向量1
        // @param value2 向量2
        // @return 距离
        static Type GetDistance(const Vector2T &value1, const Vector2T &value2);

        // 获取向量之间的距离平方
        // @param value1 向量1
        // @param value2 向量2
        // @return 距离平方
        static Type GetDistanceSquared(const Vector2T &value1, const Vector2T &value2);

        // 将两个向量点乘，即每个维度乘积之和
        // @param value1 向量1
        // @param value2 向量2
        // @return 点乘结果
        static Type Dot(const Vector2T &value1, const Vector2T &value2);

    };

    typedef Vector2T<float> Vector2;
    typedef Vector2T<double> Vector2D;

    // 3维向量{X, Y, Z}
    struct Vector3 {
        float x{};
        float y{};
        float z{};

        // 零向量
        static Vector3 GetZero();

        // 全1向量
        static Vector3 GetOne();

        // X轴单位向量
        static Vector3 GetUnitX();

        // Y轴单位向量
        static Vector3 GetUnitY();

        // Z轴单位向量
        static Vector3 GetUnitZ();

        Vector3() noexcept = default;

        Vector3(float _x, float _y, float _z) noexcept;

        Vector3(const Vector2 &value, float _z) noexcept;

        // 构造函数
        // 各个维度填充相同值
        // @param value 每个维度填充值
        Vector3(float value) noexcept;

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

        // 返回两个向量的叉积
        // @param value1 向量1
        // @param value2 向量2
        // @return 叉积结果向量
        static Vector3 Cross(const Vector3 &vector1, const Vector3 &vector2);

    };

    // 4维向量{X, Y, Z, W}
    struct Vector4 {
        float x{};
        float y{};
        float z{};
        float w{};

        // 零向量
        static Vector4 GetZero();

        // 全1向量
        static Vector4 GetOne();

        // X轴单位向量
        static Vector4 GetUnitX();

        // Y轴单位向量
        static Vector4 GetUnitY();

        // Z轴单位向量
        static Vector4 GetUnitZ();

        // W轴单位向量
        static Vector4 GetUnitW();

        constexpr Vector4() noexcept = default;

        constexpr Vector4(float _x, float _y, float _z, float _w) noexcept;

        constexpr Vector4(const Vector3 &value, float _w) noexcept;

        constexpr Vector4(const Vector2 &value, float _z, float _w) noexcept;

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
    };
}

#include "Vector.inl"