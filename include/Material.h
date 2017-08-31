#ifndef __MATERIAL__
#define __MATERIAL__

class Material {
	Color albedo;
public:
	Material(Color &c) : albedo(c) {}
	Color getColor() { return albedo; }
};

#endif