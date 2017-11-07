#ifndef __MAPR__
#define __MAPR__

#include "Renderer.h"

class MapRenderer : public Renderer {
private:
	Color foreground;
	Color background;
	float maxDepth;
public:
	MapRenderer(int &s, Color &fg, Color &bg, float &d) : Renderer(s), foreground(fg), background(bg), maxDepth(d) {}
	Color getColor(Scene &scene, Ray &ray, float &x, float &y);
};

#endif