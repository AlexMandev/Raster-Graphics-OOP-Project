#pragma once
#include "Transformation.h"

class Grayscale : public Transformation
{
public:
	Grayscale();

	Transformation* clone() const override;

	void execute(System& system) const override;
};

