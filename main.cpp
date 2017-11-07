#ifndef __MAIN__
#define __MAIN__

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "src/InputData.h"
#include "src/Image.h"

void printScene(std::string &fileName) {
	InputData data;
	std::string inputFile = "meow/" + fileName + ".meow";
	std::string outputFile = "ppm/" + fileName + ".ppm";
	if (data.load(inputFile)) {
		time_t before = time(NULL);
		Color* colors = data.renderer->render(data.scene, data.colCount, data.rowCount);
		time_t after = time(NULL);
		double seconds = difftime(after, before);
		std::cout << "Rendering done in " << seconds << " seconds." << std::endl; 
		Image img(data.colCount, data.rowCount, colors);
		if (data.isBin) {
			img.saveBin(outputFile);
		} else {
			img.save(outputFile);
		}
	}
}

int main(int argc, char* argv[]) {
	srand (time(NULL));
	if (argc > 1) {
		std::string fileName = argv[1];
		printScene(fileName);
	} else {
		std::cout << "File name must be specified." << std::endl;
	}
	return 0;
}

#endif