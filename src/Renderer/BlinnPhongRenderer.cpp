#include "BlinnPhongRenderer.h"
#include "../Light.h"
#include <limits>
#include <iostream>
#define INF std::numeric_limits<double>::infinity()

Color BlinnPhongRenderer::getLightColor(Light* light, Point3 &hitPoint, 
    Vec3 &normal, Vec3 &rayDir, Vec3 &lightDir, Object* obj) {

	BPMaterial* mat = &materials[object->materialID];
	Vec3 dir = -light->getDirection(hitPoint, normal, ray.getDirection());
	Color color = scene.lights[i]->getColor(hitPoint, normal, ray.getDirection(), dir);

	Color diff = mat->diffuse * color * diffuseCoef(normal, dir)
	Color spec = specularCoef(mat->shine, Vec3 &normal, Vec3 &lightDir, Vec3 &rayDir)

	return diff + spec;
}

Color BlinnPhongRenderer::getAmbientColor(Object* object) {
	BPMaterial* mat = &materials[object->materialID];
	return ambientLight * mat->ambient;
}