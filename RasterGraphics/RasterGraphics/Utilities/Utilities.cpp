#include "Utilities.h"
#include <iostream>

const char* extractFileExtension(const char* filePath)
{
    if (!filePath)
        return nullptr;
   
    size_t length = strlen(filePath);

    if (length == 0)
        return nullptr;

    const char* end = filePath + length - 1;

    const char* iter = end;

    while (*iter != '.' && length > 0)
    {
        iter--;
        length--;
    }

    if (length == 0)
        return "";

    return iter;
}

