#ifndef __RENDERER__
#define __RENDERER__

#include "Camera.h"
#include "Color.h"
#include "Sphere.h"

class Renderer {
public:
	Color* render(Camera* camera, int width, int height);
	Color getColor(Ray &ray);
};

#endif