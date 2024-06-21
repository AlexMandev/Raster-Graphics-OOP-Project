#pragma once
#include "../Command.h"

class Save : public Command
{
public:
	Save() = default;

	void execute(System& system) const override;

	Command* clone() const override;
};

