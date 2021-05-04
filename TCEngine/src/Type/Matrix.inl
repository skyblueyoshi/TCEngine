#include <cmath>
#include "StringHelper.h"
#include "Matrix.h"

namespace Tce {

    inline Matrix::Matrix(float m11, float m12, float m13, float m14, float m21, float m22,
                          float m23,
                          float m24, float m31, float m32, float m33, float m34, float m41,
                          float m42,
                          float m43, float m44) noexcept :
            _11(m11), _12(m12), _13(m13), _14(m14),
            _21(m21), _22(m22), _23(m23), _24(m24),
            _31(m31), _32(m32), _33(m33), _34(m34),
            _41(m41), _42(m42), _43(m43), _44(m44) {}

    inline Matrix::Matrix(const Vector4 &row1, const Vector4 &row2, const Vector4 &row3,
                          const Vector4 &row4)
            : Matrix(row1.x, row1.y, row1.z, row1.w,
                     row2.x, row2.y, row2.z, row2.w,
                     row3.x, row3.y, row3.z, row3.w,
                     row4.x, row4.y, row4.z, row4.w) {}

    inline Matrix Matrix::operator+(const Matrix &matrix) {
        return {
                _11 + matrix._11,
                _12 + matrix._12,
                _13 + matrix._13,
                _14 + matrix._14,
                _21 + matrix._21,
                _22 + matrix._22,
                _23 + matrix._23,
                _24 + matrix._24,
                _31 + matrix._31,
                _32 + matrix._32,
                _33 + matrix._33,
                _34 + matrix._34,
                _41 + matrix._41,
                _42 + matrix._42,
                _43 + matrix._43,
                _44 + matrix._44};
    }

    inline Matrix &Matrix::operator+=(const Matrix &matrix) {
        _11 += matrix._11;
        _12 += matrix._12;
        _13 += matrix._13;
        _14 += matrix._14;
        _21 += matrix._21;
        _22 += matrix._22;
        _23 += matrix._23;
        _24 += matrix._24;
        _31 += matrix._31;
        _32 += matrix._32;
        _33 += matrix._33;
        _34 += matrix._34;
        _41 += matrix._41;
        _42 += matrix._42;
        _43 += matrix._43;
        _44 += matrix._44;
        return *this;
    }

    inline Matrix Matrix::operator-(const Matrix &matrix) {
        return {
                _11 - matrix._11,
                _12 - matrix._12,
                _13 - matrix._13,
                _14 - matrix._14,
                _21 - matrix._21,
                _22 - matrix._22,
                _23 - matrix._23,
                _24 - matrix._24,
                _31 - matrix._31,
                _32 - matrix._32,
                _33 - matrix._33,
                _34 - matrix._34,
                _41 - matrix._41,
                _42 - matrix._42,
                _43 - matrix._43,
                _44 - matrix._44};
    }

    inline Matrix &Matrix::operator-=(const Matrix &matrix) {
        _11 -= matrix._11;
        _12 -= matrix._12;
        _13 -= matrix._13;
        _14 -= matrix._14;
        _21 -= matrix._21;
        _22 -= matrix._22;
        _23 -= matrix._23;
        _24 -= matrix._24;
        _31 -= matrix._31;
        _32 -= matrix._32;
        _33 -= matrix._33;
        _34 -= matrix._34;
        _41 -= matrix._41;
        _42 -= matrix._42;
        _43 -= matrix._43;
        _44 -= matrix._44;
        return *this;
    }

    inline bool Matrix::operator==(const Matrix &matrix) {
        return (_11 == matrix._11 &&
                _12 == matrix._12 &&
                _13 == matrix._13 &&
                _14 == matrix._14 &&
                _21 == matrix._21 &&
                _22 == matrix._22 &&
                _23 == matrix._23 &&
                _24 == matrix._24 &&
                _31 == matrix._31 &&
                _32 == matrix._32 &&
                _33 == matrix._33 &&
                _34 == matrix._34 &&
                _41 == matrix._41 &&
                _42 == matrix._42 &&
                _43 == matrix._43 &&
                _44 == matrix._44);
    }

    inline bool Matrix::operator!=(const Matrix &matrix) {
        return (_11 != matrix._11 ||
                _12 != matrix._12 ||
                _13 != matrix._13 ||
                _14 != matrix._14 ||
                _21 != matrix._21 ||
                _22 != matrix._22 ||
                _23 != matrix._23 ||
                _24 != matrix._24 ||
                _31 != matrix._31 ||
                _32 != matrix._32 ||
                _33 != matrix._33 ||
                _34 != matrix._34 ||
                _41 != matrix._41 ||
                _42 != matrix._42 ||
                _43 != matrix._43 ||
                _44 != matrix._44);
    }

    inline Matrix Matrix::operator-() {
        return {-_11, -_12, -_13, -_14,
                -_21, -_22, -_23, -_24,
                -_31, -_32, -_33, -_34,
                -_41, -_42, -_43, -_44};
    }

