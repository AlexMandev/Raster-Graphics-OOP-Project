#include "ImagePPM.h"
#include <fstream>

ImagePPM::ImagePPM(unsigned width, unsigned height, unsigned maxColorNumber, 
    String magicNumber, String fileName, 
    const Pixel* const* pixels)
    :Image(width, height, maxColorNumber, magicNumber, fileName)
{
    this->pixels = new Pixel * [height];
    for (size_t i = 0; i < height; i++)
    {
        this->pixels[i] = new Pixel[width];
        for (size_t j = 0; j < width; j++)
        {
            this->pixels[i][j] = pixels[i][j];
        }
    }
}

void ImagePPM::save() const
{
    std::ofstream file(fileName.c_str());

    file << magicNumber << std::endl;
    file << width << ' ' << height << '\n';
    file << (uint16_t)maxColorNumber << std::endl;


    for (size_t i = 0; i < height; i++)
    {
        for (size_t j = 0; j < width; j++)
        {
            for (size_t k = 0; k < 3; k++)
            {
                file << (uint16_t)pixels[i][j].rgb[k] << " ";
            }
        }
        file << std::endl;
    }

    file.close();
}

ImagePPM::ImagePPM(unsigned width, unsigned height, unsigned maxColorNumber, 
    String magicNumber, String fileName, 
    Pixel**&& pixels)
    :Image(width, height, maxColorNumber, magicNumber, fileName)
{
    this->pixels = pixels;
    pixels = nullptr;
}

ImagePPM::ImagePPM(const ImagePPM& other) : Image(other)
{
    copyFrom(other);
}

ImagePPM::ImagePPM(ImagePPM&& other) noexcept : Image(std::move(other))
{
    moveFrom(std::move(other));
}

ImagePPM& ImagePPM::operator=(const ImagePPM& other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
        Image::operator=(other);
    }
    return *this;
}

ImagePPM& ImagePPM::operator=(ImagePPM&& other) noexcept
{
    if (this != &other)
    {
        free();
        copyFrom(std::move(other));
        Image::operator=(std::move(other));
    }
    return *this;
}

ImagePPM::~ImagePPM()
{
    free();
}


void ImagePPM::grayscale()
{
    for (size_t i = 0; i < height; i++)
    {
        for (size_t j = 0; j < width; j++)
        {
            if (!pixels[i][j].isGray())
            {
                uint8_t grayscaleValue = pixels[i][j].rgb[0] * RED_MODIFIER +
                pixels[i][j].rgb[1] * GREEN_MODIFIER +
                pixels[i][j].rgb[2] * BLUE_MODIFIER;

                pixels[i][j].rgb[0] = grayscaleValue;
                pixels[i][j].rgb[1] = grayscaleValue;
                pixels[i][j].rgb[2] = grayscaleValue;
            }

        }
    }
}

void ImagePPM::monochrome()
{
    for (size_t i = 0; i < height; i++)
    {
        for (size_t j = 0; j < width; j++)
        {

            uint8_t monochromeValue = pixels[i][j].rgb[0] * RED_MODIFIER +
                pixels[i][j].rgb[1] * GREEN_MODIFIER +
                pixels[i][j].rgb[2] * BLUE_MODIFIER;

            if (monochromeValue <= maxColorNumber / 2)
                monochromeValue = 0;
            else
                monochromeValue = maxColorNumber;

            pixels[i][j].rgb[0] = monochromeValue;
            pixels[i][j].rgb[1] = monochromeValue;
            pixels[i][j].rgb[2] = monochromeValue;
        }
    }
}

void ImagePPM::negative()
{
    for (size_t i = 0; i < height; i++)
    {
        for (size_t j = 0; j  < width; j ++)
        {
            for (size_t k = 0; k < 3; k++)
            {
                pixels[i][j].rgb[k] = maxColorNumber - pixels[i][j].rgb[k];

            }
        }
    }
}

Image* ImagePPM::clone() const
{
    return new ImagePPM(*this);
}

void ImagePPM::free()
{
    for (size_t i = 0; i < height; i++)
    {
        delete[] pixels[i];
    }
    delete[] pixels;
}

void ImagePPM::moveFrom(ImagePPM&& other)
{
    pixels = other.pixels;
    other.pixels = nullptr;
}

void ImagePPM::copyFrom(const ImagePPM& other)
{
    pixels = new Pixel * [other.height];

    for (size_t i = 0; i < other.height; i++)
    {
        pixels[i] = new Pixel[other.width];
        for (size_t j = 0; j < other.width; j++)
        {
            pixels[i][j] = other.pixels[i][j];
        }
    }
}
