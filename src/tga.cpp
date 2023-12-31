#include <iostream>
#include <fstream>
#include "tga.hpp"
using namespace std;

/* ========== Construction / Destruction ========== */

// Copy Constructor
TGA::TGA(const TGA& other) {
    idLength = other.idLength;
    colorMapType = other.colorMapType;
    imageType = other.imageType;
    colorMapOrigin = other.colorMapOrigin;
    colorMapLength = other.colorMapLength;
    colorMapDepth = other.colorMapDepth;
    xOrigin = other.xOrigin;
    yOrigin = other.yOrigin;
    imageWidth = other.imageWidth;
    imageHeight = other.imageHeight;
    pixelDepth = other.pixelDepth;
    imageDescriptor = other.imageDescriptor;
    data = new Pixel[GetSize()];
    for (int i = 0; i < GetSize(); i++) {
        data[i] = other.data[i];
    }
}

// Copy Assignment Operator
TGA& TGA::operator=(const TGA& other) {
    idLength = other.idLength;
    colorMapType = other.colorMapType;
    imageType = other.imageType;
    colorMapOrigin = other.colorMapOrigin;
    colorMapLength = other.colorMapLength;
    colorMapDepth = other.colorMapDepth;
    xOrigin = other.xOrigin;
    yOrigin = other.yOrigin;
    imageWidth = other.imageWidth;
    imageHeight = other.imageHeight;
    pixelDepth = other.pixelDepth;
    imageDescriptor = other.imageDescriptor;
    for (int i = 0; i < GetSize(); i++) {
        data[i] = other.data[i];
    }
    return *this;
}

// Destructor
TGA::~TGA() {
    delete[] data;
}


/* ========== Accessors ========== */

// Return the total number of Pixels in the TGA
int TGA::GetSize() const {
    return imageWidth * imageHeight;
}

// Provide access to the TGA's image data
TGA::Pixel* TGA::GetImgData() const {
    return data;
}


/* ========== Mutators ========== */

// Store a .tga file in a TGA object
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
    for (int i = 0; i < GetSize(); i++) {
        input.read(reinterpret_cast<char*>(&data[i].blue), 1);
        input.read(reinterpret_cast<char*>(&data[i].green), 1);
        input.read(reinterpret_cast<char*>(&data[i].red), 1);
    }
}

// Write the data stored in a TGA object to a .tga file
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
    for (int i = 0; i < GetSize(); i++) {
        output.write(reinterpret_cast<char*>(&data[i].blue), 1);
        output.write(reinterpret_cast<char*>(&data[i].green), 1);
        output.write(reinterpret_cast<char*>(&data[i].red), 1);
    }
}

// Copy the header of one TGA object to another
void TGA::CopyHeader(const TGA& other) {
    idLength = other.idLength;
    colorMapType = other.colorMapType;
    imageType = other.imageType;
    colorMapOrigin = other.colorMapOrigin;
    colorMapLength = other.colorMapLength;
    colorMapDepth = other.colorMapDepth;
    xOrigin = other.xOrigin;
    yOrigin = other.yOrigin;
    imageWidth = other.imageWidth;
    imageHeight = other.imageHeight;
    pixelDepth = other.pixelDepth;
    imageDescriptor = other.imageDescriptor;
}


/* ========== Accessor Operations ========= */

// Return the blue channel of the invoking object
unsigned char* TGA::OnlyBlue() const {
    unsigned char* blue = new unsigned char[GetSize()];
    for (int i = 0; i < GetSize(); i++) {
        blue[i] = data[i].blue;
    }
    return blue;
}

// Return the green channel of the invoking object
unsigned char* TGA::OnlyGreen() const {
    unsigned char* green = new unsigned char[GetSize()];
    for (int i = 0; i < GetSize(); i++) {
        green[i] = data[i].green;
    }
    return green;
}

