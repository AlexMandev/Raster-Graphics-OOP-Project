#include "Grayscale.h"
#include "../../System/System.h"

Grayscale::Grayscale() : Transformation(TransformationType::GRAYSCALE)
{ }

Transformation* Grayscale::clone() const
{
	return new Grayscale(*this);
}

void Grayscale::execute(System& system) const
{
	system.queueTransformation(PolymorphicPtr<Transformation>(this->clone()));
}
