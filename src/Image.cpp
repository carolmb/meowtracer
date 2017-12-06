#include "Image.h"
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

int toInt(float a) {
    a = max(min(sqrt(a), 1.0f), 0.0f);
    return rint(a * 255);
}

float toFloat(int a) {
    return a * a / 255;
}

Image::Image(std::string& fileName) {
    std::ifstream file;
    file.open(fileName.c_str());
    std::string cod;
    int m;
    file >> cod >> width >> height >> m;
    size_t len = width * height;
    colors = new Color[len];
    if (cod == "P3") {
        for (int i = 0; i < len; i++) {
            int red, green, blue;
            file >> red >> green >> blue;
            colors[i] = Color(toFloat(red), toFloat(green), toFloat(blue));
        }
    } else {
        char* ccolors = new char[len * 3];
        file.read(ccolors, len * 3);
        for (int i = 0; i < len; i++) {
            int red = ccolors[i*3], green = ccolors[i*3+1], blue = ccolors[i*3+2];
            colors[i] = Color(toFloat(red + 255), toFloat(green + 255), toFloat(blue + 255));
        }
        delete[] ccolors;
    }
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