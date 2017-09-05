#include "../include/ParallelLight.h"

double ParallelLight::getIntensity(Vec3 &n) {
	return direction.dot(n);
}