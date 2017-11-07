#ifndef __RENDERER__
#define __RENDERER__

#include "../Scene.h"
#include "../Ray.h"
#include "../Vec3.h"

class Renderer {
private:
	int sampleCount;
public:
	Renderer(int &s) : sampleCount(s) {}
	Color* render(Scene &scene, int width, int height);
	virtual Color getColor(Scene &scene, Ray &ray, float &x, float &y) = 0;
};

#endif