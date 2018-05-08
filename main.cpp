#ifndef __MAIN__
#define __MAIN__

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "src/Parser/InputData.h"
#include "src/Image.h"

using std::string;
using std::cout;
using std::endl;

void printScene(string &fileName) {
	InputData data;
	string inputFile = "meow/" + fileName + ".meow";
	string outputFile = "ppm/" + fileName + ".ppm";
	if (data.load(inputFile)) {
		time_t before = time(NULL);
		Color* colors = data.renderer->render(data.scene, data.colCount, data.rowCount);
		time_t after = time(NULL);
		double seconds = difftime(after, before);
		cout << "Rendering done in " << seconds << " seconds." << endl; 
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
		string fileName = argv[1];
		printScene(fileName);
	} else {
		cout << "File name must be specified." << endl;
	}
	return 0;
}

#endif