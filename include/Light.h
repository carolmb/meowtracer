#ifndef __LIGHT__
#define __LIGHT__

class Light {
public:
	Color color;
	Vec3 direction;
	Light(Color &c, Vec3 &d) : color(c), direction(d) {}
};

#endif