// Return the red channel of the invoking object
unsigned char* TGA::OnlyRed() const {
    unsigned char* red = new unsigned char[GetSize()];
    for (int i = 0; i < GetSize(); i++) {
        red[i] = data[i].red;
    }
    return red;
}


/* ========== Mutator Operations ========= */

// Perform the subtraction algorithm on two TGA objects.
// Store the result in a third TGA object
void TGA::Subtract(const TGA& p1, const TGA& p2) {
    int blue, green, red;
    CopyHeader(p1);
    data = new Pixel[GetSize()];
    // subtract color channels for each pixel
    for (int i = 0; i < GetSize(); i++) {
        blue = p1.data[i].blue - p2.data[i].blue;
        green = p1.data[i].green - p2.data[i].green;
        red = p1.data[i].red - p2.data[i].red;
        if (blue < 0) {
            data[i].blue = 0;
        }
        else {
            data[i].blue = static_cast<unsigned char>(blue);
        }
        if (green < 0) {
            data[i].green = 0;
        }
        else {
            data[i].green = static_cast<unsigned char>(green);
        }
        if (red < 0) {
            data[i].red = 0;
        }
        else {
            data[i].red = static_cast<unsigned char>(red);
        }
    }
}

// Perform the multiplication algorithm on two TGA objects.
// Store the result in a third TGA object
void TGA::Multiply(const TGA& p1, const TGA& p2) {
    CopyHeader(p2);
    data = new Pixel[GetSize()];

    float n1 = 0, n2 = 0;
    for (int i = 0; i < GetSize(); i++) {
        // blue channel
        n1 = p1.data[i].blue / 255.0f;
        n2 = p2.data[i].blue / 255.0f;
        data[i].blue = static_cast<unsigned char>(((n1 * n2) * 255) + 0.5f);

        // green channel
        n1 = p1.data[i].green / 255.0f;
        n2 = p2.data[i].green / 255.0f;
        data[i].green = static_cast<unsigned char>(((n1 * n2) * 255) + 0.5f);

        // red channel
        n1 = p1.data[i].red / 255.0f;
        n2 = p2.data[i].red / 255.0f;
        data[i].red = static_cast<unsigned char>(((n1 * n2) * 255) + 0.5f);
    }
}

// Perform the overlay algorithm on two TGA objects.
// Store the result in a third TGA object
void TGA::Overlay(const TGA& p1, const TGA& p2) {
    CopyHeader(p1);
    data = new Pixel[GetSize()];

    float n1, n2, blue, green, red;
    for (int i = 0; i < GetSize(); i++) {
        n1 = 0;
        n2 = 0;

        n1 = p1.data[i].blue / 255.0f;
        n2 = p2.data[i].blue / 255.0f;

        // blue channel
        if (n2 <= 0.5f) {
            blue = 2 * n1 * n2;
            data[i].blue = (blue * 255) + 0.5f;
        }
        else {
            blue = 1 - (2 * (1 - n1) * (1 - n2));
            data[i].blue = (blue * 255) + 0.5f;
        }
        
        // green channel
        n1 = p1.data[i].green / 255.0f;
        n2 = p2.data[i].green / 255.0f;
        if (n2 <= 0.5f) {
            green = 2 * n1 * n2;
            data[i].green = (green * 255) + 0.5f;
        }
        else {
            green = 1 - (2 * (1 - n1) * (1 - n2));
            data[i].green = (green * 255) + 0.5f;
        }

        // red channel
        n1 = p1.data[i].red / 255.0f;
        n2 = p2.data[i].red / 255.0f;
        if (n2 <= 0.5f) {
            red = 2 * n1 * n2;
            data[i].red = (red * 255) + 0.5f;
        }
        else {
            red = 1 - (2 * (1 - n1) * (1 - n2));
            data[i].red = (red * 255) + 0.5f;
        }
    }
}

