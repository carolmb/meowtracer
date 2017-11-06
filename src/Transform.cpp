#include "../include/Transform.h"

// from https://graphics.stanford.edu/~mdfisher/Code/Engine/Transform.cpp.html

Transform Transform::inverse() {
  //
  // Inversion by Cramer's rule.  Code taken from an Intel publication
  //
  double Result[4][4];
  double tmp[12]; /* temp array for pairs */
  double src[16]; /* array of transpose source matrix */
  double det; /* determinant */
  /* transpose matrix */
  for (int i = 0; i < 4; i++) {
      src[i + 0 ] = (*this)[i][0];
      src[i + 4 ] = (*this)[i][1];
      src[i + 8 ] = (*this)[i][2];
      src[i + 12] = (*this)[i][3];
  }
  /* calculate pairs for first 8 elements (cofactors) */
  tmp[0] = src[10] * src[15];
  tmp[1] = src[11] * src[14];
  tmp[2] = src[9] * src[15];
  tmp[3] = src[11] * src[13];
  tmp[4] = src[9] * src[14];
  tmp[5] = src[10] * src[13];
  tmp[6] = src[8] * src[15];
  tmp[7] = src[11] * src[12];
  tmp[8] = src[8] * src[14];
  tmp[9] = src[10] * src[12];
  tmp[10] = src[8] * src[13];
  tmp[11] = src[9] * src[12];
  /* calculate first 8 elements (cofactors) */
  Result[0][0] = tmp[0]*src[5] + tmp[3]*src[6] + tmp[4]*src[7];
  Result[0][0] -= tmp[1]*src[5] + tmp[2]*src[6] + tmp[5]*src[7];
  Result[0][1] = tmp[1]*src[4] + tmp[6]*src[6] + tmp[9]*src[7];
  Result[0][1] -= tmp[0]*src[4] + tmp[7]*src[6] + tmp[8]*src[7];
  Result[0][2] = tmp[2]*src[4] + tmp[7]*src[5] + tmp[10]*src[7];
  Result[0][2] -= tmp[3]*src[4] + tmp[6]*src[5] + tmp[11]*src[7];
  Result[0][3] = tmp[5]*src[4] + tmp[8]*src[5] + tmp[11]*src[6];
  Result[0][3] -= tmp[4]*src[4] + tmp[9]*src[5] + tmp[10]*src[6];
  Result[1][0] = tmp[1]*src[1] + tmp[2]*src[2] + tmp[5]*src[3];
  Result[1][0] -= tmp[0]*src[1] + tmp[3]*src[2] + tmp[4]*src[3];
  Result[1][1] = tmp[0]*src[0] + tmp[7]*src[2] + tmp[8]*src[3];
  Result[1][1] -= tmp[1]*src[0] + tmp[6]*src[2] + tmp[9]*src[3];
  Result[1][2] = tmp[3]*src[0] + tmp[6]*src[1] + tmp[11]*src[3];
  Result[1][2] -= tmp[2]*src[0] + tmp[7]*src[1] + tmp[10]*src[3];
  Result[1][3] = tmp[4]*src[0] + tmp[9]*src[1] + tmp[10]*src[2];
  Result[1][3] -= tmp[5]*src[0] + tmp[8]*src[1] + tmp[11]*src[2];
  /* calculate pairs for second 8 elements (cofactors) */
  tmp[0] = src[2]*src[7];
  tmp[1] = src[3]*src[6];
  tmp[2] = src[1]*src[7];
  tmp[3] = src[3]*src[5];
  tmp[4] = src[1]*src[6];
  tmp[5] = src[2]*src[5];

  tmp[6] = src[0]*src[7];
  tmp[7] = src[3]*src[4];
  tmp[8] = src[0]*src[6];
  tmp[9] = src[2]*src[4];
  tmp[10] = src[0]*src[5];
  tmp[11] = src[1]*src[4];
  /* calculate second 8 elements (cofactors) */
  Result[2][0] = tmp[0]*src[13] + tmp[3]*src[14] + tmp[4]*src[15];
  Result[2][0] -= tmp[1]*src[13] + tmp[2]*src[14] + tmp[5]*src[15];
  Result[2][1] = tmp[1]*src[12] + tmp[6]*src[14] + tmp[9]*src[15];
  Result[2][1] -= tmp[0]*src[12] + tmp[7]*src[14] + tmp[8]*src[15];
  Result[2][2] = tmp[2]*src[12] + tmp[7]*src[13] + tmp[10]*src[15];
  Result[2][2] -= tmp[3]*src[12] + tmp[6]*src[13] + tmp[11]*src[15];
  Result[2][3] = tmp[5]*src[12] + tmp[8]*src[13] + tmp[11]*src[14];
  Result[2][3] -= tmp[4]*src[12] + tmp[9]*src[13] + tmp[10]*src[14];
  Result[3][0] = tmp[2]*src[10] + tmp[5]*src[11] + tmp[1]*src[9];
  Result[3][0] -= tmp[4]*src[11] + tmp[0]*src[9] + tmp[3]*src[10];
  Result[3][1] = tmp[8]*src[11] + tmp[0]*src[8] + tmp[7]*src[10];
  Result[3][1] -= tmp[6]*src[10] + tmp[9]*src[11] + tmp[1]*src[8];
  Result[3][2] = tmp[6]*src[9] + tmp[11]*src[11] + tmp[3]*src[8];
  Result[3][2] -= tmp[10]*src[11] + tmp[2]*src[8] + tmp[7]*src[9];
  Result[3][3] = tmp[10]*src[10] + tmp[4]*src[8] + tmp[9]*src[9];
  Result[3][3] -= tmp[8]*src[9] + tmp[11]*src[10] + tmp[5]*src[8];
  /* calculate determinant */
  det=src[0]*Result[0][0]+src[1]*Result[0][1]+src[2]*Result[0][2]+src[3]*Result[0][3];
  /* calculate matrix inverse */
  det = 1.0f / det;

  Transform FloatResult;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
        FloatResult[i][j] = double(Result[i][j] * det);
    }
  }
  return FloatResult;
}

