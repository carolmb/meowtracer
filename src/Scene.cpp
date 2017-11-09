#include "Scene.h"
#include <cmath>
#include <limits>
#define INF std::numeric_limits<float>::infinity()

Color Scene::backgroundColor(float tCol, float tRow)  {
	Color top = Vec3::Lerp(tl, tr, tCol);
	Color bottom = Vec3::Lerp(bl, br, tCol);
	return Vec3::Lerp(top, bottom, tRow);
}