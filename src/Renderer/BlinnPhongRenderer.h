#ifndef __BPRENDER__
#define __BPRENDER__

#include "DefaultRenderer.h"

class BlinnPhongRenderer : public DefaultRenderer {
protected:
	Color getObjectColor(Scene &scene, Ray &ray, HitRecord &hr, Object* object);
public:
	BlinnPhongRenderer(int &s) : DefaultRenderer(s) {}
};

#endif