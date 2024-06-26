#include "Session.h"
#include "../Utilities/Utilities.h"

unsigned Session::registeredSessionsCounter = 0;

void Session::addImage(const PolymorphicPtr<Image>& newImage)
{
	images.pushBack(newImage);
}

void Session::addImage(PolymorphicPtr<Image>&& newImage)
{
	images.pushBack(std::move(newImage));
}

void Session::printSessionInfo(std::ostream& out = std::cout) const
{
	out << "Session " << sessionID << " with images: " << std::endl;
	for (size_t i = 0; i < images.getSize(); i++)
	{
		images[i]->printInfo(out);
	}
}

int Session::getID() const
{
	return sessionID;
}

void Session::save()
{
	for (size_t i = 0; i < images.getSize(); i++)
	{
		std::cout << "Saving " << images[i]->getFileName() << "...\n";
		images[i]->save();
	}
}

void Session::registerSession()
{
	registeredSessionsCounter++;
	sessionID = registeredSessionsCounter;
}

void Session::addCollageFile(Direction dir, const String& first, const String& second, const String& newFileName)
{
	bool hasFirst = false;
	bool hasSecond = false;

	size_t firstInd, secondInd;

	// searching for images

	for (size_t i = 0; i < images.getSize(); i++)
	{
		if (!hasFirst && !strcmp(first.c_str(), images[i]->getFileName().c_str()))
		{
			firstInd = i;
			hasFirst = true;
		}
		if (!hasSecond && !strcmp(second.c_str(), images[i]->getFileName().c_str()))
		{
			secondInd = i;
			hasSecond = true;
		}
	}

	if (!hasFirst)
	{
		throw std::exception("Couldn't find first image of the collage");
	}
	else if (!hasSecond)
	{
		throw std::exception("Couldn't find second image of the collage");
	}

	PolymorphicPtr<Image> collage = images[secondInd]->collageWith(images[firstInd].get(), dir, newFileName);

	if (collage.get())
	{
		std::cout << "Collage with name " << collage->getFileName() << "created successfully!\n";
		images.pushBack(std::move(collage));
	}
	else
	{
		throw std::exception("Couldn't collage images!");
	}
}

void Session::saveFirstFileAs(const String& newFileName)
{
	if (images.getSize() == 0)
		throw std::exception("No active images in the session!\n");

	images[0]->setFileName(newFileName);
}

void Session::queueTransformation(const PolymorphicPtr<Transformation>& transformation)
{
	for (size_t i = 0; i < images.getSize(); i++)
	{
		images[i]->queueTransformation(transformation);
	}
}

void Session::removeLastTransformation()
{
	for (size_t i = 0; i < images.getSize(); i++)
	{
		images[i]->undoLastTransformation();
	}
}


