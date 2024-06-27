#include "ImagePPM.h"
#include <fstream>
#include "../Utilities/Utilities.h"

ImagePPM::ImagePPM(unsigned width, unsigned height, unsigned maxColorNumber, 
    const String& magicNumber, const String& fileName,
    const Pixel* const* pixels)
    :Image(width, height, maxColorNumber, magicNumber, fileName)
{
    isGrayscale = false;
    isMonochrome = false;
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

void ImagePPM::save()
{
    executeAllTransformations();

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
                file << (uint16_t)pixels[i][j].rgb[k] << ' ';
            }
        }
        file << std::endl;
    }

    file.close();
}

ImagePPM::ImagePPM(unsigned width, unsigned height, unsigned maxColorNumber, 
    const String& magicNumber, const String& fileName,
    Pixel**&& pixels)
    :Image(width, height, maxColorNumber, magicNumber, fileName)
{
    isGrayscale = false;
    isMonochrome = false;
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
    if (isGrayscale)
        return;

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
    isGrayscale = true;
}

void ImagePPM::monochrome()
{
    if (isMonochrome)
        return;

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

    isMonochrome = true;
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

void ImagePPM::rotateLeft()
{
    Pixel** newPixels = new (std::nothrow) Pixel * [width];

    if (!newPixels)
        return;

    for (size_t i = 0; i < width; i++) 
    {
        newPixels[i] = new Pixel[height];
    }

    for (size_t i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            newPixels[width - j - 1][i] = pixels[i][j];
        }
    }

    free();
    std::swap(width, height);
    pixels = newPixels;
}

void ImagePPM::rotateRight()
{
    Pixel** newPixels = new (std::nothrow) Pixel * [width];

    if (!newPixels)
        return;

    for (size_t i = 0; i < width; i++)
    {
        newPixels[i] = new Pixel[height];
    }

    for (size_t i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            newPixels[j][height - i - 1] = pixels[i][j];
        }
    }

    free();
    std::swap(width, height);
    pixels = newPixels;
}

Image* ImagePPM::collageWith(const Image* img, Direction dir, const String& newFileName) const
{
    return img->collageWithPPM(this, dir, newFileName);
}

Image* ImagePPM::collageWithPPM(const ImagePPM* img, Direction dir, const String& newFileName) const
{
    if (!img)
        return nullptr;

    if (strcmp(extractFileExtension(newFileName.c_str()), getFileExtension()) != 0)
        throw std::exception("Invalid new file name for collage!");

    size_t newWidth = dir == Direction::HORIZONTAL ? width + img->getWidth() : width;
    size_t newHeight = dir == Direction::HORIZONTAL ? height : height + img->getHeight();

    Pixel** collagePixels = new Pixel * [newHeight];

    for (size_t i = 0; i < newHeight; i++)
    {
        collagePixels[i] = new Pixel[newWidth];
    }

    for (size_t i = 0; i < height; i++)
    {
        for (size_t j = 0; j < width; j++)
        {
            collagePixels[i][j] = pixels[i][j];
        }
    }

    if (dir == Direction::HORIZONTAL)
    {
        for (size_t i = 0; i < img->getHeight(); i++)
        {
            for (size_t j = 0; j < img->getWidth(); j++)
            {
                collagePixels[i][j + width] = img->pixels[i][j];
            }
        }
    }
    else
    {
        for (size_t i = 0; i < img->getHeight(); i++)
        {
            for (size_t j = 0; j < img->getWidth(); j++)
            {
                collagePixels[i + height][j] = img->pixels[i][j];
            }
        }
    }

    return new ImagePPM(newWidth, newHeight,
        (maxColorNumber > img->maxColorNumber ? maxColorNumber : img->maxColorNumber), 
        "P3", newFileName, std::move(collagePixels));
}

Image* ImagePPM::collageWithPBM(const ImagePBM* img, Direction dir, const String& newFileName) const
{
    throw std::logic_error("Can't collage different types!");
}

Image* ImagePPM::collageWithPGM(const ImagePGM* img, Direction dir, const String& newFileName) const
{
    throw std::logic_error("Can't collage different types!");
}

Image* ImagePPM::clone() const
{
    return new ImagePPM(*this);
}

const char* ImagePPM::getFileExtension() const
{
    return ".ppm";
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
