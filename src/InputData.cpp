#include "../include/InputData.h"
#include "../include/OrthogonalCamera.h"
#include "../include/PerspectiveCamera.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>

bool readColor(std::istringstream &file, Color &a) {
	int r, g, b;
	file >> r >> g >> b;
	bool valid = r >= 0 && r < 256 && g >= 0 && g < 256 && b >= 0 && b < 256;
	a = Color((unsigned char) r, (unsigned char) g, (unsigned char) b);
	return valid;
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
	//std::cout << cleanInput << std::endl;
	return cleanInput;
}

bool readField(std::istringstream &reader, std::string fieldName) {
	std::string f;
	reader >> f;
	if (f.compare(fieldName) != 0) return false;
	reader >> f;
	if (f.compare("=") != 0) return false;
	return true;
}

bool InputData::parse(std::string &content) {
	std::istringstream reader(content);

	if (!readField(reader, "NAME")) return false;
	reader >> outputFile;

	if (!readField(reader, "TYPE")) return false;
	reader >> outputType;

	std::string cod;
	if (!readField(reader, "CODIFICATION")) return false;
	reader >> cod;
	isBin = (cod.compare("binary") == 0);
	
	if (!readField(reader, "WIDTH")) return false;
	reader >> colCount;
	if (colCount <= 0) return false;

	if (!readField(reader, "HEIGHT")) return false;
	reader >> rowCount;
	if (rowCount <= 0) return false;
	
	Color c[4];
	std::string v[4] = {"UPPER_LEFT", "LOWER_LEFT", "UPPER_RIGHT", "LOWER_RIGHT"};
	bool valid;
	for (int i = 0; i < 4; i++) {
		if (!readField(reader, v[i])) return false; 
		if (!readColor(reader, c[i])) return false;
	}
	scene.tl = c[0]; scene.bl = c[1]; scene.tr = c[2]; scene.br = c[3];

	// TODO: specify camera and objects
	//scene.camera = new OrthogonalCamera();
	scene.camera = new PerspectiveCamera();
	scene.sphere = Sphere(Point3(0.5, 0.5, 0), 0.25);

	return true;
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