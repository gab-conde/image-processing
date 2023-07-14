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
    /* ========== Construction / Destruction ========== */
    TGA() = default;
    TGA(const TGA& other);
    TGA& operator=(const TGA&);
    ~TGA();

    /* ========== Accessors ========== */
        int GetSize() const;
        Pixel* GetImgData() const;

    /* ========== Mutators ========== */
        void ReadFile(ifstream& input);
        void WriteFile(ofstream& output);
        void CopyHeader(const TGA& other);

    /* ========== Accessor Operations ========= */
        unsigned char* OnlyBlue() const;
        unsigned char* OnlyGreen() const;
        unsigned char* OnlyRed() const;

    /* ========== Mutator Operations ========= */
        void Subtract(const TGA& p1, const TGA& p2);
        void Multiply(const TGA& top, const TGA& bottom);
        void Overlay(const TGA& p1, const TGA& p2);
        void Screen(const TGA& p1, const TGA& p2);
        void Combine(unsigned char* blue, unsigned char* green, unsigned char* red);
        void Flip();
        void AddBlue(int amount);
        void AddGreen(int amount);
        void AddRed(int amount);
        void ScaleBlue(unsigned short amount);
        void ScaleGreen(unsigned short amount);
        void ScaleRed(unsigned short amount);
};