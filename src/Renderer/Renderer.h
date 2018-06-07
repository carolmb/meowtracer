#ifndef __RENDERER__
#define __RENDERER__

#include "../Scene.h"
#include "../Math/Ray.h"
#include "../Math/Vec3.h"
#include <limits>
#define INF std::numeric_limits<float>::infinity()

struct Tree {
  Tree* children[8];
  Vec3 bounds[2];
  std::vector<Object*> objects;
};

class Renderer {
protected:
	int sampleCount;
  int treeDepth;
  Tree* tree;
public:
	Renderer(int s, int d) : sampleCount(s), treeDepth(d) {}
	Color* render(Scene &scene, int width, int height);
  RayHit getHit(std::vector<Object*> objects, Ray& ray);
  RayHit getHit(Ray& ray);
  bool intersects(Scene &scene, Point3 &p, Vec3 &l);
	virtual Color getColor(Scene &scene, Ray &ray, float &x, float &y) = 0;
};

#endif