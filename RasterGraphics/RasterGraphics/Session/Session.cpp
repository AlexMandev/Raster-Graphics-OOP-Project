#include "Session.h"
#include "../Utilities/Utilities.h"

unsigned Session::createdSessionsCounter = 0;

Session::Session()
{
	createdSessionsCounter++;
	sessionID = createdSessionsCounter;
}

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
	out << "Session " << sessionID << "with images: " << std::endl;
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
		images[i]->save();
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


