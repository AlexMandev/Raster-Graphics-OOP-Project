#include "Load.h"
#include "../../System/System.h"

Load::Load(Vector<String>&& files) : files(std::move(files))
{}

Load::Load(const Vector<String>& files) : files(files)
{}

void Load::execute(System& system) const
{
    system.loadSession(this->files);
}

Command* Load::clone() const
{
    return new Load(*this);
}
