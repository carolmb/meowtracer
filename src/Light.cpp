#include "../include/Light.h"

Color Light::diffuseColor (Material* material, Vec3 &n, Vec3 &l) {
	double r = (-l).dot(n);
	if (r > 0) {
		return (material->diffuse * color) * fmin(1.0, r);
	} else {
		return Color(0, 0, 0);
	}
}

Color Light::specularColor(Material* material, Vec3 &n, Vec3 &l, Vec3 &v) {
	Vec3 half = -v - l;
	half.normalize();
	double r = half.dot(n);
	if (r > 0) {
		return (material->specular * color) * fmin(1.0, pow(r, material->shininess));
	} else {
		return Color(0, 0, 0);
	}
}

Color Light::ambientColor(Material* material) {
	return material->ambient * color;
}