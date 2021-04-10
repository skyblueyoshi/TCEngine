#include "Vector.h"
#include "StringHelper.h"
#include <cmath>
#include "MathHelper.h"
#include "Matrix.h"

namespace Tce {

    const Vector2 Vector2::kZero{};
    const Vector2 Vector2::kOne{1.0f, 1.0f};
    const Vector2 Vector2::kUnitX{1.0f, 0.0f};
    const Vector2 Vector2::kUnitY{0.0f, 1.0f};

    std::string Vector2::ToString() const {
        return StringHelper::MakeFormat("{X:%d Y:%d}", x, y);
    }

    void Vector2::Transform(const Vector2 &position, const Matrix &matrix, Vector2 &result) {
        result.x = (position.x * matrix._11) + (position.y * matrix._21) + matrix._41;
        result.y = (position.x * matrix._12) + (position.y * matrix._22) + matrix._42;
    }

    Vector2 Vector2::Transform(const Vector2 &position, const Matrix &matrix) {
        Vector2 result;
        Transform(position, matrix, result);
        return result;
    }

    bool Vector2::operator==(const Vector2 &value) const {
        return x == value.x &&
               y == value.y;
    }

    bool Vector2::operator!=(const Vector2 &value) const {
        return x != value.x ||
               y != value.y;
    }

    Vector2 Vector2::operator+(const Vector2 &value) const {
        return {x + value.x,
                y + value.y};
    }

    Vector2 &Vector2::operator+=(const Vector2 &value) {
        x += value.x;
        y += value.y;
        return *this;
    }

    Vector2 Vector2::operator-(const Vector2 &value) const {
        return {x - value.x,
                y - value.y};
    }

    Vector2 &Vector2::operator-=(const Vector2 &value) {
        x -= value.x;
        y -= value.y;
        return *this;
    }

    Vector2 Vector2::operator*(const Vector2 &value) const {
        return {x * value.x,
                y * value.y};
    }

    Vector2 &Vector2::operator*=(const Vector2 &value) {
        x *= value.x;
        y *= value.y;
        return *this;
    }

    Vector2 Vector2::operator*(float value) const {
        return {x * value,
                y * value};
    }

    Vector2 &Vector2::operator*=(float value) {
        x *= value;
        y *= value;
        return *this;
    }

    Vector2 Vector2::operator/(const Vector2 &value) const {
        return {x / value.x,
                y / value.y};
    }

    Vector2 &Vector2::operator/=(const Vector2 &value) {
        x /= value.x;
        y /= value.y;
        return *this;
    }

    Vector2 Vector2::operator/(float value) const {
        float factor = 1.0f / value;
        return {x * factor,
                y * factor};
    }

    Vector2 &Vector2::operator/=(float value) {
        float factor = 1.0f / value;
        x *= factor;
        y *= factor;
        return *this;
    }

    void Vector2::Normalize() {
        auto factor = GetLength();
        factor = 1.0f / factor;
        x *= factor;
        y *= factor;
    }

    Vector2 Vector2::Normalize(const Vector2 &value) {
        Vector2 result = value;
        result.Normalize();
        return result;
    }

    Vector2 Vector2::operator-() {
        return {-x, -y};
    }

    Vector2 Vector2::Max(const Vector2 &value1, const Vector2 &value2) {
        return {std::max(value1.x, value2.x),
                std::max(value1.y, value2.y)};
    }

    Vector2 Vector2::Min(const Vector2 &value1, const Vector2 &value2) {
        return {std::min(value1.x, value2.x),
                std::min(value1.y, value2.y)};
    }

    float Vector2::GetLength() const {
        return (float) sqrt(GetLengthSquared());
    }

    float Vector2::GetLengthSquared() const {
        return std::powf(x, 2) +
               std::powf(y, 2);
    }

    void Vector2::Floor() {
        x = floorf(x);
        y = floorf(y);
    }

    Vector2 Vector2::Floor(const Vector2 &value) {
        Vector2 result = value;
        result.Floor();
        return result;
    }