Transform Transform::transposed() {
  Transform result;
  for (int i = 0; i < 4; i++) {
      for (int i2 = 0; i2 < 4; i2++) {
          result[i2][i] = matrix[i][i2];
      }
  }
  return result;
}

Transform Transform::identity() {
  Transform result;
  for(int i = 0; i < 4; i++) {
      for (int i2 = 0; i2 < 4; i2++) {
          if (i == i2) {
              result[i][i2] = 1.0f;
          } else {
              result[i][i2] = 0.0f;
          }
      }
  }
  return result;
}

Transform Transform::translation(const Vec3 &t) {
  Transform result;
  result[0][0] = 1.0f;
  result[1][0] = 0.0f;
  result[2][0] = 0.0f;
  result[3][0] = t.x;

  result[0][1] = 0.0f;
  result[1][1] = 1.0f;
  result[2][1] = 0.0f;
  result[3][1] = t.y;

  result[0][2] = 0.0f;
  result[1][2] = 0.0f;
  result[2][2] = 1.0f;
  result[3][2] = t.z;

  result[0][3] = 0.0f;
  result[1][3] = 0.0f;
  result[2][3] = 0.0f;
  result[3][3] = 1.0f;
  return result;
}

Transform Transform::scaling(const Vec3 &scale) {
  Transform result;
  result[0][0] = scale.x;
  result[1][0] = 0.0f;
  result[2][0] = 0.0f;
  result[3][0] = 0.0f;

  result[0][1] = 0.0f;
  result[1][1] = scale.y;
  result[2][1] = 0.0f;
  result[3][1] = 0.0f;

  result[0][2] = 0.0f;
  result[1][2] = 0.0f;
  result[2][2] = scale.z;
  result[3][2] = 0.0f;

  result[0][3] = 0.0f;
  result[1][3] = 0.0f;
  result[2][3] = 0.0f;
  result[3][3] = 1.0f;
  return result;
}

Transform Transform::rotation(const Vec3 &axis, double angle) {
  double c = cosf(angle);
  double s = sinf(angle);
  double t = 1.0f - c;

  double x = axis.x;
  double y = axis.y;
  double z = axis.z;

  Transform result;
  result[0][0] = 1 + t*(x*x-1);
  result[0][1] = z*s+t*x*y;
  result[0][2] = -y*s+t*x*z;
  result[0][3] = 0.0f;

  result[1][0] = -z*s+t*x*y;
  result[1][1] = 1+t*(y*y-1);
  result[1][2] = x*s+t*y*z;
  result[1][3] = 0.0f;

  result[2][0] = y*s+t*x*z;
  result[2][1] = -x*s+t*y*z;
  result[2][2] = 1+t*(z*z-1);
  result[2][3] = 0.0f;

  result[3][0] = 0.0f;
  result[3][1] = 0.0f;
  result[3][2] = 0.0f;
  result[3][3] = 1.0f;
  return result; 
}

Transform Transform::rotation(const Vec3 &angles) {
  Vec3 x(1, 0, 0);
  Vec3 y(0, 1, 0);
  Vec3 z(0, 0, 1);
  return rotation(x, angles.x) * rotation(y, angles.y) * rotation(z, angles.z);
}

Transform operator*(const double Left[4][4], const double Right[4][4]) {
  Transform Result;
  for(int i = 0; i < 4; i++) {
    for(int i2 = 0; i2 < 4; i2++) {
      double Total = 0.0f;
      for(int i3 = 0; i3 < 4; i3++) {
        Total += Left[i][i3] * Right[i3][i2];
      }
      Result[i][i2] = Total;
    }
  }
  return Result;
}

Transform operator*(const double Left[4][4], const Transform &Right) {
  return Left * Right.matrix;
}

Transform operator*(const Transform &Left, const double Right[4][4]) {
  return Left.matrix * Right;
}

Transform operator*(const Transform &Left, const Transform &Right) {
  return Left.matrix * Right.matrix;
}

Transform operator*(const Transform &Left, double &Right) {
  Transform Result;
  for(int i = 0; i < 4; i++) {
    for(int i2 = 0; i2 < 4; i2++) {
      Result[i][i2] = Left[i][i2] * Right;
    }
  }
  return Result;
}

Transform operator*(double &Left, const Transform &Right) {
  return Right * Left;
}

Transform operator+(const Transform &Left, const Transform &Right) {
  Transform Result;
  for(int i = 0; i < 4; i++) {
    for(int i2 = 0; i2 < 4; i2++) {
      Result[i][i2] = Left[i][i2] + Right[i][i2];
    }
  }
  return Result;
}

Transform operator-(const Transform &Left, const Transform &Right) {
  Transform Result;
  for(int i = 0; i < 4; i++) {
    for(int i2 = 0; i2 < 4; i2++) {
      Result[i][i2] = Left[i][i2] - Right[i][i2];
    }
  }
  return Result;
}