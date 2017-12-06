#ifndef __MAPR__
#define __MAPR__

#include "Renderer.h"

class MapRenderer : public Renderer {
private:
	Color foreground;
	Color background;
	float maxDepth;
public:
	MapRenderer(int s, int d, Color &fg, Color &bg, float md) : Renderer(s, d), 
    foreground(fg), background(bg), maxDepth(md) {}
	Color getColor(Scene &scene, Ray &ray, float &x, float &y);
};

#endif