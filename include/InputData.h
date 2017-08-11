#ifndef __INPUTDATA__
#define __INPUTDATA__

#include "Scene.h"
#include <string>

class InputData {
private:
	bool parse(std::string &content);
public:
	Scene scene;
	bool isBin;
	int colCount;
	int rowCount;
	std::string outputFile;
	std::string outputType;
	bool load(std::string &fileName);
};

#endif