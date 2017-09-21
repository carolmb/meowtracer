#include "../../include/Renderer/BlinnPhongRenderer.h"
#include "../../include/Light.h"
#include <limits>
#include <iostream>
#define INF std::numeric_limits<double>::infinity()

Color BlinnPhongRenderer::getObjectColor(Scene &scene, Ray &ray, double &t, Object* object) {
	Point3 hitPoint = ray.at(t);
	Vec3 n = object->getNormal(hitPoint);
	Vec3 v = ray.getDirection();
	n.normalize();
	Color finalColor(0, 0, 0);
	for (int i = 0; i < scene.lights.size(); i++) {
		Vec3 dir = scene.lights[i]->getDirection(hitPoint);
		if (!intersects(scene, hitPoint, dir)) {
			finalColor += scene.lights[i]->diffuseColor(object->material, n, dir);
			finalColor += scene.lights[i]->specularColor(object->material, n, dir, v);
		}
	}
	finalColor += object->material->ambient * scene.ambientColor;
	return finalColor;
}
