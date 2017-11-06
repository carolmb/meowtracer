#ifndef __RENDERER__
#define __RENDERER__

#include "../Ray.h"
#include "../Vec3.h"
#include "../Camera/Camera.h"
#include "../Object/Object.h"
#include <vector>

class Renderer {
protected:
	int sampleCount;
  Color tl, tr, bl, br;
  std::vector<Object*> objects;
  Camera* camera;
  Color backgroundColor(double tCol, double tRow);
public:
	Color* render(int width, int height);
	virtual Color getColor(Ray &ray, double &x, double &y) = 0;
};

#endif