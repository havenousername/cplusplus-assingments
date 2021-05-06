#ifndef SEQINFILEENUMERATOR_HPP
#define SEQINFILEENUMERATOR_HPP

#include "enumerator.hpp"
#include <fstream>
#include <typeinfo>
#include <sstream>

template<typename T>
class SeqInFileEnumerator: public Enumerator<T>
{
protected:
    std::ifstream _f;
    T _df;
    bool _end;
    std::stringstream _ss;


    static std::ifstream createFstream(const std::string& str)
    {
        std::ifstream f(str);
        if (f.fail()) throw OPEN_ERROR;
        return f;
    }

    bool read_next_not_empty()
    {
        std::string line;
        _ss.clear();
        while(getline(_f, line) && line.size() == 0);
        if(!(_f.fail())) _ss.str(line);
        return !_f.fail();
    };
public:
    enum Exceptions { OPEN_ERROR };
    SeqInFileEnumerator(const std::string& str)
    {
        _f = createFstream(str);
        _end = false;
    }

    void first() final override
    {
        _end = !read_next_not_empty();
        next();
    }

    void next() final override
    {
        _ss  >> _df;
        if (_ss.fail())
        {
            _end = !read_next_not_empty();
            _ss >> _df;
        }
    }

    bool end() const final override { return _end; }
    T current() const final override { return _df; }
};

template<>
inline  std::ifstream SeqInFileEnumerator<char>::createFstream(const std::string& str)
{
    std::ifstream f(str);
    if(f.fail()) throw OPEN_ERROR;
    f.unsetf(std::ios::skipws);
    return f;
}

#endif // SEQINFILEENUMERATOR_HPP
