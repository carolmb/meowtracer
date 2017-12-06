#include "DielectricRenderer.h"
#include "RendererUtil.h"

Color DielectricRenderer::getColor(Scene &scene, Ray &initRay, float &x, float &y) {
  int depth = 0;
  Ray ray = initRay;
  Object* obj = 0;
  Color color(1, 1, 1);
  while (true) {
    RayHit minhr = getHit(ray);
    if (minhr.object) {
      color = color * getObjectColor(scene, ray, minhr);
      if (depth >= rayCount) {
        break;
      } else {
        Point3 d = minhr.normal + randomUnitVec3();
        
        ray = Ray(minhr.point, d);
        depth++;
      }
    } else {
      color = color * scene.backgroundColor(x, y);
      break;
    }
  }
  return color;
}

Color DielectricRenderer::getObjectColor(Scene &scene, Ray &ray, RayHit &hr) {
  Vec3& v = ray.direction;
  Color finalColor(0, 0, 0);
  LightHit lh(ray.direction, hr);
  for (int i = 0; i < scene.lights.size(); i++) {
    lh.lightDir = scene.lights[i]->getDirection(lh);
    if (!intersects(scene, hr.point, lh.lightDir)) {
      finalColor += scene.lights[i]->diffuseColor(lh);
      finalColor += scene.lights[i]->specularColor(lh);
    }
  }
  return finalColor;
}