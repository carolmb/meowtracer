#ifndef __DEFR__
#define __DEFR__

#include "Renderer.h"
#include "../Light/Light.h"

class DefaultRenderer : public Renderer {
protected:
	bool intersects(Point3 &p, Vec3 &l);
  Color diffuseCoef(Vec3 &normal, Vec3 &light);
  Color specularCoef(double shine, Vec3 &normal, Vec3 &light, Vec3 &ray);
	Color getObjectColor(Ray &ray, double &t, Object* object);
  virtual Color getAmbientColor(Object* obj) = 0;
  virtual Color getLightColor(Light* light, Object* obj, Point3 &hitPoint, 
    Vec3 &normal, Vec3 &rayDir, Vec3 &lightDir) = 0;
public:
  std::vector<Light*> lights;
  Color ambientLight;
  Color getColor(Ray &ray, double &x, double &y);
};

#endif