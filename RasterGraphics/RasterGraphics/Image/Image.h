#pragma once
#include "../String/String.h"
#include "../Collections/PolymorphicPtr.hpp"
#include "../Collections/Vector.hpp"
#include "../Command/Transformation/Transformation.h"

class Image
{
protected:
	unsigned width = 0, height = 0;
	uint8_t maxColorNumber = 0;
	String magicNumber;
	String fileName;
	Vector<PolymorphicPtr<Transformation>> awaitingTransformations;

public:
	Image(unsigned width, unsigned height, unsigned maxColorNumber, String magicNumber, String fileName);

	virtual void grayscale() = 0;
	virtual void monochrome() = 0;
	virtual void negative() = 0;

	virtual Image* clone() const = 0;
	
	virtual void save() const = 0;

	virtual const char* getFileExtension() const = 0;

	void undoLastTransformation();




	void queueTransformation(const PolymorphicPtr<Transformation>& transformation);

	void printInfo(std::ostream& out) const;

	unsigned getWidth() const;
	unsigned getHeight() const;
	const String& getMagicNumber() const;
	const String& getFileName() const;

	void setFileName(const String& newFileName);

	virtual ~Image() = default;
};