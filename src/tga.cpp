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

void TGA::CopyHeader(TGA& other) {
    idLength = other.idLength;
    colorMapType = other.colorMapType;
    imageType = other.imageType;
    colorMapOrigin = other.colorMapOrigin;
    colorMapLength = other.colorMapLength;
    xOrigin = other.xOrigin;
    yOrigin = other.yOrigin;
    imageWidth = other.imageWidth;
    imageHeight = other.imageHeight;
    pixelDepth = other.pixelDepth;
    imageDescriptor = other.imageDescriptor;
}


/* ========== Operations ========= */

void TGA::Subtract(TGA& p1, TGA& p2) {
    int blue, green, red;
    this->CopyHeader(p1);
    this->data = new Pixel[this->GetSize()];
    // subtract color channels for each pixel
    for (int i = 0; i < this->GetSize(); i++) {
        blue = p1.data[i].blue - p2.data[i].blue;
        green = p1.data[i].green - p2.data[i].green;
        red = p1.data[i].red - p2.data[i].red;
        if (blue < 0) {
            this->data[i].blue = 0;
        }
        else if (blue >= 0) {
            this->data[i].blue = static_cast<unsigned char>(blue);
        }
        if (green < 0) {
            this->data[i].green = 0;
        }
        else if (green >= 0) {
            this->data[i].green = static_cast<unsigned char>(green);
        }
        if (red < 0) {
            this->data[i].red = 0;
        }
        else if (red >= 0) {
            this->data[i].red = static_cast<unsigned char>(red);
        }
    }
}