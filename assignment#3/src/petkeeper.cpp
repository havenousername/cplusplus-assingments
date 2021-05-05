#include "petkeeper.h"
#include <iostream>


void PetKeeper::populate()
{
    _enor.first();
    // populate pets
    int i = _enor.current();
    for (_petsEnor.first(); !_petsEnor.end() && _pets.size() != i; _petsEnor.next())
    {
        switch(_petsEnor.current().type())
        {
            case RawPetType::FISH :
                 _pets.push_back(new Fish(_petsEnor.current().name(), _petsEnor.current().exhalationLevel()));
                 break;
            case RawPetType::BIRD :
                _pets.push_back(new Bird(_petsEnor.current().name(), _petsEnor.current().exhalationLevel()));
                break;
            case RawPetType::DOG :
                _pets.push_back(new Dog(_petsEnor.current().name(), _petsEnor.current().exhalationLevel()));
                break;
        }
    }

    _daysEnor.passIterations(i * 3);

    // populate days
    for (_daysEnor.first(); !_daysEnor.end(); _daysEnor.next())
    {
        switch (_daysEnor.current())
        {
            case RawDay::BAD_DAY :
                _days.push_back(BadDay::instance());
                break;
            case RawDay::GOOD_DAY :
                _days.push_back(GoodDay::instance());
                break;
            case RawDay::NORMAL_DAY :
                _days.push_back(NormalDay::instance());
                break;
        }
    }
}

void PetKeeper::daysSimulation()
{
    for (int i = 0; i < _days.size(); i++)
    {
        for (int j = 0; j < _pets.size(); j++)
        {
            _pets[j]->react(_days[i]);
        }
    }
}

std::vector<std::string> PetKeeper::getLowestExhalationAlive() const
{
    std::vector<std::string> lowest;
    int exhalation = HealthRange::FULL;
    for (int i = 0; i < _pets.size(); i++)
    {
        if (_pets[i]->getExhalationLevel() < exhalation)
        {
            exhalation = _pets[i]->getExhalationLevel();
        }
    }

    for (int i = 0; i < _pets.size(); i++)
    {
        if (exhalation == _pets[i]->getExhalationLevel())
        {
            lowest.push_back(_pets[i]->getName());
        }
    }

    return lowest;
}

