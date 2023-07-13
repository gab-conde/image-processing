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



/* ========== Mutator Operations ========= */

unsigned char* TGA::OnlyBlue() const {
    unsigned char* blue = new unsigned char[GetSize()];
    for (int i = 0; i < GetSize(); i++) {
        blue[i] = data[i].blue;
    }
    return blue;
}

unsigned char* TGA::OnlyGreen() const {
    unsigned char* green = new unsigned char[GetSize()];
    for (int i = 0; i < GetSize(); i++) {
        green[i] = data[i].green;
    }
    return green;
}

unsigned char* TGA::OnlyRed() const {
    unsigned char* red = new unsigned char[GetSize()];
    for (int i = 0; i < GetSize(); i++) {
        red[i] = data[i].red;
    }
    return red;
}


/* ========== Mutator Operations ========= */

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
        else {
            this->data[i].blue = static_cast<unsigned char>(blue);
        }
        if (green < 0) {
            this->data[i].green = 0;
        }
        else {
            this->data[i].green = static_cast<unsigned char>(green);
        }
        if (red < 0) {
            this->data[i].red = 0;
        }
        else {
            this->data[i].red = static_cast<unsigned char>(red);
        }
    }
}

void TGA::Multiply(TGA& top, TGA& bottom) {
    this->CopyHeader(bottom);
    this->data = new Pixel[this->GetSize()];
    for (int i = 0; i < this->GetSize(); i++) {
        float b1 = top.data[i].blue / 255.0f;
        float b2 = bottom.data[i].blue / 255.0f;
        this->data[i].blue = static_cast<unsigned char>(((b1 * b2) * 255) + 0.5f);

        float g1 = top.data[i].green / 255.0f;
        float g2 = bottom.data[i].green / 255.0f;
        this->data[i].green = static_cast<unsigned char>(((g1 * g2) * 255) + 0.5f);

        float r1 = top.data[i].red / 255.0f;
        float r2 = bottom.data[i].red / 255.0f;
        this->data[i].red = static_cast<unsigned char>(((r1 * r2) * 255) + 0.5f);
    }
}

void TGA::Overlay(TGA& p1, TGA& p2) {
    this->CopyHeader(p1);
    this->data = new Pixel[this->GetSize()];

    float n1, n2, blue, green, red;
    for (int i = 0; i < this->GetSize(); i++) {
        n1 = 0;
        n2 = 0;

        n1 = p1.data[i].blue / 255.0f;
        n2 = p2.data[i].blue / 255.0f;
        if (n2 <= 0.5) {
            blue = 2 * n1 * n2;
            this->data[i].blue = blue * 255 + 0.5;
        }
        else {
            blue = 1 - (2 * (1 - n1) * (1 - n2));
            this->data[i].blue = blue * 255 + 0.5;
        }

        n1 = p1.data[i].green / 255.0f;
        n2 = p2.data[i].green / 255.0f;
        if (n2 <= 0.5) {
            green = 2 * n1 * n2;
            this->data[i].green = green * 255 + 0.5;
        }
        else {
            green = 1 - (2 * (1 - n1) * (1 - n2));
            this->data[i].green = green * 255 + 0.5;
        }

        n1 = p1.data[i].red / 255.0f;
        n2 = p2.data[i].red / 255.0f;
        if (n2 <= 0.5) {
            red = 2 * n1 * n2;
            this->data[i].red = red * 255 + 0.5;
        }
        else {
            red = 1 - (2 * (1 - n1) * (1 - n2));
            this->data[i].red = red * 255 + 0.5;
        }
    }
}

void TGA::Screen(TGA& p1, TGA& p2) {
    this->CopyHeader(p1);
    this->data = new Pixel[this->GetSize()];

    float n1, n2, blue, green, red;
    for (int i = 0; i < this->GetSize(); i++) {
        n1 = 0;
        n2 = 0;

        n1 = p1.data[i].blue / 255.0f;
        n2 = p2.data[i].blue / 255.0f;
        blue = 1 - ((1-n1) * (1-n2));
        this->data[i].blue = blue * 255 + 0.5;

        n1 = p1.data[i].green / 255.0f;
        n2 = p2.data[i].green / 255.0f;
        green = 1 - ((1-n1) * (1-n2));
        this->data[i].green = green * 255 + 0.5;

        n1 = p1.data[i].red / 255.0f;
        n2 = p2.data[i].red / 255.0f;
        red = 1 - ((1-n1) * (1-n2));
        this->data[i].red = red * 255 + 0.5;
    }
}

void TGA::Combine(unsigned char* blue, unsigned char* green, unsigned char* red) {
    data = new Pixel[GetSize()];
    for (int i = 0; i < GetSize(); i++) {
        data[i].blue = blue[i];
        data[i].green = green[i];
        data[i].red = red[i];
    }
}

void TGA::AddBlue(unsigned char amount) {
    int blue;
    for (int i = 0; i < this->GetSize(); i++) {
        blue = data[i].green + amount;
        if (blue > 255) {
            this->data[i].blue = 255;
        }
        else {
            this->data[i].blue = static_cast<unsigned char>(blue);
        }
    }
}

void TGA::AddGreen(unsigned char amount) {
    int green;
    for (int i = 0; i < this->GetSize(); i++) {
        green = data[i].green + amount;
        if (green > 255) {
            this->data[i].green = 255;
        }
        else {
            this->data[i].green = static_cast<unsigned char>(green);
        }
    }
}

void TGA::AddRed(unsigned char amount) {
    int red;
    for (int i = 0; i < this->GetSize(); i++) {
        red = data[i].red + amount;
        if (red > 255) {
            this->data[i].red = 255;
        }
        else {
            this->data[i].red = static_cast<unsigned char>(red);
        }
    }
}

void TGA::ScaleBlue(unsigned char amount) {
    int blue;
    for (int i = 0; i < this->GetSize(); i++) {
        blue = data[i].blue * amount;
        if(blue > 255) {
            data[i].blue = 255;
        }
        else {
            data[i].blue = static_cast<unsigned char>(blue);
        }
    }
}

void TGA::ScaleGreen(unsigned char amount) {
    int green;
    for (int i = 0; i < this->GetSize(); i++) {
        green = data[i].green * amount;
        if(green > 255) {
            data[i].green = 255;
        }
        else {
            data[i].green = static_cast<unsigned char>(green);
        }
    }
}

void TGA::ScaleRed(unsigned char amount) {
    int red;
    for (int i = 0; i < this->GetSize(); i++) {
        red = data[i].red * amount;
        if(red > 255) {
            data[i].red = 255;
        }
        else {
            data[i].red = static_cast<unsigned char>(red);
        }
    }
}