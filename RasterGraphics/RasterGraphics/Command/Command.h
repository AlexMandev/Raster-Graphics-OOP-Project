#pragma once

class System;

class Command
{
public:
	virtual void execute(System&) const = 0;

	virtual Command* clone() const = 0;

	virtual ~Command() = default;
};

