#ifndef ENUMS_HPP
#define ENUMS_HPP


enum RawPetType: char
{
    FISH = 'F',
    BIRD = 'B',
    DOG = 'D',
};

enum HealthRange: int
{
    EMPTY = 0,
    CRITICAL = 5,
    FULL = 100
};

enum RawDay: char
{
    GOOD_DAY = 'g',
    BAD_DAY = 'b',
    NORMAL_DAY = 'o'
};


#endif // ENUMS_HPP
