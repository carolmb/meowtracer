#ifndef __RDRENDER__
#define __RDRENDER__

#include "Renderer.h"

class RadiosityRenderer : public Renderer {
public:
	RadiosityRenderer(int s, int d) : Renderer(s, d) {}
  Color getColor(Scene &scene, Ray &ray, float &x, float &y);
};

#endif