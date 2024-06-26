#pragma once
#include "../Image/Image.h"
#include "../Collections/Vector.hpp"

class Session
{
public:
	Session() = default;

	void addImage(const PolymorphicPtr<Image>& newImage);
	void addImage(PolymorphicPtr<Image>&& newImage);

	void printSessionInfo(std::ostream& out) const;

	int getID() const;

	void save();

	void registerSession();

	void addCollageFile(Direction dir, const String& first, const String& second, const String& newFileName);

	void saveFirstFileAs(const String& newFileName);

	void queueTransformation(const PolymorphicPtr<Transformation>& transformation);
	void removeLastTransformation();

private:
	static unsigned registeredSessionsCounter;

	int sessionID = -1;
	Vector<PolymorphicPtr<Image>> images;
};

