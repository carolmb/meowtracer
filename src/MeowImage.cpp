#include "../include/MeowImage.h"
#include <iostream>
#include <fstream>
#include <cmath>

void MeowImage::save(std::string &fileName) {
    std::ofstream file;
    file.open (fileName.c_str());
    file << "P3" << std::endl;
    file << width << " " << height << std::endl;
    file << "255" << std::endl;
    size_t len = width * height;
    for (int i = 0; i < len; i ++) {
        int red = rint(colors[i].x * 255);
        int green = rint(colors[i].y * 255);
        int blue = rint(colors[i].z * 255);
        file << red << " " << green << " " << blue << std::endl;
    }
    file.close();
}

void MeowImage::saveBin(std::string &fileName) {
    std::ofstream file;
    file.open (fileName.c_str(), std::ofstream::binary);
    file << "P6" << std::endl;
    file << width << " " << height << std::endl;
    file << "255" << std::endl;
    size_t len = width * height;
    for (int i = 0; i < len; i ++) {
        unsigned char r = rint(colors[i].x * 255);
        unsigned char g = rint(colors[i].y * 255);
        unsigned char b = rint(colors[i].z * 255);
    	file << r << g << b;
    }
	file.close();
}