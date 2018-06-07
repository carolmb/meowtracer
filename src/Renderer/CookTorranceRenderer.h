#ifndef __CTRENDER__
#define __CTRENDER__

#include "Renderer.h"

class CookTorranceRenderer : public Renderer {
public:
	CookTorranceRenderer(int s, int d) : Renderer(s, d) {}
  Color getColor(Scene &scene, Ray &ray, float &x, float &y);
};

#endif