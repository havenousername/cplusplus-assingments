#include "../include/day.h"
#include "../include/pet.h"

/* Good day class */
GoodDay* GoodDay::_instance = nullptr;
GoodDay* GoodDay::instance()
{
	if (_instance == nullptr)
	{
		_instance = new GoodDay();
	}
	return _instance;
}

Day* GoodDay::influence(Bird *p)
{
	p->changeLevel(2);
	return this;
}

Day* GoodDay::influence(Fish* p)
{
	p->changeLevel(1);
	return this;
}


Day* GoodDay::influence(Dog* p)
{
	p->changeLevel(3);
	return this;
}

/* End of Good day class */


/* Bad day class */
BadDay* BadDay::_instance = nullptr;
BadDay* BadDay::instance()
{
    if (_instance == nullptr)
    {
        _instance = new BadDay();
    }

    return _instance;
}

Day* BadDay::influence(Bird* p)
{
    p->changeLevel(-3);
    return this;
}

Day* BadDay::influence(Fish* p)
{
    p->changeLevel(-5);
    return this;
}

Day* BadDay::influence(Dog* p)
{
    p->changeLevel(-10);
    return  this;
}

/* End of Bad day class */
NormalDay* NormalDay::_instance = nullptr;
NormalDay* NormalDay::instance()
{
    if (_instance == nullptr)
    {
        _instance = new NormalDay();
    }

    return _instance;
}

Day* NormalDay::influence(Bird *p)
{
    p->changeLevel(-1);
    return this;
}

Day* NormalDay::influence(Fish *p)
{
    p->changeLevel(-3);
    return this;
}

Day* NormalDay::influence(Dog* p)
{
    p->changeLevel(0);
    return this;
}



