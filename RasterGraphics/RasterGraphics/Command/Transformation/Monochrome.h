#pragma once
#include "Transformation.h"

class Monochrome : public Transformation
{
public:
	Monochrome();

	void execute(System&) const override;

	Transformation* clone() const override;
};

