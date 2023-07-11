#pragma once
#include <fstream>
using namespace std;

class TGA {

    public:
    /* ========== Pixel Class ========== */
        struct Pixel {
            unsigned char blue;
            unsigned char green;
            unsigned char red;
        };


    private:
    /* ========== Data Members ========== */
        char idLength;
        char colorMapType;
        char imageType;
        short colorMapOrigin;
        short colorMapLength;
        char colorMapDepth;
        short xOrigin;
        short yOrigin;
        short imageWidth;
        short imageHeight;
        char pixelDepth;
        char imageDescriptor;
        Pixel* data;


    public:
    /* ========== Accessors ========== */
        int GetSize() const;
        Pixel* GetImgData() const;
};