#include <iostream>
#include "custompetkeeperenumerators.hpp"



using std::cout;
using std::endl;

int main()
{
    SeqInFileEnumeratorPets enor = SeqInFileEnumeratorPets("test01.txt");

    int i = 0;
    for(enor.first(); !enor.end(); enor.next())
    {
        cout << enor.current().type() << " : " <<enor.current().exhalationLevel() << " : " << enor.current().name() << endl;
        i++;
    }

    SeqInFileEnumeratorDays e = SeqInFileEnumeratorDays("test01.txt", i);
    for (e.first(); !e.end(); e.next())
    {
        cout << e.current() << endl;
    }

    return 0;
}
