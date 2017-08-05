
#include <cmath>

#include "../../include/util/Color.h"

Color Color::lerp(Color &other, double t) { 
	double tt = 1 - t;
	return Color(round(other.r * t + r * tt), 
				round(other.g * t + g * tt), 
				round(other.b * t + b * tt), 
				round(other.a * t + a * tt)
			); 
}