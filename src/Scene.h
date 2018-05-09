#ifndef __SCENE__
#define __SCENE__

#include "Math/Vec3.h"
#include "Math/Matrix4.h"
#include "Camera/Camera.h"
#include "Object/Object.h"
#include "Object/Material.h"
#include "Object/Texture.h"
#include "Light/Light.h"
#include <vector>

using std::vector;

class Scene {
public:
  Matrix4 transform;
  Camera* camera;
  Color tl, tr, bl, br;

  vector<Object*> objects;
  vector<Material*> materials;
  vector<Texture*> textures;

  vector<Light*> lights;
  Color ambientColor;

  Color backgroundColor(float tCol, float tRow);
};

#endif