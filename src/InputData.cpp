#include "InputData.h"
#include "Parser/NormalParser.h"
#include "Parser/MapParser.h"
#include "Parser/DiffuseParser.h"
#include "Parser/BlinnPhongParser.h"
#include "Parser/CelParser.h"
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

void InputData::parse(std::string &content) {
	json_spirit::Value value;
	json_spirit::read(content, value);
	json_spirit::Object json = value.getObject();
	isBin = json["CODIFICATION"].getString() == "binary";
	colCount = json["WIDTH"].getInt();
	rowCount = json["HEIGHT"].getInt();
	std::string type = json["RENDERER"].getString();
	RendererParser* rendererParser;
	if (type == "normal") {
		rendererParser = NormalParser();
	} else if (type == "map") {
		rendererParser = MapParser();
	} else if (type == "diffuse") {
		rendererParser = DiffuseParser();
	} else if (type == "blinnphong") {
		rendererParser = BlinnPhongParser();
	} else if (type == "cel") {
		rendererParser = CelParser();
	} else {
		std::cout << "Renderer type not recognized." << std::endl;
		return NULL;
	}
	renderer = rendererParser->parse(json);
}