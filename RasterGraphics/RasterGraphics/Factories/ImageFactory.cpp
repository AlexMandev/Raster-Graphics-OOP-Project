#include "ImageFactory.h"
#include "../Image/ImagePBM.h"
#include "../Image/ImagePGM.h"
#include "../Image/ImagePPM.h"
#include "../Utilities/Utilities.h"
#include <sstream>
#include <fstream>



PolymorphicPtr<Image> ImageFactory::imageFactory(const char* fileName)
{
    std::ifstream inFile(fileName);

    if (!inFile.is_open())
        return nullptr;

    char magicNum[3];
    inFile >> magicNum;
    inFile.get(); // skipping the new line character after the magic number

    switch (magicNum[1])
    {
    case '1':
        return readPBMInASCII(inFile, fileName);
        break;

    case '2':
        return readPGMInASCII(inFile, fileName);
        break;

    case '3':
        return readPPMInASCII(inFile, fileName);
        break;
    default:
        return nullptr;
    }
}

PolymorphicPtr<Image> ImageFactory::readPBMInASCII(std::ifstream& inFile, const char* fileName)
{
    while (inFile.peek() == '#') // ignoring comments
    {
        inFile.ignore(1024, '\n');
    }

    unsigned width, height;
    inFile >> width >> height;

    Bitset data(width * height - 1);
    size_t length = width * height;
    char ch;
    size_t iter = 0;

    while (iter < length && !inFile.eof())
    {
        char ch = inFile.get();
        
        switch (ch)
        {
            case '0':
                iter++;
                break;
            case '1':
                data.add(iter);
                iter++;
                break;
            default:
                continue;
        }
    }

    return new ImagePBM(width, height, "P1", fileName, std::move(data));
}

PolymorphicPtr<Image> ImageFactory::readPGMInASCII(std::ifstream& inFile, const char* fileName)
{
    while (inFile.peek() == '#') // ignoring comments
    {
        inFile.ignore(1024, '\n');
    }
    unsigned width, height, maxColorNumber;
    inFile >> width >> height >> maxColorNumber;
    
    uint8_t** pixels = new uint8_t * [height];

    unsigned value;
    for (size_t i = 0; i < height; i++)
    {
        pixels[i] = new uint8_t[width];
        for (size_t j = 0; j < width; j++)
        {
            inFile >> value;
            pixels[i][j] = value;
        }
    }

    return new ImagePGM(width, height, maxColorNumber, "P2", fileName, std::move(pixels));
}


PolymorphicPtr<Image> ImageFactory::readPPMInASCII(std::ifstream& inFile, const char* fileName)
{
    while (inFile.peek() == '#') // ignoring comments
    {
        inFile.ignore(1024, '\n');
    }
    std::cout << inFile.is_open();
    int width, height, maxColorNumber;
    inFile >> width >> height >> maxColorNumber;

    Pixel** pixels = new Pixel * [height];

    unsigned value;
    for (size_t i = 0; i < height; i++)
    {
        pixels[i] = new Pixel[width];
        for (size_t j = 0; j < width; j++)
        {
            for (size_t k = 0; k < 3; k++)
            {
                inFile >> value;
                pixels[i][j].rgb[k] = value;
            }
        }
    }

    return new ImagePPM(width, height, maxColorNumber, "P3", fileName, std::move(pixels));
}

