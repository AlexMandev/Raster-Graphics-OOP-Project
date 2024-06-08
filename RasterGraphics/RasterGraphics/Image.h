#pragma once
#include "String.h"

class Image
{
protected:
	unsigned width = 0, height = 0;
	uint8_t maxColorNumber = 0;
	String magicNumber;
	String fileName;
public:
	Image(unsigned width, unsigned height, unsigned maxColorNumber, String magicNumber, String fileName);

	virtual void grayscale() = 0;
	virtual void monochrome() = 0;
	virtual void negative() = 0;

	virtual Image* clone() const = 0;

	virtual void save() const = 0;

	unsigned getWidth() const;
	unsigned getHeight() const;
	const String& getMagicNumber() const;
	const String& getFileName() const;

	virtual ~Image() = default;
};