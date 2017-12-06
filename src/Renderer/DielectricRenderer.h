#ifndef __DIER__
#define __DIER__

#include "Renderer.h"

class DielectricRenderer : public Renderer {
protected:
  int rayCount;
  Color getObjectColor(Scene &scene, Ray &ray, RayHit &hr);
public:
  DielectricRenderer (int s, int d, int r) : Renderer(s, d), rayCount(r) {}
  Color getColor(Scene &scene, Ray &ray, float &x, float &y);
};

#endif