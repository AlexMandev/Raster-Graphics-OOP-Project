#pragma once
#include "../Command.h"

class Switch : public Command
{
public:
	Switch(int switchTo);

	void execute(System&) const override;

	Command* clone() const override;

private:
	int switchTo = 0;
};

