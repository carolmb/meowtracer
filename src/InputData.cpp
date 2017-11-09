#include "InputData.h"
#include "Camera/OrthogonalCamera.h"
#include "Camera/PerspectiveCamera.h"
#include "Object/Sphere.h"
#include "Object/Triangle.h"
#include "Object/Material.h"
#include "Light/DirectionalLight.h"
#include "Light/PointLight.h"
#include "Light/SpotLight.h"
#include "Renderer/NormalRenderer.h"
#include "Renderer/MapRenderer.h"
#include "Renderer/DiffuseRenderer.h"
#include "Renderer/BlinnPhongRenderer.h"
#include "Renderer/CelRenderer.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include <json_spirit/json_spirit.h>
#define PI 3.14159265359

std::string clearComments(std::string &input) {
	int found = input.find_first_of("#");
	if (found != std::string::npos) {
		input = input.substr(0, found);
	}
	return input;
}

bool isEmpty(std::string input) {
	for(int i = 0; i < input.size(); i++) {
		if (input[i] != ' ')
			return false;
	}
	return true;
}

std::string readInput(std::ifstream &file) {
	std::string input;
	std::string cleanInput = "";
	while(!file.eof()) {
		getline(file, input);
		clearComments(input);
		if (!isEmpty(input)) {
			cleanInput += input + "\n";
		}
	}
	return cleanInput;
}

bool InputData::load(std::string &fileName) {
	std::ifstream file(fileName.c_str(), std::ifstream::in);
	if (file.is_open()) {
		std::string content = readInput(file);
		if (parse(content)) {
			return true;
		} else {
			std::cout << "File not valid." << std::endl;
			return false;
		}
	} else {
		std::cout << "File does not exist." << std::endl;
	}
}

Color parseColor(json_spirit::Value &value) {
	json_spirit::Array json = value.getArray();
	float r = json[0].getReal();
	float g = json[1].getReal();
	float b = json[2].getReal();
	return Color(r, g, b);
}

Vec3 parseVec3(json_spirit::Value &value) {
	json_spirit::Array arr = value.getArray();
	float x = arr[0].getReal();
	float y = arr[1].getReal();
	float z = arr[2].getReal();
	return Vec3(x, y, z);
}

Matrix4 parseTransform(json_spirit::Value &value) {
	json_spirit::Array arr = value.getArray();
	Matrix4 transform = Matrix4::Identity();
	for (int i = 0; i < arr.size(); i++) {
		json_spirit::Object json = arr[i].getObject();
		if (json.count("TRANSLATION")) {
			Vec3 v = parseVec3(json["TRANSLATION"]);
			Matrix4 t = Matrix4::Translation(v);
			transform = transform * t;
		} else if (json.count("SCALE")) {
			Vec3 v = parseVec3(json["SCALE"]);
			Matrix4 t = Matrix4::Scaling(v);
			transform = transform * t;
		} else if (json.count("ROTATION")) {
			Vec3 v = parseVec3(json["ROTATION"]);
			Matrix4 t = Matrix4::Rotation(v.x, v.y, v.z);
			transform = transform * t;
		} else if (json.count("MATRIX")) {
			json_spirit::Array t = json["MATRIX"].getArray();
			Matrix4 m;
			for (int j = 0; j < 16; j++) {
				m[j / 4][j % 4] = t[j].getReal();
			}
			transform = transform * m;
		}
	}
	return transform;
}

Material* parseMaterial(json_spirit::Value &value) {
	json_spirit::Object json = value.getObject();
	Material* m = new Material();
	if (json.count("AMBIENT")) {
		m->ambient = parseColor(json["AMBIENT"]);
	}
	if (json.count("DIFFUSE")) {
		m->diffuse = parseColor(json["DIFFUSE"]);
	}
	if (json.count("SPECULAR")) {
		m->specular = parseColor(json["SPECULAR"]);
	}
	if (json.count("SHINE")) {
		m->shininess = json["SHINE"].getReal();
	}
	if (json.count("OUTLINECOLOR")) {
		m->outlineColor = parseColor(json["OUTLINECOLOR"]);
	}
	if (json.count("OUTLINEANGLE")) {
		m->outlineAngle = json["OUTLINEANGLE"].getReal();
	}
	if (json.count("COLORS")) {
		json_spirit::Array arr = json["COLORS"].getArray();
		for (int i = 0; i < arr.size(); i++) {
			m->colors.push_back(parseColor(arr[i]));
		}
	}
	if (json.count("INTERVALS")) {
		json_spirit::Array arr = json["INTERVALS"].getArray();
		for (int i = 0; i < arr.size(); i++) {
			m->times.push_back(arr[i].getReal());
		}
	}
	return m;
}

Light* parseLight(json_spirit::Value &value) {
	json_spirit::Object json = value.getObject();
	std::string type = json["TYPE"].getString();
	Color color = parseColor(json["COLOR"]);
	Matrix4 xform = json.count("TRANSFORM") ? parseTransform(json["TRANSFORM"]) : Matrix4::Identity();
	if (type == "directional") {
		Vec3 dir = parseVec3(json["DIRECTION"]);
		dir = Vec3::Normalize(dir);
		return new DirectionalLight(xform, color, dir);
	} else if (type == "point") {
		Point3 origin = parseVec3(json["ORIGIN"]);
		return new PointLight(xform, color, origin);
	} else if (type == "spot") {
		Point3 origin = parseVec3(json["ORIGIN"]);
		Vec3 dir = parseVec3(json["DIRECTION"]);
		float angle = cos(json["ANGLE"].getReal() * PI / 180.0);
		return new SpotLight(xform, color, origin, dir, angle);
	} else {
		return NULL;
	}
}

