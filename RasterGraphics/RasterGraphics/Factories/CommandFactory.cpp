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


Command* CommandFactory::readConsoleCommand()
{
    
}
