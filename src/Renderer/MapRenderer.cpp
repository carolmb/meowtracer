#include "MapRenderer.h"
#include <cmath>
#include <limits>
#define INF std::numeric_limits<float>::infinity()

Color MapRenderer::getColor(Scene &scene, Ray &ray, float &x, float &y) {
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
		//Point3 p1 = ray.at(mint);
		//Point3 p2 = scene.camera->pixelPosition(x, y);
		//float t = (p1 - p2).len() / maxDepth;
		float t = mint / maxDepth;
		t = std::min(1.0, fmax(0.0, t));
		return Vec3::Lerp(foreground, background, t);
	} else {
		return background;
	}
}