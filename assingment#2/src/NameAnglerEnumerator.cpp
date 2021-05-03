#include "NameAnglerEnumerator.h"
#include <string>
#include <sstream>
#include <iostream>
#include <utility>



void NameAnglerEnumerator::next()
{
    if (!(_b_End = _caughtEnor.end()))
    {
        _current.name = _caughtEnor.current().name;
        int number = 0;

        for (; _caughtEnor.current().name == _current.name && !_caughtEnor.end(); _caughtEnor.next())
        {
            number += _caughtEnor.current().countOftems;
        }
        //std::cout << number << "num\n";
        _current.sumOfItems = number;
    }
};
