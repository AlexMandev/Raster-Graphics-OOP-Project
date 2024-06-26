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
		throw std::exception("No active sessions!");

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
		std::cout << "Loading " << files[i].c_str() << "...\n";
		PolymorphicPtr<Image> img = ImageFactory::imageFactory(files[i].c_str());

		if (img.get())
		{
			std::cout << "Loaded " << files[i].c_str() << std::endl;
			toLoad.addImage(std::move(img));
			loaded++;
		}
		else
		{
			std::cout << "Couldn't open " << files[i].c_str() << "!\n";
		}
	}

	if (loaded)
	{
		toLoad.registerSession();
		std::cout << "Started session with ID: " << toLoad.getID() << std::endl;
		activeSessionID = toLoad.getID();
		sessions.pushBack(std::move(toLoad));
	}
	else
	{
		std::cout << "Couldn't load session! None of the images could be opened.\n";
	}
}

void System::undo()
{
	if (activeSessionID == -1)
		throw std::exception("No active sessions!");

	int index = findCurrentSession();

	sessions[index].removeLastTransformation();
}

void System::switchSession(int newID)
{
	if (activeSessionID == -1)
		throw std::exception("No active sessions!");

	for (size_t i = 0; i < sessions.getSize(); i++)
	{
		if (sessions[i].getID() == newID)
		{
			activeSessionID = newID;
			std::cout << "Switched to session with ID " << newID << std::endl;
			return;
		}
	}

	throw std::exception("Session not found! Check if ID is correct.");
}

void System::saveCurrentSession()
{
	if (activeSessionID == -1)
		throw std::exception("No active sessions!");

	int index = findCurrentSession();

	sessions[index].save();
}

void System::printCurrentSessionInfo() const
{
	if (activeSessionID == -1)
		throw std::exception("No active sessions!");

	int index = findCurrentSession();

	sessions[index].printSessionInfo(std::cout);
}

void System::closeCurrentSession()
{
	if (activeSessionID == -1)
		throw std::exception("No active sessions!");

	int index = findCurrentSession();

	sessions.popAt(index);

	if(sessions.empty())
		activeSessionID = -1;
}

void System::saveCurrentSessionFileAs(const String& newFileName)
{
	if (activeSessionID == -1)
		throw std::exception("No active sessions!");

	int index = findCurrentSession();

	sessions[index].saveFirstFileAs(newFileName);
}

void System::addCollageFile(Direction dir, const String& first, const String& second, const String& newFileName)
{
	if (activeSessionID == -1)
		throw std::exception("No active sessions!");

	int index = findCurrentSession();

	sessions[index].addCollageFile(dir, first, second, newFileName);
}

void System::addImageToCurrentSession(const String& fileName)
{
	if (activeSessionID == -1)
		throw std::exception("No active sessions!");

	int index = findCurrentSession();

	PolymorphicPtr<Image> img = ImageFactory::imageFactory(fileName.c_str());

	if (img.get())
	{
		sessions[index].addImage(std::move(img));
		return;
	}
	
	throw std::exception("Couldn't open file!");
}
