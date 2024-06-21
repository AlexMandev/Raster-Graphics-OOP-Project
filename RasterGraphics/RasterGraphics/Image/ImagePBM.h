#pragma once
#include "Image.h"
#include "../Collections/Bitset.h"

class ImagePBM : public Image
{
public:
	ImagePBM(unsigned width, unsigned height,
		String magicNumber,String fileName, const Bitset& data);

	ImagePBM(unsigned width, unsigned height,
		String magicNumber, String fileName, Bitset&& data);

	const char* getFileExtension() const override;

	void grayscale() override;
	void monochrome() override;
	void negative() override;

	void save() const override;

	virtual Image* clone() const override;
private:
	Bitset data;
};

