#ifndef __BPRENDER__
#define __BPRENDER__

#include "DiffuseRenderer.h"

class BlinnPhongRenderer : public DiffuseRenderer {
protected:
	Color getObjectColor(Scene &scene, Ray &ray, double &t, Object* object);
public:
	BlinnPhongRenderer (int &s, int &r) : DiffuseRenderer(s, r) {}
};

#endif