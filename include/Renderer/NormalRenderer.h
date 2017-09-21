
#ifndef __NORMALR__
#define __NORMALR__

#include "Renderer.h"

class NormalRenderer : public Renderer {
public:
	NormalRenderer (int &s) : Renderer(s) {}
	Color getColor(Scene &scene, Ray &ray, double &x, double &y);
};

#endif