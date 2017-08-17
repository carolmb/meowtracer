
#ifndef __MAPR__
#define __MAPR__

#include "Renderer.h"

class MapRenderer : public Renderer {
public:
	Color getColor(Scene &scene, Ray &ray, double x, double y);
};

#endif