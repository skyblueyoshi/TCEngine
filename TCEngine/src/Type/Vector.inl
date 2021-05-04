#include "StringHelper.h"
#include <cmath>
#include <algorithm>
#include "TCMath.h"
#include "Matrix.h"
#include "Vector.h"


namespace Tce {

    template <typename Type>
    inline Vector2T<Type> Vector2T<Type>::GetZero() {
        return {};
    }

    template <typename Type>
    inline Vector2T<Type> Vector2T<Type>::GetOne() {
        return {1, 1};
    }

    template <typename Type>
    inline Vector2T<Type> Vector2T<Type>::GetUnitX() {
        return {1, 0};
    }

    template <typename Type>
    inline Vector2T<Type> Vector2T<Type>::GetUnitY() {
        return {0, 1};
    }

    template <typename Type>
    inline Vector2T<Type>::Vector2T(Type _x, Type _y) noexcept
            : x(_x), y(_y) {}

    template <typename Type>
    inline bool Vector2T<Type>::operator==(const Vector2T &value) const {
        return x == value.x &&
               y == value.y;
    }

    template <typename Type>
    inline bool Vector2T<Type>::operator!=(const Vector2T &value) const {
        return x != value.x ||
               y != value.y;
    }

    template <typename Type>
    inline Vector2T<Type> Vector2T<Type>::operator+(const Vector2T &value) const {
        return {x + value.x,
                y + value.y};
    }

    template <typename Type>
    inline Vector2T<Type> &Vector2T<Type>::operator+=(const Vector2T &value) {
        x += value.x;
        y += value.y;
        return *this;
    }

    template <typename Type>
    inline Vector2T<Type> Vector2T<Type>::operator-(const Vector2T &value) const {
        return {x - value.x,
                y - value.y};
    }

    template <typename Type>
    inline Vector2T<Type> &Vector2T<Type>::operator-=(const Vector2T &value) {
        x -= value.x;
        y -= value.y;
        return *this;
    }

    template <typename Type>
    inline Vector2T<Type> Vector2T<Type>::operator*(const Vector2T &value) const {
        return {x * value.x,
                y * value.y};
    }

    template <typename Type>
    inline Vector2T<Type> &Vector2T<Type>::operator*=(const Vector2T &value) {
        x *= value.x;
        y *= value.y;
        return *this;
    }

    template <typename Type>
    inline Vector2T<Type> Vector2T<Type>::operator*(Type value) const {
        return {x * value,
                y * value};
    }

    template <typename Type>
    inline Vector2T<Type> &Vector2T<Type>::operator*=(Type value) {
        x *= value;
        y *= value;
        return *this;
    }

    template <typename Type>
    inline Vector2T<Type> Vector2T<Type>::operator/(const Vector2T &value) const {
        return {x / value.x,
                y / value.y};
    }

    template <typename Type>
    inline Vector2T<Type> &Vector2T<Type>::operator/=(const Vector2T &value) {
        x /= value.x;
        y /= value.y;
        return *this;
    }

    template <typename Type>
    inline Vector2T<Type> Vector2T<Type>::operator/(Type value) const {
        Type factor = 1.0f / value;
        return {x * factor,
                y * factor};
    }

    template <typename Type>
    inline Vector2T<Type> &Vector2T<Type>::operator/=(Type value) {
        Type factor = 1.0f / value;
        x *= factor;
        y *= factor;
        return *this;
    }

    template <typename Type>
    inline void Vector2T<Type>::Normalize() {
        auto factor = GetLength();
        factor = 1.0f / factor;
        x *= factor;
        y *= factor;
    }

    template <typename Type>
    inline Vector2T<Type> Vector2T<Type>::Normalize(const Vector2T &value) {
        Vector2T result = value;
        result.Normalize();
        return result;
    }

    template <typename Type>
    inline Vector2T<Type> Vector2T<Type>::operator-() {
        return {-x, -y};
    }

