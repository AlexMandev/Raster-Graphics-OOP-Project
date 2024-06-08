#pragma once
#include "Image.h"
#include <fstream>

class ImageFactory
{
public:
	static Image* imageFactory(const char* fileName);

private:
	static Image* readPBMInASCII(std::ifstream&, const char*);
	static Image* readPBMInBinary(std::ifstream&, const char*);

	static Image* readPGMInASCII(std::ifstream&, const char*);
	static Image* readPGMInBinary(std::ifstream&, const char*);

	static Image* readPPMInASCII(std::ifstream&, const char*);
	static Image* readPPMInBinary(std::ifstream&, const char*);
};

