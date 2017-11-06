#ifndef __XFORM_
#define __XFORM__

#include "Vec3.h"

class Transform {
public:
    double matrix[4][4];
    double* operator[](int i) { return matrix[i]; }
    double det();
    Transform inverse();
    Transform transposed();

    // Static
    Transform identity();
    Transform scaling(const Vec3 &scale);
    Transform translation(const Vec3 &t);
    Transform rotation(const Vec3 &axis, double angle);
    Transform rotation(const Vec3 &angles);
};

Transform operator*(const Transform &Left, const Transform &Right);
Transform operator*(const Transform &Left, double &Right);
Transform operator*(double &Left, const Transform &Right);
Transform operator+(const Transform &Left, const Transform &Right);
Transform operator-(const Transform &Left, const Transform &Right);

#endif