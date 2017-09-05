#include "../include/Image.h"
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

int toInt(double a) {
    a = max(min(sqrt(a), 1.0), 0.0);
    return rint(a * 255);
}

void Image::save(std::string &fileName) {
    std::ofstream file;
    file.open (fileName.c_str());
    file << "P3" << std::endl;
    file << width << " " << height << std::endl;
    file << "255" << std::endl;
    size_t len = width * height;
    for (int i = 0; i < len; i ++) {
        int red = toInt(colors[i].x);
        int green = toInt(colors[i].y);
        int blue = toInt(colors[i].z);
        file << red << " " << green << " " << blue << std::endl;
    }
    file.close();
}

void Image::saveBin(std::string &fileName) {
    std::ofstream file;
    file.open (fileName.c_str(), std::ofstream::binary);
    file << "P6" << std::endl;
    file << width << " " << height << std::endl;
    file << "255" << std::endl;
    size_t len = width * height;
    for (int i = 0; i < len; i ++) {
        unsigned char r = toInt(colors[i].x);
        unsigned char g = toInt(colors[i].y);
        unsigned char b = toInt(colors[i].z);
    	file << r << g << b;
    }
	file.close();
}