#include "NormalRenderer.h"
#include <cmath>
#include <limits>
#define INF std::numeric_limits<float>::infinity()

Color NormalRenderer::getColor(Scene &scene, Ray &ray, float &x, float &y) {
	int depth = 0;
	RayHit minhr = getHit(ray);
	if (minhr.object) {
		float r = (minhr.normal.x + 1) / 2;
		float g = (minhr.normal.y + 1) / 2;
		float b = (minhr.normal.z + 1) / 2;
		return Color(r, g, b);
	} else {
		return scene.backgroundColor(x, y);
	}
}
