#include <fstream>
#include <iostream>
#include <string>
#include "util/Color.h"

class MeowImage {
	int isBin;
	int col;
	int row;
	std::string outputFile; //ppm file name
	Color *colors;
	// list of objects

public:
	MeowImage () : isBin(0), col(100), row(100), outputFile("image.ppm") {}
	MeowImage (int b, int r, int c, std::string o) : isBin(b), col(c), row(r), outputFile(o) {}
	MeowImage (std::string);

	void ppm();
};
