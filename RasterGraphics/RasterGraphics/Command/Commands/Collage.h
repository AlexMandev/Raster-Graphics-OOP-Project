#pragma once
#include "../Command.h"
#include "../../Image/Image.h"


class Collage : public Command
{
public:
	Collage(Direction dir, const String& first, const String& second, const String& newFileName);

	void execute(System& system) const override;

	Command* clone() const override;

private:
	Direction dir;
	String first;
	String second;
	String newFileName;
};

