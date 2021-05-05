#ifndef PET_H
#define PET_H

#include <string>
#include "rangedinteger.hpp"
#include "day.h"
#include "enums.hpp"

class Pet
{
protected:
    std::string _name;
    BoundedValue<int, HealthRange::EMPTY, HealthRange::FULL> _exhalationLevel;
public:
    Pet(std::string& name, int exhalationLevel = HealthRange::EMPTY) : _name(name), _exhalationLevel(exhalationLevel) {}
    bool alive() const
    {
        return _exhalationLevel.getVal() > HealthRange::EMPTY;
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
