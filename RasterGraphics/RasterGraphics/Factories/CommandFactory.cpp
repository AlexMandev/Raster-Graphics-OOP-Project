#include "CommandFactory.h"
#include "../Command/Commands/Add.h"
#include "../Command/Commands/Close.h"
#include "../Command/Commands/Exit.h"
#include "../Command/Commands/Help.h"
#include "../Command/Commands/Load.h"
#include "../Command/Commands/Save.h"
#include "../Command/Commands/SessionInfo.h"
#include "../Command/Commands/Switch.h"
#include "../Command/Commands/Undo.h"
#include "../Command/Transformation/Grayscale.h"
#include "../Command/Transformation/Monochrome.h"
#include "../Command/Transformation/Negative.h"
#include "../Command/Transformation/RotateLeft.h"
#include "../Command/Transformation/RotateRight.h"

#include <iostream>
#include <sstream>
#include "../Collections/Vector.hpp"

static Vector<String> readVectorOfStrings(std::stringstream& ss)
{
    Vector<String> result;

    while (!ss.eof())
    {
        String toRead;
        ss >> toRead;
        result.pushBack(std::move(toRead));
    }

    return result;
}

void skipIntervalsInStringStream(std::stringstream& ss)
{
    while (!ss.eof() && ss.peek() == ' ')
    {
        ss.get();
    }
}

Command* CommandFactory::readConsoleCommand()
{

    char buffer[1024];

    std::cout << '>';

    std::cin.getline(buffer, 1024);

    std::stringstream line(buffer);

    String command;
    line >> command;
    command.toLower();

    skipIntervalsInStringStream(line);

    if (command == "help" && line.eof())
    {
        return new Help();
    }
    else if (command == "close" && line.eof())
    {
        return new Close();
    }
    else if (command == "exit" && line.eof())
    {
        return new Exit();
    }
    else if (command == "save" && line.eof())
    {
        return new Save();
    }
    else if (command == "undo" && line.eof())
    {
        return new Undo();
    }
    else if (command == "grayscale" && line.eof())
    {
        return new Grayscale();
    }
    else if (command == "monochrome" && line.eof())
    {
        return new Monochrome();
    }
    else if (command == "negative" && line.eof())
    {
        return new Negative();
    }
    else if (command == "load")
    {
        Vector<String> files = readVectorOfStrings(line);

        if (files.empty())
            throw std::exception("No file names given!\n");

        return new Load(std::move(files));
    }
    else if (command == "add")
    {
        String fileName;
        line >> fileName;
        
        skipIntervalsInStringStream(line);

        if (line.eof())
        {
            return new Add(std::move(fileName));
        }
        else 
        {
            throw std::exception("Invalid command!\n");
        }
    }
    else if (command == "switch")
    {
        int id;
        line >> id;
        
        skipIntervalsInStringStream(line);

        if (!line.eof() || line.fail())
        {
            throw std::exception("Invalid command!\n");
        }
        else
        {
            return new Switch(id);
        }
    }
    else if (command == "session")
    {
        skipIntervalsInStringStream(line);
        if (line.eof())
        {
            throw std::exception("Invalid command!\n");
        }
        else 
        {
            String toRead;
            line >> toRead;

            skipIntervalsInStringStream(line);
            if (toRead == "info" && line.eof())
            {
                return new SessionInfo();
            }
            else {
                throw std::exception("Invalid command!\n");
            }
        }
    }
    else if (command == "rotate")
    {
        skipIntervalsInStringStream(line);
        if (line.eof())
        {
            throw std::exception("Invalid command!\n");
        }
        else
        {
            String toRead;
            line >> toRead;

            toRead.toLower();

            if (toRead == "left" && line.eof())
            {
                return new RotateLeft();
            }
            else if (toRead == "right" && line.eof())
            {
                return new RotateRight();
            }
            else
            {
                throw std::exception("Invalid command!\n");
            }
        }
    }
    else
    {
        throw std::exception("Invalid command!\n");
    }
}
