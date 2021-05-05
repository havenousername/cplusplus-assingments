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
    std::string _name;
public:
    PetKeeper(const std::string& filename, const std::string& name = "Cathy"): _name(name), _petsEnor(filename), _daysEnor(filename)
    {
        _pets.clear();
        _days.clear();
    }

    void populate();
    void unpopulate();
    void daysSimulation();
    std::string getLowestExhalationAlive() const;

};

#endif // PETKEEPER_H
