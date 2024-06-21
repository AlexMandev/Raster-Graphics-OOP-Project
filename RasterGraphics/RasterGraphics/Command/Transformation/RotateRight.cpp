#include "RotateRight.h"
#include "../../System/System.h"

RotateRight::RotateRight() : Transformation(TransformationType::ROTATE_RIGHT)
{
}

Transformation* RotateRight::clone() const
{
	return new RotateRight(*this);
}

void RotateRight::execute(System& system) const
{
	system.queueTransformation(PolymorphicPtr<Transformation>(this->clone()));
}
