#ifndef __IMAGE__
#define __IMAGE__

#include "Color.h"
#include <string>

class MeowImage {
	int width;
	int height;
	Color *colors;
public:
	MeowImage (int w, int h) : width(w), height(h) {}
	MeowImage (int w, int h, Color* crls) : width(w), height(h), colors(crls) {}

	void save(std::string &fileName);
	void saveBin(std::string &fileName);
	void ppm(std::string &fileName, bool binary);
};

#endif