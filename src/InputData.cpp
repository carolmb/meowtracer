#include "../include/InputData.h"
#include "../include/OrthogonalCamera.h"
#include "../include/PerspectiveCamera.h"
#include "../include/NormalRenderer.h"
#include "../include/MapRenderer.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include <json_spirit/json_spirit.h>

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
	int r = json[0].getInt();
	int g = json[1].getInt();
	int b = json[2].getInt();
	return Color(r, g, b);
}

Vec3 parseVec3(json_spirit::Value &value) {
	json_spirit::Array arr = value.getArray();
	double x = arr[0].getReal();
	double y = arr[1].getReal();
	double z = arr[2].getReal();
	return Vec3(x, y, z);
}

Sphere parseSphere(json_spirit::Value &value) {
	json_spirit::Object json = value.getObject();
	double r = json["RADIUS"].getReal();
	Vec3 center = parseVec3(json["CENTER"]);
	return Sphere(center, r);
}

Camera* parseCamera(json_spirit::Value &value) {
	json_spirit::Object json = value.getObject();
	std::string type = json["TYPE"].getString();
	Vec3 h = parseVec3(json["HORIZONTAL"]);
	Vec3 v = parseVec3(json["VERTICAL"]);
	Point3 p = parseVec3(json["POSITION"]);
	if (type == "perspective") {
		Vec3 lens = parseVec3(json["LENS"]);
		return new PerspectiveCamera(h, v, p, lens);
	} else {
		return new OrthogonalCamera(h, v, p);
	}
}

Renderer* parseRenderer(json_spirit::Value &value) {
	std::string type = value.getString();
	if (type == "normal") {
		return new NormalRenderer();
	} else {
		return new MapRenderer();
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
	scene.maxDepth = json["DEPTH"].getReal();

	scene.tl = parseColor(json["UPPER_LEFT"]);
	scene.tr = parseColor(json["UPPER_RIGHT"]);
	scene.bl = parseColor(json["LOWER_LEFT"]);
	scene.br = parseColor(json["LOWER_RIGHT"]);

	json_spirit::Array spheres = json["SPHERES"].getArray();
	for (int i = 0; i < spheres.size(); i++) {
		scene.spheres.push_back(parseSphere(spheres[i]));
	}
	scene.camera = parseCamera(json["CAMERA"]);

	renderer = parseRenderer(json["RENDERER"]);
}