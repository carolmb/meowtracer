#include "../include/MeowImage.h"

Color readColor(std::ifstream &file) {
	int r, g, b;
	file >> r >> g >> b;
	return Color((unsigned char) r, (unsigned char) g, (unsigned char) b);
}

MeowImage MeowImage::gradient(std::string inputFile) {
	std::ifstream file(inputFile.c_str(), std::ifstream::in);
	std::string outputFile;
	bool isBin;
	int colCount, rowCount;
	if (file.is_open()) {
		file >> outputFile >> isBin >> colCount >> rowCount;
		Color tl = readColor(file);
		Color tr = readColor(file);
		Color bl = readColor(file);
		Color br = readColor(file);
		return MeowImage::gradient(isBin, colCount, rowCount, outputFile, tl, tr, bl, br);
	} else {
		std::cout << "File does not exist." << std::endl;
	}
}

MeowImage MeowImage::gradient(bool bin, int colCount, int rowCount, std::string file, Color tl, Color tr, Color bl, Color br) {
	Color* colors = new Color[rowCount * colCount];
	for (int col = 0; col < colCount; col ++) {
		for (int row = 0; row < rowCount; row ++) {
			double tCol = 1.0 * col / (colCount - 1);
			double tRow = 1.0 * row / (rowCount - 1);
			Color top = tl.lerp(tr, tCol);
			Color bottom = bl.lerp(br, tCol);
			colors[row * colCount + col] = top.lerp(bottom, tRow);
		}
	}
	return MeowImage(bin, colCount, rowCount, file, colors);
}

void MeowImage::save() {
    std::ofstream file;
    file.open (outputFile.c_str());
    file << "P3" << std::endl;
    file << colCount << " " << rowCount << std::endl;
    file << "255" << std::endl;
    size_t len = colCount * rowCount;
    for (int i = 0; i < len; i ++) {
        int red = (unsigned char) colors[i].r;
        int green = (unsigned char) colors[i].g;
        int blue = (unsigned char) colors[i].b;
        file << red << " " << green << " " << blue << std::endl;
    }
    file.close();
}

void MeowImage::saveBin() {
    std::ofstream file;
    file.open (outputFile.c_str(), std::ofstream::binary);
    file << "P6" << std::endl;
    file << colCount << " " << rowCount << std::endl;
    file << "255" << std::endl;
    size_t len = colCount * rowCount * 3;
    for (int i = 0; i < len; i ++) {
    	file << colors[i].r;
    	file << colors[i].g;
    	file << colors[i].b;
    }
    std::cout << colors[0].r << " " << colors[0].g << " " << colors[0].b << " " << std::endl;
    file.close();
}

void MeowImage::ppm() {
	if (isBin) {
		saveBin();
	} else {
		save();
	}
}