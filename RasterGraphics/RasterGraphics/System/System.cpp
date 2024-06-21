#include "System.h"
#include "../Factories/ImageFactory.h"

System& System::getInstance()
{
    static System system;

    return system;
}

void System::queueTransformation(const PolymorphicPtr<Transformation>& transformation)
{
    if (activeSessionID == -1)
		throw std::exception("No active sessions!\n");

	int index = findCurrentSession();

	sessions[index].queueTransformation(transformation);
}

void System::exitProgram()
{
	running = false;
}

bool System::isRunning() const
{
	return running;
}

int System::findCurrentSession() const
{
	for (size_t i = 0; i < sessions.getSize(); i++)
	{
		if (sessions[i].getID() == activeSessionID)
			return i;
	}
	return -1;
}

void System::help(std::ostream& out = std::cout) const
{
	out << "The following commands are supported:\n";
	out << "* load <image1> <image2> ... -> opens <file> and creates a session\n";
	out << "* close -> closes the active session and closes all its files\n";
	out << "* save -> saves all the files in the active session\n";
	out << "* saveas <file> -> saves the first file in the active session in <file>\n";
	out << "* grayscale -> transforms every non-grayscale (excluding the monochrome) image (in the active session) into grayscale\n";
	out << "* monochrome -> transforms every non-monochrome image (in the active session) into monochrome\n";
	out << "* negative -> applies the negative transformation for every image in the active session\n";
	out << "* rotate <direction> -> rotates every image (in the active session) in a desired direction (90 degrees) - either left or right\n";
	out << "* undo -> undos the last command (doesn't affect save and doesn't work on saved transformations)\n";
	out << "* add <image> -> adds an image to the current session\n";
	out << "* session info -> prints information about the current session\n";
	out << "* switch <sessionId> -> switches to the session with <sessionId>\n";
	out << "* collage <direction> <image1> <image2> <outimage> -> creates a collage of <image1> and <image2> in <outimage>. <direction> is either horizontal or vertical\n";
	out << "* help -> prints information about every command\n";
	out << "* exit -> exits the program\n";
}

void System::loadSession(const Vector<String>& files)
{
	size_t loaded = 0;
	Session toLoad;
	
	for (size_t i = 0; i < files.getSize(); i++)
	{
		PolymorphicPtr<Image> img = ImageFactory::imageFactory(files[i].c_str());

		if (img.get())
		{
			toLoad.addImage(std::move(img));
			loaded++;
		}
	}

	if (loaded)
	{
		activeSessionID = toLoad.getID();
		sessions.pushBack(std::move(toLoad));
	}

}

void System::undo()
{
	if (activeSessionID == -1)
		throw std::exception("No active sessions!\n");

	int index = findCurrentSession();

	sessions[index].removeLastTransformation();
}

void System::switchSession(int newID)
{
	if (activeSessionID == -1)
		throw std::exception("No active sessions!\n");

	for (size_t i = 0; i < sessions.getSize(); i++)
	{
		if (sessions[i].getID() == newID)
		{
			activeSessionID = newID;
			return;
		}
	}

	throw std::exception("Session not found! Check if ID is correct.");
}

void System::saveCurrentSession() const
{
	if (activeSessionID == -1)
		throw std::exception("No active sessions!\n");

	int index = findCurrentSession();

	sessions[index].save();
}

void System::printCurrentSessionInfo() const
{
	if (activeSessionID == -1)
		throw std::exception("No active sessions\n");

	int index = findCurrentSession();

	sessions[index].printSessionInfo(std::cout);
}

void System::closeCurrentSession()
{
	if (activeSessionID == -1)
		throw std::exception("No active sessions!\n");

	int index = findCurrentSession();

	sessions.popAt(index);
}

void System::saveCurrentSessionFileAs(const String& newFileName)
{
	if (activeSessionID == -1)
		throw std::exception("No active sessions!\n");

	int index = findCurrentSession();

	sessions[index].saveFirstFileAs(newFileName);
}

void System::addImageToCurrentSession(const String& fileName)
{
	if (activeSessionID == -1)
		throw std::exception("No active sessions!\n");

	int index = findCurrentSession();

	PolymorphicPtr<Image> img = ImageFactory::imageFactory(fileName.c_str());

	if (img.get())
	{
		sessions[index].addImage(std::move(img));
		return;
	}
	
	throw std::exception("Couldn't open file!\n");
}
