#ifndef __IMAGE__
#define __IMAGE__

#include "Math/Vec3.h"
#include <string>

class Image {
	Color *colors;
public:
	int width;
	int height;

  Image (std::string &fileName);
	Image (int w, int h);
	Image (int w, int h, Color* crls) : width(w), height(h), colors(crls) {}

  Color& at(int i, int j);

	void save(std::string &fileName);
	void saveBin(std::string &fileName);
	void ppm(std::string &fileName, bool binary);
};

#endif