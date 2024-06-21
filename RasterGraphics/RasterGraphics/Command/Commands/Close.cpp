#include "Close.h"
#include "../../System/System.h"

void Close::execute(System& system) const
{
    system.closeCurrentSession();
}

Command* Close::clone() const
{
    return new Close(*this);
}
