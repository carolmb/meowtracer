#include "../include/PerspectiveCamera.h"

Ray PerspectiveCamera::getRay(double i, double j) { 
	return Ray(lens, pixelPosition(i, j) - lens); 
}

double PerspectiveCamera::getDepth(Point3 p) {
	return (p - lens).len();
}