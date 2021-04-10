#include <cmath>
#include <src/Utils/ExceptionHelper.h>
#include "Matrix.h"
#include "StringHelper.h"
#include "Vector.h"

namespace Tce {

    Matrix const Matrix::identity(1.0f, 0.0f, 0.0f, 0.0f,
                                  0.0f, 1.0f, 0.0f, 0.0f,
                                  0.0f, 0.0f, 1.0f, 0.0f,
                                  0.0f, 0.0f, 0.0f, 1.0f);

    Matrix::Matrix(float m11, float m12, float m13, float m14, float m21, float m22, float m23,
                   float m24, float m31, float m32, float m33, float m34, float m41, float m42,
                   float m43, float m44) noexcept :
            _11(m11), _12(m12), _13(m13), _14(m14),
            _21(m21), _22(m22), _23(m23), _24(m24),
            _31(m31), _32(m32), _33(m33), _34(m34),
            _41(m41), _42(m42), _43(m43), _44(m44) {}

    Matrix::Matrix(const Vector4 &row1, const Vector4 &row2, const Vector4 &row3,
                   const Vector4 &row4) : Matrix(row1.x, row1.y, row1.z, row1.w,
                                                 row2.x, row2.y, row2.z, row2.w,
                                                 row3.x, row3.y, row3.z, row3.w,
                                                 row4.x, row4.y, row4.z, row4.w) {}

