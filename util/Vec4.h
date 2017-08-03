
#include "util/Vec3.h"

class Vec4 : Vec3 {
public:
	double w;

	Vec4(double x0, double y0, double z0, double w0 = 1) {
		x = x0;
		y = y0;
		z = z0;
		w = w0;
	}

	Vec4 operator + (Vec4 & other) {
		Vec4 v(x + other.x, y + other.y, z + other.z, w + other.w);
		return v;
	}

	Vec4 operator * (double s) { 
		Vec4 v(x * s, y * s, z * s, w * s);
		return v;
	}

	double operator * (Vec4 other) {
		return x * other.x + y * other.y + z * other.z + w * other.w;
	}

};