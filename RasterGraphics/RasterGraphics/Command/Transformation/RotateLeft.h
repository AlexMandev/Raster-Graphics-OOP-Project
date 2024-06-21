#pragma once
#include "Transformation.h"


class RotateLeft : public Transformation
{
public:
	RotateLeft();

	Transformation* clone() const override;

	void execute(System& system) const override;
};

