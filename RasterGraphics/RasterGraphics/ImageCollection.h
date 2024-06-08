#pragma once
#include "Image.h"

class ImageCollection
{
public:
	ImageCollection();

	ImageCollection(const ImageCollection& other);
	ImageCollection(ImageCollection&& other) noexcept;

	ImageCollection& operator=(const ImageCollection& other);
	ImageCollection& operator=(ImageCollection&& other) noexcept;

	void addImage(const Image& newImage);
	void addImage(Image*&& newImage);

	size_t getSize() const;

	~ImageCollection();
private:
	Image** data = nullptr;
	size_t capacity = 0;
	size_t size = 0;

	void resize(size_t newCap);

	void free();
	void copyFrom(const ImageCollection& other);
	void moveFrom(ImageCollection&& other);
};

