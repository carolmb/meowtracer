
#ifndef __DIFR__
#define __DIFR__

#include "Renderer.h"

class DiffuseRenderer : public Renderer {
private:
	int rayCount;
public:
	DiffuseRenderer (int &s, int &r) : Renderer(s), rayCount(r) {}
	Color getColor(Scene &scene, Ray &ray, double &x, double &y);
};

#endif