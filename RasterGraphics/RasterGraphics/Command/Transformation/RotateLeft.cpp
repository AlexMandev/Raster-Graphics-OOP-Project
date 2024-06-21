#include "RotateLeft.h"
#include "../../System/System.h"


RotateLeft::RotateLeft() : Transformation(TransformationType::ROTATE_LEFT)
{
}

Transformation* RotateLeft::clone() const
{
	return new RotateLeft(*this);
}

void RotateLeft::execute(System& system) const
{
	system.queueTransformation(PolymorphicPtr<Transformation>(this->clone()));
}
