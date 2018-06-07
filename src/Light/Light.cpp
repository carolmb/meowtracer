#include "Light.h"
#include <iostream>
#define PI 3.14159265359

Color Light::diffuseColor (LightHit &lh) {
  float r = Vec3::Dot(lh.lightDir, lh.rayHit.normal) / lh.lightDir.Length();
  if (r > 0) {
    float a = getIntensity(lh);
    if (a > 0) {
      Color &diff = lh.rayHit.object->material->diffuse;
      return (diff * color) * fmin(1.0, r * a);
    }
  }
  return Color(0, 0, 0);
}

Color Light::specularColor(LightHit &lh) {
  Vec3 half = lh.lightDir - lh.rayDir;
  half = Vec3::Normalize(half);
  float r = Vec3::Dot(half, lh.rayHit.normal);
  if (r > 0) {
    float a = getIntensity(lh);
    if (a > 0) {
      float s = lh.rayHit.object->material->shininess;
      Color &spec = lh.rayHit.object->material->specular;
      return (spec * color) * fmin(1.0, pow(r * a, s));
    }
  }
  return Color(0, 0, 0);
}

// Code below from https://github.com/pboechat/cook_torrance/

Color Light::fresnel(LightHit &lh) {
  Vec3& p = lh.rayHit.point;
  Vec3& n = lh.rayHit.normal;
  Vec3 w0 = -lh.rayDir;
  Vec3& wi = lh.lightDir;

  // Light
  Vec3 Li = getIntensity(lh) * color;
  float n_wi = fmax(0, Vec3::Dot(n, wi));

  // Diffuse
  Color color = lh.rayHit.object->material->diffuse * Li * n_wi;

  if (n_wi > 0)  {
    float n_w0 = fmax(0, Vec3::Dot(n, w0));
    if (n_w0 <= 0)
      return color;

    Vec3 h = wi + w0;
    h = Vec3::Normalize(h);

    float h_w0 = fmax(0, Vec3::Dot(h, w0));
    if (h_w0 <= 0)
      return color;
    float h_wi = fmax(0, Vec3::Dot(h, wi));
    float n_h = fmax(0, Vec3::Dot(n, h));

    // Fresnel reflectance
    float f = pow(1.0 - h_wi, 5.0);
    Vec3& spec = lh.rayHit.object->material->specular;
    Vec3 F(spec.x + (1 - spec.x)*f, spec.y + (1 - spec.y)*f, spec.z + (1 - spec.z)*f);

    // Microfacet distribution by Beckmann
    float m2 = lh.rayHit.object->material->roughness * lh.rayHit.object->material->roughness;
    float n_h2 = n_h * n_h;
    float r1 = PI * m2 * n_h2 * n_h2;
    float r2 = (n_h2 - 1.0) / (m2 * n_h2);
    float D = exp(r2) / r1;

    // Geometric shadowing
    float g = 2.0 * n_h / h_w0;
    float G = fmin(1.0, fmin(n_w0 * g, n_wi * g));

    // Fresnel
    Vec3 Fr = F * (D * G) / (4 * n_wi * n_w0);

    // Weight
    float p = 2 * PI;

    // Result
    color += Li * Fr * n_wi * p;
  }

  return color;
}