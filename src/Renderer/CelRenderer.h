#ifndef __CRENDER__
#define __CRENDER__

#include "DefaultRenderer.h"

class CelRenderer : public DefaultRenderer {
protected:
	Color getObjectColor(Scene &scene, Ray &ray, HitRecord &hr, Object* object);
public:
	CelRenderer(int &s) : DefaultRenderer(s) {}
};

#endif