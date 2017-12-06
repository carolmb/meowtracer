#include "Material.h"
#include "../Math/Perlin.h"

Color CheckersMaterial::texture(float u, float v, Point3 &p) {
  /*
  float sines = sin(10*p.x)*sin(10*p.y)*sin(10*p.z);
  if (sines < 0)
      return color1;
  else
      return color2;
  */
  int x = floor(u * repeatx);
  int y = floor(v * repeaty * 2);
  if ((x + y) % 2)
    return color1;
  else
    return color2;
}

Color ImageMaterial::texture(float u, float v, Point3 &p) {
  int x = rint(v * image.width);
  int y = rint(u * image.height);
  return image.at(x % image.width, y % image.height);
}

Color PerlinMaterial::texture(float u, float v, Point3 &p) {
  return Vec3(1,1,1)*0.5*(1 + sin(scale*p.x + 5*perlin(scale*p)));
}
