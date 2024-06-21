#pragma once
#include "../Command.h"

class Undo : public Command
{
public:
	Undo() = default;

	void execute(System& system) const override;

	Command* clone() const override;
};

