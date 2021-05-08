#ifndef PET_H
#define PET_H

#include <string>
#include <stdlib.h>
#include "rangedinteger.hpp"
#include "day.h"
#include "enums.hpp"

class Pet
{
protected:
    std::string _name;
    BoundedValue<int, HealthRange::EMPTY, HealthRange::FULL> _exhalationLevel;
public:
    Pet(const std::string& name, int exhalationLevel = HealthRange::EMPTY) : _name(name), _exhalationLevel(exhalationLevel) {}
    bool alive() const
    {
        return _exhalationLevel.getVal() > HealthRange::EMPTY;
    }
    std::string getName() const
    {
        return _name;
    }

    int getExhalationLevel()
    {
        return _exhalationLevel.getVal();
    }

    void changeLevel(int level)
    {
        if (!alive())
        {
            return;
        }

        bool isNegative = level < 0;
        int levl = abs(level);
        if (isNegative)
        {
            _exhalationLevel = _exhalationLevel - levl;
        }
        else
        {
            _exhalationLevel = _exhalationLevel + levl;
        }
    }

    virtual void react(Day* &day) = 0;
    virtual ~Pet() {};
};

class Fish : public Pet
{
public:
    Fish(const std::string& name, int exhalationLevel) : Pet(name, exhalationLevel) {};
    void react(Day* &day) override
    {
        day = day->influence(this);
    }
};

class Bird : public Pet
{
public:
    Bird(const std::string& name, int exhalationLevel) : Pet(name, exhalationLevel) {};
    void react(Day* &day) override
    {
        day = day->influence(this);
    }
};

class Dog : public Pet
{
public:
    Dog(const std::string& name, int exhalationLevel) : Pet(name, exhalationLevel) {};
    void react(Day* &day) override
    {
        day = day->influence(this);
    }
};



#endif // PET_H
