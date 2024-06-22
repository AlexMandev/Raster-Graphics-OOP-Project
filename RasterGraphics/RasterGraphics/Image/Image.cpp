#include "Image.h"
#include "../Utilities/Utilities.h"

Image::Image(unsigned width, unsigned height, unsigned maxColorNumber, String magicNumber, String fileName)
	:width(width), height(height) , maxColorNumber(maxColorNumber), magicNumber(magicNumber),
	fileName(fileName)
{

}

void Image::undoLastTransformation()
{
	if (!awaitingTransformations.empty())
		awaitingTransformations.popBack();
}

void Image::executeAllTransformations()
{
	for (size_t i = 0; i < awaitingTransformations.getSize(); i++)
	{
		executeTransformation(awaitingTransformations[i]->getType());
	}
}

void Image::queueTransformation(const PolymorphicPtr<Transformation>& transformation)
{
	awaitingTransformations.pushBack(transformation);
}

void Image::printInfo(std::ostream& out = std::cout) const
{
	out << fileName << std::endl;
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

void Image::setFileName(const String& newFileName)
{
	const char* ext = extractFileExtension(newFileName.c_str());

	if (strcmp(ext, getFileExtension()) != 0 || strlen(ext) != 4)
		throw std::exception("Invalid file name!\n");

	fileName = newFileName;
}

void Image::executeTransformation(TransformationType type)
{
	switch (type)
	{
		case TransformationType::GRAYSCALE:
			grayscale();
			break;
		case TransformationType::MONOCHROME:
			monochrome();
			break;
		case TransformationType::NEGATIVE:
			negative();
			break;
		case TransformationType::ROTATE_LEFT:
			rotateLeft();
			break;
		case TransformationType::ROTATE_RIGHT:
			rotateRight();
			break;
	}
}

