#include "NormalRenderer.h"
#include <cmath>
#include <limits>
#define INF std::numeric_limits<float>::infinity()

Color NormalRenderer::getColor(Scene &scene, Ray &ray, float &x, float &y) {
	int depth = 0;
	Object* hitObject = 0;
	float mint = INF;
	for (int i = 0; i < scene.objects.size(); i++) {
		float t = scene.objects[i]->hit(ray);
		if (!isnan(t) && t < mint && t > 0) {
			mint = t;
			hitObject = scene.objects[i];
		}
	}
	if (hitObject) {
		Point3 hitPoint = ray.at(mint);
		Vec3 n = hitObject->getNormal(hitPoint);
		float r = (n.x + 1) / 2;
		float g = (n.y + 1) / 2;
		float b = (n.z + 1) / 2;
		return Color(r, g, b);
	} else {
		return scene.backgroundColor(x, y);
	}
}
