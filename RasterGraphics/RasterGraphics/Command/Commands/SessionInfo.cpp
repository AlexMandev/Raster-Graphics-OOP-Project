#include "SessionInfo.h"
#include "../../System/System.h"

void SessionInfo::execute(System& system) const
{
	system.printCurrentSessionInfo();
}

Command* SessionInfo::clone() const
{
	return new SessionInfo(*this);
}
