
#ifndef __MAPR__
#define __MAPR__

#include "Renderer.h"

class MapRenderer : public Renderer {
private:
	Color foreground;
	Color background;
	double maxDepth;
public:
	MapRenderer(int &s, Color &fg, Color &bg, double &d) : Renderer(s), foreground(fg), background(bg), maxDepth(d) {}
	Color getColor(Scene &scene, Ray &ray, double &x, double &y);
};

#endif