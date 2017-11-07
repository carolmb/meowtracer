/*
Matrix4.h
Written by Matthew Fisher

a 4x4 transformation matrix structure.
*/

#ifndef __MAT4__
#define __MAT4__

#include "Vec3.h"
#include "Vec4.h"

class Matrix4
{
public:
    //
    // Initalization
    //
    Matrix4();
    Matrix4(const Matrix4 &M);
    Matrix4(const Vec3 &V0, const Vec3 &V1, const Vec3 &V2);

#ifdef USE_D3D
    Matrix4(const D3DXMATRIX &M);
#endif

    //
    // Assignment
    //
    Matrix4& operator = (const Matrix4 &M);

    //
    // Math properties
    //
    float Determinant() const;
    Matrix4 Transpose() const;
    Matrix4 Inverse() const;

    //
    // Vector transforms
    //
     Vec3 TransformPoint(const Vec3 &point) const
    {
        float w = point.x * _Entries[0][3] + point.y * _Entries[1][3] + point.z * _Entries[2][3] + _Entries[3][3];
        if(w)
        {
            const float invW = 1.0f / w;
            return Vec3( (point.x * _Entries[0][0] + point.y * _Entries[1][0] + point.z * _Entries[2][0] + _Entries[3][0]) * invW,
                          (point.x * _Entries[0][1] + point.y * _Entries[1][1] + point.z * _Entries[2][1] + _Entries[3][1]) * invW,
                          (point.x * _Entries[0][2] + point.y * _Entries[1][2] + point.z * _Entries[2][2] + _Entries[3][2]) * invW);
        }
        else
        {
            return Vec3::Origin;
        }
    }
    
     Vec3 TransformNormal(const Vec3 &normal) const
    {
        return Vec3(normal.x * _Entries[0][0] + normal.y * _Entries[1][0] + normal.z * _Entries[2][0],
                     normal.x * _Entries[0][1] + normal.y * _Entries[1][1] + normal.z * _Entries[2][1],
                     normal.x * _Entries[0][2] + normal.y * _Entries[1][2] + normal.z * _Entries[2][2]);
    }

#ifdef USE_D3D
    operator D3DXMATRIX() const;
#endif
    
    //
    // Accessors
    //
     float* operator [] (int Row)
    {
        return _Entries[Row];
    }
     const float* operator [] (int Row) const
    {
        return _Entries[Row];
    }
     void SetColumn(int Column, const Vec4 &Values)
    {
        _Entries[0][Column] = Values.x;
        _Entries[1][Column] = Values.y;
        _Entries[2][Column] = Values.z;
        _Entries[3][Column] = Values.w;
    }
     void SetRow(int Row, const Vec4 &Values)
    {
        _Entries[Row][0] = Values.x;
        _Entries[Row][1] = Values.y;
        _Entries[Row][2] = Values.z;
        _Entries[Row][3] = Values.w;
    }
     Vec4 GetColumn(int Column)
    {
        Vec4 Result;
        Result.x = _Entries[0][Column];
        Result.y = _Entries[1][Column];
        Result.z = _Entries[2][Column];
        Result.w = _Entries[3][Column];
        return Result;
    }
     Vec4 GetRow(int Row)
    {
        Vec4 Result;
        Result.x = _Entries[Row][0];
        Result.y = _Entries[Row][1];
        Result.z = _Entries[Row][2];
        Result.w = _Entries[Row][3];
        return Result;
    }

    //
    // Transformation matrices
    //
    static Matrix4 Identity();
    static Matrix4 Scaling(const Vec3 &ScaleFactors);
    static Matrix4 Scaling(float ScaleFactor)
    {
        return Scaling(Vec3(ScaleFactor, ScaleFactor, ScaleFactor));
    }
    static Matrix4 Translation(const Vec3 &Pos);
    static Matrix4 Rotation(const Vec3 &Axis, float Angle, const Vec3 &Center);
    static Matrix4 Rotation(const Vec3 &Axis, float Angle);
    static Matrix4 Rotation(float Yaw, float Pitch, float Roll);
    static Matrix4 Rotation(const Vec3 &Basis1, const Vec3 &Basis2, const Vec3 &Basis3);
    static Matrix4 RotationX(float Theta);
    static Matrix4 RotationY(float Theta);
    static Matrix4 RotationZ(float Theta);
    static Matrix4 Camera(const Vec3 &Eye, const Vec3 &Look, const Vec3 &Up, const Vec3 &Right);
    static Matrix4 LookAt(const Vec3 &Eye, const Vec3 &At, const Vec3 &Up);
    static Matrix4 Orthogonal(float Width, float Height, float ZNear, float ZFar);
    static Matrix4 Perspective(float Width, float Height, float ZNear, float ZFar);
    static Matrix4 PerspectiveFov(float FOV, float Aspect, float ZNear, float ZFar);
    static Matrix4 PerspectiveMultiFov(float FovX, float FovY, float ZNear, float ZFar);
    static Matrix4 Viewport(float Width, float Height);
    static Matrix4 ChangeOfBasis(const Vec3 &Source0, const Vec3 &Source1, const Vec3 &Source2, const Vec3 &SourceOrigin, 
                                 const Vec3 &Target0, const Vec3 &Target1, const Vec3 &Target2, const Vec3 &TargetOrigin);
private:
    float _Entries[4][4];
};

//
// Overloaded operators
//
Matrix4 operator * (const Matrix4 &Left, const Matrix4 &Right);
Matrix4 operator * (const Matrix4 &Left, float &Right);
Matrix4 operator * (float &Left, const Matrix4 &Right);
Matrix4 operator + (const Matrix4 &Left, const Matrix4 &Right);
Matrix4 operator - (const Matrix4 &Left, const Matrix4 &Right);
Vec4 operator * (const Vec4 &Right, const Matrix4 &Left);
Vec3 operator * (const Vec3 &Right, const Matrix4 &Left);

#endif