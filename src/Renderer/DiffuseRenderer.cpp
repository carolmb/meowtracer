#include "DiffuseRenderer.h"
#include "RendererUtil.h"

Color DiffuseRenderer::getColor(Scene &scene, Ray &initRay, float &x, float &y) {
	int depth = 0;
	Ray ray = initRay;
	Color color(1, 1, 1);
	while (true) {
		RayHit minhr = getHit(ray);
		if (minhr.object) {
			color = color * getObjectColor(scene, ray, minhr);
			if (depth >= rayCount) {
				break;
			} else {
				Point3 d = minhr.normal + randomUnitVec3();
				ray = Ray(minhr.point, d);
			}
		} else {
			color = color * scene.backgroundColor(x, y);
			break;
		}
	}
	return color;
}

Color DiffuseRenderer::getObjectColor(Scene &scene, Ray &ray, RayHit &hr) {
	Color finalColor(0, 0, 0);
	for (int i = 0; i < scene.lights.size(); i++) {
		LightHit lh(ray.direction, hr);
		Vec3 dir = scene.lights[i]->getDirection(lh);
		finalColor += scene.lights[i]->diffuseColor(lh);
	}
	return finalColor;
}
