#ifndef __SCENE__
#define __SCENE__

#include "Color.h"
#include "Camera.h"
#include "Sphere.h"
#include <vector>

class Scene {
public:
	Camera* camera;
	Color tl, tr, bl, br;
	std::vector<Sphere> spheres;
	double maxDepth;

	Color backgroundColor(double tCol, double tRow);
};

#endif