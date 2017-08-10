#ifndef __RENDERER__
#define __RENDERER__

#include "util/Camera.h"
#include "util/Color.h"

class Renderer {
public:
	Color* render(Camera* camera, int width, int height);
	Color getColor(const Ray& r);
};

#endif