#include "Image.h"

Image::Image(unsigned width, unsigned height, unsigned maxColorNumber, String magicNumber, String fileName)
	:width(width), height(height) , maxColorNumber(maxColorNumber), magicNumber(magicNumber),
	fileName(fileName)
{

}

unsigned Image::getWidth() const
{
	return width;
}

unsigned Image::getHeight() const
{
	return height;
}

const String& Image::getMagicNumber() const
{
	return magicNumber;
}

const String& Image::getFileName() const
{
	return fileName;
}

