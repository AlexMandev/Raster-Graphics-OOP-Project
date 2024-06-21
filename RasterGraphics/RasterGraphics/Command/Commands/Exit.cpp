#include "Exit.h"
#include "../../System/System.h"

void Exit::execute(System& system) const
{
	system.exitProgram();
}

Command* Exit::clone() const
{
	return new Exit(*this);
}
