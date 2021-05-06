#ifndef ENUMERATOR_HPP
#define ENUMERATOR_HPP

template <typename T>
class Enumerator
{
public:
    virtual void first() = 0;
    virtual void next() = 0;
    virtual bool end() const = 0;
    virtual T current() const = 0;
    virtual ~Enumerator() {};
};

#endif // ENUMERATOR_HPP
