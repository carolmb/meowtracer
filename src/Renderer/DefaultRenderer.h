#ifndef __DEFR__
#define __DEFR__

#include "Renderer.h"

class DefaultRenderer : public Renderer {
protected:
	bool intersects(Scene &scene, Point3 &p, Vec3 &l);
	virtual Color getObjectColor(Scene &scene, Ray &ray, HitRecord &hr, Object* object) = 0;
public:
	DefaultRenderer (int &s) : Renderer(s) {}
  Color getColor(Scene &scene, Ray &ray, float &x, float &y);
};

#endif