    Matrix Matrix::operator+(const Matrix &matrix) {
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

    Matrix &Matrix::operator+=(const Matrix &matrix) {
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

    Matrix Matrix::operator-(const Matrix &matrix) {
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

    Matrix &Matrix::operator-=(const Matrix &matrix) {
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

    bool Matrix::operator==(const Matrix &matrix) {
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

    bool Matrix::operator!=(const Matrix &matrix) {
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

    Matrix Matrix::operator*(const Matrix &matrix) {
        return {(((_11 * matrix._11) + (_12 * matrix._21)) + (_13 * matrix._31)) +
                (_14 * matrix._41),
                (((_11 * matrix._12) + (_12 * matrix._22)) + (_13 * matrix._32)) +
                (_14 * matrix._42),
                (((_11 * matrix._13) + (_12 * matrix._23)) + (_13 * matrix._33)) +
                (_14 * matrix._43),
                (((_11 * matrix._14) + (_12 * matrix._24)) + (_13 * matrix._34)) +
                (_14 * matrix._44),
                (((_21 * matrix._11) + (_22 * matrix._21)) + (_23 * matrix._31)) +
                (_24 * matrix._41),
                (((_21 * matrix._12) + (_22 * matrix._22)) + (_23 * matrix._32)) +
                (_24 * matrix._42),
                (((_21 * matrix._13) + (_22 * matrix._23)) + (_23 * matrix._33)) +
                (_24 * matrix._43),
                (((_21 * matrix._14) + (_22 * matrix._24)) + (_23 * matrix._34)) +
                (_24 * matrix._44),
                (((_31 * matrix._11) + (_32 * matrix._21)) + (_33 * matrix._31)) +
                (_34 * matrix._41),
                (((_31 * matrix._12) + (_32 * matrix._22)) + (_33 * matrix._32)) +
                (_34 * matrix._42),
                (((_31 * matrix._13) + (_32 * matrix._23)) + (_33 * matrix._33)) +
                (_34 * matrix._43),
                (((_31 * matrix._14) + (_32 * matrix._24)) + (_33 * matrix._34)) +
                (_34 * matrix._44),
                (((_41 * matrix._11) + (_42 * matrix._21)) + (_43 * matrix._31)) +
                (_44 * matrix._41),
                (((_41 * matrix._12) + (_42 * matrix._22)) + (_43 * matrix._32)) +
                (_44 * matrix._42),
                (((_41 * matrix._13) + (_42 * matrix._23)) + (_43 * matrix._33)) +
                (_44 * matrix._43),
                (((_41 * matrix._14) + (_42 * matrix._24)) + (_43 * matrix._34)) +
                (_44 * matrix._44)};
    }

    Matrix Matrix::operator-() {
        return {-_11, -_12, -_13, -_14,
                -_21, -_22, -_23, -_24,
                -_31, -_32, -_33, -_34,
                -_41, -_42, -_43, -_44};
    }

    Matrix Matrix::operator/(const Matrix &matrix) {
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

    Matrix Matrix::operator/(float divider) {
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

    Matrix Matrix::operator*(float scaleFactor) {
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

    std::string Matrix::ToString() {
        return StringHelper::MakeFormat("{M11:%d M12:%d M13:%d M14:%d}"
                                        " {M21:%d M22:%d M23:%d M24:%d}"
                                        " {M31:%d M32:%d M33:%d M34:%d}"
                                        " {M41:%d M42:%d M43:%d M44:%d}",
                                        _11, _12, _13, _14,
                                        _21, _22, _23, _24,
                                        _31, _32, _33, _34,
                                        _41, _42, _43, _44);
    }

    Matrix Matrix::Transpose() {
        return {_11, _21, _31, _41,
                _12, _22, _32, _42,
                _13, _23, _33, _43,
                _14, _24, _34, _44};
    }

    Matrix Matrix::Lerp(Matrix matrix, float amount) {
        return {
                _11 + ((matrix._11 - _11) * amount),
                _12 + ((matrix._12 - _12) * amount),
                _13 + ((matrix._13 - _13) * amount),
                _14 + ((matrix._14 - _14) * amount),
                _21 + ((matrix._21 - _21) * amount),
                _22 + ((matrix._22 - _22) * amount),
                _23 + ((matrix._23 - _23) * amount),
                _24 + ((matrix._24 - _24) * amount),
                _31 + ((matrix._31 - _31) * amount),
                _32 + ((matrix._32 - _32) * amount),
                _33 + ((matrix._33 - _33) * amount),
                _34 + ((matrix._34 - _34) * amount),
                _41 + ((matrix._41 - _41) * amount),
                _42 + ((matrix._42 - _42) * amount),
                _43 + ((matrix._43 - _43) * amount),
                _44 + ((matrix._44 - _44) * amount)
        };
    }

    Matrix Matrix::Invert() {

        // UNITY 源码注释
        /*


        ///
        // Use Laplace expansion theorem to calculate the inverse of a 4x4 matrix
        //
        // 1. Calculate the 2x2 determinants needed the 4x4 determinant based on the 2x2 determinants
        // 3. Create the adjugate matrix, which satisfies: A * adj(A) = det(A) * I
        // 4. Divide adjugate matrix with the determinant to find the inverse

        float det1, det2, det3, det4, det5, det6, det7, det8, det9, det10, det11, det12;
        float detMatrix;
        FindDeterminants(ref matrix, out detMatrix, out det1, out det2, out det3, out det4, out det5, out det6,
                         out det7, out det8, out det9, out det10, out det11, out det12);

        float invDetMatrix = 1f / detMatrix;

        Matrix ret; // Allow for matrix and result to point to the same structure

        ret.M11 = (matrix.M22*det12 - matrix.M23*det11 + matrix.M24*det10) * invDetMatrix;
        ret.M12 = (-matrix.M12*det12 + matrix.M13*det11 - matrix.M14*det10) * invDetMatrix;
        ret.M13 = (matrix.M42*det6 - matrix.M43*det5 + matrix.M44*det4) * invDetMatrix;
        ret.M14 = (-matrix.M32*det6 + matrix.M33*det5 - matrix.M34*det4) * invDetMatrix;
        ret.M21 = (-matrix.M21*det12 + matrix.M23*det9 - matrix.M24*det8) * invDetMatrix;
        ret.M22 = (matrix.M11*det12 - matrix.M13*det9 + matrix.M14*det8) * invDetMatrix;
        ret.M23 = (-matrix.M41*det6 + matrix.M43*det3 - matrix.M44*det2) * invDetMatrix;
        ret.M24 = (matrix.M31*det6 - matrix.M33*det3 + matrix.M34*det2) * invDetMatrix;
        ret.M31 = (matrix.M21*det11 - matrix.M22*det9 + matrix.M24*det7) * invDetMatrix;
        ret.M32 = (-matrix.M11*det11 + matrix.M12*det9 - matrix.M14*det7) * invDetMatrix;
        ret.M33 = (matrix.M41*det5 - matrix.M42*det3 + matrix.M44*det1) * invDetMatrix;
        ret.M34 = (-matrix.M31*det5 + matrix.M32*det3 - matrix.M34*det1) * invDetMatrix;
        ret.M41 = (-matrix.M21*det10 + matrix.M22*det8 - matrix.M23*det7) * invDetMatrix;
        ret.M42 = (matrix.M11*det10 - matrix.M12*det8 + matrix.M13*det7) * invDetMatrix;
        ret.M43 = (-matrix.M41*det4 + matrix.M42*det2 - matrix.M43*det1) * invDetMatrix;
        ret.M44 = (matrix.M31*det4 - matrix.M32*det2 + matrix.M33*det1) * invDetMatrix;

        result = ret;
        */

        Matrix result{};

        float num1 = _11;
        float num2 = _12;
        float num3 = _13;
        float num4 = _14;
        float num5 = _21;
        float num6 = _22;
        float num7 = _23;
        float num8 = _24;
        float num9 = _31;
        float num10 = _32;
        float num11 = _33;
        float num12 = _34;
        float num13 = _41;
        float num14 = _42;
        float num15 = _43;
        float num16 = _44;
        auto num17 = (float) ((double) num11 * (double) num16 - (double) num12 * (double) num15);
        auto num18 = (float) ((double) num10 * (double) num16 - (double) num12 * (double) num14);
        auto num19 = (float) ((double) num10 * (double) num15 - (double) num11 * (double) num14);
        auto num20 = (float) ((double) num9 * (double) num16 - (double) num12 * (double) num13);
        auto num21 = (float) ((double) num9 * (double) num15 - (double) num11 * (double) num13);
        auto num22 = (float) ((double) num9 * (double) num14 - (double) num10 * (double) num13);
        auto num23 = (float) ((double) num6 * (double) num17 - (double) num7 * (double) num18 +
                              (double) num8 * (double) num19);
        auto num24 = (float) -((double) num5 * (double) num17 - (double) num7 * (double) num20 +
                               (double) num8 * (double) num21);
        auto num25 = (float) ((double) num5 * (double) num18 - (double) num6 * (double) num20 +
                              (double) num8 * (double) num22);
        auto num26 = (float) -((double) num5 * (double) num19 - (double) num6 * (double) num21 +
                               (double) num7 * (double) num22);
        auto num27 = (float) (1.0 /
                              ((double) num1 * (double) num23 + (double) num2 * (double) num24 +
                               (double) num3 * (double) num25 + (double) num4 * (double) num26));

        result._11 = num23 * num27;
        result._21 = num24 * num27;
        result._31 = num25 * num27;
        result._41 = num26 * num27;
        result._12 = (float) -((double) num2 * (double) num17 - (double) num3 * (double) num18 +
                               (double) num4 * (double) num19) * num27;
        result._22 = (float) ((double) num1 * (double) num17 - (double) num3 * (double) num20 +
                              (double) num4 * (double) num21) * num27;
        result._32 = (float) -((double) num1 * (double) num18 - (double) num2 * (double) num20 +
                               (double) num4 * (double) num22) * num27;
        result._42 = (float) ((double) num1 * (double) num19 - (double) num2 * (double) num21 +
                              (double) num3 * (double) num22) * num27;
        auto num28 = (float) ((double) num7 * (double) num16 - (double) num8 * (double) num15);
        auto num29 = (float) ((double) num6 * (double) num16 - (double) num8 * (double) num14);
        auto num30 = (float) ((double) num6 * (double) num15 - (double) num7 * (double) num14);
        auto num31 = (float) ((double) num5 * (double) num16 - (double) num8 * (double) num13);
        auto num32 = (float) ((double) num5 * (double) num15 - (double) num7 * (double) num13);
        auto num33 = (float) ((double) num5 * (double) num14 - (double) num6 * (double) num13);
        result._13 = (float) ((double) num2 * (double) num28 - (double) num3 * (double) num29 +
                              (double) num4 * (double) num30) * num27;
        result._23 = (float) -((double) num1 * (double) num28 - (double) num3 * (double) num31 +
                               (double) num4 * (double) num32) * num27;
        result._33 = (float) ((double) num1 * (double) num29 - (double) num2 * (double) num31 +
                              (double) num4 * (double) num33) * num27;
        result._43 = (float) -((double) num1 * (double) num30 - (double) num2 * (double) num32 +
                               (double) num3 * (double) num33) * num27;
        auto num34 = (float) ((double) num7 * (double) num12 - (double) num8 * (double) num11);
        auto num35 = (float) ((double) num6 * (double) num12 - (double) num8 * (double) num10);
        auto num36 = (float) ((double) num6 * (double) num11 - (double) num7 * (double) num10);
        auto num37 = (float) ((double) num5 * (double) num12 - (double) num8 * (double) num9);
        auto num38 = (float) ((double) num5 * (double) num11 - (double) num7 * (double) num9);
        auto num39 = (float) ((double) num5 * (double) num10 - (double) num6 * (double) num9);
        result._14 = (float) -((double) num2 * (double) num34 - (double) num3 * (double) num35 +
                               (double) num4 * (double) num36) * num27;
        result._24 = (float) ((double) num1 * (double) num34 - (double) num3 * (double) num37 +
                              (double) num4 * (double) num38) * num27;
        result._34 = (float) -((double) num1 * (double) num35 - (double) num2 * (double) num37 +
                               (double) num4 * (double) num39) * num27;
        result._44 = (float) ((double) num1 * (double) num36 - (double) num2 * (double) num38 +
                              (double) num3 * (double) num39) * num27;

        return result;
    }

    float Matrix::Determinant() {
        float num22 = _11;
        float num21 = _12;
        float num20 = _13;
        float num19 = _14;
        float num12 = _21;
        float num11 = _22;
        float num10 = _23;
        float num9 = _24;
        float num8 = _31;
        float num7 = _32;
        float num6 = _33;
        float num5 = _34;
        float num4 = _41;
        float num3 = _42;
        float num2 = _43;
        float num = _44;
        float num18 = (num6 * num) - (num5 * num2);
        float num17 = (num7 * num) - (num5 * num3);
        float num16 = (num7 * num2) - (num6 * num3);
        float num15 = (num8 * num) - (num5 * num4);
        float num14 = (num8 * num2) - (num6 * num4);
        float num13 = (num8 * num3) - (num7 * num4);
        return ((((num22 * (((num11 * num18) - (num10 * num17)) + (num9 * num16))) -
                  (num21 * (((num12 * num18) - (num10 * num15)) + (num9 * num14)))) +
                 (num20 * (((num12 * num17) - (num11 * num15)) + (num9 * num13)))) -
                (num19 * (((num12 * num16) - (num11 * num14)) + (num10 * num13))));

    }

    Vector3 Matrix::GetTranslation() {
        return {_41, _42, _43};
    }

    void Matrix::SetTranslation(const Vector3 &vector3) {
        _41 = vector3.x;
        _42 = vector3.y;
        _43 = vector3.z;
    }

    Vector3 Matrix::GetLeft() {
        return {-_11, -_12, -_13};
    }

    void Matrix::SetLeft(const Vector3 &vector3) {
        _11 = -vector3.x;
        _12 = -vector3.y;
        _13 = -vector3.z;
    }

    Vector3 Matrix::GetRight() {
        return {_11, _12, _13};
    }

    void Matrix::SetRight(const Vector3 &vector3) {
        _11 = vector3.x;
        _12 = vector3.y;
        _13 = vector3.z;
    }

    Vector3 Matrix::GetUp() {
        return {_21, _22, _23};
    }

    void Matrix::SetUp(const Vector3 &vector3) {
        _21 = vector3.x;
        _22 = vector3.y;
        _23 = vector3.z;
    }

    Vector3 Matrix::GetDown() {
        return {-_21, -_22, -_23};
    }

    void Matrix::SetDown(const Vector3 &vector3) {
        _21 = -vector3.x;
        _22 = -vector3.y;
        _23 = -vector3.z;
    }

    Vector3 Matrix::GetForward() {
        return {-_31, -_32, -_33};
    }

    void Matrix::SetForward(const Vector3 &vector3) {
        _31 = -vector3.x;
        _32 = -vector3.y;
        _33 = -vector3.z;
    }

    Vector3 Matrix::GetBackward() {
        return {_31, _32, _33};
    }

    void Matrix::SetBackward(const Vector3 &vector3) {
        _31 = vector3.x;
        _32 = vector3.y;
        _33 = vector3.z;
    }

    void Matrix::CreateLookAt(const Vector3 &cameraPosition, const Vector3 &cameraTarget,
                              const Vector3 &cameraUpVector, Matrix & result) {
        auto vector = Vector3::Normalize(cameraPosition - cameraTarget);
        auto vector2 = Vector3::Normalize(Vector3::Cross(cameraUpVector, vector));
        auto vector3 = Vector3::Cross(vector, vector2);
        result._11 = vector2.x;
        result._12 = vector3.x;
        result._13 = vector.x;
        result._14 = 0.0f;
        result._21 = vector2.y;
        result._22 = vector3.y;
        result._23 = vector.y;
        result._24 = 0.0f;
        result._31 = vector2.z;
        result._32 = vector3.z;
        result._33 = vector.z;
        result._34 = 0.0f;
        result._41 = -Vector3::Dot(vector2, cameraPosition);
        result._42 = -Vector3::Dot(vector3, cameraPosition);
        result._43 = -Vector3::Dot(vector, cameraPosition);
        result._44 = 1.0f;
    }

    Matrix Matrix::CreateLookAt(const Vector3 &cameraPosition, const Vector3 &cameraTarget,
                                const Vector3 &cameraUpVector) {
        Matrix result;
        CreateLookAt(cameraPosition, cameraTarget, cameraUpVector, result);
        return result;
    }

    void Matrix::CreatePerspectiveFOV(float fieldOfView, float aspectRatio, float nearPlaneDistance,
                                      float farPlaneDistance, Matrix &result) {
        CHECK_RANGE_OR_ERROR(fieldOfView > 0.0f && fieldOfView < 3.141593f);
        CHECK_RANGE_OR_ERROR(nearPlaneDistance > 0.0f);
        CHECK_RANGE_OR_ERROR(farPlaneDistance > 0.0f);
        CHECK_RANGE_OR_ERROR(nearPlaneDistance < farPlaneDistance);


        float num = 1.0f / ((float) std::tan((double) (fieldOfView * 0.5f)));
        float num9 = num / aspectRatio;
        result._11 = num9;
        result._12 = result._13 = result._14 = 0;
        result._22 = num;
        result._21 = result._23 = result._24 = 0;
        result._31 = result._32 = 0.0f;
        result._33 = farPlaneDistance / (nearPlaneDistance - farPlaneDistance);
        result._34 = -1.0f;
        result._41 = result._42 = result._44 = 0;
        result._43 = (nearPlaneDistance * farPlaneDistance) / (nearPlaneDistance - farPlaneDistance);
    }

    Matrix Matrix::CreatePerspectiveFOV(float fieldOfView, float aspectRatio, float nearPlaneDistance,
                                 float farPlaneDistance) {
        Matrix result;
        CreatePerspectiveFOV(fieldOfView, aspectRatio, nearPlaneDistance, farPlaneDistance, result);
        return result;
    }

}