#include "ImageCollection.h"

ImageCollection::ImageCollection() : size(0) , capacity(8)
{
	data = new Image * [capacity] {nullptr};
}

ImageCollection::ImageCollection(const ImageCollection& other)
{
	copyFrom(other);
}

ImageCollection::ImageCollection(ImageCollection&& other) noexcept
{
	moveFrom(std::move(other));
}

ImageCollection& ImageCollection::operator=(const ImageCollection& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

ImageCollection& ImageCollection::operator=(ImageCollection&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

void ImageCollection::addImage(const Image& newImage)
{
	Image* cloned = newImage.clone();
	addImage(std::move(cloned));
}

void ImageCollection::addImage(Image*&& newImage)
{
	if (size == capacity)
		resize(capacity * 2);

	data[size++] = newImage;
	newImage = nullptr;
}

size_t ImageCollection::getSize() const
{
	return size;
}

ImageCollection::~ImageCollection()
{
	free();
}

void ImageCollection::resize(size_t newCap)
{
	Image** newData = new Image * [newCap] {nullptr};
	
	for (size_t i = 0; i < capacity; i++)
	{
		newData[i] = data[i];
	}
	delete[] data;
	data = newData;
	capacity = newCap;
}

void ImageCollection::free()
{
	for (size_t i = 0; i < size; i++)
	{
		delete data[i];
	}
	delete[] data;
}

void ImageCollection::copyFrom(const ImageCollection& other)
{
	data = new Image * [other.capacity] {nullptr};
	capacity = other.capacity;
	size = other.size;

	for (size_t i = 0; i < size; i++)
	{
		data[i] = other.data[i]->clone();
	}
}

void ImageCollection::moveFrom(ImageCollection&& other)
{
	data = other.data;
	other.data = nullptr;

	size = other.size;
	capacity = other.capacity;

	other.size = other.capacity = 0;
}







