
class Color {
public:
	char r;
	char g;
	char b;
	char a;

	Color(char r0, char g0, char b0, char a0 = 255) : r(r0), g(g0), b(b0), a(a0);
	Color lerp(Color &other, double t) { 
		double tt = 1 - t;
		return Color(other.r * t + r * tt, other.g * t + g * tt, other.b * t + b * tt, other.a * t + a * tt); 
	}

};