#ifndef __MATERIAL__
#define __MATERIAL__

#include "../Math/Vec3.h"
#include <vector>
#include <cmath>

using std::vector;

struct Material {

	Color ambient = Color(1, 1, 1);
	Color diffuse = Color(1, 1, 1);
	Color specular = Color(1, 1, 1);
	float shininess = 1;
  float ref = 0;
  vector<Color> colors;
  vector<float> times;
  float outlineAngle = 0;
  Color outlineColor = Color(0, 0, 0);

};

#endif