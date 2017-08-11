#include "../include/PerspectiveCamera.h"

Vec3 PerspectiveCamera::getRayDirection(double i, double j) { 
	return lens + horizontal * i + vertical * j; 
}