Object* parseObject(json_spirit::Value &value, Scene &scene) {
	json_spirit::Object json = value.getObject();
	std::string type = json["TYPE"].getString();
	Matrix4 xform;
	if (json.count("TRANSFORM")) {
		xform = parseTransform(json["TRANSFORM"]);
	} else {
		xform = Matrix4::Identity();
	}
	Object* obj = 0;
	if (type == "sphere") {
		float r = json["RADIUS"].getReal();
		Vec3 center = parseVec3(json["CENTER"]);
		obj = new Sphere(xform, center, r);
	} else if (type == "triangle") {
		Vec3 p0 = parseVec3(json["P0"]);
		Vec3 p1 = parseVec3(json["P1"]);
		Vec3 p2 = parseVec3(json["P2"]);
		obj = new Triangle(xform, p0, p1, p2);
	} else {
		return NULL;
	}
	if (json.count("MATERIAL")) {
		int material = json["MATERIAL"].getInt();
		obj->material = scene.materials[material];
	}
	return obj;
}

Camera* parseCamera(json_spirit::Value &value) {
	json_spirit::Object json = value.getObject();
	std::string type = json["TYPE"].getString();
	Matrix4 xform = json.count("TRANSFORM") ? parseTransform(json["TRANSFORM"]) : Matrix4::Identity();
	Point3 center = parseVec3(json["CENTER"]);
	float w = json["WIDTH"].getReal();
	float h = json["HEIGHT"].getReal();
	Vec3 hor(w, 0, 0);
	Vec3 ver(0, h, 0);
	Point3 p = center - Vec3(w / 2, h / 2, 0);
	if (type == "perspective") {
		Point3 viewer = parseVec3(json["VIEWER"]);
		Point3 lens = center + viewer;
		return new PerspectiveCamera(xform, hor, ver, p, lens);
	} else if (type == "orthogonal") {
		Vec3 dir = json.count("DIRECTION") ? parseVec3(json["DIRECTION"]) : Vec3(0, 0, -1);
		return new OrthogonalCamera(xform, hor, ver, p, dir);
	} else {
		std::cout << "Camera type not recognized: " << type << std::endl;
		return NULL;
	}
}

Renderer* parseRenderer(json_spirit::Value &value) {
	json_spirit::Object json = value.getObject();
	std::string type = json["TYPE"].getString();
	int samples = json["SAMPLES"].getInt();
	if (type == "normal") {
		return new NormalRenderer(samples);
	} else if (type == "map") {
		Color fg = parseColor(json["FOREGROUND"]);
		Color bg = parseColor(json["BACKGROUND"]);
		float d = json["MAXDEPTH"].getReal();
		return new MapRenderer(samples, fg, bg, d);
	} else if (type == "diffuse") {
		int depth = json["RAYDEPTH"].getInt();
		return new DiffuseRenderer(samples, depth);
	} else if (type == "blinnphong") {
		return new BlinnPhongRenderer(samples);
	} else if (type == "cel") {
		return new CelRenderer(samples);
	} else {
		std::cout << "Renderer type not recognized: " << type << std::endl;
		return NULL;
	}
}

bool InputData::parse(std::string &content) {
	json_spirit::Value value;
	json_spirit::read(content, value);
	json_spirit::Object json = value.getObject();

	outputFile = json["NAME"].getString();
	outputType = json["TYPE"].getString();
	isBin = json["CODIFICATION"].getString() == "binary";
	colCount = json["WIDTH"].getInt();
	rowCount = json["HEIGHT"].getInt();
	scene.tl = parseColor(json["UPPER_LEFT"]);
	scene.tr = parseColor(json["UPPER_RIGHT"]);
	scene.bl = parseColor(json["LOWER_LEFT"]);
	scene.br = parseColor(json["LOWER_RIGHT"]);
	scene.ambientColor = parseColor(json["AMBIENT"]);
	if (json.count("MATERIALS")) {
		json_spirit::Array materials = json["MATERIALS"].getArray();
		for (int i = 0; i < materials.size(); i++) {
			scene.materials.push_back(parseMaterial(materials[i]));
		}
	}
	if (json.count("LIGHTS")) {
		json_spirit::Array lights = json["LIGHTS"].getArray();
		for (int i = 0; i < lights.size(); i++) {
			scene.lights.push_back(parseLight(lights[i]));
		}
	}
	if (json.count("PREFABS")) {
		json_spirit::Array prefabs = json["PREFABS"].getArray();
		for (int i = 0; i < prefabs.size(); i++) {
			// TODO
			// scene.prefabs.push_back(prefabs[i].getObject());
		}
	}
	json_spirit::Array objects = json["OBJECTS"].getArray();
	for (int i = 0; i < objects.size(); i++) {
		scene.objects.push_back(parseObject(objects[i], scene));
	}
	scene.camera = parseCamera(json["CAMERA"]);
	renderer = parseRenderer(json["RENDERER"]);
}