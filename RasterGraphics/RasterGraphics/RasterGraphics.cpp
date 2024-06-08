#include <iostream>
#include "ImageFactory.h"

int main()
{
	Image* img = ImageFactory::imageFactory("federer.ppm");

	img->grayscale();
	img->save();
}