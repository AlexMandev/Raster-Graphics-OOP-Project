#pragma once
#include "../Image/Image.h"
#include "../Collections/PolymorphicPtr.hpp"
#include <fstream>

class ImageFactory
{
public:
	static PolymorphicPtr<Image> imageFactory(const char* fileName);

private:
	static PolymorphicPtr<Image> readPBMInASCII(std::ifstream&, const char*);
	
	static PolymorphicPtr<Image> readPGMInASCII(std::ifstream&, const char*);
	
	static PolymorphicPtr<Image> readPPMInASCII(std::ifstream&, const char*);
	
};

