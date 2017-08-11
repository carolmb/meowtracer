#include "../include/MeowImage.h"
#include <sstream>

Color readColor(std::istringstream &file, Color &a, bool &valid) {
	int r, g, b;
	file >> r >> g >> b;
	valid = r >= 0 && r < 256 && g >= 0 && g < 256 && b >= 0 && b < 256;
	a = Color((unsigned char) r, (unsigned char) g, (unsigned char) b);
}

std::string clearComments(std::string &input) {
	int found = input.find_first_of("#");
	if (found != std::string::npos) {
		input = input.substr(0, found);
	}
	return input;
}

bool isEmpty(std::string input) {
	for(int i = 0; i < input.size(); i++) {
		if (input[i] != ' ')
			return false;
	}
	return true;
}

std::string readInput(std::ifstream &file) {
	std::string input;
	std::string cleanInput = "";
	while(!file.eof()) {
		getline(file, input);
		clearComments(input);
		if (!isEmpty(input)) {
			cleanInput += input + "\n";
		}
	}
	std::cout << cleanInput << std::endl;
	return cleanInput;
}

bool parser(std::string content, std::string &outputFile, std::string &outputType, bool &isBin, int &colCount, int &rowCount, 
	Color &tl, Color &tr, Color &bl, Color &br) {
	
	std::istringstream reader(content);

	std::string fieldName;
	reader >> fieldName;
	if (fieldName.compare("NAME") != 0) return false;
	reader >> fieldName;
	if (fieldName.compare("=") != 0) return false;
	reader >> outputFile;
	
	reader >> fieldName;
	if (fieldName.compare("TYPE") != 0) return false;
	reader >> fieldName;
	if (fieldName.compare("=") != 0) return false;
	reader >> outputType;

	reader >> fieldName;
	if (fieldName.compare("CODIFICATION") != 0) return false;
	reader >> fieldName;
	if (fieldName.compare("=") != 0) return false;
	reader >> fieldName;
	isBin = (fieldName.compare("binary") == 0);
	
	reader >> fieldName;
	if (fieldName.compare("WIDTH") != 0) return false;
	reader >> fieldName;
	if (fieldName.compare("=") != 0) return false;
	reader >> colCount;
	if (colCount <= 0) return false;

	reader >> fieldName;
	if (fieldName.compare("HEIGHT") != 0) return false;
	reader >> fieldName;
	if (fieldName.compare("=") != 0) return false;
	reader >> rowCount;
	if (rowCount <= 0) return false;
	
	Color c[4];
	std::string v[4] = {"UPPER_LEFT", "LOWER_LEFT", "UPPER_RIGHT", "LOWER_RIGHT"};
	bool valid;
	for (int i = 0; i < 4; i++) {
		reader >> fieldName;
		if (fieldName.compare(v[i]) != 0) return false;
		reader >> fieldName;
		if (fieldName.compare("=") != 0) return false;
		readColor(reader, c[i], valid);
		if (!valid) return false;
	}
	tl = c[0]; bl = c[1]; tr = c[2]; br = c[3];
	return true;
}

MeowImage MeowImage::gradient(std::string inputFile) {
	std::ifstream file(inputFile.c_str(), std::ifstream::in);
	std::string outputFile, outputType;
	bool isBin;
	int colCount, rowCount;
	if (file.is_open()) {
		Color tl, tr, bl, br;
		std::string content = readInput(file);
		if (parser(content, outputFile, outputType, isBin, colCount, rowCount, tl, tr, bl, br)) {
			return MeowImage::gradient(isBin, colCount, rowCount, outputFile, tl, tr, bl, br);
		} else {
			std::cout << "File not valid." << std::endl;
			return MeowImage();
		}
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
    size_t len = colCount * rowCount;
    for (int i = 0; i < len; i ++) {
    	file << colors[i].r;
    	file << colors[i].g;
    	file << colors[i].b;
    }
	file.close();
}

void MeowImage::ppm() {
	if (isBin) {
		saveBin();
	} else {
		save();
	}
}