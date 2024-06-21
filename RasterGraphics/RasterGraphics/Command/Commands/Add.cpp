#include "Add.h"
#include "../../System/System.h"

Add::Add(const String& fileName) : fileName(fileName)
{}

Add::Add(String && fileName) : fileName(std::move(fileName))
{}

void Add::execute(System & system) const
{
	system.addImageToCurrentSession(this->fileName);
}

Command* Add::clone() const
{
	return new Add(*this);
}





