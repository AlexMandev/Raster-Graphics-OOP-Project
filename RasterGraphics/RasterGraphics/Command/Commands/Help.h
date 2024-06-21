#pragma once
#include "../Command.h"

class Help : public Command
{
public:
	Help() = default;

	void execute(System&) const override;

	Command* clone() const override;
};

