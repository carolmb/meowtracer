#ifndef __BPRENDER__
#define __BPRENDER__

#include "Renderer.h"

class BlinnPhongRenderer : public Renderer {
protected:
  Color getColor(Scene &scene, Ray &initRay, double &x, double &y);
	Color getObjectColor(Scene &scene, Ray &ray, double &t, Object* object);
public:
	BlinnPhongRenderer (int &s) : Renderer(s) {}
};

#endif