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