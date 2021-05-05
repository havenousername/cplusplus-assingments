#include <iostream>
#include "Pet.h"
#include "rangedinteger.hpp"
#include "seqinfileenumerator.hpp"
#include <limits>

using std::cout;
using std::endl;

enum RawPetType: char
{
    FISH = 'F',
    BIRD = 'B',
    DOG = 'D',
};

enum HealthRange: int
{
    EMPTY = 0,
    FULL = 100
};

struct RawPet
{
private:
    RawPetType _type;
    std::string _name;
    BoundedValue<int, 0, 100> _exhalationLevel;
    enum TypeErrors { BOUNDED_VALUE_OUT_OF_RANGE, NOT_ENUM_CHAR_VALUE };
public:
    RawPet(): _exhalationLevel(int(0))
    {
        _type = RawPetType::DOG;
        _name = "";
    }

    char type() const
    {
        return _type;
    }

    std::string name() const
    {
        return _name;
    }

    int exhalationLevel() const
    {
        int casted = 0;
        return casted;
    }

    void type(char t)
    {
        bool isInType = t == RawPetType::BIRD || t == RawPetType::DOG || t == RawPetType::FISH;
        if (!isInType)
        {
            throw NOT_ENUM_CHAR_VALUE;
        }

        _type = static_cast<RawPetType>(t);
    }

    void name(std::string name)
    {
        _name = name;
    }

    void exhalationLevel(int level)
    {
        if (level < HealthRange::EMPTY || level > HealthRange::FULL)
        {
            throw BOUNDED_VALUE_OUT_OF_RANGE;
        }

        _exhalationLevel = level;
    }


};

class SeqInFileEnumeratorPets: public Enumerator<RawPet>
{
private:
    RawPet* _current;
    SeqInFileEnumerator<std::string> *_f;
    bool _end;
public:
    SeqInFileEnumeratorPets(const std::string& filename)
    {
        _f = new SeqInFileEnumerator<std::string>(filename);
        _current = new RawPet();
    };

    ~SeqInFileEnumeratorPets()
    {
        delete _f;
    }

    void first() override
    {
        _f->first();
        next();
    }

    void next() override
    {
    }
    bool end() const override
    {
        return _end;
    }
    RawPet current() const override
    {
        char t = _f->current()[0];
        cout << _f->current() << endl;
        try
        {
            _current->type(t);
        } catch ()
        {

        }
        return *(_current);
    }
};


int main()
{
    SeqInFileEnumeratorPets enor = SeqInFileEnumeratorPets("test01.txt");
    cout << enor.current().type();
    return 0;
}