    float Vector2::Dot(const Vector2 &value1, const Vector2 &value2) {
        return value1.x * value2.x +
               value1.y * value2.y;
    }

    float Vector2::GetDistance(const Vector2 &value1, const Vector2 &value2) {
        return std::sqrtf(GetDistanceSquared(value1, value2));
    }

    float Vector2::GetDistanceSquared(const Vector2 &value1, const Vector2 &value2) {
        return std::powf(value1.x - value2.x, 2) +
               std::powf(value1.y - value2.y, 2);
    }

    void Vector2::Ceil() {
        x = ceilf(x);
        y = ceilf(y);
    }

    Vector2 Vector2::Ceil(const Vector2 &value) {
        Vector2 result = value;
        result.Ceil();
        return result;
    }

    void Vector2::Clamp(const Vector2 &min, const Vector2 &max) {
        x = MathHelper::Clamp(x, min.x, max.x);
        y = MathHelper::Clamp(y, min.y, max.y);
    }

    Vector2 Vector2::Clamp(const Vector2 &value, const Vector2 &min, const Vector2 &max) {
        Vector2 result;
        result.Clamp(min, max);
        return result;
    }

    const Vector3 Vector3::kZero{};
    const Vector3 Vector3::kOne{1.0f, 1.0f, 1.0f};
    const Vector3 Vector3::kUnitX{1.0f, 0.0f, 0.0f};
    const Vector3 Vector3::kUnitY{0.0f, 1.0f, 0.0f};
    const Vector3 Vector3::kUnitZ{0.0f, 0.0f, 1.0f};

    std::string Vector3::ToString() const {
        return StringHelper::MakeFormat("{X:%d Y:%d Z:%d}", x, y, z);
    }

    void Vector3::Transform(const Vector3 &position, const Matrix &matrix, Vector3 &result) {
        result.x =
                (position.x * matrix._11) + (position.y * matrix._21) + (position.z * matrix._31) +
                matrix._41;
        result.y =
                (position.x * matrix._12) + (position.y * matrix._22) + (position.z * matrix._32) +
                matrix._42;
        result.z =
                (position.x * matrix._13) + (position.y * matrix._23) + (position.z * matrix._33) +
                matrix._43;
    }

    Vector3 Vector3::Transform(const Vector3 &position, const Matrix &matrix) {
        Vector3 result;
        Transform(position, matrix, result);
        return result;
    }

    bool Vector3::operator==(const Vector3 &value) const {
        return x == value.x &&
               y == value.y &&
               z == value.z;
    }

    bool Vector3::operator!=(const Vector3 &value) const {
        return x != value.x ||
               y != value.y ||
               z != value.z;
    }

    Vector3 Vector3::operator+(const Vector3 &value) const {
        return {x + value.x,
                y + value.y,
                z + value.z};
    }

    Vector3 &Vector3::operator+=(const Vector3 &value) {
        x += value.x;
        y += value.y;
        z += value.z;
        return *this;
    }

    Vector3 Vector3::operator-(const Vector3 &value) const {
        return {x - value.x,
                y - value.y,
                z - value.z};
    }

    Vector3 &Vector3::operator-=(const Vector3 &value) {
        x -= value.x;
        y -= value.y;
        z -= value.z;
        return *this;
    }

    Vector3 Vector3::operator*(const Vector3 &value) const {
        return {x * value.x,
                y * value.y,
                z * value.z};
    }

    Vector3 &Vector3::operator*=(const Vector3 &value) {
        x *= value.x;
        y *= value.y;
        z *= value.z;
        return *this;
    }

    Vector3 Vector3::operator*(float value) const {
        return {x * value,
                y * value,
                z * value};
    }

    Vector3 &Vector3::operator*=(float value) {
        x *= value;
        y *= value;
        z *= value;
        return *this;
    }

    Vector3 Vector3::operator/(const Vector3 &value) const {
        return {x / value.x,
                y / value.y,
                z / value.z};
    }

