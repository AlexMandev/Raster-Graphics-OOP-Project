#include "Switch.h"
#include "../../System/System.h"

Switch::Switch(int switchTo) : switchTo(switchTo)
{ }

void Switch::execute(System& system) const
{
	system.switchSession(this->switchTo);
}

Command* Switch::clone() const
{
	return new Switch(*this);
}



