
#ifndef __DIFR__
#define __DIFR__

#include "Renderer.h"

class DiffuseRenderer : public Renderer {
protected:
	int rayCount;
  vector<Color> materials;
  Vec3 randomUnitVec3();
  Color getAmbientColor(Object* obj);
  Color getLightColor(Light* light, Object* obj, Point3 &hitPoint, 
    Vec3 &normal, Vec3 &rayDir, Vec3 &lightDir);
public:
	Color getColor(Ray &ray, double &x, double &y);
};

#endif