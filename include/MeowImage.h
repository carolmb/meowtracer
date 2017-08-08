#include <fstream>
#include <iostream>
#include <string>
#include "util/Color.h"

#ifndef __IMAGE__
#define __IMAGE__

class MeowImage {
	bool isBin;
	int colCount;
	int rowCount;
	std::string outputFile; //ppm file name
	Color *colors;
	// list of objects

public:
	MeowImage () : isBin(false), colCount(100), rowCount(100), outputFile("image.ppm") {}
	MeowImage (bool b, int r, int c, std::string o) : isBin(b), colCount(c), rowCount(r), outputFile(o) {}
	MeowImage (bool b, int c, int r, std::string o, Color* crls) : isBin(b), colCount(c), rowCount(r), outputFile(o), colors(crls) {}

	void save();
	void saveBin();
	void ppm();

	static MeowImage gradient(bool bin, int colCount, int rowCount, std::string file, Color tl, Color tr, Color bl, Color br);
	static MeowImage gradient(std::string fileName);
};

#endif