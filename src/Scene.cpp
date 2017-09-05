#include "../include/Scene.h"
#include <cmath>
#include <limits>
#define INF std::numeric_limits<double>::infinity()

Color Scene::backgroundColor(double tCol, double tRow)  {
	Color top = tl.lerp(tr, tCol);
	Color bottom = bl.lerp(br, tCol);
	return top.lerp(bottom, tRow);
}