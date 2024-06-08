#include "ImagePBM.h"

ImagePBM::ImagePBM(unsigned width, unsigned height, String magicNumber, String fileName, const Bitset& data)
    :Image(width, height, 1, magicNumber, fileName), data(data)
{ }

ImagePBM::ImagePBM(unsigned width, unsigned height, String magicNumber, String fileName, Bitset && data)
    :Image(width, height, 1, magicNumber, fileName), data(std::move(data))
{
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

void ImagePBM::save() const
{

}



Image* ImagePBM::clone() const
{
    return new ImagePBM(*this);
}
