#ifndef __MAPR__
#define __MAPR__

#include "Renderer.h"

class MapRenderer : public Renderer {
private:
	Color foreground;
	Color background;
	double maxDepth;
public:
	MapRenderer(Color &fg, Color &bg, double &d) : foreground(fg), background(bg), maxDepth(d) {}
	Color getColor(Ray &ray, double &x, double &y);
};

#endif