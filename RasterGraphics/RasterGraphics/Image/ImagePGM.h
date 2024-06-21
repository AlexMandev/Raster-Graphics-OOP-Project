#pragma once
#include "Image.h"

class ImagePGM : public Image
{
public:
	/*
		constructor copying the pixels
	*/
	ImagePGM(unsigned width, unsigned height, unsigned maxColorNumber, 
		String magicNumber, String fileName,
		const uint8_t* const* pixels);


	/*
		constructor moving the pixels (will be used in the factory)
	*/
	ImagePGM(unsigned width, unsigned height, unsigned maxColorNumber,
		String magicNumber, String fileName,
		uint8_t**&& pixels);

	ImagePGM(const ImagePGM& other);
	ImagePGM(ImagePGM&& other) noexcept;

	ImagePGM& operator=(const ImagePGM& other);
	ImagePGM& operator=(ImagePGM&& other) noexcept;

	~ImagePGM();

	void grayscale() override;
	void monochrome() override;
	void negative() override;

	void save() const override;

	Image* clone() const override;

	const char* getFileExtension() const override;

private:
	uint8_t** pixels = nullptr;

	void free();
	void copyFrom(const ImagePGM& other);
	void moveFrom(ImagePGM&& other);
};

