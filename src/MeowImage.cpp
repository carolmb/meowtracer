#include "../include/MeowImage.h"
#include <iostream>
#include <fstream>

void MeowImage::save(std::string &fileName) {
    std::ofstream file;
    file.open (fileName.c_str());
    file << "P3" << std::endl;
    file << width << " " << height << std::endl;
    file << "255" << std::endl;
    size_t len = width * height;
    for (int i = 0; i < len; i ++) {
        int red = (unsigned char) colors[i].r;
        int green = (unsigned char) colors[i].g;
        int blue = (unsigned char) colors[i].b;
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
    	file << colors[i].r;
    	file << colors[i].g;
    	file << colors[i].b;
    }
	file.close();
}