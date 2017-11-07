#ifndef __SCENE__
#define __SCENE__

#include "Vec3.h"
#include "Camera/Camera.h"
#include "Object/Object.h"
#include "Object/Material.h"
#include "Light/Light.h"
#include <vector>

class Scene {
public:
	Camera* camera;
	Color tl, tr, bl, br;
	std::vector<Object*> objects;
	std::vector<Material*> materials;
	std::vector<Light*> lights;
  Color ambientColor;
	Color backgroundColor(double tCol, double tRow);
};

#endif