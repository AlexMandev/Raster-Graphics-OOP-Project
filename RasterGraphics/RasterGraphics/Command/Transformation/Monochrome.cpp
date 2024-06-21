#include "Monochrome.h"
#include "../../System/System.h"

Monochrome::Monochrome() : Transformation(TransformationType::MONOCHROME)
{ }

void Monochrome::execute(System& system) const
{
	system.queueTransformation(PolymorphicPtr<Transformation>(this->clone()));
}

Transformation* Monochrome::clone() const
{
	return new Monochrome(*this);
}


