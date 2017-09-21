#ifndef __MATERIAL__
#define __MATERIAL__

#include "Vec3.h"
#include <vector>

class Material {
public:
	Color ambient;
	Color diffuse;
	Color specular;
	double shininess;
  std::vector<Color> colors;
  std::vector<double> times;
  double outlineAngle;
  Color outlineColor;
	Material() {}
};

#endif