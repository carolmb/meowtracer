#include "../include/OrthogonalCamera.h"

Vec3 OrthogonalCamera::getRayDirection(double i, double j) { 
	return horizontal + vertical; 
}