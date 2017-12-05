#ifndef __BPRENDER__
#define __BPRENDER__

#include "Renderer.h"

class BlinnPhongRenderer : public Renderer {
public:
	BlinnPhongRenderer(int &s) : Renderer(s) {}
  Color getColor(Scene &scene, Ray &ray, float &x, float &y);
};

#endif