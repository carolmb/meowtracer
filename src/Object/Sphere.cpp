#include "Sphere.h"
#include <iostream>
#include <cmath>

double Sphere::hit(Ray &ray) {
	Vec3 o = ray.getOrigin();
	Vec3 d = ray.getDirection();
	o = o * invt;
	d = d * invt;
	double a = Vec3::Dot(d, d);
	double b = 2 * Vec3::Dot(d, o);
	double c = Vec3::Dot(o, o) - 1;

	double delta = b * b - 4 * a * c;
	if (delta >= 0) {
		double sqrtdelta = std::sqrt(delta);
		double t1 = (-b - sqrtdelta) / (2 * a);
		double t2 = (-b + sqrtdelta) / (2 * a);
		return std::min(t1, t2);
	} else {
		return NAN;
	}
}

Vec3 Sphere::getNormal(Point3 &p) {
	Point3 tp = p * invt;
	Vec3::Normalize(tp);
	return tp * transform;
}

void Sphere::preprocess() {
	Vec3 scaling(1, 1, 1);
	Matrix4 t1 = Matrix4::Scaling(scaling);
	Matrix4 t2 = Matrix4::Translation(center);
	transform = t2 * transform;
	transform = t1 * transform;
	invt = transform.Inverse();
}