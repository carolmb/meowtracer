#ifndef __INPUTDATA__
#define __INPUTDATA__

#include "Renderer/Renderer.h"
#include <string>

class InputData {
private:
	bool parse(std::string &content);
public:
	bool isBin;
	int colCount;
	int rowCount;
	Renderer* renderer;
	bool load(std::string &fileName);
};

#endif