#include "ImagePGM.h"
#include <fstream>

ImagePGM::ImagePGM(unsigned width, unsigned height, unsigned maxColorNumber, 
	String magicNumber, String fileName,
	const uint8_t* const* pixels)
	: Image(width, height, maxColorNumber, magicNumber, fileName)
{
	isGrayscale = true;
	isMonochrome = false;
	this->pixels = new uint8_t * [height];

	for (size_t i = 0; i < height; i++)
	{
		this->pixels[i] = new uint8_t[width];
		for (size_t j = 0; j < width; j++)
		{
			this->pixels[i][j] = pixels[i][j];
		}
	}
}

ImagePGM::ImagePGM(unsigned width, unsigned height, unsigned maxColorNumber, 
	String magicNumber, String fileName, 
	uint8_t**&& pixels)
	: Image(width, height, maxColorNumber, magicNumber, fileName)
{
	isGrayscale = true;
	isMonochrome = false;
	this->pixels = pixels;
	pixels = nullptr;
}

ImagePGM::ImagePGM(const ImagePGM& other) :Image(other)
{
	copyFrom(other);
}

ImagePGM::ImagePGM(ImagePGM&& other) noexcept : Image(std::move(other))
{
	moveFrom(std::move(other));
}

ImagePGM& ImagePGM::operator=(const ImagePGM& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
		Image::operator=(other);
	}
	return *this;
}

ImagePGM& ImagePGM::operator=(ImagePGM&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
		Image::operator=(std::move(other));
	}
	return *this;
}

ImagePGM::~ImagePGM()
{
	free();
}

void ImagePGM::grayscale()
{
	return;
}

void ImagePGM::monochrome()
{
	if (isMonochrome)
		return;

	for (size_t i = 0; i < height; i++)
	{
		for (size_t j = 0; j < width; j++)
		{
			if (pixels[i][j] <= maxColorNumber / 2)
				pixels[i][j] = 0;
			else
				pixels[i][j] = maxColorNumber;
		}
	}
	isMonochrome = true;
}

void ImagePGM::negative()
{
	for (size_t i = 0; i < height; i++)
	{
		for (size_t j = 0; j < width; j++)
		{
			pixels[i][j] = maxColorNumber - pixels[i][j];
		}
	}
}

void ImagePGM::rotateLeft()
{
	uint8_t** newPixels = new (std::nothrow) uint8_t * [width];

	if (!newPixels)
		return;

	for (size_t i = 0; i < width; i++)
	{
		newPixels[i] = new uint8_t[height];
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

void ImagePGM::rotateRight()
{
	uint8_t** newPixels = new (std::nothrow) uint8_t * [width];

	if (!newPixels)
		return;

	for (size_t i = 0; i < width; i++)
	{
		newPixels[i] = new uint8_t[height];
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

void ImagePGM::save()
{
	executeAllTransformations();

	std::ofstream file(fileName.c_str());

	file << magicNumber << std::endl;
	file << width << ' ' << height << std::endl;
	file << (uint16_t)maxColorNumber << std::endl;

	for (size_t i = 0; i < height; i++)
	{
		for (size_t j = 0; j < width; j++)
		{
			file << (uint16_t)pixels[i][j] << ' ';
		}
		file << std::endl;
	}

	file.close();
}

Image* ImagePGM::clone() const
{
	return new ImagePGM(*this);
}

const char* ImagePGM::getFileExtension() const
{
	return ".pgm";
}

void ImagePGM::free()
{
	for (size_t i = 0; i < height; i++)
	{
		delete[] pixels[i];
	}
	delete[] pixels;
	pixels = nullptr;
}

void ImagePGM::copyFrom(const ImagePGM& other)
{
	pixels = new uint8_t * [other.height];

	for (size_t i = 0; i < other.height; i++)
	{
		pixels[i] = new uint8_t[other.width];
		for (size_t j = 0; j < other.width; j++)
		{
			pixels[i][j] = other.pixels[i][j];
		}
	}
}

void ImagePGM::moveFrom(ImagePGM&& other)
{
	pixels = other.pixels;
	other.pixels = nullptr;
}


