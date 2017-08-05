#include <iostream>
#include "include/util/Color.h"
#include "include/util/Vec3.h"

void testColor() {
	Color c1;
	Color c2(255, 255, 255, 255);
	Color c3 = c1.lerp(c2, 0.5);
	std::cout << (int) c3.r << " " << (int) c3.g << " " << (int) c3.b << " " << (int) c3.a << std::endl;
}

void testVec3() {
	Vec3 v1(1, 1, 1);
	Vec3 v2(2, 2, 2);
	Vec3 v3 = v1 + v2;
	std::cout << (int) v3.x << " " << (int) v3.y << " " << (int) v3.z << std::endl;
}

int main(int argc, char* argv[]) {
	if (argc > 1) {
		char* fileName = argv[1];
		// TODO: load file and stuff
	} else {
		std::cout << "File name must be specified." << std::endl;
	}

	testColor();
	testVec3();
	return 0;
}