    template <typename Type>
    inline Vector2T<Type>Vector2T<Type>::Max(const Vector2T &value1, const Vector2T &value2) {
        return {std::max(value1.x, value2.x),
                std::max(value1.y, value2.y)};
    }

    template <typename Type>
    inline Vector2T<Type> Vector2T<Type>::Min(const Vector2T &value1, const Vector2T &value2) {
        return {std::min(value1.x, value2.x),
                std::min(value1.y, value2.y)};
    }

    template <typename Type>
    inline Type Vector2T<Type>::GetLength() const {
        return (Type) sqrt(GetLengthSquared());
    }

    template <typename Type>
    inline Type Vector2T<Type>::GetLengthSquared() const {
        return std::powf(x, 2) +
               std::powf(y, 2);
    }

    template <typename Type>
    inline void Vector2T<Type>::Floor() {
        x = floorf(x);
        y = floorf(y);
    }

    template <typename Type>
    inline Vector2T<Type> Vector2T<Type>::Floor(const Vector2T &value) {
        Vector2T result = value;
        result.Floor();
        return result;
    }

    template <typename Type>
    inline Type Vector2T<Type>::Dot(const Vector2T &value1, const Vector2T &value2) {
        return value1.x * value2.x +
               value1.y * value2.y;
    }

    template <typename Type>
    inline Type Vector2T<Type>::GetDistance(const Vector2T &value1, const Vector2T &value2) {
        return std::sqrtf(GetDistanceSquared(value1, value2));
    }

    template <typename Type>
    inline Type Vector2T<Type>::GetDistanceSquared(const Vector2T &value1, const Vector2T &value2) {
        return std::powf(value1.x - value2.x, 2) +
               std::powf(value1.y - value2.y, 2);
    }

    template <typename Type>
    inline void Vector2T<Type>::Ceil() {
        x = ceilf(x);
        y = ceilf(y);
    }

    template <typename Type>
    inline Vector2T<Type> Vector2T<Type>::Ceil(const Vector2T &value) {
        Vector2T result = value;
        result.Ceil();
        return result;
    }

    template <typename Type>
    inline void Vector2T<Type>::Clamp(const Vector2T &min, const Vector2T &max) {
        x = TCMath::Clamp(x, min.x, max.x);
        y = TCMath::Clamp(y, min.y, max.y);
    }

    template <typename Type>
    inline Vector2T<Type> Vector2T<Type>::Clamp(const Vector2T &value, const Vector2T &min, const Vector2T &max) {
        Vector2T result;
        result.Clamp(min, max);
        return result;
    }

    inline Vector3::Vector3(float _x, float _y, float _z) noexcept
            : x(_x), y(_y), z(_z) {}

    inline Vector3::Vector3(const Vector2 &value, float _z) noexcept
            : x(value.x), y(value.y), z(_z) {}

    inline Vector3::Vector3(float value) noexcept
            : x(value), y(value), z(value) {}

    inline Vector3 Vector3::GetZero() {
        return {};
    }

    inline Vector3 Vector3::GetOne() {
        return {1.0f, 1.0f, 1.0f};
    }

    inline Vector3 Vector3::GetUnitX() {
        return {1.0f, 0.0f, 0.0f};
    }

    inline Vector3 Vector3::GetUnitY() {
        return {0.0f, 1.0f, 0.0f};
    }

    inline Vector3 Vector3::GetUnitZ() {
        return {0.0f, 0.0f, 1.0f};
    }

    inline std::string Vector3::ToString() const {
        return StringHelper::MakeFormat("{X:%d Y:%d Z:%d}", x, y, z);
    }

    inline bool Vector3::operator==(const Vector3 &value) const {
        return x == value.x &&
               y == value.y &&
               z == value.z;
    }

    inline bool Vector3::operator!=(const Vector3 &value) const {
        return x != value.x ||
               y != value.y ||
               z != value.z;
    }

