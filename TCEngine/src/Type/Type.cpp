#include <Utils/ExceptionHelper.h>
#include "Type.h"

namespace Tce {

    void Vector2::Transform(const Vector2 &position, const Matrix &matrix, Vector2 &result) {
        result.x = (position.x * matrix._11) + (position.y * matrix._21) + matrix._41;
        result.y = (position.x * matrix._12) + (position.y * matrix._22) + matrix._42;
    }

    Vector2 Vector2::Transform(const Vector2 &position, const Matrix &matrix) {
        Vector2 result;
        Transform(position, matrix, result);
        return result;
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

    void Matrix::CreateLookAt(const Vector3 &cameraPosition, const Vector3 &cameraTarget,
                              const Vector3 &cameraUpVector, Matrix &result) {
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

    void
    Matrix::CreatePerspectiveFOV(float fieldOfView, float aspectRatio, float nearPlaneDistance,
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
        result._43 =
                (nearPlaneDistance * farPlaneDistance) / (nearPlaneDistance - farPlaneDistance);
    }

    void
    Matrix::CreateOrthographic(float width, float height, float zNearPlane, float zFarPlane,
                               Matrix &result) {
        result._11 = 2.0f / width;
        result._12 = result._13 = result._14 = 0.0f;
        result._22 = 2.0f / height;
        result._21 = result._23 = result._24 = 0.0f;
        result._33 = 1.0f / (zNearPlane - zFarPlane);
        result._31 = result._32 = result._34 = 0.0f;
        result._41 = result._42 = 0.0f;
        result._43 = zNearPlane / (zNearPlane - zFarPlane);
        result._44 = 1.0f;
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
}