#include "Save.h"
#include "../../System/System.h"

void Save::execute(System& system) const
{
	system.saveCurrentSession();
}

Command* Save::clone() const
{
	return new Save(*this);
}


