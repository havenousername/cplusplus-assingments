#include "CaughtItemsEnumerator.h"
#include <string>
#include <sstream>
#include <iostream>
#include <utility>

CaughtItemsEnumerator::CaughtItemsEnumerator (const std::string& filename, const std::string& itemName) throw (FileErrors)
{
    _file.open(filename);

    if (_file.fail())
    {
        throw MissingFileError;
    }

    _itemName = itemName;
    _b_End = false;
}


void CaughtItemsEnumerator::next()
{
    std::string line;
    getline(_file, line, '\n');

    if (!(_b_End = _file.fail()))
    {
        std::istringstream stringStream(line);
        std::string comp;
        stringStream >> _current.name >> comp;
        _current.countOftems = 0;

        std::pair<std::string, int> haul;
        for (stringStream >> haul.first >> haul.second; !stringStream.fail(); stringStream >> haul.first >> haul.second)
        {
            if (haul.first == _itemName)
            {
                _current.countOftems++;
            }
        }
    }
};