    Vector3 &Vector3::operator/=(const Vector3 &value) {
        x /= value.x;
        y /= value.y;
        z /= value.z;
        return *this;
    }

    Vector3 Vector3::operator/(float value) const {
        float factor = 1.0f / value;
        return {x * factor,
                y * factor,
                z * factor};
    }

    Vector3 &Vector3::operator/=(float value) {
        float factor = 1.0f / value;
        x *= factor;
        y *= factor;
        z *= factor;
        return *this;
    }

    void Vector3::Normalize() {
        auto factor = GetLength();
        factor = 1.0f / factor;
        x *= factor;
        y *= factor;
        z *= factor;
    }

    Vector3 Vector3::Normalize(const Vector3 &value) {
        Vector3 result = value;
        result.Normalize();
        return result;
    }

    Vector3 Vector3::operator-() {
        return {-x, -y, -z};
    }

    Vector3 Vector3::Max(const Vector3 &value1, const Vector3 &value2) {
        return {std::max(value1.x, value2.x),
                std::max(value1.y, value2.y),
                std::max(value1.z, value2.z)};
    }

    Vector3 Vector3::Min(const Vector3 &value1, const Vector3 &value2) {
        return {std::min(value1.x, value2.x),
                std::min(value1.y, value2.y),
                std::min(value1.z, value2.z)};
    }

    float Vector3::GetLength() const {
        return (float) sqrt(GetLengthSquared());
    }

    float Vector3::GetLengthSquared() const {
        return std::powf(x, 2) +
               std::powf(y, 2) +
               std::powf(z, 2);
    }

    void Vector3::Floor() {
        x = floorf(x);
        y = floorf(y);
        z = floorf(z);
    }

    Vector3 Vector3::Floor(const Vector3 &value) {
        Vector3 result = value;
        result.Floor();
        return result;
    }

    float Vector3::Dot(const Vector3 &value1, const Vector3 &value2) {
        return value1.x * value2.x +
               value1.y * value2.y +
               value1.z * value2.z;
    }

    float Vector3::GetDistance(const Vector3 &value1, const Vector3 &value2) {
        return std::sqrtf(GetDistanceSquared(value1, value2));
    }

    float Vector3::GetDistanceSquared(const Vector3 &value1, const Vector3 &value2) {
        return std::powf(value1.x - value2.x, 2) +
               std::powf(value1.y - value2.y, 2) +
               std::powf(value1.z - value2.z, 2);
    }

    void Vector3::Ceil() {
        x = ceilf(x);
        y = ceilf(y);
        z = ceilf(z);
    }

    Vector3 Vector3::Ceil(const Vector3 &value) {
        Vector3 result = value;
        result.Ceil();
        return result;
    }

    void Vector3::Clamp(const Vector3 &min, const Vector3 &max) {
        x = MathHelper::Clamp(x, min.x, max.x);
        y = MathHelper::Clamp(y, min.y, max.y);
        z = MathHelper::Clamp(z, min.z, max.z);
    }

    Vector3 Vector3::Clamp(const Vector3 &value, const Vector3 &min, const Vector3 &max) {
        Vector3 result;
        result.Clamp(min, max);
        return result;
    }

    Vector3 Vector3::Cross(const Vector3 &vector1, const Vector3 &vector2) {
        return {vector1.y * vector2.z - vector2.y * vector1.z,
                -(vector1.x * vector2.z - vector2.x * vector1.z),
                vector1.x * vector2.y - vector2.x * vector1.y};
    }

    const Vector4 Vector4::kZero{};
    const Vector4 Vector4::kOne{1.0f, 1.0f, 1.0f, 1.0f};
    const Vector4 Vector4::kUnitX{1.0f, 0.0f, 0.0f, 0.0f};
    const Vector4 Vector4::kUnitY{0.0f, 1.0f, 0.0f, 0.0f};
    const Vector4 Vector4::kUnitZ{0.0f, 0.0f, 1.0f, 0.0f};
    const Vector4 Vector4::kUnitW{0.0f, 0.0f, 0.0f, 1.0f};


