#include "RendererParser.h"

#include "../OrthogonalCamera.h"
#include "../PerspectiveCamera.h"
#include "../AmbientLight.h"
#include "../DirectionalLight.h"
#include "../PointLight.h"
#include "../SpotLight.h"
#include "../Sphere.h"
#include <iostream>

#define PI 3.14159265359

void RendererParser::parseInfo(json_spirit::Object &json, Renderer* r) {
	if (json.count("OBJECTS")) {
		json_spirit::Array objects = json["OBJECTS"].getArray();	
		for (int i = 0; i < objects.size(); i++) {
			parseObject(renderer, objects[i]);
			r->objects.push_back(parseObject(objects[i]));
		}
	}
	r->sampleCount = json["SAMPLES"].getInt();
	r->camera = parseCamera(json["CAMERA"]);
}

Vec3 RendererParser::parseVec3(json_spirit::Value &value) {
	json_spirit::Array arr = value.getArray();
	double x = arr[0].getReal();
	double y = arr[1].getReal();
	double z = arr[2].getReal();
	return Vec3(x, y, z);
}

Transform RendererParser::parseTransform(json_spirit::Value &value) {
	json_spirit::Array arr = value.getArray();
	Transform transform = Transform::identity();
	for (int i = 0; i < arr.size(); i++) {
		json_spirit::Object t = arr[i].getObject();
		if (json.count("TRANSLATION")) {
			Vec3 v = parseVec3(json["TRANSLATION"]);
			transform = Transform::translation(v) * transform;
		} else if (json.count("SCALE")) {
			Vec3 v = parseVec3(json["SCALE"]);
			transform = Transform::scale(v) * transform;
		} else if (json.count("ROTATION")) {
			Vec3 v = parseVec3(json["ROTATION"]);
			transform = Transform::rotation(v) * transform;
		} else if (json.count("MATRIX")) {
			json_spirit::Array t = json["MATRIX"].getArray();
			double m[4][4];
			for (int j = 0; j < 16; j++) {
				m[j / 4][j % 4] = t[j];
			}
			transform = m * transform;
		}
	}
	return transform;
}

Light* RendererParser::parseLight(json_spirit::Value &value) {
	json_spirit::Object json = value.getObject();
	std::string type = json["TYPE"].getString();
	Color color = parseColor(json["COLOR"]);
	if (type == "ambient") {
		return new AmbientLight(color);
	} else if (type == "directional") {
		Vec3 dir = parseVec3(json["DIRECTION"]);
		dir.normalize();
		return new DirectionalLight(color, dir);
	} else if (type == "point") {
		Point3 origin = parseVec3(json["ORIGIN"]);
		return new PointLight(color, origin);
	} else if (type == "spot") {
		Point3 origin = parseVec3(json["ORIGIN"]);
		Vec3 dir = parseVec3(json["DIRECTION"]);
		double angle = cos(json["ANGLE"].getReal() * PI / 180.0);
		return new SpotLight(color, origin, dir, angle);
	} else {
		std::cout << "Light type not recognized: " << type << std::endl;
		return NULL;
	}
}

Camera* RendererParser::parseCamera(json_spirit::Value &value) {
	json_spirit::Object json = value.getObject();
	std::string type = json["TYPE"].getString();
	Point3 center = parseVec3(json["CENTER"]);
	double w = json["WIDTH"].getReal();
	double h = json["HEIGHT"].getReal();
	Vec3 hor(w, 0, 0);
	Vec3 ver(0, h, 0);
	Point3 p = center - Vec3(w / 2, h / 2, 0);
	Transform transform = parseTransform(json["TRANSFORM"]);
	if (type == "perspective") {
		Point3 viewer = parseVec3(json["VIEWER"]);
		Point3 lens = center + viewer;
		return new PerspectiveCamera(hor, ver, p, transform, lens);
	} else if (type == "orthogonal")  {
		Vec3 dir = parseVec3(json["DIRECTION"]);
		return new OrthogonalCamera(hor, ver, p, transform, dir);
	} else {
		std::cout << "Camera type not recognized: " << type << std::endl;
		return NULL;
	}
}

Object* RendererParser::parseObject(json_spirit::Value &value) {
	json_spirit::Object json = value.getObject();
	std::string type = json["TYPE"].getString();
	Object* obj = 0;
	if (type == "sphere") {
		obj = new Sphere();
	} else {
		std::cout << "Object type not recognized: " << type << std::endl;
		return NULL;
	}
	obj->transform = parseTransform(json["TRANSFORM"]);
	if (json.count("MATERIAL")) {
		obj->materialID = json["MATERIAL"].getInt();
	} else {
		obj->materialID = -1;
	}
	return obj;
}