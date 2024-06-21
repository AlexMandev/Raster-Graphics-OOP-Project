#pragma once
#include "../Command.h"
#include "../../String/String.h"
#include "../../Collections/Vector.hpp"

class Load : public Command
{
public:
	Load(const Vector<String>& files);
	Load(Vector<String>&& files);

	void execute(System& system) const override;

	Command* clone() const override;

private:
	Vector<String> files;
};