    inline Vector3 Vector3::operator+(const Vector3 &value) const {
        return {x + value.x,
                y + value.y,
                z + value.z};
    }

    inline Vector3 &Vector3::operator+=(const Vector3 &value) {
        x += value.x;
        y += value.y;
        z += value.z;
        return *this;
    }

    inline Vector3 Vector3::operator-(const Vector3 &value) const {
        return {x - value.x,
                y - value.y,
                z - value.z};
    }

    inline Vector3 &Vector3::operator-=(const Vector3 &value) {
        x -= value.x;
        y -= value.y;
        z -= value.z;
        return *this;
    }

    inline Vector3 Vector3::operator*(const Vector3 &value) const {
        return {x * value.x,
                y * value.y,
                z * value.z};
    }

    inline Vector3 &Vector3::operator*=(const Vector3 &value) {
        x *= value.x;
        y *= value.y;
        z *= value.z;
        return *this;
    }

    inline Vector3 Vector3::operator*(float value) const {
        return {x * value,
                y * value,
                z * value};
    }

    inline Vector3 &Vector3::operator*=(float value) {
        x *= value;
        y *= value;
        z *= value;
        return *this;
    }

    inline Vector3 Vector3::operator/(const Vector3 &value) const {
        return {x / value.x,
                y / value.y,
                z / value.z};
    }

    inline Vector3 &Vector3::operator/=(const Vector3 &value) {
        x /= value.x;
        y /= value.y;
        z /= value.z;
        return *this;
    }

    inline Vector3 Vector3::operator/(float value) const {
        float factor = 1.0f / value;
        return {x * factor,
                y * factor,
                z * factor};
    }

    inline Vector3 &Vector3::operator/=(float value) {
        float factor = 1.0f / value;
        x *= factor;
        y *= factor;
        z *= factor;
        return *this;
    }

    inline void Vector3::Normalize() {
        auto factor = GetLength();
        factor = 1.0f / factor;
        x *= factor;
        y *= factor;
        z *= factor;
    }

    inline Vector3 Vector3::Normalize(const Vector3 &value) {
        Vector3 result = value;
        result.Normalize();
        return result;
    }

    inline Vector3 Vector3::operator-() {
        return {-x, -y, -z};
    }

    inline Vector3 Vector3::Max(const Vector3 &value1, const Vector3 &value2) {
        return {std::max(value1.x, value2.x),
                std::max(value1.y, value2.y),
                std::max(value1.z, value2.z)};
    }

    inline Vector3 Vector3::Min(const Vector3 &value1, const Vector3 &value2) {
        return {std::min(value1.x, value2.x),
                std::min(value1.y, value2.y),
                std::min(value1.z, value2.z)};
    }

    inline float Vector3::GetLength() const {
        return (float) sqrt(GetLengthSquared());
    }

    inline float Vector3::GetLengthSquared() const {
        return std::powf(x, 2) +
               std::powf(y, 2) +
               std::powf(z, 2);
    }

    inline void Vector3::Floor() {
        x = floorf(x);
        y = floorf(y);
        z = floorf(z);
    }

    inline Vector3 Vector3::Floor(const Vector3 &value) {
        Vector3 result = value;
        result.Floor();
        return result;
    }

    inline float Vector3::Dot(const Vector3 &value1, const Vector3 &value2) {
        return value1.x * value2.x +
               value1.y * value2.y +
               value1.z * value2.z;
    }

    inline float Vector3::GetDistance(const Vector3 &value1, const Vector3 &value2) {
        return std::sqrtf(GetDistanceSquared(value1, value2));
    }

    inline float Vector3::GetDistanceSquared(const Vector3 &value1, const Vector3 &value2) {
        return std::powf(value1.x - value2.x, 2) +
               std::powf(value1.y - value2.y, 2) +
               std::powf(value1.z - value2.z, 2);
    }

    inline void Vector3::Ceil() {
        x = ceilf(x);
        y = ceilf(y);
        z = ceilf(z);
    }

