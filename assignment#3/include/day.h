#ifndef DAY_H
#define DAY_H

class Fish;
class Bird;
class Dog;

// Day Interface
class Day
{
public:
    virtual Day* influence(Fish *p) = 0;
    virtual Day* influence(Bird *p) = 0;
    virtual Day* influence(Dog *p) = 0;
    virtual ~Day() {}
};

class GoodDay : public Day
{
public:
    static GoodDay* instance();
    Day* influence(Bird *p) override;
    Day* influence(Fish *p) override;
    Day* influence(Dog *p) override;
protected:
    GoodDay() {}
private:
    static GoodDay* _instance;
};


class BadDay : public Day
{
public:
    static BadDay* instance();
    Day* influence(Bird *p) override;
    Day* influence(Fish *p) override;
    Day* influence(Dog *p) override;
protected:
    BadDay() {}
private:
    static BadDay* _instance;
};

class NormalDay : public Day
{
public:
    static NormalDay* instance();
    Day* influence(Bird *p) override;
    Day* influence(Fish *p) override;
    Day* influence(Dog *p) override;
protected:
    NormalDay() {}
private:
    static NormalDay* _instance;
};


#endif // DAY_H
