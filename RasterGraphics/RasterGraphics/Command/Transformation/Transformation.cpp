#include "Transformation.h"

Transformation::Transformation(TransformationType type) : type(type)
{
}

TransformationType Transformation::getType() const
{
	return type;
}
