#ifndef __SCENE__
#define __SCENE__

#include "Color.h"
#include "Camera.h"
#include "Sphere.h"
#include <string>

class Scene {
public:
	Camera* camera;
	Color tl, tr, bl, br;
	Sphere sphere;

	Scene() : sphere(Sphere(Point3(0, 0, 0), 0.25)) {}
	Color backgroundColor(double tCol, double tRow) {
		Color top = tl.lerp(tr, tCol);
		Color bottom = bl.lerp(br, tCol);
		return top.lerp(bottom, tRow);
	}
};

#endif