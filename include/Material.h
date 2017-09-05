#ifndef __MATERIAL__
#define __MATERIAL__

class Material {
public:
	Color ambient;
	Color diffuse;
	Color specular;
	double shininess;
	Material(Color &a, Color &d, Color &s, double i) : 
		ambient(a), diffuse(d), specular(s), shininess(i) {}
};

#endif