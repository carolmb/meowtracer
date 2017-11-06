#include "MapRenderer.h"
#include <cmath>
#include <limits>
#define INF std::numeric_limits<double>::infinity()

Color MapRenderer::getColor(Ray &ray, double &x, double &y) {
	Object* hitObject = 0;
	double mint = INF;
	for (int i = 0; i < objects.size(); i++) {
		double t = objects[i]->hit(ray);
		if (!isnan(t) && t < mint && t > 0) {
			mint = t;
			hitObject = objects[i];
		}
	}
	if (hitObject) {
		double t = mint / maxDepth;
		t = std::min(1.0, std::max(0.0, t));
		return foreground.lerp(background, t);
	} else {
		return background;
	}
}