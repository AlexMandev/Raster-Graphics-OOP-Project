#pragma once
#include "Transformation.h"


class Negative : public Transformation
{
public:
	Negative();

	Transformation* clone() const override;

	void execute(System& system) const override;
};

