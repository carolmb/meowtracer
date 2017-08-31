#ifndef __VEC3__
#define __VEC3__

#include <cmath>

class Vec3 {
	typedef double number; 
public:
	number x;
	number y;
	number z;

	Vec3 () : x(0), y(0), z(0) {}
	Vec3 (number x0, number y0, number z0) : x(x0), y(y0), z(z0) {}

	number len2() { return x * x + y * y + z * z; }

	number len() { return sqrt(len2()); }

	Vec3 operator + (Vec3 other) { return Vec3(x + other.x, y + other.y, z + other.z); }
	Vec3 operator - (Vec3 other) { return Vec3(x - other.x, y - other.y, z - other.z); }
	Vec3 operator - (void) { return Vec3(-x, -y, -z); }
	Vec3 operator * (double scalar) { return Vec3(x * scalar, y * scalar, z * scalar); }
	Vec3 operator * (Vec3 other) { return Vec3(x * other.x, y * other.y, z * other.z); }
	Vec3 operator / (double scalar) { return Vec3(x / scalar, y / scalar, z / scalar); }

	void operator += (Vec3 other) { x += other.x; y += other.y; z += other.z; }
	void operator -= (Vec3 other) { x -= other.x; y -= other.y; z -= other.z; }
	void operator *= (double scalar) { x *= scalar; y *= scalar; z *= scalar; }
	void operator *= (Vec3 other) { x *= other.x; y *= other.y; z *= other.z; }
	void operator /= (double scalar) { x /= scalar; y /= scalar; z /= scalar; }

	number dot(Vec3 &other) { return x * other.x + y * other.y + z * other.z; }

	Vec3 norm() { 
		double l = len();
		return Vec3(x/l, y/l, z/l); 
	}

	Vec3 lerp(Vec3 &other, double t) { 
		double tt = 1 - t;
		return Vec3(other.x * t + x * tt, 
					other.y * t + y * tt, 
					other.z * t + z * tt); 
	}

	Vec3 lamb(Vec3 normal, Vec3 light, Vec3 i) {
		number cos = fmax(light.dot(normal), 0.0);
		return Vec3(cos * x * i.x, cos * y * i.y, cos * z * i.z);
	}

};

typedef Vec3 Point3;
typedef Vec3 Color;

#endif