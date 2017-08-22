#include "../include/MapRenderer.h"
#include <cmath>
#include <limits>
#define INF std::numeric_limits<double>::infinity()

Color MapRenderer::getColor(Scene &scene, Ray &ray, double x, double y) {
	Object* hitObject = 0;
	double mint = INF;
	for (int i = 0; i < scene.objects.size(); i++) {
		double t = scene.objects[i]->hit(ray);
		if (!isnan(t) && t < mint && t > 0) {
			mint = t;
			hitObject = scene.objects[i];
		}
	}
	if (hitObject) {
		//Point3 p1 = ray.at(mint);
		//Point3 p2 = scene.camera->pixelPosition(x, y);
		//double t = (p1 - p2).len() / maxDepth;
		double t = mint / maxDepth;
		t = std::min(1.0, std::max(0.0, t));
		return foreground.lerp(background, t);
	} else {
		return background;
	}
}