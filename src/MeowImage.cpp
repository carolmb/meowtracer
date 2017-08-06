#include "../include/MeowImage.h"

void MeowImage::ppm() {
	std::ofstream out (output); // TODO: bin
	char buffer[col*row*3];
	
	out << "P3\n";
	out << col << " " << row << '\n';
	out << 255 << '\n';
	for(int i = 0; i < row; i++) {
		for(int j = 0; j < col; j++) {
			buffer[i * 3 * col + 3 * j] = 0;
			buffer[i * 3 * col + 3 * j + 1] = 0;
			buffer[i * 3 * col + 3 * j + 2] = 0;	
		}
	}
	out.write(buffer, col*row*3);
	out.close();
}