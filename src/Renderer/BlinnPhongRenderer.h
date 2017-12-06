#ifndef __BPRENDER__
#define __BPRENDER__

#include "Renderer.h"

class BlinnPhongRenderer : public Renderer {
public:
	BlinnPhongRenderer(int s, int d) : Renderer(s, d) {}
  Color getColor(Scene &scene, Ray &ray, float &x, float &y);
};

#endif