    void Vector4::Transform(const Vector4 &value, const Matrix &matrix, Vector4 &result) {
        result.x = (value.x * matrix._11) + (value.y * matrix._21) + (value.z * matrix._31) +
                   (value.w * matrix._41);
        result.y = (value.x * matrix._12) + (value.y * matrix._22) + (value.z * matrix._32) +
                   (value.w * matrix._42);
        result.z = (value.x * matrix._13) + (value.y * matrix._23) + (value.z * matrix._33) +
                   (value.w * matrix._43);
        result.w = (value.x * matrix._14) + (value.y * matrix._24) + (value.z * matrix._34) +
                   (value.w * matrix._44);
    }

    Vector4 Vector4::Transform(const Vector4 &value, const Matrix &matrix) {
        Vector4 result;
        Transform(value, matrix, result);
        return result;
    }

    void Vector4::Transform(const Vector3 &value, const Matrix &matrix, Vector4 &result) {
        result.x = (value.x * matrix._11) + (value.y * matrix._21) + (value.z * matrix._31) +
                   (matrix._41);
        result.y = (value.x * matrix._12) + (value.y * matrix._22) + (value.z * matrix._32) +
                   (matrix._42);
        result.z = (value.x * matrix._13) + (value.y * matrix._23) + (value.z * matrix._33) +
                   (matrix._43);
        result.w = (value.x * matrix._14) + (value.y * matrix._24) + (value.z * matrix._34) +
                   (matrix._44);
    }

    Vector4 Vector4::Transform(const Vector3 &value, const Matrix &matrix) {
        Vector4 result;
        Transform(value, matrix, result);
        return result;
    }

    void Vector4::Transform(const Vector2 &value, const Matrix &matrix, Vector4 &result) {
        result.x = (value.x * matrix._11) + (value.y * matrix._21) +
                   (matrix._41);
        result.y = (value.x * matrix._12) + (value.y * matrix._22) +
                   (matrix._42);
        result.z = (value.x * matrix._13) + (value.y * matrix._23) +
                   (matrix._43);
        result.w = (value.x * matrix._14) + (value.y * matrix._24) +
                   (matrix._44);
    }

    Vector4 Vector4::Transform(const Vector2 &value, const Matrix &matrix) {
        Vector4 result;
        Transform(value, matrix, result);
        return result;
    }

    std::string Vector4::ToString() const {
        return StringHelper::MakeFormat("{X:%d Y:%d Z:%d W:%d}", x, y, z, w);
    }

    bool Vector4::operator==(const Vector4 &value) const {
        return w == value.w &&
               x == value.x &&
               y == value.y &&
               z == value.z;
    }

    bool Vector4::operator!=(const Vector4 &value) const {
        return w != value.w ||
               x != value.x ||
               y != value.y ||
               z != value.z;
    }

    Vector4 Vector4::operator+(const Vector4 &value) const {
        return {x + value.x,
                y + value.y,
                z + value.z,
                w + value.w};
    }

    Vector4 &Vector4::operator+=(const Vector4 &value) {
        x += value.x;
        y += value.y;
        z += value.z;
        w += value.w;
        return *this;
    }

    Vector4 Vector4::operator-(const Vector4 &value) const {
        return {x - value.x,
                y - value.y,
                z - value.z,
                w - value.w};
    }

    Vector4 &Vector4::operator-=(const Vector4 &value) {
        x -= value.x;
        y -= value.y;
        z -= value.z;
        w -= value.w;
        return *this;
    }

    Vector4 Vector4::operator*(const Vector4 &value) const {
        return {x * value.x,
                y * value.y,
                z * value.z,
                w * value.w};
    }

    Vector4 &Vector4::operator*=(const Vector4 &value) {
        x *= value.x;
        y *= value.y;
        z *= value.z;
        w *= value.w;
        return *this;
    }

