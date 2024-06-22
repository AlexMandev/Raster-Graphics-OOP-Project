#include "String.h"
#include <cstring>
#pragma warning (disable : 4996)


static char getLowerCharacter(char ch)
{
    if (ch >= 'A' && ch <= 'Z')
        return (ch + 'a' - 'A');

    return ch;
}

static unsigned roundToPowerOfTwo(unsigned v)
{
    v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    v++;
    return v;
}

static unsigned dataToAllocByStringLen(unsigned stringLength)
{
    return std::max(roundToPowerOfTwo(stringLength + 1), 16u);
}

String::String() : String("") {}

String::String(const char* data)
{
    _size = std::strlen(data);
    _allocatedDataSize = dataToAllocByStringLen(_size);
    _data = new char[_allocatedDataSize];
    std::strcpy(_data, data);
}

String::String(size_t stringLength)
{
    _allocatedDataSize = dataToAllocByStringLen(stringLength);
    _data = new char[_allocatedDataSize];
    _size = 0;
    _data[0] = '\0';
}

String::String(const String& other)
{
    copyFrom(other);
}
String::String(String&& other) noexcept
{
    moveFrom(std::move(other));
}


void String::moveFrom(String&& other)
{
    _data = other._data;
    other._data = nullptr;

    _size = other._size;
    other._size = 0;

    _allocatedDataSize = other._allocatedDataSize;
    other._allocatedDataSize = 0;
}


String& String::operator=(const String& other)
{
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

String& String::operator=(String&& other) noexcept
{
    if (this != &other)
    {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}


String::~String()
{
    free();
}

size_t String::getCapacity() const
{
    return _allocatedDataSize - 1;
}

size_t String::getSize() const
{
    return _size;
}

const char* String::c_str() const
{
    return _data;
}

String& String::operator+=(const String& other)
{
    if (getSize() + other.getSize() + 1 > _allocatedDataSize)
        resize(dataToAllocByStringLen(getSize() + other.getSize()));

    std::strncat(_data, other._data, other.getSize());

    _size = getSize() + other.getSize();
    return *this;
}

char& String::operator[](size_t index)
{
    return _data[index];
}

const char& String::operator[](size_t index) const
{
    return _data[index];
}

void String::toLower()
{
    for (size_t i = 0; i < getSize(); i++)
    {
        _data[i] = getLowerCharacter(_data[i]);
    }
}

std::ostream& operator<<(std::ostream& os, const String& obj)
{
    return os << obj._data;
}

std::istream& operator>>(std::istream& is, String& ref)
{
    char buff[1024];
    is >> buff;
    size_t buffStringSize = std::strlen(buff);

    if (buffStringSize > ref.getCapacity())
        ref.resize(dataToAllocByStringLen(buffStringSize));

    strcpy(ref._data, buff);
    ref._size = buffStringSize;
    return is;
}

void String::resize(unsigned newAllocatedDataSize)
{
    char* newData = new char[newAllocatedDataSize + 1];
    std::strcpy(newData, _data);
    delete[] _data;
    _data = newData;
    _allocatedDataSize = newAllocatedDataSize;
}

void String::free()
{
    delete[] _data;
}

void String::copyFrom(const String& other)
{
    _allocatedDataSize = other._allocatedDataSize;
    _data = new char[_allocatedDataSize];
    std::strcpy(_data, other._data);
    _size = other._size;
}

String operator+(const String& lhs, const String& rhs)
{
    String result(lhs.getSize() + rhs.getSize());
    result += lhs; // no resize is needed
    result += rhs;
    return result;
}

bool operator==(const String& lhs, const String& rhs)
{
    return std::strcmp(lhs.c_str(), rhs.c_str()) == 0;
}

bool operator!=(const String& lhs, const String& rhs)
{
    return std::strcmp(lhs.c_str(), rhs.c_str()) != 0;
}

bool operator<(const String& lhs, const String& rhs)
{
    return std::strcmp(lhs.c_str(), rhs.c_str()) < 0;
}

bool operator<=(const String& lhs, const String& rhs)
{
    return std::strcmp(lhs.c_str(), rhs.c_str()) <= 0;
}

bool operator>(const String& lhs, const String& rhs)
{
    return std::strcmp(lhs.c_str(), rhs.c_str()) > 0;
}

bool operator>=(const String& lhs, const String& rhs)
{
    return std::strcmp(lhs.c_str(), rhs.c_str()) >= 0;
}
