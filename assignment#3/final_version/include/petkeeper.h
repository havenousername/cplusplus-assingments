#ifndef PETKEEPER_H
#define PETKEEPER_H

#include "pet.h"
#include "day.h"
#include "custompetkeeperenumerators.hpp"
#include <vector>

class PetKeeper
{
private:
    std::vector<Pet*> _pets;
    std::vector<Day*> _days;
    SeqInFileEnumeratorPets _petsEnor;
    SeqInFileEnumeratorDays _daysEnor;
    SeqInFileEnumerator<int> _enor;
    std::string _name;
    std::string _filename;
public:
    PetKeeper(const std::string& filename, const std::string& name = "Cathy"):
         _name(name), _petsEnor(filename, 1), _daysEnor(filename), _enor(filename), _filename(filename)
    {
        _pets.clear();
        _days.clear();
    }

    void populate();
    void daysSimulation();
    std::vector<std::string> getLowestExhalationAlive() const;

    int petsSize()
    {
        return  _pets.size();
    }

    int daysSize()
    {
        return _days.size();
    }

    ~PetKeeper()
    {
        for (int i = 0; i < _pets.size(); i++)
        {
            delete _pets[i];
        }

        BadDay::destroy();
        GoodDay::destroy();
        NormalDay::destroy();
    }
};

#endif // PETKEEPER_H
