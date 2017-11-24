#include "InputData.h"
#include "SceneParser.h"
#include "ObjectParser.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>

bool InputData::parse(std::string &content) {
  json_spirit::Value value;
  json_spirit::read(content, value);
  json_spirit::Object json = value.getObject();

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
    json_spirit::Object json = objects[i].getObject();
    Matrix4 xform = json.count("TRANSFORM") ? parseTransform(json["TRANSFORM"]) : Matrix4::Identity();
    std::string type = json["TYPE"].getString();
    if (type == "obj") {
      parseObjFile(json, xform, scene);
    } else {
      scene.objects.push_back(parseObject(json, xform, type, scene));
    }
  }
  scene.camera = parseCamera(json["CAMERA"]);
  renderer = parseRenderer(json["RENDERER"]);
}

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