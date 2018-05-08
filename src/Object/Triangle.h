#ifndef __TRIANGLE__
#define __TRIANGLE__

#include "Object.h"

class Triangle : public Object {
private:
	bool culling;
	Vec3 normals[3];
	float tx[3];
	float ty[3];

	Vec3 origin;
	Vec3 e1, e2;
	public:
	Triangle(Matrix4 xform, Point3 &p0, Point3 &p1, Point3 &p2, bool c = false);
	void setNormals(Vec3& n1, Vec3& n2, Vec3& n3);
	void setTexture(float t[6]);
	RayHit hit(Ray &ray);
};

#endif