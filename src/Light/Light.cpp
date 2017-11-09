#include "Light.h"
#include <iostream>

Color Light::diffuseColor (Material* material, HitRecord &hr, Vec3 &l) {
	float r = Vec3::Dot(l, hr.normal);
	if (r > 0) {
		return (material->diffuse * color) * fmin(1.0, r);
	} else {
		return Color(0, 0, 0);
	}
}

Color Light::specularColor(Material* material, HitRecord &hr, Vec3 &l, Vec3 &v) {
	Vec3 half = l - v;
	half = Vec3::Normalize(half);
	float r = Vec3::Dot(half, hr.normal);
	if (r > 0) {
		return (material->specular * color) * fmin(1.0, pow(r, material->shininess));
	} else {
		return Color(0, 0, 0);
	}
}