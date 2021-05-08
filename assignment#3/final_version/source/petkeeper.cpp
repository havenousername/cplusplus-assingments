#include "../include/petkeeper.h"
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

    _daysEnor.passIterations(1 + i * 3);

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

void PetKeeper::changeDayMood(int index)
{
    switch (_days[index]->getDay())
        {
            case RawDay::BAD_DAY :
                if (_mood > 0)
                {
                    _days[index] = NormalDay::instance();
                }
                break;
            case RawDay::NORMAL_DAY:
                if (_mood > 0)
                {
                    _days[index] = GoodDay::instance();
                }
                else if (_mood < 0)
                {
                    _days[index] = BadDay::instance();
                }
                break;
            case RawDay::GOOD_DAY:
                if (_mood < 0)
                {
                    _days[index] = NormalDay::instance();
                }
                break;
            default:
                break;
        }
}

void PetKeeper::daysSimulation()
{
    for (int i = 0; i < _days.size(); i++)
    {
        bool goodPetsCondition = true;
        for (int j = 0; j < _pets.size(); j++)
        {
            //std::cout << "pet name" << _pets[j]->getName() << ", exh: " << _pets[j]->getExhalationLevel() << std::endl;
            if (_pets[j]->getExhalationLevel() < HealthRange::CRITICAL)
            {
                goodPetsCondition = false;
            }
        }
        changeMood(goodPetsCondition ? 1 : - 1);
        changeDayMood(i);

        //std::cout << "LOG: petkeeper mood - " << _mood << std::endl;
        //std::cout << "LOG: day mood - " << _days[i]->getDay() << std::endl;

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
        //std::cout  << "LOG:" << " pets level- " << _pets[i]->getExhalationLevel() << ", pets name- " << _pets[i]->getName() << std::endl;
        if (_pets[i]->getExhalationLevel() < exhalation && _pets[i]->alive())
        {
            exhalation = _pets[i]->getExhalationLevel();
        }
    }


    for (int i = 0; i < _pets.size(); i++)
    {
        if (exhalation == _pets[i]->getExhalationLevel())
        {
            //std::cout  << "LOG:" << " pets level- " << _pets[i]->getExhalationLevel() << ", pets name- " << _pets[i]->getName() << std::endl;
            lowest.push_back(_pets[i]->getName());
        }
    }

    // std::cout << "LOG: lowest size - " << lowest.size() << ", exhalation - " << exhalation << std::endl;

    return lowest;
}

