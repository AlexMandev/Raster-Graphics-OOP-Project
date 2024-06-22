#pragma once
#include "Image.h"


constexpr double RED_MODIFIER = 0.299;
constexpr double GREEN_MODIFIER = 0.587;
constexpr double BLUE_MODIFIER = 0.114;

struct Pixel {
	uint8_t rgb[3]{ 0 };

	bool isGray() const
	{
		return rgb[0] == rgb[1] && rgb[1] == rgb[2];
	}
};

class ImagePPM : public Image
{
public:
	/*
		Constructor copying the pixels
	*/
	ImagePPM(unsigned width, unsigned height, unsigned maxColorNumber, 
		String magicNumber, String fileName,
		const Pixel* const * pixels); 

	/*
		constructor moving the pixels (will be used in the factory)
	*/
	ImagePPM(unsigned width, unsigned height, unsigned maxColorNumber, 
		String magicNumber, String fileName,
		Pixel**&& pixels);

	ImagePPM(const ImagePPM& other);
	ImagePPM(ImagePPM&& other) noexcept;

	ImagePPM& operator=(const ImagePPM& other);
	ImagePPM& operator=(ImagePPM&& other) noexcept;

	~ImagePPM();

	void grayscale() override;
	void monochrome() override;
	void negative() override;
	void rotateLeft() override;
	void rotateRight() override;

	void save();

	Image* clone() const override;

	const char* getFileExtension() const override;

private:
	Pixel** pixels = nullptr;

	void free();
	void moveFrom(ImagePPM&& other);
	void copyFrom(const ImagePPM& other);
};

