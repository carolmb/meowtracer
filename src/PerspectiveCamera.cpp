#include "../include/PerspectiveCamera.h"

Vec3 PerspectiveCamera::getRayDirection(double i, double j) { 
	return horizontal * i + vertical * j - lens; 
}