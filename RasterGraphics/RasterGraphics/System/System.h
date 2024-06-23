#pragma once
#include "../Collections/Vector.hpp"
#include "../Session/Session.h"

class System
{
public:
	static System& getInstance();

	System(const System&) = delete;
	System& operator=(const System&) = delete;



	void help(std::ostream& out) const;
	void loadSession(const Vector<String>& files);
	void undo();
	void switchSession(int newID);
	void saveCurrentSession();
	void printCurrentSessionInfo() const;
	void closeCurrentSession();

	void saveCurrentSessionFileAs(const String& newFileName);

	void addCollageFile(Direction dir, const String& first, const String& second, const String& newFileName);

	void addImageToCurrentSession(const String& fileName);

	void queueTransformation(const PolymorphicPtr<Transformation>& transformation);

	void exitProgram();

	bool isRunning() const;

private:
	Vector<Session> sessions;
	int activeSessionID = -1;
	bool running = true;

	System() = default;

	int findCurrentSession() const;
};

