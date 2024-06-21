#pragma once
#include "Transformation.h"


class RotateRight : public Transformation
{
public:
	RotateRight();

	Transformation* clone() const override;

	void execute(System& system) const override;
};

