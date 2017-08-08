#include "../include/MeowImage.h"

MeowImage::MeowImage (std::string inputFile) {
	std::ifstream file(inputFile.c_str(), std::ifstream::in);
	int r, g, b;
	int count = 0;
	int max;
	if (file.is_open()) {
		file >> outputFile >> isBin >> col >> row >> max;
		std::cout << max << std::endl;
		colors = new Color[max];
		while (count < max) {
			file >> r >> g >> b;
			colors[count].r = r; 
			colors[count].g = g; 
			colors[count].b = b; 
			colors[count].a = 255;
			count++;
		}
	} else {
		std::cout << "File does not exist." << std::endl;
	}
}

void MeowImage::ppm() {
	
	std::ofstream out (outputFile.c_str(), ((isBin > 0) ? std::ofstream::binary : std::ofstream::out)); // TODO: error when not bin
	
	out << ((isBin > 0) ? "P6\n" : "P3\n");
	out << col << " " << row << '\n';
	out << 255 << '\n';

	Color currentColor;
	int count = 0;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			currentColor = colors[0].lerp(colors[1], (float)j/(float)col);
			out << currentColor.r;
			out << currentColor.g;
			out << currentColor.b;
		}
	}

	out.close();
}