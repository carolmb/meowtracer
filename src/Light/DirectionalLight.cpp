#include "DirectionalLight.h"

Vec3 DirectionalLight::getDirection(Point3 &point, Vec3 &normal, Vec3 &ray) {
  return direction;
}

Color DirectionalLight::getColor(Point3 &point, Vec3 &normal, Vec3 &ray, Vec3 &light) {
	return color;
}