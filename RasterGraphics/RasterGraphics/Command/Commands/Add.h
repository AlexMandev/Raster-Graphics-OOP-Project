#pragma once
#include "../Command.h"
#include "../../String/String.h"

class Add : public Command
{
public:
	Add(const String& fileName);
	Add(String&& fileName);

	void execute(System& system) const override;

	Command* clone() const override;

private:
	String fileName;
};

