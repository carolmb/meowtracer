#ifndef __RENDERER__
#define __RENDERER__

#include "Scene.h"
#include "Ray.h"
#include "Color.h"

class Renderer {
public:
	Color* render(Scene &scene, int width, int height);
	virtual Color getColor(Scene &scene, Ray &ray, double x, double y) = 0;
};

#endif