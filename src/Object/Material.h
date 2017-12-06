#ifndef __MATERIAL__
#define __MATERIAL__

#include "../Math/Vec3.h"
#include "../Image.h"
#include <vector>
#include <cmath>

class Material {
public:
	Color ambient = Color(1, 1, 1);
	Color diffuse = Color(1, 1, 1);
	Color specular = Color(1, 1, 1);
	float shininess = 1;
  float ref = 0;
  std::vector<Color> colors;
  std::vector<float> times;
  float outlineAngle = 0;
  Color outlineColor = Color(0, 0, 0);

	Material() {}
  virtual Color texture(float u, float v, Point3 &p) { return Color(1, 1, 1); }
  
};

class CheckersMaterial : public Material {
private:
  Color color1, color2;
  int repeatx, repeaty;
public:
  CheckersMaterial(Color &c1, Color &c2, int rx, int ry) : 
    color1(c1), color2(c2), repeatx(rx), repeaty(ry) {}
  Color texture(float u, float v, Point3 &p);
};

class PerlinMaterial : public Material {
private:
  float scale;
public:
  PerlinMaterial(float s) : scale(s) {}
  Color texture(float u, float v, Point3 &p);
};

class ImageMaterial : public Material {
private:
  Image image;
public:
  ImageMaterial(std::string &fileName) : image(fileName) {}
  Color texture(float u, float v, Point3 &p);
};

#endif