#ifndef __IMAGE__
#define __IMAGE__

#include "Math/Vec3.h"
#include <string>

class Image {
	int width;
	int height;
	Color *colors;
public:
  Image (std::string &fileName);
	Image (int w, int h) : width(w), height(h) {}
	Image (int w, int h, Color* crls) : width(w), height(h), colors(crls) {}

	void save(std::string &fileName);
	void saveBin(std::string &fileName);
	void ppm(std::string &fileName, bool binary);
};

#endif