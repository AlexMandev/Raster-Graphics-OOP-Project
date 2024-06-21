#include "Negative.h"
#include "../../System/System.h"


Negative::Negative() : Transformation(TransformationType::NEGATIVE)
{
}

Transformation* Negative::clone() const
{
	return new Negative(*this);
}

void Negative::execute(System& system) const
{
	system.queueTransformation(PolymorphicPtr<Transformation>(this->clone()));
}