    inline Matrix Matrix::operator/(const Matrix &matrix) {
        return {
                _11 / matrix._11,
                _12 / matrix._12,
                _13 / matrix._13,
                _14 / matrix._14,
                _21 / matrix._21,
                _22 / matrix._22,
                _23 / matrix._23,
                _24 / matrix._24,
                _31 / matrix._31,
                _32 / matrix._32,
                _33 / matrix._33,
                _34 / matrix._34,
                _41 / matrix._41,
                _42 / matrix._42,
                _43 / matrix._43,
                _44 / matrix._44};
    }

    inline Matrix Matrix::operator/(float divider) {
        float num = 1.0f / divider;
        return {
                _11 * num,
                _12 * num,
                _13 * num,
                _14 * num,
                _21 * num,
                _22 * num,
                _23 * num,
                _24 * num,
                _31 * num,
                _32 * num,
                _33 * num,
                _34 * num,
                _41 * num,
                _42 * num,
                _43 * num,
                _44 * num};
    }

    inline Matrix Matrix::operator*(float scaleFactor) {
        return {
                _11 * scaleFactor,
                _12 * scaleFactor,
                _13 * scaleFactor,
                _14 * scaleFactor,
                _21 * scaleFactor,
                _22 * scaleFactor,
                _23 * scaleFactor,
                _24 * scaleFactor,
                _31 * scaleFactor,
                _32 * scaleFactor,
                _33 * scaleFactor,
                _34 * scaleFactor,
                _41 * scaleFactor,
                _42 * scaleFactor,
                _43 * scaleFactor,
                _44 * scaleFactor};
    }

    inline std::string Matrix::ToString() {
        return StringHelper::MakeFormat("{M11:%d M12:%d M13:%d M14:%d}"
                                        " {M21:%d M22:%d M23:%d M24:%d}"
                                        " {M31:%d M32:%d M33:%d M34:%d}"
                                        " {M41:%d M42:%d M43:%d M44:%d}",
                                        _11, _12, _13, _14,
                                        _21, _22, _23, _24,
                                        _31, _32, _33, _34,
                                        _41, _42, _43, _44);
    }

    inline Matrix Matrix::Transpose() {
        return {_11, _21, _31, _41,
                _12, _22, _32, _42,
                _13, _23, _33, _43,
                _14, _24, _34, _44};
    }

    inline Vector3 Matrix::GetTranslation() {
        return {_41, _42, _43};
    }

    inline void Matrix::SetTranslation(const Vector3 &vector3) {
        _41 = vector3.x;
        _42 = vector3.y;
        _43 = vector3.z;
    }

    inline Vector3 Matrix::GetLeft() {
        return {-_11, -_12, -_13};
    }

    inline void Matrix::SetLeft(const Vector3 &vector3) {
        _11 = -vector3.x;
        _12 = -vector3.y;
        _13 = -vector3.z;
    }

    inline Vector3 Matrix::GetRight() {
        return {_11, _12, _13};
    }

    inline void Matrix::SetRight(const Vector3 &vector3) {
        _11 = vector3.x;
        _12 = vector3.y;
        _13 = vector3.z;
    }

    inline Vector3 Matrix::GetUp() {
        return {_21, _22, _23};
    }

    inline void Matrix::SetUp(const Vector3 &vector3) {
        _21 = vector3.x;
        _22 = vector3.y;
        _23 = vector3.z;
    }

    inline Vector3 Matrix::GetDown() {
        return {-_21, -_22, -_23};
    }

    inline void Matrix::SetDown(const Vector3 &vector3) {
        _21 = -vector3.x;
        _22 = -vector3.y;
        _23 = -vector3.z;
    }

    inline Vector3 Matrix::GetForward() {
        return {-_31, -_32, -_33};
    }

    inline void Matrix::SetForward(const Vector3 &vector3) {
        _31 = -vector3.x;
        _32 = -vector3.y;
        _33 = -vector3.z;
    }

    inline Vector3 Matrix::GetBackward() {
        return {_31, _32, _33};
    }

    inline void Matrix::SetBackward(const Vector3 &vector3) {
        _31 = vector3.x;
        _32 = vector3.y;
        _33 = vector3.z;
    }

    inline Matrix Matrix::CreateLookAt(const Vector3 &cameraPosition, const Vector3 &cameraTarget,
                                       const Vector3 &cameraUpVector) {
        Matrix result{};
        CreateLookAt(cameraPosition, cameraTarget, cameraUpVector, result);
        return result;
    }

    inline Matrix
    Matrix::CreatePerspectiveFOV(float fieldOfView, float aspectRatio, float nearPlaneDistance,
                                 float farPlaneDistance) {
        Matrix result{};
        CreatePerspectiveFOV(fieldOfView, aspectRatio, nearPlaneDistance, farPlaneDistance, result);
        return result;
    }

    inline Matrix
    Matrix::CreateOrthographic(float width, float height, float zNearPlane, float zFarPlane) {
        Matrix result{};
        CreateOrthographic(width, height, zNearPlane, zFarPlane, result);
        return result;
    }

    inline Matrix Matrix::CreateIdentity() {
        return {1.0f, 0.0f, 0.0f, 0.0f,
                0.0f, 1.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 1.0f, 0.0f,
                0.0f, 0.0f, 0.0f, 1.0f};
    }

}