    inline Vector3 Vector3::Ceil(const Vector3 &value) {
        Vector3 result = value;
        result.Ceil();
        return result;
    }

    inline void Vector3::Clamp(const Vector3 &min, const Vector3 &max) {
        x = TCMath::Clamp(x, min.x, max.x);
        y = TCMath::Clamp(y, min.y, max.y);
        z = TCMath::Clamp(z, min.z, max.z);
    }

    inline Vector3 Vector3::Clamp(const Vector3 &value, const Vector3 &min, const Vector3 &max) {
        Vector3 result;
        result.Clamp(min, max);
        return result;
    }

    inline Vector3 Vector3::Cross(const Vector3 &vector1, const Vector3 &vector2) {
        return {vector1.y * vector2.z - vector2.y * vector1.z,
                -(vector1.x * vector2.z - vector2.x * vector1.z),
                vector1.x * vector2.y - vector2.x * vector1.y};
    }

    inline Vector4 Vector4::GetZero() {
        return {};
    };

    inline Vector4 Vector4::GetOne() {
        return {1.0f, 1.0f, 1.0f, 1.0f};
    };

    inline Vector4 Vector4::GetUnitX() {
        return {1.0f, 0.0f, 0.0f, 0.0f};
    };

    inline Vector4 Vector4::GetUnitY() {
        return {0.0f, 1.0f, 0.0f, 0.0f};
    };

    inline Vector4 Vector4::GetUnitZ() {
        return {0.0f, 0.0f, 1.0f, 0.0f};
    };

    inline Vector4 Vector4::GetUnitW() {
        return {0.0f, 0.0f, 0.0f, 1.0f};
    };

    inline std::string Vector4::ToString() const {
        return StringHelper::MakeFormat("{X:%d Y:%d Z:%d W:%d}", x, y, z, w);
    }

    inline bool Vector4::operator==(const Vector4 &value) const {
        return w == value.w &&
               x == value.x &&
               y == value.y &&
               z == value.z;
    }

    inline bool Vector4::operator!=(const Vector4 &value) const {
        return w != value.w ||
               x != value.x ||
               y != value.y ||
               z != value.z;
    }

    inline Vector4 Vector4::operator+(const Vector4 &value) const {
        return {x + value.x,
                y + value.y,
                z + value.z,
                w + value.w};
    }

    inline Vector4 &Vector4::operator+=(const Vector4 &value) {
        x += value.x;
        y += value.y;
        z += value.z;
        w += value.w;
        return *this;
    }

    inline Vector4 Vector4::operator-(const Vector4 &value) const {
        return {x - value.x,
                y - value.y,
                z - value.z,
                w - value.w};
    }

    inline Vector4 &Vector4::operator-=(const Vector4 &value) {
        x -= value.x;
        y -= value.y;
        z -= value.z;
        w -= value.w;
        return *this;
    }

    inline Vector4 Vector4::operator*(const Vector4 &value) const {
        return {x * value.x,
                y * value.y,
                z * value.z,
                w * value.w};
    }

    inline Vector4 &Vector4::operator*=(const Vector4 &value) {
        x *= value.x;
        y *= value.y;
        z *= value.z;
        w *= value.w;
        return *this;
    }

    inline Vector4 Vector4::operator*(float value) const {
        return {x * value,
                y * value,
                z * value,
                w * value};
    }

    inline Vector4 &Vector4::operator*=(float value) {
        x *= value;
        y *= value;
        z *= value;
        w *= value;
        return *this;
    }

    inline Vector4 Vector4::operator/(const Vector4 &value) const {
        return {x / value.x,
                y / value.y,
                z / value.z,
                w / value.w};
    }

    inline Vector4 &Vector4::operator/=(const Vector4 &value) {
        x /= value.x;
        y /= value.y;
        z /= value.z;
        w /= value.w;
        return *this;
    }

