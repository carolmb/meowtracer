#ifndef __DIER__
#define __DIER__

#include "Renderer.h"

class DieletricRenderer : public Renderer {
protected:
  int rayCount;
  Color getObjectColor(Scene &scene, Ray &ray, RayHit &hr);
public:
  DieletricRenderer (int &s, int &r) : Renderer(s), rayCount(r) {}
  Color getColor(Scene &scene, Ray &ray, float &x, float &y);
};

#endif