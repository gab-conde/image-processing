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


    /* ========== Mutators ========== */
        void ReadFile(ifstream& input);
        void WriteFile(ofstream& output);
        void CopyHeader(TGA& other);

    /* ========== Accessor Operations ========= */
        unsigned char* OnlyBlue() const;
        unsigned char* OnlyGreen() const;
        unsigned char* OnlyRed() const;

    /* ========== Mutator Operations ========= */
        void Subtract(TGA& p1, TGA& p2);
        void Multiply(TGA& top, TGA& bottom);
        void Screen(TGA& p1, TGA& p2);
        void Overlay(TGA& p1, TGA& p2);
        void AddGreen(unsigned char amount);
        void ScaleBlue(unsigned char amount);
        void ScaleGreen(unsigned char amount);
        void ScaleRed(unsigned char amount);
        void Combine(unsigned char* blue, unsigned char* green, unsigned char* red);
};