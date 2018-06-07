#ifndef __MATERIAL__
#define __MATERIAL__

#include "../Math/Vec3.h"
#include <vector>
#include <cmath>

using std::vector;

struct Material {

	Color ambient = Color(0, 0, 0);
	Color diffuse = Color(0, 0, 0);
	Color specular = Color(0, 0, 0);
	Color emissive = Color(0, 0, 0);

	int illum = 0;
	float shininess = 1;
	float roughness = 1;
	float ref = 0;
	float opacity = 1;
	
	vector<Color> colors;
	vector<float> times;
	float outlineAngle = 0;
	Color outlineColor = Color(0, 0, 0);

};

#endif