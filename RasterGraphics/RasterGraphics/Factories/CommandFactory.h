#pragma once
#include "../Command/Command.h"

class CommandFactory
{
public:
	static Command* readConsoleCommand();
};

