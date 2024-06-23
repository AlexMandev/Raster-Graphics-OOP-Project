#include "ImagePBM.h"
#include <fstream>
#include "../Utilities/Utilities.h"

ImagePBM::ImagePBM(unsigned width, unsigned height, String magicNumber, String fileName, const Bitset& data)
    :Image(width, height, 1, magicNumber, fileName), data(data)
{ }

ImagePBM::ImagePBM(unsigned width, unsigned height, String magicNumber, String fileName, Bitset && data)
    :Image(width, height, 1, magicNumber, fileName), data(std::move(data))
{
}

const char* ImagePBM::getFileExtension() const
{
    return ".pbm";
}

void ImagePBM::grayscale()
{

}

void ImagePBM::monochrome()
{

}

void ImagePBM::negative()
{
    for (size_t i = 0; i < data.getN(); i++)
    {
        if (data.contains(i))
            data.remove(i);
        else
            data.add(i);
    }
}

void ImagePBM::rotateLeft()
{
    Bitset newData(data.getN());

    for (size_t i = 0; i < height; i++)
    {
        for (size_t j = 0; j < width; j++)
        {
            if (data.contains(i * width + j))
            {
                newData.add((width - 1 - j)* height + i);
            }
        }
    }
    std::swap(width, height);
    data = std::move(newData);
}

void ImagePBM::rotateRight()
{
    Bitset newData(data.getN());

    for (size_t i = 0; i < height; i++)
    {
        for (size_t j = 0; j < width; j++)
        {
            if (data.contains(i * width + j))
            {
                newData.add(j*height + (height - 1 - i));
            }
        }
    }
    std::swap(width, height);
    data = std::move(newData);
}

void ImagePBM::save()
{
    executeAllTransformations();

    std::ofstream file(fileName.c_str());

    file << magicNumber << std::endl;
    file << width << ' ' << height << '\n';

    size_t length = width * height - 1;
    for (size_t i = 0; i < length; i++)
    {
        if (data.contains(i))
            file << true;
        else
            file << false;
    }

    file.close();
}

Image* ImagePBM::collageWith(const Image* img, Direction dir, const String& newFileName) const
{
    return img->collageWithPBM(this, dir, newFileName);
}

Image* ImagePBM::collageWithPPM(const ImagePPM* img, Direction dir, const String& newFileName) const
{
    throw std::logic_error("Can't collage different types!");
}

Image* ImagePBM::collageWithPBM(const ImagePBM* img, Direction dir, const String& newFileName) const
{
    if (!img)
        return nullptr;

    if (strcmp(extractFileExtension(newFileName.c_str()), getFileExtension()) != 0)
        throw std::exception("Invalid new file name for collage!");

    int newWidth = (dir == Direction::HORIZONTAL) ? width + img->getWidth() : width;
    int newHeight = (dir == Direction::HORIZONTAL) ? height : height + img->getHeight();

    Bitset newData(data.getN() + img->data.getN());

    for (size_t i = 0; i < height; i++)
    {
        for (size_t j = 0; j < width; j++)
        {
            if (data.contains(i * width + j))
            {
                newData.add(i * newWidth + j);
            }
        }
    }

    if (dir == Direction::HORIZONTAL)
    {
        for (size_t i = 0; i < img->getHeight(); i++)
        {
            for (size_t j = 0; j < img->getWidth(); j++)
            {
                if (img->data.contains(i * img->getWidth() + j))
                {
                    newData.add(i * newWidth + j + width);
                }
            }
        }
    }
    else
    {
        for (size_t i = 0; i < img->getHeight(); +i++) {
            for (size_t j = 0; j < img->getWidth(); j++) {
                if (img->data.contains(i * img->getWidth() + j)) {
                    newData.add((i + height) * newWidth + j);
                }
            }
        }
    }

    return new ImagePBM(width, height, "P1", newFileName, std::move(newData));
}

Image* ImagePBM::collageWithPGM(const ImagePGM* img, Direction dir, const String& newFileName) const
{
    throw std::logic_error("Can't collage different types!");
}



Image* ImagePBM::clone() const
{
    return new ImagePBM(*this);
}