// Perform the screen algorithm on two TGA objects.
// Store the result in a third TGA object
void TGA::Screen(const TGA& p1, const TGA& p2) {
    CopyHeader(p1);
    data = new Pixel[GetSize()];

    float n1, n2, blue, green, red;
    for (int i = 0; i < GetSize(); i++) {
        n1 = 0;
        n2 = 0;

        // blue channel
        n1 = p1.data[i].blue / 255.0f;
        n2 = p2.data[i].blue / 255.0f;
        blue = 1 - ((1-n1) * (1-n2));
        data[i].blue = blue * 255 + 0.5;

        // green channel
        n1 = p1.data[i].green / 255.0f;
        n2 = p2.data[i].green / 255.0f;
        green = 1 - ((1-n1) * (1-n2));
        data[i].green = green * 255 + 0.5;

        // red channel
        n1 = p1.data[i].red / 255.0f;
        n2 = p2.data[i].red / 255.0f;
        red = 1 - ((1-n1) * (1-n2));
        data[i].red = red * 255 + 0.5;
    }
}

// Combine three color channels (B, G, R) into the image data of a TGA object
void TGA::Combine(unsigned char* blue, unsigned char* green, unsigned char* red) {
    data = new Pixel[GetSize()];
    for (int i = 0; i < GetSize(); i++) {
        data[i].blue = blue[i];
        data[i].green = green[i];
        data[i].red = red[i];
    }
}

// Rotate the invoking object by 180 degrees
void TGA::Flip() {
    Pixel temp;
    for (int i = 0; i < GetSize() / 2; i++) {
        temp = data[i];
        data[i] = data[(GetSize() - 1) - i];
        data[(GetSize() - 1) - i] = temp;
    }
}

// Add a specified amount to the TGA's blue channel of the invoking object
void TGA::AddBlue(int amount) {
    for (int i = 0; i < GetSize(); i++) {
        if (data[i].blue + amount > 255) {
            data[i].blue = 255;
        }
        else if (data[i].blue + amount < 0) {
            data[i].blue = 0;
        }
        else {
            data[i].blue += amount;
        }
    }
}

// Add a specified amount to the TGA's green channel of the invoking object
void TGA::AddGreen(int amount) {
    for (int i = 0; i < GetSize(); i++) {
        if (data[i].green + amount > 255) {
            data[i].green = 255;
        }
        else if (data[i].green + amount < 0) {
            data[i].green = 0;
        }
        else {
            data[i].green += amount;
        }
    }
}

// Add a specified amount to the TGA's red channel of the invoking object
void TGA::AddRed(int amount) {
    for (int i = 0; i < GetSize(); i++) {
        if (data[i].red + amount > 255) {
            data[i].red = 255;
        }
        else if (data[i].red + amount < 0) {
            data[i].red = 0;
        }
        else {
            data[i].red += amount;
        }
    }
}

// Increase the intensity of the TGA's blue channel by a specified factor
void TGA::ScaleBlue(unsigned short amount) {
    int blue = 0;
    for (int i = 0; i < GetSize(); i++) {
        blue = data[i].blue * amount;
        if(blue > 255) {
            data[i].blue = 255;
        }
        else {
            data[i].blue = static_cast<unsigned char>(blue);
        }
    }
}

// Increase the intensity of the TGA's green channel by a specified factor
void TGA::ScaleGreen(unsigned short amount) {
    int green = 0;
    for (int i = 0; i < GetSize(); i++) {
        green = data[i].green * amount;
        if(green > 255) {
            data[i].green = 255;
        }
        else {
            data[i].green = static_cast<unsigned char>(green);
        }
    }
}

// Increase the intensity of the TGA's red channel by a specified factor
void TGA::ScaleRed(unsigned short amount) {
    int red;
    for (int i = 0; i < GetSize(); i++) {
        red = data[i].red * amount;
        if(red > 255) {
            data[i].red = 255;
        }
        else {
            data[i].red = static_cast<unsigned char>(red);
        }
    }
}