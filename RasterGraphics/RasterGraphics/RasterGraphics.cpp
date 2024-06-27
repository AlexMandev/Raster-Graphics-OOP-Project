#include <iostream>
#include "System/System.h"
#include "Factories/CommandFactory.h"
#include "Collections/PolymorphicPtr.hpp"

int main()
{
	System& app = System::getInstance();

	while (app.isRunning())
	{
		try
		{
			PolymorphicPtr<Command> cmd = CommandFactory::readConsoleCommand();
			cmd->execute(app);
		}
		catch (std::exception& exc)
		{
			std::cerr << exc.what() << std::endl;
		}
	}
}