
#ifndef __NORMALR__
#define __NORMALR__

#include "Renderer.h"

class NormalRenderer : public Renderer {
public:
	Color getColor(Ray &ray, double &x, double &y);
};

#endif