#pragma once
#include "../Command.h"

class Close : public Command
{
public:
	Close() = default;
	
	void execute(System& system) const override;

	Command* clone() const override;
};
