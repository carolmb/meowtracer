#include "DielectricRenderer.h"
#include "RendererUtil.h"

float schlick(float cosine, float ref_idx) {
    float r0 = (1-ref_idx) / (1+ref_idx);
    r0 = r0*r0;
    return r0 + (1-r0)*pow((1 - cosine),5);
}

Vec3 reflect(const Vec3& v, const Vec3& n) {
     return v - 2*Vec3::Dot(v,n)*n;
}

bool refract(const Vec3& v, const Vec3& n, float ni_over_nt, Vec3& refracted) {
    Vec3 uv = Vec3::Normalize(v);
    float dt = Vec3::Dot(uv, n);
    float discriminant = 1.0 - ni_over_nt*ni_over_nt*(1-dt*dt);
    if (discriminant > 0) {
        refracted = ni_over_nt*(uv - n*dt) - n*sqrt(discriminant);
        return true;
    }
    else 
        return false;
}

void scatter(Ray& ray, RayHit &rec) {
  float ref_idx = rec.object->material->ref;
  Vec3 outward_normal, refracted, reflected = reflect(ray.direction, rec.normal);
  float ni_over_nt, reflect_prob, cosine;
  if (Vec3::Dot(ray.direction, rec.normal) > 0) {
      outward_normal = -rec.normal;
      ni_over_nt = ref_idx;
  //         cosine = ref_idx * dot(r_in.direction(), rec.normal) / r_in.direction().length();
      cosine = Vec3::Dot(ray.direction, rec.normal) / ray.direction.Length();
      cosine = sqrt(1 - ref_idx*ref_idx*(1-cosine*cosine));
  }
  else {
      outward_normal = rec.normal;
      ni_over_nt = 1.0 / ref_idx;
      cosine = -Vec3::Dot(ray.direction, rec.normal) / ray.direction.Length();
  }
  if (refract(ray.direction, outward_normal, ni_over_nt, refracted)) 
    reflect_prob = schlick(cosine, ref_idx);
  else 
    reflect_prob = 1.0;
  if (drand48() < reflect_prob) 
    ray = Ray(rec.point, reflected);
  else 
    ray = Ray(rec.point, refracted);
}

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
        scatter(ray, minhr);
        depth++;
      }
    } else {
      color = color * scene.backgroundColor(x, y);
      break;
    }
  }
  return color;
}

Color DielectricRenderer::getObjectColor(Scene &scene, Ray &ray, RayHit &rh) {
  Vec3& v = ray.direction;
  Color finalColor(0, 0, 0);
  for (int i = 0; i < scene.lights.size(); i++) {
    LightHit lh = scene.lights[i]->getHit(ray.direction, rh);
    if (!intersects(scene, lh)) {
      finalColor += scene.lights[i]->diffuseColor(lh);
      finalColor += scene.lights[i]->specularColor(lh);
    }
    finalColor = finalColor * rh.getTexture();
  }
  return finalColor;
}