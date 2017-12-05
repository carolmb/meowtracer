#include "MapRenderer.h"
#include <cmath>
#include <limits>
#define INF std::numeric_limits<float>::infinity()

Color MapRenderer::getColor(Scene &scene, Ray &ray, float &x, float &y) {
	Object* hitObject = 0;
	float mint = INF;
	for (int i = 0; i < scene.objects.size(); i++) {
		RayHit hr = scene.objects[i]->hit(ray);
		if (!std::isnan(hr.t) && hr.t < mint && hr.t > 0) {
			mint = hr.t;
			hitObject = scene.objects[i];
		}
	}
	if (hitObject) {
		float t = mint / maxDepth;
		t = std::min(1.0, fmax(0.0, t));
		return Vec3::Lerp(foreground, background, t);
	} else {
		return background;
	}
}