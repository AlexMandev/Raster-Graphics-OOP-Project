#include "Collage.h"
#include "../../System/System.h"

Collage::Collage(Direction dir, const String& first, const String& second, const String& newFileName)
	: dir(dir), first(first), second(second), newFileName(newFileName)
{}

void Collage::execute(System & system) const
{
	system.addCollageFile(dir, first, second, newFileName);
}



Command* Collage::clone() const
{
	return new Collage(*this);
}

