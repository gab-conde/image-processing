#include <iostream>
#include <fstream>
#include "tga.hpp"
using namespace std;


/* ========== Accessors ========== */

int TGA::GetSize() const {
    return imageWidth * imageHeight;
}

TGA::Pixel* TGA::GetImgData() const {
    return data;
}


/* ========== Mutators ========== */

void TGA::ReadFile(ifstream& input) {
    // read header
    input.read(&idLength, 1);
    input.read(&colorMapType, 1);
    input.read(&imageType, 1);
    input.read(reinterpret_cast<char*>(&colorMapOrigin), 2);
    input.read(reinterpret_cast<char*>(&colorMapLength), 2);
    input.read(&colorMapDepth, 1);
    input.read(reinterpret_cast<char*>(&xOrigin), 2);
    input.read(reinterpret_cast<char*>(&yOrigin), 2);
    input.read(reinterpret_cast<char*>(&imageWidth), 2);
    input.read(reinterpret_cast<char*>(&imageHeight), 2);
    input.read(&pixelDepth, 1);
    input.read(&imageDescriptor, 1);
    // read image data
    data = new Pixel[imageWidth * imageHeight];
    for (int i = 0; i < imageWidth * imageHeight; i++) {
        input.read(reinterpret_cast<char*>(&data[i].blue), 1);
        input.read(reinterpret_cast<char*>(&data[i].green), 1);
        input.read(reinterpret_cast<char*>(&data[i].red), 1);
    }
}

void TGA::WriteFile(ofstream& output) {
    // write header
    output.write(&idLength, 1);
    output.write(&colorMapType, 1);
    output.write(&imageType, 1);
    output.write(reinterpret_cast<char*>(&colorMapOrigin), 2);
    output.write(reinterpret_cast<char*>(&colorMapLength), 2);
    output.write(&colorMapDepth, 1);
    output.write(reinterpret_cast<char*>(&xOrigin), 2);
    output.write(reinterpret_cast<char*>(&yOrigin), 2);
    output.write(reinterpret_cast<char*>(&imageWidth), 2);
    output.write(reinterpret_cast<char*>(&imageHeight), 2);
    output.write(&pixelDepth, 1);
    output.write(&imageDescriptor, 1);
    // write image data
    for (int i = 0; i < imageWidth * imageHeight; i++) {
        output.write(reinterpret_cast<char*>(&data[i].blue), 1);
        output.write(reinterpret_cast<char*>(&data[i].green), 1);
        output.write(reinterpret_cast<char*>(&data[i].red), 1);
    }
}