#ifndef __NORMALR__
#define __NORMALR__

#include "Renderer.h"

class NormalRenderer : public Renderer {
public:
	NormalRenderer (int s, int d) : Renderer(s, d) {}
	Color getColor(Scene &scene, Ray &ray, float &x, float &y);
};

#endif