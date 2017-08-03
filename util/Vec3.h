
typedef double number; 

class Vec3 {
public:
	number x;
	number y;
	number z;

	Vec3 (number x0, number y0, number z0) {
		x = x0;
		y = y0;
		z = z0;
	}

	number len2() {
		return x * x + y * y + z * z;

	}

	number len() {
		return len2();
	}

	Vec3 operator + (Vec3 other) {

	}

};