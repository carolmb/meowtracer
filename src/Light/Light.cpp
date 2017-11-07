#include "Light.h"
#include <iostream>

Color Light::diffuseColor (Material* material, Vec3 &n, Vec3 &l) {
	float r = Vec3::Dot(l, n);
	if (r > 0) {
		return Vec3::Cross(material->diffuse, color) * fmin(1.0, r);
	} else {
		return Color(0, 0, 0);
	}
}

Color Light::specularColor(Material* material, Vec3 &n, Vec3 &l, Vec3 &v) {
	Vec3 half = l - v;
	half = Vec3::Normalize(half);
	float r = Vec3::Dot(half, n);
	if (r > 0) {
		return Vec3::Cross(material->specular, color) * fmin(1.0, pow(r, material->shininess));
	} else {
		return Color(0, 0, 0);
	}
}