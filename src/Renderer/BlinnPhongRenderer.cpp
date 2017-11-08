#include "BlinnPhongRenderer.h"
#include "../Light/Light.h"
#include <limits>
#include <iostream>
#define INF std::numeric_limits<float>::infinity()

Color BlinnPhongRenderer::getObjectColor(Scene &scene, Ray &ray, HitRecord &hr, Object* object) {
	Vec3 v = ray.direction;
	Color finalColor(0, 0, 0);
	for (int i = 0; i < scene.lights.size(); i++) {
		Vec3 dir = scene.lights[i]->getDirection(hr.point);
		if (!intersects(scene, hr.point, dir)) {
			finalColor += scene.lights[i]->diffuseColor(object->material, hr, dir);
			finalColor += scene.lights[i]->specularColor(object->material, hr, dir, v);
		}
	}
	finalColor += Vec3::Cross(object->material->ambient, scene.ambientColor);
	return finalColor;
}
