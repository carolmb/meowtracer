#include "Sphere.h"
#include <iostream>
#include <cmath>

Sphere::Sphere(Matrix4 &xform, Point3 p, float r) : center(p), radius(r) {	
	Matrix4 translation = Matrix4::Translation(center);
	Matrix4 scaling = Matrix4::Scaling(radius);
	transform = scaling * translation;	
	transform = transform * xform;
	invt = transform.Inverse();
}

HitRecord Sphere::hit(Ray &ray) {
	HitRecord hr;

	Point3 o = invt.TransformPoint(ray.origin);
	Vec3 d = invt.TransformVector(ray.direction);

	float a = Vec3::Dot(d, d);
	float b = 2 * Vec3::Dot(d, o);
	float c = Vec3::Dot(o, o) - 1;
	float delta = b * b - 4 * a * c;

	if (delta >= 0) {
		Ray tRay = Ray(o, d);
		float sqrtdelta = std::sqrt(delta);
		float t1 = (-b - sqrtdelta) / (2 * a);
		float t2 = (-b + sqrtdelta) / (2 * a);
		hr.t = std::min(t1, t2);
		hr.point = ray.at(hr.t);
		hr.normal = tRay.at(hr.t);
		hr.normal = transform.TransformVector(hr.normal);
		hr.normal = Vec3::Normalize(hr.normal);
	} else {
		hr.t = NAN;
	}
	return hr;
}