#ifndef PET_H
#define PET_H

#include "rangedinteger.hpp"

class Pet
{
protected:
    std::string name;
    BoundedValue<int, 0, 100> exhilationLevel;

public:
    bool alive()
    {
        return exhilationLevel.getVal() == 0;
    }
};

#endif // PET_H

