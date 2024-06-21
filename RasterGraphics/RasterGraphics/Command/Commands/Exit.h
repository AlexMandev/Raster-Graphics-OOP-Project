#pragma once
#include "../Command.h"

class Exit : public Command
{
public:
	Exit() = default;

	void execute(System& system) const override;

	Command* clone() const override;
};

