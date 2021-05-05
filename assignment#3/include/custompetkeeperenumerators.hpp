#ifndef CUSTOMPETKEEPERENUMERATORS_HPP
#define CUSTOMPETKEEPERENUMERATORS_HPP

#include <iostream>
#include <string>
#include "seqinfileenumerator.hpp"
#include "rangedinteger.hpp"
#include "enumerator.hpp"
#include "enums.hpp"

using std::cout;
using std::endl;

class RawPet
{
private:
    RawPetType _type;
    std::string _name;
    BoundedValue<int, HealthRange::EMPTY, HealthRange::FULL> _exhalationLevel;
public:
    enum class RawPetTypeErrors: int { BOUNDED_VALUE_OUT_OF_RANGE, NOT_ENUM_CHAR_VALUE };
    RawPet(): _exhalationLevel(int(HealthRange::EMPTY))
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
        return _exhalationLevel.getVal();
    }

    void type(char t)
    {
        bool isInType =
        t == static_cast<char>(RawPetType::BIRD) ||
        t == static_cast<char>(RawPetType::DOG) ||
        t == static_cast<char>(RawPetType::FISH);
        if (!isInType)
        {
            throw RawPetTypeErrors::NOT_ENUM_CHAR_VALUE;
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
            throw RawPetTypeErrors::BOUNDED_VALUE_OUT_OF_RANGE;
        }

        _exhalationLevel = level;
    }


};

class SeqInFileEnumeratorPets: public Enumerator<RawPet>
{
private:
    RawPet *_current;
    SeqInFileEnumerator<std::string> *_f;
    bool _end;
public:
    SeqInFileEnumeratorPets(const std::string& filename)
    {
        _f = new SeqInFileEnumerator<std::string>(filename);
        _current = new RawPet();
        _end = false;
    };

    ~SeqInFileEnumeratorPets()
    {
        delete _f;
        delete _current;
    }

    void first() override
    {
        _f->first();
        next();
    }

    bool passesValidation(const std::string& s)
    {
        const char nonvalid[] = {'o', 'g',  'b'};
        unsigned int counter = 0;
        for (unsigned int i = 0; i < s.size(); i++)
        {
            if (s[i] == nonvalid[0] || s[i] == nonvalid[1] || s[i] ==  nonvalid[2])
            {
                counter++;
            }
        }
        return (counter != s.size());
    }

    void next() override
    {
        if(!passesValidation(static_cast<std::string>(_f->current())))
        {
            _end = true;
        }
        else
        {
            _end = _f->end();
        }


        if (_end)
        {
            return;
        }

        try
        {
            _current->type(_f->current()[0]);
            _f->next();
            _current->name(_f->current());
            _f->next();
            _current->exhalationLevel(stoi(_f->current()));
            _f->next();
        }
        catch (RawPet::RawPetTypeErrors e)
        {
            if (e == RawPet::RawPetTypeErrors::BOUNDED_VALUE_OUT_OF_RANGE)
            {
                cout << "BOUNDED_VALUE_OUT_OF_RANGE, " << "Reason: ";
            }
            else if (e == RawPet::RawPetTypeErrors::NOT_ENUM_CHAR_VALUE)
            {
                cout << "NOT_ENUM_CHAR_VALUE, " << "Reason: ";
            }
        }
    }
    bool end() const override
    {
        return _end;
    }
    RawPet current() const override
    {
        return *(_current);
    };
};

class SeqInFileEnumeratorDays : public Enumerator<char>
{
private:
    char _current;
    SeqInFileEnumerator<std::string> *_enor;
    int _passIterations;
    int _currentPosition;
    bool _end;
public:
    SeqInFileEnumeratorDays(const std::string& filename, int passIterations = 0):
        _passIterations(passIterations * 3), _end(false), _currentPosition(0)
    {
        _enor = new SeqInFileEnumerator<std::string>(filename);
        _current = 0;
    }

    ~SeqInFileEnumeratorDays()
    {
        delete _enor;
    }

    void next()
    {
        while(_passIterations != 0)
        {
            _enor->next();
            _passIterations--;
        }

        if(!(_end = _currentPosition == _enor->current().size()))
        {
            _current = _enor->current()[_currentPosition];
            _currentPosition++;
        }
    }

    void first() override final
    {
        _enor->first();
        next();
    }

    char current() const override final
    {
        return _current;
    }

    bool end() const override final
    {
        return _end;
    }
};

#endif // CUSTOMPETKEEPERENUMERATORS_HPP
