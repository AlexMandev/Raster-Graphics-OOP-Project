#include "Help.h"
#include "../../System/System.h"


void Help::execute(System& system) const
{
	system.help(std::cout);
}

Command* Help::clone() const
{
	return new Help(*this);
}
