#pragma once
#include "../Command.h"

class SessionInfo : public Command
{
public:
	SessionInfo() = default;

	void execute(System& system) const override;

	Command* clone() const override;
};

