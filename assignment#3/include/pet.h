#ifndef PET_H
#define PET_H

#include <string>
#include "rangedinteger.hpp"
#include "day.h"

class Pet
{
protected:
    std::string _name;
    BoundedValue<int, 0, 100> _exhalationLevel;
public:
    Pet(std::string& name, int exhalationLevel = 0) : _name(name), _exhalationLevel(exhalationLevel) {}
    bool alive() const
    {
        return _exhalationLevel.getVal() > 0;
    }
    std::string getName() const
    {
        return _name;
    }

    void changeLevel(int level)
    {
        _exhalationLevel = _exhalationLevel + level;
    }

    virtual void react(Day* &day) = 0;
    virtual ~Pet() {};
};

class Fish : public Pet
{
public:
    Fish(std::string& name, int exhalationLevel) : Pet(name, exhalationLevel) {};
};

class Bird : public Pet
{
public:
    Bird(std::string& name, int exhalationLevel) : Pet(name, exhalationLevel) {};
};

class Dog : public Pet
{
public:
    Dog(std::string& name, int exhalationLevel) : Pet(name, exhalationLevel) {};
};



#endif // PET_H
