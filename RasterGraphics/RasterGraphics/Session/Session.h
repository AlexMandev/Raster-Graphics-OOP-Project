#pragma once
#include "../Image/Image.h"
#include "../Collections/Vector.hpp"

class Session
{
public:
	Session();
	 
	void addImage(const PolymorphicPtr<Image>& newImage);
	void addImage(PolymorphicPtr<Image>&& newImage);

	void printSessionInfo(std::ostream& out) const;

	int getID() const;

	void save() const;

	void saveFirstFileAs(const String& newFileName);

	void queueTransformation(const PolymorphicPtr<Transformation>& transformation);
	void removeLastTransformation();

private:
	static unsigned createdSessionsCounter;

	int sessionID;
	Vector<PolymorphicPtr<Image>> images;
};

