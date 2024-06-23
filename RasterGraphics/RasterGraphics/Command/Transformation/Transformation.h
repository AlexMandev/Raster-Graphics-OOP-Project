#pragma once
#include "../Command.h"

enum class TransformationType
{
	GRAYSCALE,
	MONOCHROME,
	NEGATIVE,
	ROTATE_LEFT,
	ROTATE_RIGHT,
	UNDEFINED
};

class Transformation : public Command
{
public:
	Transformation(TransformationType type);

	TransformationType getType() const;
	
	Transformation* clone() const override = 0;
private:
	TransformationType type;
};

