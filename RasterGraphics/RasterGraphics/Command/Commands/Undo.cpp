#include "Undo.h"
#include "../../System/System.h"

void Undo::execute(System& system) const
{
	system.undo();
}

Command* Undo::clone() const
{
	return new Undo(*this);
}


