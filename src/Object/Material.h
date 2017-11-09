#ifndef __MATERIAL__
#define __MATERIAL__

#include "../Math/Vec3.h"
#include <vector>

class Material {
public:
	Color ambient;
	Color diffuse;
	Color specular;
	float shininess;
  std::vector<Color> colors;
  std::vector<float> times;
  float outlineAngle;
  Color outlineColor;
	Material() {}
};

#endif