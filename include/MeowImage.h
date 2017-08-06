#include <fstream>
#include <iostream>

class MeowImage {
	int isBin;
	int col;
	int row;
	char *output; //ppm file
	// list of objects

public:
	MeowImage () : isBin(0), col(100), row(100), output("image.ppm") {}
	MeowImage (int b, int r, int c, char* o) : isBin(b), col(c), row(r), output(o) {}
	MeowImage (char* fileName) {
		std::ifstream file(fileName, std::ifstream::in);
		if (file.is_open()) {
			file >> isBin >> col >> row >> output;
		} else {
			std::cout << "File does not exist." << std::endl;
		}
		std::cout << "Bla" << std::endl;
	}

	void ppm();
};