    Vector4 Vector4::operator*(float value) const {
        return {x * value,
                y * value,
                z * value,
                w * value};
    }

    Vector4 &Vector4::operator*=(float value) {
        x *= value;
        y *= value;
        z *= value;
        w *= value;
        return *this;
    }

    Vector4 Vector4::operator/(const Vector4 &value) const {
        return {x / value.x,
                y / value.y,
                z / value.z,
                w / value.w};
    }

    Vector4 &Vector4::operator/=(const Vector4 &value) {
        x /= value.x;
        y /= value.y;
        z /= value.z;
        w /= value.w;
        return *this;
    }

    Vector4 Vector4::operator/(float value) const {
        float factor = 1.0f / value;
        return {x * factor,
                y * factor,
                z * factor,
                w * factor};
    }

    Vector4 &Vector4::operator/=(float value) {
        float factor = 1.0f / value;
        x *= factor;
        y *= factor;
        z *= factor;
        w *= factor;
        return *this;
    }

    void Vector4::Normalize() {
        auto factor = GetLength();
        factor = 1.0f / factor;
        x *= factor;
        y *= factor;
        z *= factor;
        w *= factor;
    }

    Vector4 Vector4::Normalize(const Vector4 &value) {
        Vector4 result = value;
        result.Normalize();
        return result;
    }

    Vector4 Vector4::operator-() {
        return {-x, -y, -z, -w};
    }

    Vector4 Vector4::Max(const Vector4 &value1, const Vector4 &value2) {
        return {std::max(value1.x, value2.x),
                std::max(value1.y, value2.y),
                std::max(value1.z, value2.z),
                std::max(value1.w, value2.w)};
    }

    Vector4 Vector4::Min(const Vector4 &value1, const Vector4 &value2) {
        return {std::min(value1.x, value2.x),
                std::min(value1.y, value2.y),
                std::min(value1.z, value2.z),
                std::min(value1.w, value2.w)};
    }

    float Vector4::GetLength() const {
        return (float) sqrt(GetLengthSquared());
    }

    float Vector4::GetLengthSquared() const {
        return std::powf(x, 2) +
               std::powf(y, 2) +
               std::powf(z, 2) +
               std::powf(w, 2);
    }

    void Vector4::Floor() {
        x = floorf(x);
        y = floorf(y);
        z = floorf(z);
        w = floorf(w);
    }

    Vector4 Vector4::Floor(const Vector4 &value) {
        Vector4 result = value;
        result.Floor();
        return result;
    }

    float Vector4::Dot(const Vector4 &value1, const Vector4 &value2) {
        return value1.x * value2.x +
               value1.y * value2.y +
               value1.z * value2.z +
               value1.w * value2.w;
    }

    float Vector4::GetDistance(const Vector4 &value1, const Vector4 &value2) {
        return std::sqrtf(GetDistanceSquared(value1, value2));
    }

    float Vector4::GetDistanceSquared(const Vector4 &value1, const Vector4 &value2) {
        return std::powf(value1.x - value2.x, 2) +
               std::powf(value1.y - value2.y, 2) +
               std::powf(value1.z - value2.z, 2) +
               std::powf(value1.w - value2.w, 2);
    }

    void Vector4::Ceil() {
        x = ceilf(x);
        y = ceilf(y);
        z = ceilf(z);
        w = ceilf(w);
    }

    Vector4 Vector4::Ceil(const Vector4 &value) {
        Vector4 result = value;
        result.Ceil();
        return result;
    }

    void Vector4::Clamp(const Vector4 &min, const Vector4 &max) {
        x = MathHelper::Clamp(x, min.x, max.x);
        y = MathHelper::Clamp(y, min.y, max.y);
        z = MathHelper::Clamp(z, min.z, max.z);
        w = MathHelper::Clamp(w, min.w, max.w);
    }

    Vector4 Vector4::Clamp(const Vector4 &value, const Vector4 &min, const Vector4 &max) {
        Vector4 result;
        result.Clamp(min, max);
        return result;
    }


}