#ifndef __CRENDER__
#define __CRENDER__

#include "Renderer.h"

class CelRenderer : public Renderer {
public:
	CelRenderer(int s, int d) : Renderer(s, d) {}
  Color getColor(Scene &scene, Ray &ray, float &x, float &y);
};

#endif