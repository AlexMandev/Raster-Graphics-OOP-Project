#pragma once
#include "Image.h"
#include "../Collections/Bitset.h"

class ImagePBM : public Image
{
public:
	ImagePBM(unsigned width, unsigned height,
		const String& magicNumber, const String& fileName, const Bitset& data);

	ImagePBM(unsigned width, unsigned height,
		const String& magicNumber, const String& fileName, Bitset&& data);

	const char* getFileExtension() const override;

	void grayscale() override;
	void monochrome() override;
	void negative() override;
	void rotateLeft() override;
	void rotateRight() override;

	void save() override;

	Image* collageWith(const Image* img, Direction dir, const String& newFileName) const override;

	Image* collageWithPPM(const ImagePPM* img, Direction dir, const String& newFileName) const override;
	Image* collageWithPBM(const ImagePBM* img, Direction dir, const String& newFileName) const override;
	Image* collageWithPGM(const ImagePGM* img, Direction dir, const String& newFileName) const override;

	virtual Image* clone() const override;
private:
	Bitset data;
};

