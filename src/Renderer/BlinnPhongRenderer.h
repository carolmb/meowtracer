#ifndef __BPRENDER__
#define __BPRENDER__

#include "DefaultRenderer.h"

struct BPMaterial {
  Color diffuse;
  Color specular;
  Color ambient;
  double shine;
}

class BlinnPhongRenderer : public DefaultRenderer {
protected:
  vector<BPMaterial> materials;
  Color getAmbientColor(Object* obj);
  Color getLightColor(Light* light, Object* obj, Point3 &hitPoint, 
    Vec3 &normal, Vec3 &rayDir, Vec3 &lightDir);
};

#endif