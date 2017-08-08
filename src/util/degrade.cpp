#include <iostream>
#include <fstream>
#include <string>

int save(std::string fileName, char* pixels, int n_col, int n_row) {
    std::ofstream file;
    file.open (fileName + ".ppm");
    file << "P3" << std::endl;
    file << n_col << " " << n_row << std::endl;
    file << "255" << std::endl;
    size_t len = n_col * n_row * 3;
    for (int i = 0; i < len; i += 3) {
        int red = (unsigned char) pixels[i];
        int green = (unsigned char) pixels[i + 1];
        int blue = (unsigned char) pixels[i + 2];
        file << red << " " << green << " " << blue << std::endl;
    }
    file.close();
}

int save_bin(std::string fileName, char* pixels, int n_col, int n_row) {
    std::ofstream file;
    file.open (fileName + ".ppm", std::ios::binary);
    file << "P6" << std::endl;
    file << n_col << " " << n_row << std::endl;
    file << "255" << std::endl;
    size_t len = n_col * n_row * 3;
    file.write(pixels, len);
    file.close();
}

char* degrade(int n_col, int n_row) {
    size_t len = n_col * n_row * 3;
    char* pixels = new char[len];
    int p = 0;
    for (int i = 0; i < n_row; i++) {
        for (int j = 0; j < n_col; j++) {
            char red = 255 - (255 * i) / (n_row - 1);
            char green = (255 * j) / (n_col - 1);
            char blue = 0;
            pixels[p] = red;
            pixels[p + 1] = green;
            pixels[p + 2] = blue;
            p += 3;
        }
    }
    return pixels;
}

int main() {
    int n_col(200);
    int n_row(150);
    char* pixels = degrade(n_col, n_row);
    save("ibagem", pixels, n_col, n_row);
    save_bin("ibagem_bin", pixels, n_col, n_row);
    return 0;
}
