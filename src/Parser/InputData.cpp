#include "InputData.h"
#include "SceneParser.h"
#include "ObjectParser.h"
#include "ModelParser.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>

using std::string;
using std::cout;
using std::endl;
using std::ifstream;

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
      parseLight(scene, lights[i]);
    }
  }
  json_spirit::Array objects = json["OBJECTS"].getArray();
  for (int i = 0; i < objects.size(); i++) {
    json_spirit::Object json = objects[i].getObject();
    Matrix4 xform = json.count("TRANSFORM") ? parseTransform(json["TRANSFORM"]) : Matrix4::Identity();
    std::string type = json["TYPE"].getString();
    if (type == "obj") {
      parseModel(json, xform, scene);
    } else {
      Object* obj = parseObject(json, xform, type, scene);
      if (obj->bounds[0].Valid() && obj->bounds[1].Valid())
        scene.objects.push_back(obj);
    }
  }
  scene.camera = parseCamera(json["CAMERA"]);
  renderer = parseRenderer(json["RENDERER"]);
  return true;
}

bool isEmpty(std::string input) {
	for(int i = 0; i < input.size(); i++) {
		if (input[i] != ' ')
			return false;
	}
	return true;
}

std::string readInput(std::ifstream &file) {
	string input;
	string cleanInput = "";
	while(!file.eof()) {
		getline(file, input);
		if (!isEmpty(input)) {
			cleanInput += input + "\n";
		}
	}
	return cleanInput;
}

bool InputData::load(std::string &fileName) {
	ifstream file(fileName.c_str(), std::ifstream::in);
	if (file.is_open()) {
		string content = readInput(file);
		if (parse(content)) {
			return true;
		} else {
			cout << "File not valid." << endl;
			return false;
		}
	} else {
		cout << "File does not exist." << endl;
	}
}