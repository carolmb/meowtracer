
class Color {
	typedef unsigned char number;
public:
	number r;
	number g;
	number b;
	number a;

	Color() : r(0), g(0), b(0), a(0) {}
	Color(number r0, number g0, number b0, number a0 = 255) : r(r0), g(g0), b(b0), a(a0) {}
	Color lerp(Color &other, double t);

};