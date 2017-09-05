#ifndef __SCENE__
#define __SCENE__

#include "Vec3.h"
#include "Camera.h"
#include "Object.h"
#include "Material.h"
#include "Light.h"
#include <vector>

class Scene {
public:
	Camera* camera;
	Color tl, tr, bl, br;
	std::vector<Object*> objects;
	std::vector<Material*> materials;
	std::vector<Light*> lights;
	Color backgroundColor(double tCol, double tRow);
};

#endif