    inline Vector4 Vector4::operator/(float value) const {
        float factor = 1.0f / value;
        return {x * factor,
                y * factor,
                z * factor,
                w * factor};
    }

    inline Vector4 &Vector4::operator/=(float value) {
        float factor = 1.0f / value;
        x *= factor;
        y *= factor;
        z *= factor;
        w *= factor;
        return *this;
    }

    inline void Vector4::Normalize() {
        auto factor = GetLength();
        factor = 1.0f / factor;
        x *= factor;
        y *= factor;
        z *= factor;
        w *= factor;
    }

    inline Vector4 Vector4::Normalize(const Vector4 &value) {
        Vector4 result = value;
        result.Normalize();
        return result;
    }

    inline Vector4 Vector4::operator-() {
        return {-x, -y, -z, -w};
    }

    inline Vector4 Vector4::Max(const Vector4 &value1, const Vector4 &value2) {
        return {std::max(value1.x, value2.x),
                std::max(value1.y, value2.y),
                std::max(value1.z, value2.z),
                std::max(value1.w, value2.w)};
    }

    inline Vector4 Vector4::Min(const Vector4 &value1, const Vector4 &value2) {
        return {std::min(value1.x, value2.x),
                std::min(value1.y, value2.y),
                std::min(value1.z, value2.z),
                std::min(value1.w, value2.w)};
    }

    inline float Vector4::GetLength() const {
        return (float) sqrt(GetLengthSquared());
    }

    inline float Vector4::GetLengthSquared() const {
        return std::powf(x, 2) +
               std::powf(y, 2) +
               std::powf(z, 2) +
               std::powf(w, 2);
    }

    inline void Vector4::Floor() {
        x = floorf(x);
        y = floorf(y);
        z = floorf(z);
        w = floorf(w);
    }

    inline Vector4 Vector4::Floor(const Vector4 &value) {
        Vector4 result = value;
        result.Floor();
        return result;
    }

    inline float Vector4::Dot(const Vector4 &value1, const Vector4 &value2) {
        return value1.x * value2.x +
               value1.y * value2.y +
               value1.z * value2.z +
               value1.w * value2.w;
    }

    inline float Vector4::GetDistance(const Vector4 &value1, const Vector4 &value2) {
        return std::sqrtf(GetDistanceSquared(value1, value2));
    }

    inline float Vector4::GetDistanceSquared(const Vector4 &value1, const Vector4 &value2) {
        return std::powf(value1.x - value2.x, 2) +
               std::powf(value1.y - value2.y, 2) +
               std::powf(value1.z - value2.z, 2) +
               std::powf(value1.w - value2.w, 2);
    }

    inline void Vector4::Ceil() {
        x = ceilf(x);
        y = ceilf(y);
        z = ceilf(z);
        w = ceilf(w);
    }

    inline Vector4 Vector4::Ceil(const Vector4 &value) {
        Vector4 result = value;
        result.Ceil();
        return result;
    }

    inline void Vector4::Clamp(const Vector4 &min, const Vector4 &max) {
        x = TCMath::Clamp(x, min.x, max.x);
        y = TCMath::Clamp(y, min.y, max.y);
        z = TCMath::Clamp(z, min.z, max.z);
        w = TCMath::Clamp(w, min.w, max.w);
    }

    inline Vector4 Vector4::Clamp(const Vector4 &value, const Vector4 &min, const Vector4 &max) {
        Vector4 result;
        result.Clamp(min, max);
        return result;
    }

    inline constexpr Vector4::Vector4(float _x, float _y, float _z, float _w) noexcept
            : x(_x), y(_y), z(_z), w(_w) {}

    inline constexpr Vector4::Vector4(const Vector3 &value, float _w) noexcept
            : x(value.x), y(value.y), z(value.z), w(_w) {}

    inline constexpr Vector4::Vector4(const Vector2 &value, float _z, float _w) noexcept
            : x(value.x), y(value.y), z(_z), w(_w) {}


}